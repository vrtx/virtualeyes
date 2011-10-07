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

#include "gdb_iface.hpp"
#include "snapshot.hpp"
#include "breakpoint.hpp"

/// @brief   Default constructor
gdb_iface::gdb_iface()
{

        gdb_handle = mi_connect_local();
        if (!gdb_handle) {
                // failed to connect

                VDEBUG(0, "Failed to open GDB/MI connection");
                // BB TODO: issue error?
        }

        // setup GDB IO callbacks
        mi_set_console_cb(gdb_handle, cb_console, NULL);
        mi_set_target_cb(gdb_handle, cb_target, NULL);
        mi_set_log_cb(gdb_handle, cb_log, NULL);
        mi_set_async_cb(gdb_handle, cb_async, NULL);
        mi_set_to_gdb_cb(gdb_handle, cb_to_gdb, NULL);
        mi_set_from_gdb_cb(gdb_handle, cb_from_gdb, NULL);

}

/// @brief   Copy constructor
gdb_iface::gdb_iface(const gdb_iface &a_gdb_iface) :
        gdb_handle(a_gdb_iface.gdb_handle)
{

}

/// @brief   Destructor
gdb_iface::~gdb_iface()
{

        disconnect();

}

/// @brief   Connect to the VM debugger
/// @return  0 on success, -1 on failure
int gdb_iface::connect()
{

         // connect to the remote target
         if (!gmi_target_select(gdb_handle, "remote", ":1234")) {
                 // failed to load symbols

                 VDEBUG(1, "Failed to connect to GDB target");
                 // BB TODO: seems to be reaching a timeout?
                 // mi_disconnect(gdb_handle);
                 // return -1;

         }

         // load a local target process
//         if (!gmi_set_exec(gdb_handle, "./build/virtualeyes", " --help")) {
//                 VDEBUG(1, "Failed to connect to GDB target");
//         };

         return 0;

}

/// @brief   Disconnect from the VM debugger
/// @return  0 on success, -1 on failure
int gdb_iface::disconnect()
{

        // disconnect and close the gdb subprocess
        gmi_gdb_exit(gdb_handle);
        mi_disconnect(gdb_handle);

        return 0;
}

/// @brief       Register a breakpoint with the VM debugger
/// @param[in]   a_breakpoint     Breakpoint to register with the VM debugger
/// @return      0 on success, -1 on failure
int gdb_iface::register_breakpoint(breakpoint *a_breakpoint)
{

        string l_breakpoint = "*";

        // sanity check
        if (a_breakpoint == NULL) {
                // invalid breakpoint

                VDEBUG(0, "Error registering breakpoint.");
                return -1;

        }

        // insert a new breakpoint
        a_breakpoint->gdb_breakpoint = gmi_break_insert_full(gdb_handle,   // habdle of the GDB instance
                                                             0,            // is the breakpoint temporary?
                                                             0,            // set hardware breakpoint?
                                                             NULL,         // condition to break on
                                                             -1,           // number of hits to ignore before next break
                                                             -1,           // thread
                                                             a_breakpoint->breakpoint_symbol.toStdString().c_str());  // address/symbol to break on

        if (a_breakpoint->gdb_breakpoint == NULL) {
                // error registering breakpoint

                VDEBUG(0, "Error registering breakpoint.");
                return -1;

        }

        return 0;

}

/// @brief      Load the available types from the GDB instance
vector <QString> gdb_iface::load_available_types()
{
    if (!mi_send(gdb_handle, "-symbol-list-types \r\n")) {
        VDEBUG(0, "Error: Unable to get symbol list");
    }
    return vector <QString>();

}


/// @brief       Remove a breakpoint from the VM debugger
/// @param[in]   a_breakpoint     Breakpoint to remove from the VM debugger
/// @return      0 on success, -1 on failure
int gdb_iface::unregister_breakpoint(const breakpoint *a_breakpoint)
{

        // delete the breakpoint
        if (!gmi_break_delete(gdb_handle, a_breakpoint->gdb_breakpoint->number))
                // failed
                return -1;

        return 0;

}

