/*
 * Copyright (c) 2002 International Computer Science Institute
 * See LICENSE file for licensing, conditions, and warranties on use.
 *
 * DO NOT EDIT THIS FILE - IT IS PROGRAMMATICALLY GENERATED
 *
 * Generated by '../scripts/clnt-gen'.
 *
 * $XORP: xorp/xrl/interfaces/bgp_xif.hh,v 1.1.1.1 2002/12/11 23:56:17 hodson Exp $
 */


#ifndef __XRL_INTERFACES_BGP_XIF_HH__
#define __XRL_INTERFACES_BGP_XIF_HH__

#undef XORP_LIBRARY_NAME
#define XORP_LIBRARY_NAME "XifBgp"
#include "libxorp/xlog.h"
#include "libxipc/xrl_router.hh"

class XrlBgpV0p2Client {
public:
    XrlBgpV0p2Client(XrlRouter* r) : _router(r) {}
    virtual ~XrlBgpV0p2Client() {}

    typedef XorpCallback1<void, const XrlError&>::RefPtr CB0;
    /**
     *  Send Xrl intended to:
     *  
     *  Get local config
     *  
     *  @param tgt_name Xrl Target name
     *  
     *  @param id our BGP ID.
     */
    bool send_local_config(
	const char*	target_name, 
	const uint32_t&	as, 
	const IPv4&	id, 
	const CB0&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr CB1;
    /**
     *  Send Xrl intended to:
     *  
     *  Set the local AS number.
     *  
     *  @param tgt_name Xrl Target name
     *  
     *  @param as our AS number.
     */
    bool send_set_local_as(
	const char*	target_name, 
	const uint32_t&	as, 
	const CB1&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr CB2;
    /**
     *  Send Xrl intended to:
     *  
     *  Set the BGP id.
     *  
     *  @param tgt_name Xrl Target name
     *  
     *  @param id our BGP ID.
     */
    bool send_set_bgpid(
	const char*	target_name, 
	const IPv4&	id, 
	const CB2&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr CB3;
    /**
     *  Send Xrl intended to:
     *  
     *  Add peer.
     *  
     *  @param tgt_name Xrl Target name
     *  
     *  @param as the peer's AS number.
     *  
     *  @param next_hop the local next hop.
     *  
     *  @param holdtime expects traffic in this time interval.
     */
    bool send_add_peer(
	const char*	target_name, 
	const string&	local_ip, 
	const uint32_t&	local_port, 
	const string&	peer_ip, 
	const uint32_t&	peer_port, 
	const uint32_t&	as, 
	const IPv4&	next_hop, 
	const uint32_t&	holdtime, 
	const CB3&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr CB4;
    /**
     *  Send Xrl intended to:
     *  
     *  Delete peer.
     *  
     *  @param tgt_name Xrl Target name
     *  
     *  @param as the peer's AS number.
     */
    bool send_delete_peer(
	const char*	target_name, 
	const string&	local_ip, 
	const uint32_t&	local_port, 
	const string&	peer_ip, 
	const uint32_t&	peer_port, 
	const uint32_t&	as, 
	const CB4&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr CB5;
    /**
     *  Send Xrl intended to:
     *  
     *  Enable this peer.
     *  
     *  @param tgt_name Xrl Target name
     */
    bool send_enable_peer(
	const char*	target_name, 
	const string&	local_ip, 
	const uint32_t&	local_port, 
	const string&	peer_ip, 
	const uint32_t&	peer_port, 
	const CB5&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr CB6;
    /**
     *  Send Xrl intended to:
     *  
     *  Disable this peer.
     *  
     *  @param tgt_name Xrl Target name
     */
    bool send_disable_peer(
	const char*	target_name, 
	const string&	local_ip, 
	const uint32_t&	local_port, 
	const string&	peer_ip, 
	const uint32_t&	peer_port, 
	const CB6&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr CB7;
    /**
     *  Send Xrl intended to:
     *  
     *  Set the peer state enabled or disabled.
     *  
     *  @param tgt_name Xrl Target name
     *  
     *  @param toggle enabled or disabled.
     */
    bool send_set_peer_state(
	const char*	target_name, 
	const string&	local_ip, 
	const uint32_t&	local_port, 
	const string&	peer_ip, 
	const uint32_t&	peer_port, 
	const bool&	toggle, 
	const CB7&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr CB8;
    /**
     *  Send Xrl intended to:
     *  
     *  Register rib.
     *  
     *  @param tgt_name Xrl Target name
     *  
     *  @param name rib name.
     */
    bool send_register_rib(
	const char*	target_name, 
	const string&	name, 
	const CB8&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr CB9;
    /**
     *  Send Xrl intended to:
     *  
     *  add route
     *  
     *  @param tgt_name Xrl Target name
     *  
     *  @param origin the origin of the path information.
     *  
     *  @param next_hop the border router that should be used as a detination
     *  for the nlri.
     *  
     *  @param nlri network level reachability information.
     */
    bool send_add_route(
	const char*	target_name, 
	const int32_t&	origin, 
	const int32_t&	asnum, 
	const IPv4&	next_hop, 
	const IPv4Net&	nlri, 
	const CB9&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr CB10;
    /**
     *  Send Xrl intended to:
     *  
     *  delete route
     *  
     *  @param tgt_name Xrl Target name
     *  
     *  @param nlri network level reachability information.
     */
    bool send_delete_route(
	const char*	target_name, 
	const IPv4Net&	nlri, 
	const CB10&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr CB11;
    /**
     *  Send Xrl intended to:
     *  
     *  Terminate bgp process
     *  
     *  @param tgt_name Xrl Target name
     */
    bool send_terminate(
	const char*	target_name, 
	const CB11&	cb
    );

    typedef XorpCallback1<void, const XrlError&>::RefPtr CB12;
    /**
     *  Send Xrl intended to:
     *  
     *  Set which parameters we support per peer
     *  
     *  @param tgt_name Xrl Target name
     */
    bool send_set_parameter(
	const char*	target_name, 
	const string&	local_ip, 
	const uint32_t&	local_port, 
	const string&	peer_ip, 
	const uint32_t&	peer_port, 
	const string&	parameter, 
	const CB12&	cb
    );

protected:
    XrlRouter* _router;

private:
    void unmarshall0(
	const XrlError&	e, 
	XrlRouter&	/* r */, 
	const Xrl&	/* x */, 
	XrlArgs*	a, 
	CB0		cb
    );

    void unmarshall1(
	const XrlError&	e, 
	XrlRouter&	/* r */, 
	const Xrl&	/* x */, 
	XrlArgs*	a, 
	CB1		cb
    );

    void unmarshall2(
	const XrlError&	e, 
	XrlRouter&	/* r */, 
	const Xrl&	/* x */, 
	XrlArgs*	a, 
	CB2		cb
    );

    void unmarshall3(
	const XrlError&	e, 
	XrlRouter&	/* r */, 
	const Xrl&	/* x */, 
	XrlArgs*	a, 
	CB3		cb
    );

    void unmarshall4(
	const XrlError&	e, 
	XrlRouter&	/* r */, 
	const Xrl&	/* x */, 
	XrlArgs*	a, 
	CB4		cb
    );

    void unmarshall5(
	const XrlError&	e, 
	XrlRouter&	/* r */, 
	const Xrl&	/* x */, 
	XrlArgs*	a, 
	CB5		cb
    );

    void unmarshall6(
	const XrlError&	e, 
	XrlRouter&	/* r */, 
	const Xrl&	/* x */, 
	XrlArgs*	a, 
	CB6		cb
    );

    void unmarshall7(
	const XrlError&	e, 
	XrlRouter&	/* r */, 
	const Xrl&	/* x */, 
	XrlArgs*	a, 
	CB7		cb
    );

    void unmarshall8(
	const XrlError&	e, 
	XrlRouter&	/* r */, 
	const Xrl&	/* x */, 
	XrlArgs*	a, 
	CB8		cb
    );

    void unmarshall9(
	const XrlError&	e, 
	XrlRouter&	/* r */, 
	const Xrl&	/* x */, 
	XrlArgs*	a, 
	CB9		cb
    );

    void unmarshall10(
	const XrlError&	e, 
	XrlRouter&	/* r */, 
	const Xrl&	/* x */, 
	XrlArgs*	a, 
	CB10		cb
    );

    void unmarshall11(
	const XrlError&	e, 
	XrlRouter&	/* r */, 
	const Xrl&	/* x */, 
	XrlArgs*	a, 
	CB11		cb
    );

    void unmarshall12(
	const XrlError&	e, 
	XrlRouter&	/* r */, 
	const Xrl&	/* x */, 
	XrlArgs*	a, 
	CB12		cb
    );

};

#endif /* __XRL_INTERFACES_BGP_XIF_HH__ */
