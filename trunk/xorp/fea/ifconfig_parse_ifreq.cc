// -*- c-basic-offset: 4; tab-width: 8; indent-tabs-mode: t -*-

// Copyright (c) 2001-2003 International Computer Science Institute
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software")
// to deal in the Software without restriction, subject to the conditions
// listed in the XORP LICENSE file. These conditions include: you must
// preserve this copyright notice, and you cannot mention the copyright
// holders in advertising related to the Software without their permission.
// The Software is provided WITHOUT ANY WARRANTY, EXPRESS OR IMPLIED. This
// notice is a summary of the XORP LICENSE file; the license in that file is
// legally binding.

#ident "$XORP: xorp/fea/ifconfig_parse_ifreq.cc,v 1.4 2003/05/21 05:32:50 pavlin Exp $"


#include "fea_module.h"
#include "libxorp/xorp.h"
#include "libxorp/xlog.h"
#include "libxorp/debug.h"

#include "libxorp/ether_compat.h"
#include "libxorp/ipvx.hh"

#ifdef HAVE_SYS_IOCTL_H
#include <sys/ioctl.h>
#endif
#include <net/if.h>
#ifdef HAVE_NET_IF_VAR_H
#include <net/if_var.h>
#endif
#ifdef HAVE_NET_IF_DL_H
#include <net/if_dl.h>
#endif
#ifdef HAVE_NET_IF_TYPES_H
#include <net/if_types.h>
#endif
#ifdef HAVE_NETINET6_IN6_VAR_H
#include <netinet6/in6_var.h>
#endif

#include "ifconfig.hh"
#include "ifconfig_get.hh"
#include "kernel_utils.hh"


//
// Parse information about network interface configuration change from
// the underlying system.
//
// The information to parse is in "struct ifreq" format
// (e.g., obtained by ioctl(SIOCGIFCONF) mechanism).
//

#ifndef HAVE_IOCTL_SIOCGIFCONF
bool
IfConfigGet::parse_buffer_ifreq(IfTree& , int ,
				const uint8_t* , size_t )
{
    return false
}

#else // HAVE_IOCTL_SIOCGIFCONF

