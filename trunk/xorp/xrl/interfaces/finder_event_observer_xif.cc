/*
 * Copyright (c) 2001-2003 International Computer Science Institute
 * See LICENSE file for licensing, conditions, and warranties on use.
 *
 * DO NOT EDIT THIS FILE - IT IS PROGRAMMATICALLY GENERATED
 *
 * Generated by '../scripts/clnt-gen'.
 */

#ident "$XORP: xorp/xrl/interfaces/finder_event_observer_xif.cc,v 1.1 2003/05/09 19:36:03 hodson Exp $"

#include "finder_event_observer_xif.hh"

bool
XrlFinderEventObserverV0p1Client::send_xrl_target_birth(
	const char*	the_tgt, 
	const string&	target_class, 
	const string&	target_instance, 
	const CB0&	cb
)
{
    Xrl x(the_tgt, "finder_event_observer/0.1/xrl_target_birth");
    x.args().add("target_class", target_class);
    x.args().add("target_instance", target_instance);
    return _sender->send(x, callback(this, &XrlFinderEventObserverV0p1Client::unmarshall0, cb));
}


/* Unmarshall xrl_target_birth */
void
XrlFinderEventObserverV0p1Client::unmarshall0(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB0		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e);
	return;
    } else if (a && a->size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != 0)", (uint32_t)a->size());
	cb->dispatch(XrlError::BAD_ARGS());
	return;
    }
    cb->dispatch(e);
}

bool
XrlFinderEventObserverV0p1Client::send_xrl_target_death(
	const char*	the_tgt, 
	const string&	target_class, 
	const string&	target_instance, 
	const CB1&	cb
)
{
    Xrl x(the_tgt, "finder_event_observer/0.1/xrl_target_death");
    x.args().add("target_class", target_class);
    x.args().add("target_instance", target_instance);
    return _sender->send(x, callback(this, &XrlFinderEventObserverV0p1Client::unmarshall1, cb));
}


/* Unmarshall xrl_target_death */
void
XrlFinderEventObserverV0p1Client::unmarshall1(
	const XrlError&	e, 
	XrlArgs*	a, 
	CB1		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e);
	return;
    } else if (a && a->size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != 0)", (uint32_t)a->size());
	cb->dispatch(XrlError::BAD_ARGS());
	return;
    }
    cb->dispatch(e);
}
