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

// @brief      Attach to the VM debugger
// @param[in]  vm_config  Configuration data for the VM debugging session
int session::attach(const vm_config &a_config)
{
	// TEMP: Testing
    breakpoint *b = new breakpoint;
    b->breakpoint_address = 0x80200000;
    b->breakpoint_symbol = "main";

    return 0;
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
