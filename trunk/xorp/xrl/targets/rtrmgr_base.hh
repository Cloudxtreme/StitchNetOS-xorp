/*
 * Copyright (c) 2002 International Computer Science Institute
 * See LICENSE file for licensing, conditions, and warranties on use.
 *
 * DO NOT EDIT THIS FILE - IT IS PROGRAMMATICALLY GENERATED
 *
 * Generated by '../scripts/tgt-gen'.
 *
 * $XORP: xorp/xrl/targets/rtrmgr_base.hh,v 1.1.1.1 2002/12/11 23:56:19 hodson Exp $
 */


#ifndef __XRL_INTERFACES_RTRMGR_BASE_HH__
#define __XRL_INTERFACES_RTRMGR_BASE_HH__

#undef XORP_LIBRARY_NAME
#define XORP_LIBRARY_NAME "XrlRtrmgrTarget"

#include "libxorp/xlog.h"
#include "libxipc/xrl_router.hh"

class XrlRtrmgrTargetBase {
protected:
    XrlCmdMap* _router;
    
public:
    XrlRtrmgrTargetBase(XrlCmdMap* r) : _router(r) { add_handlers(); }
    virtual ~XrlRtrmgrTargetBase() { remove_handlers(); }

protected:

    /**
     *  Pure-virtual function that needs to be implemented to:
     *  
     *  Get name of Xrl Target
     */
    virtual XrlCmdError common_0_1_get_target_name(
	// Output values, 
	string&	name) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *  
     *  Get version string from Xrl Target
     */
    virtual XrlCmdError common_0_1_get_version(
	// Output values, 
	string&	version) = 0;

    virtual XrlCmdError rtrmgr_0_1_get_pid(
	// Output values, 
	uint32_t&	pid) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *  
     *  Register a user and client process with the rtrmgr.
     *  
     *  @param clientname name of xrl entity supporting rtrmgr_client.xif
     *  methods.
     */
    virtual XrlCmdError rtrmgr_0_1_register_client(
	// Input values, 
	const uint32_t&	userid, 
	const string&	clientname, 
	// Output values, 
	string&	filename, 
	uint32_t&	pid) = 0;

    virtual XrlCmdError rtrmgr_0_1_unregister_client(
	// Input values, 
	const string&	token) = 0;

    virtual XrlCmdError rtrmgr_0_1_authenticate_client(
	// Input values, 
	const uint32_t&	userid, 
	const string&	clientname, 
	const string&	token) = 0;

    virtual XrlCmdError rtrmgr_0_1_enter_config_mode(
	// Input values, 
	const string&	token, 
	const bool&	exclusive) = 0;

    virtual XrlCmdError rtrmgr_0_1_leave_config_mode(
	// Input values, 
	const string&	token) = 0;

    virtual XrlCmdError rtrmgr_0_1_get_config_users(
	// Input values, 
	const string&	token, 
	// Output values, 
	XrlAtomList&	users) = 0;

    virtual XrlCmdError rtrmgr_0_1_get_running_config(
	// Input values, 
	const string&	token, 
	// Output values, 
	string&	config) = 0;

    virtual XrlCmdError rtrmgr_0_1_apply_config_change(
	// Input values, 
	const string&	token, 
	const string&	target, 
	const string&	deltas, 
	const string&	deletions) = 0;

    virtual XrlCmdError rtrmgr_0_1_lock_config(
	// Input values, 
	const string&	token, 
	const uint32_t&	timeout, 
	// Output values, 
	bool&	success, 
	uint32_t&	holder) = 0;

    virtual XrlCmdError rtrmgr_0_1_unlock_config(
	// Input values, 
	const string&	token) = 0;

    virtual XrlCmdError rtrmgr_0_1_lock_node(
	// Input values, 
	const string&	token, 
	const string&	node, 
	const uint32_t&	timeout, 
	// Output values, 
	bool&	success, 
	uint32_t&	holder) = 0;

    virtual XrlCmdError rtrmgr_0_1_unlock_node(
	// Input values, 
	const string&	token, 
	const string&	node) = 0;