bool
IfConfigGet::parse_buffer_ifreq(IfTree& it, int family,
				const uint8_t* buf, size_t buf_bytes)
{
    u_short if_index = 0;
    string if_name;
    const uint8_t *ptr;
    
    for (ptr = buf; ptr < buf + buf_bytes; ) {
	int len = 0;
	const struct ifreq	*ifreq = (const struct ifreq *)ptr;
	struct ifreq		ifrcopy;
#ifdef HAVE_SA_LEN
	len = MAX(sizeof(struct sockaddr), ifreq->ifr_addr.sa_len);
#else
	switch (ifreq->ifr_addr.sa_family) {
#ifdef HAVE_IPV6
	case AF_INET6:
	    len = sizeof(struct sockaddr_in6);
	    break;
#endif // HAVE_IPV6
	case AF_INET:
	default:
	    len = sizeof(struct sockaddr);
	    break;
	}
#endif // HAVE_SA_LEN
	len += sizeof(ifreq->ifr_name);
	len = MAX(len, (int)sizeof(struct ifreq));
	ptr += len;				// Point to the next entry
	
	//
	// Get the interface name
	//
	char tmp_if_name[IFNAMSIZ+1];
	strncpy(tmp_if_name, ifreq->ifr_name, sizeof(tmp_if_name));
#ifdef HOST_OS_SOLARIS
	char *cptr;
	if ( (cptr = strchr(tmp_if_name, ':')) != NULL) {
	    // Replace colon with null. Needed because in Solaris the
	    // interface name changes for aliases
	    *cptr = '\0';
	}
#endif // HOST_OS_SOLARIS
	if_name = string(tmp_if_name);
	
	//
	// Try to get the physical interface index
	//
	do {
	    if_index = 0;
	    
#ifdef HAVE_IF_NAMETOINDEX
	    // TODO: check whether for Solaris we have to use the
	    // original interface name instead (i.e., the one that has
	    // unique vif name per alias (see the ':' substitution
	    // above).
	    if_index = if_nametoindex(if_name.c_str());
	    if (if_index > 0)
		break;
#endif // HAVE_IF_NAMETOINDEX
	    
#ifdef SIOCGIFINDEX
	    {
		struct ifreq ifridx;
		
		memset(&ifridx, 0, sizeof(ifridx));
		strncpy(ifridx.ifr_name, if_name.c_str(),
			sizeof(ifridx.ifr_name));
		if (ioctl(sock(family), SIOCGIFINDEX, &ifridx) < 0) {
		    XLOG_ERROR("ioctl(SIOCGIFINDEX) for interface %s failed: %s",
			       if_name.c_str(), strerror(errno));
		    return false;
		}
		if_index = ifridx.ifr_ifindex;
	    }
	    if (if_index > 0)
		break;
#endif // SIOCGIFINDEX
	} while (false);
	if (if_index == 0) {
	    // TODO: what to do? Shall I assign my own pseudo-indexes?
	    XLOG_FATAL("Could not find index for interface %s", if_name.c_str());
	}
	
	//
	// Add the interface (if a new one)
	//
	ifc().map_ifindex(if_index, if_name);
	it.add_if(if_name);
	IfTreeInterface& fi = it.get_if(if_name)->second;
	
	//
	// Get the MAC address
	//
	// TODO: XXX: PAVPAVPAV: this won't work on Linux!!
#ifdef AF_LINK
	{
	    const sockaddr *sa = &ifreq->ifr_addr;
	    if (sa->sa_family == AF_LINK) {
		const sockaddr_dl* sdl = reinterpret_cast<const sockaddr_dl*>(sa);
		if (sdl->sdl_type == IFT_ETHER) {
		    if (sdl->sdl_alen == sizeof(ether_addr)) {
			ether_addr ea;
			memcpy(&ea, sdl->sdl_data + sdl->sdl_nlen,
			       sdl->sdl_alen);
			fi.set_mac(EtherMac(ea));
		    } else if (sdl->sdl_alen != 0) {
			XLOG_ERROR("Address size %d uncatered for interface %s",
				   sdl->sdl_alen, if_name.c_str());
		}
		}
	    }
	}
#endif // AF_LINK
	
	//
	// Get the MTU
	//
	int mtu = 0;
	memcpy(&ifrcopy, ifreq, sizeof(ifrcopy));
	if (ioctl(sock(family), SIOCGIFMTU, &ifrcopy) < 0) {
	    XLOG_ERROR("ioctl(SIOCGIFMTU) for interface %s failed: %s",
		       if_name.c_str(), strerror(errno));
	} else {
	    mtu = ifrcopy.ifr_mtu;
	    fi.set_mtu(mtu);
	}
	
	//
	// Get the flags
	//
	int flags = 0;
	memcpy(&ifrcopy, ifreq, sizeof(ifrcopy));
	if (ioctl(sock(family), SIOCGIFFLAGS, &ifrcopy) < 0) {
	    XLOG_ERROR("ioctl(SIOCGIFFLAGS) for interface %s failed: %s",
		       if_name.c_str(), strerror(errno));
	} else {
	    flags = ifrcopy.ifr_flags;
	}
	fi.set_enabled(flags & IFF_UP);
	
	debug_msg("%s flags %s\n",
		  if_name.c_str(), IfConfigGet::iff_flags(flags).c_str());
	// XXX: vifname == ifname on this platform
	fi.add_vif(if_name);
	IfTreeVif& fv = fi.get_vif(if_name)->second;
	fv.set_pif_index(if_index);
	fv.set_enabled(fi.enabled() && (flags & IFF_UP));
	fv.set_broadcast(flags & IFF_BROADCAST);
	fv.set_loopback(flags & IFF_LOOPBACK);
	fv.set_point_to_point(flags & IFF_POINTOPOINT);
	fv.set_multicast(flags & IFF_MULTICAST);
	
	//
	// Get the interface addresses for the same address family
	//
	if (ifreq->ifr_addr.sa_family != family)
	    continue;
	
	//
	// Get the IP address, netmask, broadcast address, P2P destination
	//
        // The default values
	IPvX lcl_addr = IPvX::ZERO(family);
	IPvX subnet_mask = IPvX::ZERO(family);
	IPvX broadcast_addr = IPvX::ZERO(family);
	IPvX peer_addr = IPvX::ZERO(family);
	
	// Get the IP address
	lcl_addr.copy_in(ifreq->ifr_addr);
	lcl_addr = kernel_ipvx_adjust(lcl_addr);
	
	// Get the netmask
	switch (family) {
	case AF_INET:
#ifdef SIOCGIFNETMASK
	    memcpy(&ifrcopy, ifreq, sizeof(ifrcopy));
	    if (ioctl(sock(family), SIOCGIFNETMASK, &ifrcopy) < 0) {
		if (! fv.point_to_point()) {
		    XLOG_ERROR("ioctl(SIOCGIFNETMASK) failed: %s",
			       strerror(errno));
		}
	    } else {
		// The interface is configured
		// XXX: SIOCGIFNETMASK doesn't return proper family
		ifrcopy.ifr_addr.sa_family = family;
		subnet_mask.copy_in(ifrcopy.ifr_addr);
	    }
#endif // SIOCGIFNETMASK
	    break;
#ifdef HAVE_IPV6
	case AF_INET6:
#ifdef SIOCGIFNETMASK_IN6
	{
	    const struct in6_ifreq *ifreq6 = (const struct in6_ifreq *)ifreq;
	    struct in6_ifreq	ifrcopy6;
	    
	    memcpy(&ifrcopy6, ifreq6, sizeof(ifrcopy6));
	    if (ioctl(sock(family), SIOCGIFNETMASK_IN6, &ifrcopy6) < 0) {
		if (! fv.point_to_point()) {
		    XLOG_ERROR("ioctl(SIOCGIFNETMASK_IN6) failed: %s",
			       strerror(errno));
		}
	    } else {
		// The interface is configured
		// XXX: SIOCGIFNETMASK_IN6 doesn't return proper family
		ifrcopy6.ifr_ifru.ifru_addr.sin6_family = family;
		subnet_mask.copy_in(ifrcopy6.ifr_ifru.ifru_addr);
	    }
	}
#endif // SIOCGIFNETMASK_IN6
	break;
#endif // HAVE_IPV6
	default:
	    XLOG_UNREACHABLE();
	    break;
	}
	
	// Get the broadcast address	
	if (fv.broadcast()) {
	    switch (family) {
	    case AF_INET:
#ifdef SIOCGIFBRDADDR
		memcpy(&ifrcopy, ifreq, sizeof(ifrcopy));
		if (ioctl(sock(family), SIOCGIFBRDADDR, &ifrcopy) < 0) {
		    XLOG_ERROR("ioctl(SIOCGIFBRADDR) failed: %s",
			       strerror(errno));
		} else {
		    // XXX: in case it doesn't return proper family
		    ifrcopy.ifr_broadaddr.sa_family = family;
		    broadcast_addr.copy_in(ifrcopy.ifr_addr);
		}
#endif // SIOCGIFBRDADDR
		break;
#ifdef HAVE_IPV6
	    case AF_INET6:
		break;	// IPv6 doesn't have the idea of broadcast
#endif // HAVE_IPV6
	    default:
		XLOG_UNREACHABLE();
		break;
	    }
	}
	
	// Get the p2p address
	if (fv.point_to_point()) {
	    switch (family) {
	    case AF_INET:
#ifdef SIOCGIFDSTADDR
		memcpy(&ifrcopy, ifreq, sizeof(ifrcopy));
		if (ioctl(sock(family), SIOCGIFDSTADDR, &ifrcopy) < 0) {
		    // Probably the p2p address is not configured
		} else {
		    // The p2p address is configured
		    // XXX: in case it doesn't return proper family
		    ifrcopy.ifr_dstaddr.sa_family = family;
		    peer_addr.copy_in(ifrcopy.ifr_dstaddr);
		}
#endif // SIOCGIFDSTADDR
		break;
#ifdef HAVE_IPV6
	    case AF_INET6:
#ifdef SIOCGIFDSTADDR_IN6
	    {
		const struct in6_ifreq *ifreq6 = (const struct in6_ifreq *)ifreq;
		struct in6_ifreq	ifrcopy6;
		
		memcpy(&ifrcopy6, ifreq6, sizeof(ifrcopy6));
		if (ioctl(sock(family), SIOCGIFDSTADDR_IN6, &ifrcopy6) < 0) {
		    // Probably the p2p address is not configured
		} else {
		    // The p2p address is configured
		    // Just in case it doesn't return proper family
		    ifrcopy6.ifr_ifru.ifru_dstaddr.sin6_family = family;
		    peer_addr.copy_in(ifrcopy6.ifr_ifru.ifru_dstaddr);
		}
	    }
#endif // SIOCGIFDSTADDR_IN6
	    break;
#endif // HAVE_IPV6
	    default:
		XLOG_UNREACHABLE();
		break;
	    }
	}
	
	// Add the address
	switch (family) {
	case AF_INET:
	{
	    fv.add_addr(lcl_addr.get_ipv4());
	    IfTreeAddr4& fa = fv.get_addr(lcl_addr.get_ipv4())->second;
	    fa.set_enabled(fv.enabled() && (flags & IFF_UP));
	    fa.set_broadcast(fv.broadcast() && (flags & IFF_BROADCAST));
	    fa.set_loopback(fv.loopback() && (flags & IFF_LOOPBACK));
	    fa.set_point_to_point(fv.point_to_point() && (flags & IFF_POINTOPOINT));
	    fa.set_multicast(fv.multicast() && (flags & IFF_MULTICAST));
	    
	    fa.set_prefix(subnet_mask.prefix_length());
	    if (fa.broadcast())
		fa.set_bcast(broadcast_addr.get_ipv4());
	    if (fa.point_to_point())
		fa.set_endpoint(peer_addr.get_ipv4());
	    break;
	}
#ifdef HAVE_IPV6
	case AF_INET6:
	{
	    fv.add_addr(lcl_addr.get_ipv6());
	    IfTreeAddr6& fa = fv.get_addr(lcl_addr.get_ipv6())->second;
	    fa.set_enabled(fv.enabled() && (flags & IFF_UP));
	    fa.set_loopback(fv.loopback() && (flags & IFF_LOOPBACK));
	    fa.set_point_to_point(fv.point_to_point() && (flags & IFF_POINTOPOINT));
	    fa.set_multicast(fv.multicast() && (flags & IFF_MULTICAST));
	    
	    fa.set_prefix(subnet_mask.prefix_length());
	    if (fa.point_to_point())
		fa.set_endpoint(peer_addr.get_ipv6());
	    break;
	}
#endif // HAVE_IPV6
	default:
	    XLOG_UNREACHABLE();
	    break;
	}
    }
    
    return true;
}

#endif // HAVE_IOCTL_SIOCGIFCONF
