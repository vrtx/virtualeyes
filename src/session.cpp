///////////////////////////////////////////////////////
//
// virtualeyes
//
// Copyright (c) 2011 Benjamnin Becker
// All Rights Reserved
//
/// @author  Ben Becker
/// @date    2/20/11
//
///////////////////////////////////////////////////////

#include "session.hpp"
#include "virtualeyes.hpp"
#include "breakpoint.hpp"
#include "models/x86_32.hpp"
#include "opsys/win2k8.hpp"
#include "target_host.hpp"
#include "main_view.hpp"

/// @brief   Default constructor
session::session() :
    m_breakpoints(),
    m_snapshots()
{
    // connect the new session -> core signal indicating a new session has been created
    connect(this, SIGNAL(session_created()),
            global <virtualeyes>().raw_ptr, SLOT(new_session()));

    emit session_created();
}

/// @brief   Copy constructor
session::session(const session &a_session):
    m_breakpoints(a_session.m_breakpoints),
    m_snapshots(a_session.m_snapshots)
{

}

/// @brief   Destructor
session::~session()
{
    // free all references to child objects
    if (!m_breakpoints.empty())
        m_breakpoints.clear();

    if (!m_snapshots.empty())
        m_snapshots.clear();

    if (!m_vm_runs.empty())
        m_vm_runs.clear();
}

// @brief      Attach to a system and/or process
// @param[in]  target_config  Configuration data for the monitoring/debugging session
int session::attach(const target_config &a_config)
{
	// TEMP: Testing
    breakpoint *b = new breakpoint;
    b->breakpoint_address = 0x80200000;
    b->breakpoint_symbol = "main";

    return 0;
}

/// @brief		Set the db configuration params
void session::init_db(const db_config_t &a_conf)
{
	db_conf = a_conf;
    m_active_db = new db;
    m_active_db->set_config(db_conf);
    m_active_db->connect();
}	

// @brief      Get the active DB connection
soft_handle<db> session::get_db()
{
	if (m_active_db.is_valid())
		// connection exists
		return m_active_db;
    return new db;
}

// @brief      Add a new realtime feed to this session
// @param[in]  a_snapshot   The snapshot object to add to the session
soft_handle <realtime_feed> session::init_rt_feed(const char *collection_name, int timeout, bool load_initial)
{
    handle <realtime_feed> retval = new realtime_feed(get_db(), collection_name, timeout);
    m_rt_feeds.insert(pair <const char *, handle <realtime_feed> >(collection_name, retval));
    connect(retval.raw_ptr, SIGNAL(new_event(const BSONObj &)),
            this, SLOT(process_new_event(const BSONObj &)));
    retval->start();

    return retval;
}

void session::process_new_event(const BSONObj &o)
{
    cout << o.toString() << endl;
}

// @brief      Add a new snapshot to the session
// @param[in]  a_snapshot   The snapshot object to add to the session
void session::add_snapshot(const veyes::handle <snapshot> &a_snapshot)
{
    // add this snapshot to the session's list
    m_snapshots.insert(a_snapshot);
    VDEBUG(10, "Added new snapshot to the session's list");
    // notify any relevant views of the new snapshot
    emit snapshot_added(a_snapshot);
}


// @brief      Add a new breakpoint to the session
// @param[in]  a_breakpoint   The breakpoint object to add to the session
void session::add_breakpoint(const veyes::handle <breakpoint> &a_breakpoint)
{
    // add this breakpoint to the session's list
    m_breakpoints.push_back(a_breakpoint);

    // notify any relevant views of the new breakpoint
    emit breakpoint_added(a_breakpoint);
}

// @brief      Add a new vm_run to the session
// @param[in]  a_vm_run   The vm_run object to add to the session
void session::add_vm_run(const veyes::handle <vm_run> &a_vm_run)
{
    // add this vm_run to the session's list
    m_vm_runs.push_back(a_vm_run);

    // notify any relevant views of the new vm_run
    emit vm_run_added(a_vm_run);
}
