/*
 * Copyright (c) 2002 International Computer Science Institute
 * See LICENSE file for licensing, conditions, and warranties on use.
 *
 * DO NOT EDIT THIS FILE - IT IS PROGRAMMATICALLY GENERATED
 *
 * Generated by '../scripts/clnt-gen'.
 *
 * $XORP: xorp/xrl/interfaces/mld6igmp_client_xif.hh,v 1.1.1.1 2002/12/11 23:56:17 hodson Exp $
 */


#ifndef __XRL_INTERFACES_MLD6IGMP_CLIENT_XIF_HH__
#define __XRL_INTERFACES_MLD6IGMP_CLIENT_XIF_HH__

#undef XORP_LIBRARY_NAME
#define XORP_LIBRARY_NAME "XifMld6igmpClient"
#include "libxorp/xlog.h"
#include "libxipc/xrl_router.hh"

class XrlMld6igmpClientV0p1Client {
public:
    XrlMld6igmpClientV0p1Client(XrlRouter* r) : _router(r) {}
    virtual ~XrlMld6igmpClientV0p1Client() {}

    typedef XorpCallback3<void, const XrlError&, const bool*, const string*>::RefPtr CB0;
    /**
     *  Send Xrl intended to:
     *  
     *  Add/delete membership information.
     *  
     *  @param tgt_name Xrl Target name
     *  
     *  @param xrl_sender_name the XRL name of the originator of this XRL.
     *  
     *  @param vif_name the name of the new vif.
     *  
     *  @param vif_index the index of the new vif.
     *  
     *  @param source the source address that has been joined/left.
     *  
     *  @param group the group address that has been joined/left.
     */
    bool send_add_membership4(
	const char*	target_name, 
	const string&	xrl_sender_name, 
	const string&	vif_name, 
	const uint32_t&	vif_index, 
	const IPv4&	source, 
	const IPv4&	group, 
	const CB0&	cb
    );

    typedef XorpCallback3<void, const XrlError&, const bool*, const string*>::RefPtr CB1;

    bool send_add_membership6(
	const char*	target_name, 
	const string&	xrl_sender_name, 
	const string&	vif_name, 
	const uint32_t&	vif_index, 
	const IPv6&	source, 
	const IPv6&	group, 
	const CB1&	cb
    );

    typedef XorpCallback3<void, const XrlError&, const bool*, const string*>::RefPtr CB2;

    bool send_delete_membership4(
	const char*	target_name, 
	const string&	xrl_sender_name, 
	const string&	vif_name, 
	const uint32_t&	vif_index, 
	const IPv4&	source, 
	const IPv4&	group, 
	const CB2&	cb
    );

    typedef XorpCallback3<void, const XrlError&, const bool*, const string*>::RefPtr CB3;

    bool send_delete_membership6(
	const char*	target_name, 
	const string&	xrl_sender_name, 
	const string&	vif_name, 
	const uint32_t&	vif_index, 
	const IPv6&	source, 
	const IPv6&	group, 
	const CB3&	cb
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

};

#endif /* __XRL_INTERFACES_MLD6IGMP_CLIENT_XIF_HH__ */
