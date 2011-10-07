///////////////////////////////////////////////////////
//
// virtualeyes
//
// Copyright (c) 2011 Benjamnin Becker
// All Rights Reserved
//
/// @brief   This file defines the data region that represents a portion of
//           guest memory and various methods of displaying it (hex, ascii, structure and assembly).
//
/// @author  Ben Becker
/// @date    2/13/11
//
///////////////////////////////////////////////////////

#include "vm_iface.hpp"
#include "snapshot.hpp"
#include "breakpoint.hpp"

/// @brief   Default constructor
vm_iface::vm_iface() :
        handle_base()
{

}

/// @brief   Copy constructor
vm_iface::vm_iface(const vm_iface &a_vm_iface)
{

}

/// @brief   Destructor
vm_iface::~vm_iface()
{

}

/// @brief   Connect to the VM debugger
/// @return  0 on success, -1 on failure
int vm_iface::connect()
{

        VDEBUG(7, "WARNING: " << __FUNCTION__ << " called in pure virtual base class!");
        return -1;

}

/// @brief   Disconnect from the VM debugger
/// @return  0 on success, -1 on failure
int vm_iface::disconnect()
{

        VDEBUG(7, "WARNING: " << __FUNCTION__ << " called in pure virtual base class!");
        return -1;

}

/// @brief       Register a breakpoint with the VM debugger
/// @param[in]   a_breakpoint     Breakpoint to register with the VM debugger
/// @return      0 on success, -1 on failure
int vm_iface::register_breakpoint(breakpoint *a_breakpoint)
{

        VDEBUG(7, "WARNING: " << __FUNCTION__ << " called in pure virtual base class!");
        return -1;

}

/// @brief       Remove a breakpoint from the VM debugger
/// @param[in]   a_breakpoint     Breakpoint to remove from the VM debugger
/// @return      0 on success, -1 on failure
int vm_iface::unregister_breakpoint(const breakpoint *a_breakpoint)
{

        VDEBUG(7, "WARNING: " << __FUNCTION__ << " called in pure virtual base class!");
        return -1;

}

/// @brief       Pause the VM
/// @param[out]  o_snapshot     Snapshot data to populate
/// @param[out]  o_breakpoint   Breakpoint to populate
/// @return      0 on success, -1 on failure
int vm_iface::pause()
{

        // BB TODO: generate snapshot and breakpoint.
        // VDEBUG(7, "WARNING: " << __FUNCTION__ << " called in pure virtual base class!";
        return -1;

}

/// @brief       Generate a snapshot of the VM state (including CPU registers, stack contents, etc.) without explicitly pausing
/// @param[out]
/// @return      0 on success, -1 on failure
int vm_iface::collect_snapshot()
{

        VDEBUG(7, "WARNING: " << __FUNCTION__ << " called in pure virtual base class!");
        return -1;

}

/// @brief       Resume the VM
/// @return      0 on success, -1 on failure
int vm_iface::resume()
{

        VDEBUG(7, "WARNING: " << __FUNCTION__ << " called in pure virtual base class!");
        return -1;

}


/// @brief       Step into the next instruction (or a_step_count instructions), then pause the VM
/// @param[out]  o_snapshot     Snapshot data to populate
/// @param[out]  o_breakpoint   Breakpoint to populate
/// @param[in]   o_step_count   Number of steps to take before breaking
/// @return      0 on success, -1 on failure
int vm_iface::step(uint64_t a_step_count)
{

        // BB TODO: generate snapshot and breakpoint.
        // VDEBUG(7, "WARNING: " << __FUNCTION__ << " called in pure virtual base class!";
        return 1;

}

/// @brief       Resume the VM until the next time a_breakpoint is hit
/// @param[in]   o_snapshot     Snapshot data to populate
/// @param[out]  a_breakpoint   Breakpoint to continue to
/// @return      0 on success, -1 on failure
int vm_iface::resume_until_bp(const breakpoint &a_breakpoint)
{

        // BB TODO: generate snapshot
        VDEBUG(7, "WARNING: " << __FUNCTION__ << " called in pure virtual base class!");
        return -1;

}








