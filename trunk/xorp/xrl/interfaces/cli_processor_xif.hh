/*
 * Copyright (c) 2002 International Computer Science Institute
 * See LICENSE file for licensing, conditions, and warranties on use.
 *
 * DO NOT EDIT THIS FILE - IT IS PROGRAMMATICALLY GENERATED
 *
 * Generated by '../scripts/clnt-gen'.
 *
 * $XORP: xorp/xrl/interfaces/cli_processor_xif.hh,v 1.1.1.1 2002/12/11 23:56:17 hodson Exp $
 */


#ifndef __XRL_INTERFACES_CLI_PROCESSOR_XIF_HH__
#define __XRL_INTERFACES_CLI_PROCESSOR_XIF_HH__

#undef XORP_LIBRARY_NAME
#define XORP_LIBRARY_NAME "XifCliProcessor"
#include "libxorp/xlog.h"
#include "libxipc/xrl_router.hh"

class XrlCliProcessorV0p1Client {
public:
    XrlCliProcessorV0p1Client(XrlRouter* r) : _router(r) {}
    virtual ~XrlCliProcessorV0p1Client() {}

    typedef XorpCallback5<void, const XrlError&, const string*, const string*, const uint32_t*, const string*>::RefPtr CB0;

    bool send_process_command(
	const char*	target_name, 
	const string&	processor_name, 
	const string&	cli_term_name, 
	const uint32_t&	cli_session_id, 
	const string&	command_name, 
	const string&	command_args, 
	const CB0&	cb
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

};

#endif /* __XRL_INTERFACES_CLI_PROCESSOR_XIF_HH__ */