/// @brief       Get a snapshot of the VM state (including CPU registers, stack contents, etc.)
/// @param[out]  o_snapshot     Snapshot data to populate
/// @return      0 on success, -1 on failure
int gdb_iface::collect_snapshot()
{

        // BB TODO: create and register a new breakpoint and
        //          snapshot.

        return 0;

}

/// @brief       Pause the VM
/// @param[out]  o_snapshot     Snapshot data to populate
/// @param[out]  o_breakpoint   Breakpoint to populate
/// @return      0 on success, -1 on failure
int gdb_iface::pause()
{

        // interrupt the VM
        if (!gmi_exec_interrupt(gdb_handle)) {
                // error

                VDEBUG(0, "Error attempting to pause the VM");
                return -1;

        }

        if (collect_snapshot() != 0) {
                // error

                VDEBUG(0, "Error getting snapshot from paused VM");
                return -1;

        }
        // success

        return 0;

}


/// @brief       Resume the VM
/// @return      0 on success, -1 on failure
int gdb_iface::resume()
{

        // resume VM execution
        if (!gmi_exec_continue(gdb_handle)) {
                // error

                VDEBUG(0, "Error attempting to resume the VCPU" << endl);
                return -1;

        }
        // success

        return 0;

}


/// @brief       Step into the next instruction (or a_step_count instructions), then pause the VM
/// @param[out]  o_snapshot     Snapshot data to populate
/// @param[out]  o_breakpoint   Breakpoint to populate
/// @param[in]   o_step_count   Number of steps to take before breaking
/// @return      0 on success, -1 on failure
int gdb_iface::step(uint64_t a_step_count)
{

        // interrupt the VM
        if (!gmi_exec_step_instruction(gdb_handle)) {
                // error

                VDEBUG(0, "Error occured while trying to single-step the VCPU.");
                return -1;

        }

        if (collect_snapshot() != 0) {
                // error

                VDEBUG(0, "An error occured while trying to get a snapshot from the current step");
                return -1;

        }
        // success

        return 0;

}

/// @brief       Resume the VM until the next time a_breakpoint is hit
/// @param[in]   o_snapshot     Snapshot data to populate
/// @param[out]  a_breakpoint   Breakpoint to continue to
/// @return      0 on success, -1 on failure
int gdb_iface::resume_until_bp(const breakpoint &a_breakpoint)
{

        if (!gmi_exec_until_addr(gdb_handle, reinterpret_cast <void *>(a_breakpoint.breakpoint_address))) {
                // error

                VDEBUG(0, "Error occured while attempting to continue until breakpoint " << a_breakpoint.breakpoint_name << ".");
                return -1;

        }

        if (collect_snapshot() != 0) {
                // error

                VDEBUG(0, "An error occured while trying to get a snapshot from the current step");
                return -1;

        }
        // success

        return 0;


}

// resume the VM until return of the current function
//int gdb_iface::resume_until_return();
//
// BB TODO: determine if gdb/mi supports this over the QEMU+GDB or VMWare stub.
//          this function will be dropped otherwise.
//
// -exec-finish [--reverse]

//
// GDB/MI callbacks
//

// console output callback
void gdb_iface::cb_console(const char *a_str, void *a_data)
{
        VDEBUG(5, a_str);
}

void gdb_iface::cb_target(const char *a_str, void *a_data)
{
        VDEBUG(5, a_str);
}

void gdb_iface::cb_log(const char *a_str, void *a_data)
{
        VDEBUG(5, a_str);
}

void gdb_iface::cb_async(mi_output *a_output, void *a_data)
{
        VDEBUG(5, "Got async callback.");
}

void gdb_iface::cb_to_gdb(const char *a_str, void *a_data)
{
        VDEBUG(5, a_str);
}

void gdb_iface::cb_from_gdb(const char *a_str, void *a_data)
{
        VDEBUG(5, a_str);
}