    virtual XrlCmdError rtrmgr_0_1_save_config(
	// Input values, 
	const string&	token, 
	const string&	filename) = 0;

    virtual XrlCmdError rtrmgr_0_1_load_config(
	// Input values, 
	const string&	token, 
	const string&	target, 
	const string&	filename) = 0;

private:
    const XrlCmdError handle_common_0_1_get_target_name(const Xrl& x, XrlArgs* a);

    const XrlCmdError handle_common_0_1_get_version(const Xrl& x, XrlArgs* a);

    const XrlCmdError handle_rtrmgr_0_1_get_pid(const Xrl& x, XrlArgs* a);

    const XrlCmdError handle_rtrmgr_0_1_register_client(const Xrl& x, XrlArgs* a);

    const XrlCmdError handle_rtrmgr_0_1_unregister_client(const Xrl& x, XrlArgs* a);

    const XrlCmdError handle_rtrmgr_0_1_authenticate_client(const Xrl& x, XrlArgs* a);

    const XrlCmdError handle_rtrmgr_0_1_enter_config_mode(const Xrl& x, XrlArgs* a);

    const XrlCmdError handle_rtrmgr_0_1_leave_config_mode(const Xrl& x, XrlArgs* a);

    const XrlCmdError handle_rtrmgr_0_1_get_config_users(const Xrl& x, XrlArgs* a);

    const XrlCmdError handle_rtrmgr_0_1_get_running_config(const Xrl& x, XrlArgs* a);

    const XrlCmdError handle_rtrmgr_0_1_apply_config_change(const Xrl& x, XrlArgs* a);

    const XrlCmdError handle_rtrmgr_0_1_lock_config(const Xrl& x, XrlArgs* a);

    const XrlCmdError handle_rtrmgr_0_1_unlock_config(const Xrl& x, XrlArgs* a);

    const XrlCmdError handle_rtrmgr_0_1_lock_node(const Xrl& x, XrlArgs* a);

    const XrlCmdError handle_rtrmgr_0_1_unlock_node(const Xrl& x, XrlArgs* a);

    const XrlCmdError handle_rtrmgr_0_1_save_config(const Xrl& x, XrlArgs* a);

    const XrlCmdError handle_rtrmgr_0_1_load_config(const Xrl& x, XrlArgs* a);

