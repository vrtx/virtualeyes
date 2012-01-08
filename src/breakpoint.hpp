///////////////////////////////////////////////////////
// virtualeyes
//
// Copyright (c) 2011 Benjamnin Becker
// All Rights Reserved
/// @author  Ben Becker
/// @date    2/12/11
///////////////////////////////////////////////////////

#ifndef VIRTUALEYES_BREAKPOINT_HPP
#define VIRTUALEYES_BREAKPOINT_HPP

// Includes
#include "common.hpp"
#include "handle_base.hpp"
#include "handle.hpp"
#include "soft_handle.hpp"
#include "snapshot.hpp"

namespace veyes
{
    // Forward Declarations
    class breakpoint;

    // Container Type Definitions
    typedef vector <handle <breakpoint> > breakpoint_list_t;
    typedef vector <soft_handle <breakpoint> > breakpoint_soft_list_t;
    typedef breakpoint_list_t owned_breakpoints_t;
    typedef breakpoint_soft_list_t soft_breakpoints_t;

    ///////////////////////////////////////////////////////
    /// @class   breakpoint
    /// @brief   This class defines a breakpoint to be set in the
    ///          VM debugger.
    ///////////////////////////////////////////////////////
    class breakpoint : public handle_base
    {
    public:
        // Member variables
        uint64_t breakpoint_address;    // address of this breakpoint
        QString  breakpoint_name;       // user-defined name of the breakpoint
        QString  breakpoint_symbol;     // symbol of this sbreakpoint
        uint64_t breakpoint_sym_offset; // offset from symbol of the breakpoint
        uint64_t break_count;           // number of times to break on this breakpoint

        // Member Functions
        breakpoint();                   // default ctor
        virtual ~breakpoint();          // dtor
        breakpoint(const breakpoint &a_breakpoint); // copy ctor
        void add_snapshot();            // add a snapshot (when a breakpoint is hit)
        void handle_bp();               // callback for a collected breakpoint

    private:
        owned_snapshots_t snapshots;       // all snapshots collected from this breakpoint
    };
}

#endif
