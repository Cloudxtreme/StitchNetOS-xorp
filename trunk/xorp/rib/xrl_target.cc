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

#ident "$XORP: xorp/rib/xrl_target.cc,v 1.33 2004/05/06 23:07:47 hodson Exp $"

// #define DEBUG_LOGGING
// #define DEBUG_PRINT_FUNCTION_NAME

#include "rib_module.h"

#include "libxorp/xorp.h"
#include "libxorp/status_codes.h"

#include "xrl_target.hh"
#include "rt_tab_register.hh"
#include "rib_manager.hh"
#include "vifmanager.hh"


XrlCmdError
XrlRibTarget::common_0_1_get_target_name(string& name)
{
    name = XrlRibTargetBase::name();
    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::common_0_1_get_version(string& v)
{
    v = string(version());
    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::common_0_1_get_status(
    // Output values,
    uint32_t& status,
    string&	reason)
{
    status = _rib_manager->status(reason);
    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::common_0_1_shutdown()
{
    _rib_manager->stop();
    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::rib_0_1_enable_rib()
{
    _rib_manager->enable();
    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::rib_0_1_disable_rib()
{
    _rib_manager->disable();
    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::rib_0_1_start_rib()
{
    if (_rib_manager->start() != XORP_OK) {
	return XrlCmdError::COMMAND_FAILED("Failed to start rib manager");
    }
    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::rib_0_1_stop_rib()
{
    if (_rib_manager->stop() != XORP_OK) {
	return XrlCmdError::COMMAND_FAILED("Failed to stop rib manager");
    }
    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::rib_0_1_add_rib_client4(
    // Input values,
    const string&	target_name,
    const bool&		unicast,
    const bool&		multicast)
{
    if (_rib_manager->add_rib_client(target_name, AF_INET, unicast,
				     multicast) != XORP_OK) {
	return XrlCmdError::COMMAND_FAILED("Failed to add rib client");
    }
    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::rib_0_1_add_rib_client6(
    // Input values,
    const string&	target_name,
    const bool&		unicast,
    const bool&		multicast)
{
#ifndef HAVE_IPV6
    UNUSED(target_name);
    UNUSED(unicast);
    UNUSED(multicast);
    return XrlCmdError::COMMAND_FAILED("IPv6 not supported.");
#else
    if (_rib_manager->add_rib_client(target_name, AF_INET6, unicast,
				     multicast) != XORP_OK) {
	return XrlCmdError::COMMAND_FAILED("Failed to add rib client");
    }
    return XrlCmdError::OKAY();
#endif // HAVE_IPV6
}

XrlCmdError
XrlRibTarget::rib_0_1_delete_rib_client4(
    // Input values,
    const string&	target_name,
    const bool&		unicast,
    const bool&		multicast)
{
    if (_rib_manager->delete_rib_client(target_name, AF_INET, unicast,
					multicast) != XORP_OK) {
	return XrlCmdError::COMMAND_FAILED("Failed to delete rib client");
    }
    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::rib_0_1_delete_rib_client6(
    // Input values,
    const string&	target_name,
    const bool&		unicast,
    const bool&		multicast)
{
#ifndef HAVE_IPV6
    UNUSED(target_name);
    UNUSED(unicast);
    UNUSED(multicast);
    return XrlCmdError::COMMAND_FAILED("IPv6 not supported");
#else
    if (_rib_manager->delete_rib_client(target_name, AF_INET6, unicast,
					multicast) != XORP_OK) {
	return XrlCmdError::COMMAND_FAILED("Failed to delete rib client");
    }
    return XrlCmdError::OKAY();
#endif // HAVE_IPV6
}

XrlCmdError
XrlRibTarget::rib_0_1_enable_rib_client4(
    // Input values,
    const string&	target_name,
    const bool&		unicast,
    const bool&		multicast)
{
    if (_rib_manager->enable_rib_client(target_name, AF_INET, unicast,
					multicast) != XORP_OK) {
	return XrlCmdError::COMMAND_FAILED("Failed to enable rib client");
    }
    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::rib_0_1_enable_rib_client6(
    // Input values,
    const string&	target_name,
    const bool&		unicast,
    const bool&		multicast)
{
#ifndef HAVE_IPV6
    UNUSED(target_name);
    UNUSED(unicast);
    UNUSED(multicast);
    return XrlCmdError::COMMAND_FAILED("IPv6 not supported");
#else
    if (_rib_manager->enable_rib_client(target_name, AF_INET6, unicast,
					multicast) != XORP_OK) {
	return XrlCmdError::COMMAND_FAILED("Failed to enable rib client");
    }
    return XrlCmdError::OKAY();
#endif // HAVE_IPV6
}

XrlCmdError
XrlRibTarget::rib_0_1_disable_rib_client4(
    // Input values,
    const string&	target_name,
    const bool&		unicast,
    const bool&		multicast)
{
    if (_rib_manager->disable_rib_client(target_name, AF_INET, unicast,
					 multicast) != XORP_OK) {
	return XrlCmdError::COMMAND_FAILED("Failed to disable rib client");
    }
    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::rib_0_1_disable_rib_client6(
    // Input values,
    const string&	target_name,
    const bool&		unicast,
    const bool&		multicast)
{
#ifndef HAVE_IPV6
    UNUSED(target_name);
    UNUSED(unicast);
    UNUSED(multicast);
    return XrlCmdError::COMMAND_FAILED("IPv6 not supported");
#else
    if (_rib_manager->disable_rib_client(target_name, AF_INET6, unicast,
					 multicast) != XORP_OK) {
	return XrlCmdError::COMMAND_FAILED("Failed to disable rib client");
    }
    return XrlCmdError::OKAY();
#endif // HAVE_IPV6
}

XrlCmdError
XrlRibTarget::rib_0_1_no_fea()
{
    _rib_manager->no_fea();
    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::rib_0_1_make_errors_fatal()
{
    _rib_manager->make_errors_fatal();
    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::rib_0_1_add_igp_table4(const string&	protocol,
				     const string&	target_class,
				     const string&	target_instance,
				     const bool&	unicast,
				     const bool&	multicast)
{
    if (unicast &&
	_urib4.add_igp_table(protocol, target_class, target_instance)
	!= XORP_OK) {
	string err = c_format("Could not add unicast IPv4 igp table \"%s\"",
			      protocol.c_str());
	return XrlCmdError::COMMAND_FAILED(err);
    }

    if (multicast &&
	_mrib4.add_igp_table(protocol, target_class, target_instance)
	!= XORP_OK) {
	string err = c_format("Could not add multicast IPv4 igp table \"%s\"",
			      protocol.c_str());
	return XrlCmdError::COMMAND_FAILED(err);
    }

    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::rib_0_1_add_igp_table6(const string&	protocol,
				     const string&	target_class,
				     const string&	target_instance,
				     const bool&	unicast,
				     const bool&	multicast)
{
    if (unicast &&
	_urib6.add_igp_table(protocol, target_class, target_instance)
	!= XORP_OK) {
	string err = c_format("Could not add unicast IPv6 igp table \"%s\"",
			      protocol.c_str());
	return XrlCmdError::COMMAND_FAILED(err);
    }

    if (multicast &&
	_mrib6.add_igp_table(protocol, target_class, target_instance)
	!= XORP_OK) {
	string err = c_format("Could not add multicast IPv6 igp table \"%s\"",
			      protocol.c_str());
	return XrlCmdError::COMMAND_FAILED(err);
    }

    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::rib_0_1_delete_igp_table4(const string&	protocol,
				     const string&	target_class,
					const string&	target_instance,
					const bool&	unicast,
					const bool&	multicast)
{
    if (unicast &&
	_urib4.delete_igp_table(protocol, target_class, target_instance)
	!= XORP_OK) {
	string err = c_format("Could not delete unicast IPv4 igp table \"%s\"",
			      protocol.c_str());
	return XrlCmdError::COMMAND_FAILED(err);
    }

    if (multicast &&
	_mrib4.delete_igp_table(protocol, target_class, target_instance)
	!= XORP_OK) {
	string err = c_format("Could not delete multicast IPv4 igp table "
			      "\"%s\"", protocol.c_str());
	return XrlCmdError::COMMAND_FAILED(err);
    }

    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::rib_0_1_delete_igp_table6(const string&	protocol,
					const string&	target_class,
					const string&	target_instance,
					const bool&	unicast,
					const bool&	multicast)
{
    if (unicast &&
	_urib6.delete_igp_table(protocol, target_class, target_instance)
	!= XORP_OK) {
	string err = c_format("Could not delete unicast IPv6 igp table \"%s\"",
			      protocol.c_str());
	return XrlCmdError::COMMAND_FAILED(err);
    }

    if (multicast &&
	_mrib6.delete_igp_table(protocol, target_class, target_instance)
	!= XORP_OK) {
	string err = c_format("Could not delete multicast IPv6 igp table \"%s\"",
			      protocol.c_str());
	return XrlCmdError::COMMAND_FAILED(err);
    }

    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::rib_0_1_add_egp_table4(const string&	protocol,
				     const string&	target_class,
				     const string&	target_instance,
				     const bool&	unicast,
				     const bool&	multicast)
{
    if (unicast &&
	_urib4.add_egp_table(protocol, target_class, target_instance)
	!= XORP_OK) {
	string err = c_format("Could not add unicast IPv4 egp table \"%s\"",
			      protocol.c_str());
	return XrlCmdError::COMMAND_FAILED(err);
    }

    if (multicast &&
	_mrib4.add_egp_table(protocol, target_class, target_instance)
	!= XORP_OK) {
	string err = c_format("Could not add multicast IPv4 egp table \"%s\"",
			      protocol.c_str());
	return XrlCmdError::COMMAND_FAILED(err);
    }

    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::rib_0_1_add_egp_table6(const string&	protocol,
				     const string&	target_class,
				     const string&	target_instance,
				     const bool&	unicast,
				     const bool&	multicast)
{
    if (unicast &&
	_urib6.add_egp_table(protocol, target_class, target_instance)
	!= XORP_OK) {
	string err = c_format("Could not add unicast IPv6 egp table \"%s\"",
			      protocol.c_str());
	return XrlCmdError::COMMAND_FAILED(err);
    }

    if (multicast &&
	_mrib6.add_egp_table(protocol, target_class, target_instance)
	!= XORP_OK) {
	string err = c_format("Could not add multicast IPv6 egp table \"%s\"",
			      protocol.c_str());
	return XrlCmdError::COMMAND_FAILED(err);
    }

    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::rib_0_1_delete_egp_table4(const string&	protocol,
					const string&	target_class,
					const string&	target_instance,
					const bool&	unicast,
					const bool&	multicast)
{
    if (unicast &&
	_urib4.delete_egp_table(protocol, target_class, target_instance)
	!= XORP_OK) {
	string err = c_format("Could not delete unicast IPv4 egp table \"%s\"",
			      protocol.c_str());
	return XrlCmdError::COMMAND_FAILED(err);
    }

    if (multicast &&
	_mrib4.delete_egp_table(protocol, target_class, target_instance)
	!= XORP_OK) {
	string err = c_format("Could not delete multicast IPv4 egp table "
			      "\"%s\"", protocol.c_str());
	return XrlCmdError::COMMAND_FAILED(err);
    }

    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::rib_0_1_delete_egp_table6(const string&	protocol,
					const string&	target_class,
					const string&	target_instance,
					const bool&	unicast,
					const bool&	multicast)
{
    if (unicast &&
	_urib6.delete_egp_table(protocol, target_class, target_instance)
	!= XORP_OK) {
	string err = c_format("Could not delete unicast IPv6 egp table \"%s\"",
			      protocol.c_str());
	return XrlCmdError::COMMAND_FAILED(err);
    }

    if (multicast &&
	_mrib6.delete_egp_table(protocol, target_class, target_instance)
	!= XORP_OK) {
	string err = c_format("Could not delete multicast IPv6 egp table \"%s\"",
			      protocol.c_str());
	return XrlCmdError::COMMAND_FAILED(err);
    }

    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::rib_0_1_add_route4(const string&	protocol,
				 const bool&	unicast,
				 const bool&	multicast,
				 const IPv4Net&	network,
				 const IPv4&	nexthop,
				 const uint32_t& metric)
{
    debug_msg("#### XRL: ADD ROUTE net %s, nexthop: %s\n",
	      network.str().c_str(), nexthop.str().c_str());
    if (unicast &&
	_urib4.add_route(protocol, network, nexthop, "", "", metric)
	!= XORP_OK) {
	string err = "Could not add IPv4 route to unicast RIB";
	return XrlCmdError::COMMAND_FAILED(err);
    }

    if (multicast &&
	_mrib4.add_route(protocol, network, nexthop, "", "", metric)
	!= XORP_OK) {
	string err = "Could not add IPv4 route to multicast RIB";
	return XrlCmdError::COMMAND_FAILED(err);
    }

    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::rib_0_1_add_route6(const string&	protocol,
				 const bool&	unicast,
				 const bool&	multicast,
				 const IPv6Net&	network,
				 const IPv6&	nexthop,
				 const uint32_t& metric)
{
    if (unicast &&
	_urib6.add_route(protocol, network, nexthop, "", "", metric)
	!= XORP_OK) {
	string err = "Could not add IPv6 route to unicast RIB";
	return XrlCmdError::COMMAND_FAILED(err);
    }

    if (multicast &&
	_mrib6.add_route(protocol, network, nexthop, "", "", metric)
	!= XORP_OK) {
	string err = "Could not add IPv6 route to multicast RIB";
	return XrlCmdError::COMMAND_FAILED(err);
    }

    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::rib_0_1_replace_route4(const string&	protocol,
				     const bool&	unicast,
				     const bool&	multicast,
				     const IPv4Net&	network,
				     const IPv4&	nexthop,
				     const uint32_t&	metric)
{
    if (unicast &&
	_urib4.replace_route(protocol, network, nexthop, "", "", metric)
	!= XORP_OK) {
	string err = "Could not replace IPv4 route in unicast RIB";
	return XrlCmdError::COMMAND_FAILED(err);
    }

    if (multicast &&
	_mrib4.replace_route(protocol, network, nexthop, "", "", metric)
	!= XORP_OK) {
	string err = "Could not replace IPv4 route in multicast RIB";
	return XrlCmdError::COMMAND_FAILED(err);
    }

    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::rib_0_1_replace_route6(const string&	protocol,
				     const bool&	unicast,
				     const bool&	multicast,
				     const IPv6Net&	network,
				     const IPv6&	nexthop,
				     const uint32_t&	metric)
{
    if (unicast &&
	_urib6.replace_route(protocol, network, nexthop, "", "", metric)
	!= XORP_OK) {
	string err = "Could not replace IPv6 route in unicast RIB";
	return XrlCmdError::COMMAND_FAILED(err);
    }

    if (multicast &&
	_mrib6.replace_route(protocol, network, nexthop, "", "", metric)
	!= XORP_OK) {
	string err = "Could not add IPv6 route in multicast RIB";
	return XrlCmdError::COMMAND_FAILED(err);
    }

    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::rib_0_1_delete_route4(const string&	protocol,
				    const bool&		unicast,
				    const bool&		multicast,
				    const IPv4Net&	network)
{
    debug_msg("#### XRL: DELETE ROUTE net %s\n",
	      network.str().c_str());
    if (unicast && _urib4.delete_route(protocol, network) != XORP_OK) {
	string err = "Could not delete IPv4 route from unicast RIB";
	return XrlCmdError::COMMAND_FAILED(err);
    }

    if (multicast && _mrib4.delete_route(protocol, network) != XORP_OK) {
	string err = "Could not delete IPv4 route from multicast RIB";
	return XrlCmdError::COMMAND_FAILED(err);
    }

    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::rib_0_1_delete_route6(const string&	protocol,
				    const bool&		unicast,
				    const bool&		multicast,
				    const IPv6Net&	network)
{
    if (unicast && _urib6.delete_route(protocol, network) != XORP_OK) {
	string err = "Could not delete IPv6 route from unicast RIB";
	return XrlCmdError::COMMAND_FAILED(err);
    }

    if (multicast && _mrib6.delete_route(protocol, network) != XORP_OK) {
	string err = "Could not delete IPv6 route from multicast RIB";
	return XrlCmdError::COMMAND_FAILED(err);
    }

    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::rib_0_1_add_interface_route4(const string&	protocol,
					   const bool&		unicast,
					   const bool&		multicast,
					   const IPv4Net&	network,
					   const IPv4&		nexthop,
					   const string&	ifname,
					   const string&	vifname,
					   const uint32_t&	metric)
{
    debug_msg("#### XRL: ADD INTERFACE ROUTE net %s, nexthop: %s "
	      "ifname: %s vifname: %s\n",
	      network.str().c_str(), nexthop.str().c_str(),
	      ifname.c_str(), vifname.c_str());
    if (unicast &&
	_urib4.add_route(protocol, network, nexthop, ifname, vifname, metric)
	!= XORP_OK) {
	string err = "Could not add IPv4 interface route to unicast RIB";
	return XrlCmdError::COMMAND_FAILED(err);
    }

    if (multicast &&
	_mrib4.add_route(protocol, network, nexthop, ifname, vifname, metric)
	!= XORP_OK) {
	string err = "Could not add IPv4 interface route to multicast RIB";
	return XrlCmdError::COMMAND_FAILED(err);
    }

    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::rib_0_1_add_interface_route6(const string&	protocol,
					   const bool&		unicast,
					   const bool&		multicast,
					   const IPv6Net&	network,
					   const IPv6&		nexthop,
					   const string&	ifname,
					   const string&	vifname,
					   const uint32_t&	metric)
{
    debug_msg("#### XRL: ADD INTERFACE ROUTE net %s, nexthop: %s "
	      "ifname: %s vifname: %s\n",
	      network.str().c_str(), nexthop.str().c_str(),
	      ifname.c_str(), vifname.c_str());
    if (unicast &&
	_urib6.add_route(protocol, network, nexthop, ifname, vifname, metric)
	!= XORP_OK) {
	string err = "Could not add IPv6 interface route to unicast RIB";
	return XrlCmdError::COMMAND_FAILED(err);
    }

    if (multicast &&
	_mrib6.add_route(protocol, network, nexthop, ifname, vifname, metric)
	!= XORP_OK) {
	string err = "Could not add IPv6 interface route to multicast RIB";
	return XrlCmdError::COMMAND_FAILED(err);
    }

    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::rib_0_1_replace_interface_route4(const string&	protocol,
					       const bool&	unicast,
					       const bool&	multicast,
					       const IPv4Net&	network,
					       const IPv4&	nexthop,
					       const string&	ifname,
					       const string&	vifname,
					       const uint32_t&	metric)
{
    if (unicast &&
	_urib4.replace_route(protocol, network, nexthop, ifname, vifname,
			     metric)
	!= XORP_OK) {
	string err = "Could not replace IPv4 interface route in unicast RIB";
	return XrlCmdError::COMMAND_FAILED(err);
    }

    if (multicast &&
	_mrib4.replace_route(protocol, network, nexthop, ifname, vifname,
			     metric)
	!= XORP_OK) {
	string err = "Could not replace IPv4 interface route in multicast RIB";
	return XrlCmdError::COMMAND_FAILED(err);
    }

    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::rib_0_1_replace_interface_route6(const string&	protocol,
					       const bool&	unicast,
					       const bool&	multicast,
					       const IPv6Net&	network,
					       const IPv6&	nexthop,
					       const string&	ifname,
					       const string&	vifname,
					       const uint32_t&	metric)
{
    if (unicast &&
	_urib6.replace_route(protocol, network, nexthop, ifname, vifname,
			     metric)
	!= XORP_OK) {
	string err = "Could not replace IPv6 interface route in unicast RIB";
	return XrlCmdError::COMMAND_FAILED(err);
    }

    if (multicast &&
	_mrib6.replace_route(protocol, network, nexthop, ifname, vifname,
			     metric)
	!= XORP_OK) {
	string err = "Could not replace IPv6 interface route in multicast RIB";
	return XrlCmdError::COMMAND_FAILED(err);
    }

    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::rib_0_1_lookup_route4(// Input values,
				    const IPv4&	addr,
				    const bool&	unicast,
				    const bool&	multicast,
				    // Output values,
				    IPv4& nexthop)
{
    // if unicast and multicast then fail, can only look one place at time
    if (unicast == multicast) {
	nexthop = IPv4::ZERO();
    } else if (unicast) {
	nexthop = _urib4.lookup_route(addr);
    } else if (multicast) {
	nexthop = _mrib4.lookup_route(addr);
    }
    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::rib_0_1_lookup_route6(// Input values,
				    const IPv6&	addr,
				    const bool&	unicast,
				    const bool&	multicast,
				    // Output values,
				    IPv6& nexthop)
{
    // Must look in exactly one RIB
    if (unicast == multicast) {
	nexthop = IPv6::ZERO();
    } else if (unicast) {
	nexthop = _urib6.lookup_route(addr);
    } else if (multicast) {
	nexthop = _mrib6.lookup_route(addr);
    }
    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::rib_0_1_new_vif(const string& name)
{
    //
    // One vif per RIB or one shared VifStore ? Latter as no guarantee that
    // all vifs have valid IPv4/IPv6/Unicast/Multicast meaning
    //

    Vif v(name);

    // XXX probably want something more selective (eg rib selector)
    if (_urib4.new_vif(name, v) != XORP_OK) {
	string err = c_format("Failed to add vif \"%s\" to unicast IPv4 rib",
			      name.c_str());
	return XrlCmdError::COMMAND_FAILED(err);
    }

    if (_mrib4.new_vif(name, v) != XORP_OK) {
	string err = c_format("Failed to add vif \"%s\" to multicast IPv4 rib",
			      name.c_str());
	return XrlCmdError::COMMAND_FAILED(err);
    }

    if (_urib6.new_vif(name, v) != XORP_OK) {
	string err = c_format("Failed to add vif \"%s\" to unicast IPv6 rib",
			      name.c_str());
	return XrlCmdError::COMMAND_FAILED(err);
    }

    if (_mrib6.new_vif(name, v) != XORP_OK) {
	string err = c_format("Failed to add vif \"%s\" to multicast IPv6 rib",
			      name.c_str());
	return XrlCmdError::COMMAND_FAILED(err);
    }

    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::rib_0_1_add_vif_addr4(const string&	name,
				    const IPv4&		addr,
				    const IPv4Net&	subnet)
{
    if (_urib4.add_vif_address(name, addr, subnet) != XORP_OK) {
	string err = "Failed to add IPv4 Vif address to unicast RIB";
	return XrlCmdError::COMMAND_FAILED(err);
    }

    if (_mrib4.add_vif_address(name, addr, subnet) != XORP_OK) {
	string err = "Failed to add IPv4 Vif address to multicast RIB";
	return XrlCmdError::COMMAND_FAILED(err);
    }

    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::rib_0_1_add_vif_addr6(const string&	name,
				    const IPv6&		addr,
				    const IPv6Net&	subnet)
{
    if (_urib6.add_vif_address(name, addr, subnet) != XORP_OK) {
	string err = "Failed to add IPv6 Vif address to unicast RIB";
	return XrlCmdError::COMMAND_FAILED(err);
    }

    if (_mrib6.add_vif_address(name, addr, subnet) != XORP_OK) {
	string err = "Failed to add IPv6 Vif address to multicast RIB";
	return XrlCmdError::COMMAND_FAILED(err);
    }

    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::rib_0_1_redist_enable4(const string&	target_name,
				     const string&	from,
				     const bool&	ucast,
				     const bool&	mcast,
				     const string&	cookie)
{
    if (_rib_manager->add_redist_xrl_output4(target_name, from, ucast, mcast,
					     cookie, false) != XORP_OK) {
	string err = c_format("Failed to enable route redistribution from "
			      "protocol \"%s\" to XRL target \"%s\"",
			      from.c_str(), target_name.c_str());
	return XrlCmdError::COMMAND_FAILED(err);
    }
    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::rib_0_1_redist_enable6(const string&	target_name,
				     const string&	from,
				     const bool&	ucast,
				     const bool&	mcast,
				     const string&	cookie)
{
    if (_rib_manager->add_redist_xrl_output6(target_name, from, ucast, mcast,
					     cookie, false) != XORP_OK) {
	string err = c_format("Failed to enable route redistribution from "
			      "protocol \"%s\" to XRL target \"%s\"",
			      from.c_str(), target_name.c_str());
	return XrlCmdError::COMMAND_FAILED(err);
    }
    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::rib_0_1_redist_disable4(const string&	target_name,
				      const string&	from,
				      const bool&	ucast,
				      const bool&	mcast,
				      const string&	cookie)
{
    if (_rib_manager->delete_redist_xrl_output4(target_name, from,
						ucast, mcast,
						cookie, false) != XORP_OK) {
	string err = c_format("Failed to disable route redistribution from "
			      "protocol \"%s\" to XRL target \"%s\"",
			      from.c_str(), target_name.c_str());
	return XrlCmdError::COMMAND_FAILED(err);
    }
    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::rib_0_1_redist_disable6(const string&	target_name,
				      const string&	from,
				      const bool&	ucast,
				      const bool&	mcast,
				      const string&	cookie)
{
    if (_rib_manager->delete_redist_xrl_output6(target_name, from,
						ucast, mcast,
						cookie, false) != XORP_OK) {
	string err = c_format("Failed to disable route redistribution from "
			      "protocol \"%s\" to XRL target \"%s\"",
			      from.c_str(), target_name.c_str());
	return XrlCmdError::COMMAND_FAILED(err);
    }
    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::rib_0_1_redist_transaction_enable4(const string&	target_name,
						 const string&	from,
						 const bool&	ucast,
						 const bool&	mcast,
						 const string&	cookie)
{
    if (_rib_manager->add_redist_xrl_output4(target_name, from, ucast, mcast,
					     cookie, true) != XORP_OK) {
	string err = c_format("Failed to enable transaction-based "
			      "route redistribution from "
			      "protocol \"%s\" to XRL target \"%s\"",
			      from.c_str(), target_name.c_str());
	return XrlCmdError::COMMAND_FAILED(err);
    }
    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::rib_0_1_redist_transaction_enable6(const string&	target_name,
						 const string&	from,
						 const bool&	ucast,
						 const bool&	mcast,
						 const string&	cookie)
{
    if (_rib_manager->add_redist_xrl_output6(target_name, from, ucast, mcast,
					     cookie, true) != XORP_OK) {
	string err = c_format("Failed to enable transaction-based "
			      "route redistribution from "
			      "protocol \"%s\" to XRL target \"%s\"",
			      from.c_str(), target_name.c_str());
	return XrlCmdError::COMMAND_FAILED(err);
    }
    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::rib_0_1_redist_transaction_disable4(const string&	target_name,
						  const string&	from,
						  const bool&	ucast,
						  const bool&	mcast,
						  const string&	cookie)
{
    if (_rib_manager->delete_redist_xrl_output4(target_name, from,
						ucast, mcast,
						cookie, true) != XORP_OK) {
	string err = c_format("Failed to disable transaction-based "
			      "route redistribution from "
			      "protocol \"%s\" to XRL target \"%s\"",
			      from.c_str(), target_name.c_str());
	return XrlCmdError::COMMAND_FAILED(err);
    }
    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::rib_0_1_redist_transaction_disable6(const string&	target_name,
						  const string&	from,
						  const bool&	ucast,
						  const bool&	mcast,
						  const string&	cookie)
{
    if (_rib_manager->delete_redist_xrl_output6(target_name, from,
						ucast, mcast,
						cookie, true) != XORP_OK) {
	string err = c_format("Failed to disable transaction-based "
			      "route redistribution from "
			      "protocol \"%s\" to XRL target \"%s\"",
			      from.c_str(), target_name.c_str());
	return XrlCmdError::COMMAND_FAILED(err);
    }
    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::rib_0_1_register_interest4(// Input values,
					 const string& target,
					 const IPv4& addr,
					 // Output values,
					 bool& resolves,
					 IPv4&	base_addr,
					 uint32_t& prefix_len,
					 uint32_t& real_prefix_len,
					 IPv4&	nexthop,
					 uint32_t& metric)
{
    debug_msg("#### XRL: REGISTER INTEREST addr %s\n",
	   addr.str().c_str());
    RouteRegister<IPv4>* rt_reg = _urib4.route_register(addr, target);
    if (rt_reg->route() == NULL) {
	base_addr = rt_reg->valid_subnet().masked_addr();
	prefix_len = real_prefix_len = rt_reg->valid_subnet().prefix_len();
	resolves = false;
	debug_msg("#### XRL -> REGISTER INTEREST UNRESOLVABLE %s\n",
	       rt_reg->valid_subnet().str().c_str());
    } else {
	metric = rt_reg->route()->metric();
	base_addr = rt_reg->valid_subnet().masked_addr();
	prefix_len = rt_reg->valid_subnet().prefix_len();
	NextHop *nh = rt_reg->route()->nexthop();
	switch (nh->type()) {
	case GENERIC_NEXTHOP:
	    // this shouldn't be possible
	    XLOG_UNREACHABLE();
	case PEER_NEXTHOP:
	case ENCAPS_NEXTHOP:
	    resolves = true;
	    nexthop = ((IPNextHop<IPv4>*)nh)->addr();
	    real_prefix_len = rt_reg->route()->prefix_len();
	    break;
	case EXTERNAL_NEXTHOP:
	case DISCARD_NEXTHOP:
	    resolves = false;
	    break;
	}
    }
    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::rib_0_1_deregister_interest4(// Input values,
					   const string& target,
					   const IPv4& addr,
					   const uint32_t& prefix_len)
{
    if (_urib4.route_deregister(IPv4Net(addr, prefix_len), target)
	!= XORP_OK) {
	string error_msg = c_format("Failed to deregister target %s for "
				    "prefix %s/%u",
				    target.c_str(),
				    addr.str().c_str(),
				    prefix_len);
	return XrlCmdError::COMMAND_FAILED(error_msg);
    }
    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::rib_0_1_register_interest6(// Input values,
					 const string& target,
					 const IPv6& addr,
					 // Output values,
					 bool& resolves,
					 IPv6& base_addr,
					 uint32_t& prefix_len,
					 uint32_t& real_prefix_len,
					 IPv6&	nexthop,
					 uint32_t& metric)
{
    RouteRegister<IPv6>* rt_reg = _urib6.route_register(addr, target);
    if (rt_reg->route() == NULL) {
	base_addr = rt_reg->valid_subnet().masked_addr();
	prefix_len = real_prefix_len = rt_reg->valid_subnet().prefix_len();
	resolves = false;
    } else {
	metric = rt_reg->route()->metric();
	base_addr = rt_reg->valid_subnet().masked_addr();
	prefix_len = rt_reg->valid_subnet().prefix_len();
	NextHop *nh = rt_reg->route()->nexthop();
	switch (nh->type()) {
	case GENERIC_NEXTHOP:
	    // this shouldn't be possible
	    XLOG_UNREACHABLE();
	case PEER_NEXTHOP:
	case ENCAPS_NEXTHOP:
	    resolves = true;
	    nexthop = ((IPNextHop<IPv6>*)nh)->addr();
	    real_prefix_len = rt_reg->route()->prefix_len();
	    break;
	case EXTERNAL_NEXTHOP:
	case DISCARD_NEXTHOP:
	    resolves = false;
	    break;
	}
    }
    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::rib_0_1_deregister_interest6(// Input values,
					   const string& target,
					   const IPv6&	addr,
					   const uint32_t& prefix_len)
{
    if (_urib6.route_deregister(IPv6Net(addr, prefix_len), target)
	!= XORP_OK) {
	string error_msg = c_format("Failed to deregister target %s for "
				    "prefix %s/%u",
				    target.c_str(),
				    addr.str().c_str(),
				    prefix_len);
	return XrlCmdError::COMMAND_FAILED(error_msg);
    }
    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::fea_ifmgr_client_0_1_interface_update(// Input values,
						    const string& ifname,
						    const uint32_t& event)
{
    _vif_manager.interface_update(ifname, event);
    return XrlCmdError::OKAY();
}


XrlCmdError
XrlRibTarget::fea_ifmgr_client_0_1_vif_update(// Input values,
					      const string& ifname,
					      const string& vifname,
					      const uint32_t& event)
{
    _vif_manager.vif_update(ifname, vifname, event);
    return XrlCmdError::OKAY();
}


XrlCmdError
XrlRibTarget::fea_ifmgr_client_0_1_vifaddr4_update(// Input values,
						   const string& ifname,
						   const string& vifname,
						   const IPv4& addr,
						   const uint32_t& event)
{
    _vif_manager.vifaddr4_update(ifname, vifname, addr, event);
    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::fea_ifmgr_client_0_1_vifaddr6_update(// Input values,
						   const string& ifname,
						   const string& vifname,
						   const IPv6& addr,
						   const uint32_t& event)
{
    _vif_manager.vifaddr6_update(ifname, vifname, addr, event);
    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::fea_ifmgr_client_0_1_updates_completed()
{
    _vif_manager.updates_completed();
    
    return XrlCmdError::OKAY();
}


XrlCmdError
XrlRibTarget::finder_event_observer_0_1_xrl_target_birth(
        const string&	target_class,
	const string&	target_instance)
{
    debug_msg(("Target Birth: " + target_class + " " + target_instance
	       + "\n").c_str());
    UNUSED(target_class);
    UNUSED(target_instance);

    return XrlCmdError::OKAY();
}

XrlCmdError
XrlRibTarget::finder_event_observer_0_1_xrl_target_death(
	const string&	target_class,
	const string&	target_instance)
{
    debug_msg(("Target Death: " + target_class + " " + target_instance
	       + "\n").c_str());
    _rib_manager->target_death(target_class, target_instance);
    return XrlCmdError::OKAY();
}
