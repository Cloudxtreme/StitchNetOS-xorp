/*
 * Copyright (c) 2002 International Computer Science Institute
 * See LICENSE file for licensing, conditions, and warranties on use.
 *
 * DO NOT EDIT THIS FILE - IT IS PROGRAMMATICALLY GENERATED
 *
 * Generated by '../scripts/clnt-gen'.
 *
 * $XORP: xorp/xrl/interfaces/coord_xif.hh,v 1.1.1.1 2002/12/11 23:56:17 hodson Exp $
 */


#ifndef __XRL_INTERFACES_COORD_XIF_HH__
#define __XRL_INTERFACES_COORD_XIF_HH__

#undef XORP_LIBRARY_NAME
#define XORP_LIBRARY_NAME "XifCoord"
#include "libxorp/xlog.h"
#include "libxipc/xrl_router.hh"

class XrlCoordV0p1Client {
public:
    XrlCoordV0p1Client(XrlRouter* r) : _router(r) {}
    virtual ~XrlCoordV0p1Client() {}

    typedef XorpCallback1<void, const XrlError&>::RefPtr CB0;
    /**
     *  Send Xrl intended to:
     *  
     *  Command to be executed by the coordinating process.
     *  
     *  @param tgt_name Xrl Target name
     *  
     *  @param command to be sent to the coordinator.
     */
    bool send_command(
	const char*	target_name, 
	const string&	command, 
	const CB0&	cb
    );

    typedef XorpCallback2<void, const XrlError&, const bool*>::RefPtr CB1;
    /**
     *  Send Xrl intended to:
     *  
     *  If there are still any outstanding commands pending will return true.
     *  Can be used to poll the coordinating process to verify that the
     *  previous command has completed.
     *  
     *  @param tgt_name Xrl Target name
     */
    bool send_pending(
	const char*	target_name, 
	const CB1&	cb
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

};

#endif /* __XRL_INTERFACES_COORD_XIF_HH__ */
