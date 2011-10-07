///////////////////////////////////////////////////////
//
// virtualeyes
//
// Copyright (c) 2011 Benjamnin Becker
// All Rights Reserved
//
/// @author  Ben Becker
/// @date    2/12/11
//
///////////////////////////////////////////////////////

#include "breakpoint.hpp"
#include "virtualeyes.hpp"
#include "common.hpp"

/// @brief   Default constructor
breakpoint::breakpoint() :
        handle_base(),
        breakpoint_address(0),
        breakpoint_name(),
        gdb_breakpoint(NULL)
{

}

/// @brief   Copy constructor
breakpoint::breakpoint(const breakpoint &a_breakpoint):
        handle_base(a_breakpoint),
        breakpoint_address(a_breakpoint.breakpoint_address),
        breakpoint_name(a_breakpoint.breakpoint_name),
        gdb_breakpoint(a_breakpoint.gdb_breakpoint)
{

}

/// @brief   Destructor
breakpoint::~breakpoint()
{

        // NOTE: assumes gdb_breakpoint is NULL if the breakpoint has already
        //       been invalidated
        if (gdb_breakpoint != NULL) {

                mi_free_bkpt(gdb_breakpoint);

        }

        if (!snapshots.empty())
                snapshots.clear();

}

/// @brief   Add a collected snapshot to this breakpoint
///          NOTE:  assumes there is an active session
void breakpoint::add_snapshot()
{

        // helpers
        pair <owned_snapshots_t::iterator, bool> i_snap;

        // create a new snapshot
        handle <snapshot> l_new_snapshot(new snapshot);

        // populate the snapshot object
        l_new_snapshot->parent_bp = this;
        l_new_snapshot->time = QTime::currentTime();
        l_new_snapshot->snapshot_name = breakpoint_name.append(QString(" [").append(QString(boost::lexical_cast <string>(snapshots.size()).c_str()).append("]")));

        // add the new snapshot to the breakpoint's list of snapshots
        i_snap = snapshots.insert(l_new_snapshot);
        if (i_snap.first != snapshots.begin()) {
                // previous snapshot exists for this breakpoint

                l_new_snapshot->collect_using_template(*(--i_snap.first));

        }

        // register the snapshot with the session
        global <virtualeyes>()->m_active_session->add_snapshot(l_new_snapshot);

}

/// @brief   Callback for triggered breakpoint
void breakpoint::handle_bp()
{

        // sanity check
        if (!global <virtualeyes>()->m_active_session.is_valid())
                // invalid session
                throw(vexcept("Unable to handle breakpoint trigger.  Session object is invalid."));

        // generate a new snapshot instance
        add_snapshot();

}