    void add_handlers()
    {
	if (_router->add_handler("common/0.1/get_target_name", 
	    callback(this, &XrlRtrmgrTargetBase::handle_common_0_1_get_target_name)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://rtrmgr/common/0.1/get_target_name");
	}
	if (_router->add_handler("common/0.1/get_version", 
	    callback(this, &XrlRtrmgrTargetBase::handle_common_0_1_get_version)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://rtrmgr/common/0.1/get_version");
	}
	if (_router->add_handler("rtrmgr/0.1/get_pid", 
	    callback(this, &XrlRtrmgrTargetBase::handle_rtrmgr_0_1_get_pid)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://rtrmgr/rtrmgr/0.1/get_pid");
	}
	if (_router->add_handler("rtrmgr/0.1/register_client", 
	    callback(this, &XrlRtrmgrTargetBase::handle_rtrmgr_0_1_register_client)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://rtrmgr/rtrmgr/0.1/register_client");
	}
	if (_router->add_handler("rtrmgr/0.1/unregister_client", 
	    callback(this, &XrlRtrmgrTargetBase::handle_rtrmgr_0_1_unregister_client)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://rtrmgr/rtrmgr/0.1/unregister_client");
	}
	if (_router->add_handler("rtrmgr/0.1/authenticate_client", 
	    callback(this, &XrlRtrmgrTargetBase::handle_rtrmgr_0_1_authenticate_client)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://rtrmgr/rtrmgr/0.1/authenticate_client");
	}
	if (_router->add_handler("rtrmgr/0.1/enter_config_mode", 
	    callback(this, &XrlRtrmgrTargetBase::handle_rtrmgr_0_1_enter_config_mode)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://rtrmgr/rtrmgr/0.1/enter_config_mode");
	}
	if (_router->add_handler("rtrmgr/0.1/leave_config_mode", 
	    callback(this, &XrlRtrmgrTargetBase::handle_rtrmgr_0_1_leave_config_mode)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://rtrmgr/rtrmgr/0.1/leave_config_mode");
	}
	if (_router->add_handler("rtrmgr/0.1/get_config_users", 
	    callback(this, &XrlRtrmgrTargetBase::handle_rtrmgr_0_1_get_config_users)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://rtrmgr/rtrmgr/0.1/get_config_users");
	}
	if (_router->add_handler("rtrmgr/0.1/get_running_config", 
	    callback(this, &XrlRtrmgrTargetBase::handle_rtrmgr_0_1_get_running_config)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://rtrmgr/rtrmgr/0.1/get_running_config");
	}
	if (_router->add_handler("rtrmgr/0.1/apply_config_change", 
	    callback(this, &XrlRtrmgrTargetBase::handle_rtrmgr_0_1_apply_config_change)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://rtrmgr/rtrmgr/0.1/apply_config_change");
	}
	if (_router->add_handler("rtrmgr/0.1/lock_config", 
	    callback(this, &XrlRtrmgrTargetBase::handle_rtrmgr_0_1_lock_config)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://rtrmgr/rtrmgr/0.1/lock_config");
	}
	if (_router->add_handler("rtrmgr/0.1/unlock_config", 
	    callback(this, &XrlRtrmgrTargetBase::handle_rtrmgr_0_1_unlock_config)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://rtrmgr/rtrmgr/0.1/unlock_config");
	}
	if (_router->add_handler("rtrmgr/0.1/lock_node", 
	    callback(this, &XrlRtrmgrTargetBase::handle_rtrmgr_0_1_lock_node)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://rtrmgr/rtrmgr/0.1/lock_node");
	}
	if (_router->add_handler("rtrmgr/0.1/unlock_node", 
	    callback(this, &XrlRtrmgrTargetBase::handle_rtrmgr_0_1_unlock_node)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://rtrmgr/rtrmgr/0.1/unlock_node");
	}
	if (_router->add_handler("rtrmgr/0.1/save_config", 
	    callback(this, &XrlRtrmgrTargetBase::handle_rtrmgr_0_1_save_config)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://rtrmgr/rtrmgr/0.1/save_config");
	}
	if (_router->add_handler("rtrmgr/0.1/load_config", 
	    callback(this, &XrlRtrmgrTargetBase::handle_rtrmgr_0_1_load_config)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://rtrmgr/rtrmgr/0.1/load_config");
	}
    }

    void remove_handlers()
    {
	_router->remove_handler("common/0.1/get_target_name");
	_router->remove_handler("common/0.1/get_version");
	_router->remove_handler("rtrmgr/0.1/get_pid");
	_router->remove_handler("rtrmgr/0.1/register_client");
	_router->remove_handler("rtrmgr/0.1/unregister_client");
	_router->remove_handler("rtrmgr/0.1/authenticate_client");
	_router->remove_handler("rtrmgr/0.1/enter_config_mode");
	_router->remove_handler("rtrmgr/0.1/leave_config_mode");
	_router->remove_handler("rtrmgr/0.1/get_config_users");
	_router->remove_handler("rtrmgr/0.1/get_running_config");
	_router->remove_handler("rtrmgr/0.1/apply_config_change");
	_router->remove_handler("rtrmgr/0.1/lock_config");
	_router->remove_handler("rtrmgr/0.1/unlock_config");
	_router->remove_handler("rtrmgr/0.1/lock_node");
	_router->remove_handler("rtrmgr/0.1/unlock_node");
	_router->remove_handler("rtrmgr/0.1/save_config");
	_router->remove_handler("rtrmgr/0.1/load_config");
    }
};

#endif /* __XRL_INTERFACES_RTRMGR_BASE_HH__ */
