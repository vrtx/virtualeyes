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

#ifndef VIRTUALEYES_SESSION_HPP
#define VIRTUALEYES_SESSION_HPP

// Includes
#include "common.hpp"
#include "snapshot.hpp"
#include "breakpoint.hpp"
#include "handle_base.hpp"
#include "vm_run.hpp"
#include "core/db/realtime_feed.hpp"

namespace veyes
{
        typedef string target_config;               // BB TODO:  temp until config classes are implemented

        ///////////////////////////////////////////////////////
        /// @class   session
        /// @brief   This class defines the virtualeyes session instance
        ///////////////////////////////////////////////////////
        class session : public QObject,
                        public handle_base
        {
        Q_OBJECT
        public:

	        // Member Variables
	        owned_breakpoints_t m_breakpoints;              // breakpoints defined for this session
	        owned_snapshots_t m_snapshots;                  // set of all snapshots in this session
	        owned_vm_runs_t m_vm_runs;                      // set of all VM runs

	        // Member Functions
	        session();                                      // ctor
	        session(const session &a_session);              // copy ctor
	        virtual ~session();                             // dtor
	        int attach(const target_config &a_target_config);       // attach to a system and/or process

        public slots:
            void add_snapshot(const veyes::handle <snapshot> &a_snapshot);         // register a new collection snapshot with the session
            void add_breakpoint(const veyes::handle <breakpoint> &a_breakpoint);   // register a new breakpoint with the session
            void add_vm_run(const veyes::handle <vm_run> &a_vm_run);               // register a new vm run with the session
            void process_new_event(const BSONObj o);                               // process and forward the new event

        signals:
            void session_created();                                                // signal new session creation
            void snapshot_added(const veyes::handle <snapshot> &a_snapshot);       // notify that a snapshot was added
            void breakpoint_added(const veyes::handle <breakpoint> &a_breakpoint); // notify that a breakpoint was added
            void vm_run_added(const veyes::handle <vm_run> &a_vm_run);             // notify that a vm_run was added
        };

}

#endif
