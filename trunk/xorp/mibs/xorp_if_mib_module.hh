/*
 * Note: this file originally auto-generated by mib2c using
 *        : mib2c.int_watch.conf,v 5.0 2002/04/20 07:30:13 hardaker Exp $
 */
#ifndef __MIBS_XORP_IF_MIB_HH__
#define __MIBS_XORP_IF_MIB_HH__ 

#include "config.h"
#include <queue>
#include "libxorp/xorp.h"
#include "libxorp/xlog.h"
#include "libxipc/xrl_std_router.hh"
#include "libxipc/xrl_args.hh"
#include "xrl/interfaces/xorp_if_mib_xif.hh"
#include "xorp_if_mib_xrl_target.hh"


/* dlopen functions */
extern "C" {
void   init_xorp_if_mib_module(void);
void deinit_xorp_if_mib_module(void);
}



/**
 * @short Special MIB module that allows XORP and Net-SNMP to communicate 
 *
 */

class XorpIfMib {

public:
    static XorpIfMib& the_instance();
    static void explicit_destructor();
 
    const char * name() { return _name.c_str(); };

private:
    XorpIfMib();
    XrlStdRouter _xrl_router;
    XrlXorpIfMibTarget _xrl_target;

    const string  _name; 

    static XorpIfMib* _xorp_if_mib;
};

#endif    /* __MIBS_XORP_IF_MIB_HH__ */                      
