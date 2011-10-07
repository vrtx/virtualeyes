///////////////////////////////////////////////////////
//
// virtualeyes
//
// Copyright (c) 2011 Benjamnin Becker
// All Rights Reserved
//
/// @author  Ben Becker
/// @date    2/13/11
//
///////////////////////////////////////////////////////

#ifndef VIRTUALEYES_GDB_IFACE_HPP
#define VIRTUALEYES_GDB_IFACE_HPP

//
// Includes
//
#include "common.hpp"
#include <QObject>
#include <mi_gdb.h>
#include "vm_iface.hpp"
#include "handle_base.hpp"

namespace veyes {

        //
        // Forward Declarations
        //
        class breakpoint;



        ///////////////////////////////////////////////////////
        //
        /// @class   gdb_iface
        /// @brief   This class implementes the interface to a VM's GDB stub
        //
        ///////////////////////////////////////////////////////
        class gdb_iface : public QObject,
                          public vm_iface
        {

        public:

                //
                // Member Functions
                //

                // default ctor
                gdb_iface();

                // copy ctor
                gdb_iface(const gdb_iface &a_gdb_iface);

                // dtor
                virtual ~gdb_iface();

                // connect to the VM debugger
                int connect();

                // disconnect from the VM debugger
                int disconnect();

                // add a breakpoint
                int register_breakpoint(breakpoint *a_breakpoint);

                // delete a breakpoint
                int unregister_breakpoint(const breakpoint *a_breakpoint);

                // pause the VM
                int pause();

                // create a snapshot from the current state
                int collect_snapshot();

                // resume the VM
                int resume();

                // step into the next instruction (or a_step_count instructions), then pause the VM
                int step(uint64_t a_step_count = 1);

                // resume the VM until the next instance of a_breakpoint
                int resume_until_bp(const breakpoint &a_breakpoint);

                // load available types from the gdb iface
                vector <QString> load_available_types();

        //        // resume the VM until return of the current function
        //        int resume_until_return();

                // gdb/mi callbacks
                static void cb_console(const char *a_str, void *a_data);
                static void cb_target(const char *a_str, void *a_data);
                static void cb_log(const char *a_str, void *a_data);
                static void cb_async(mi_output *a_output, void *a_data);
                static void cb_to_gdb(const char *a_str, void *a_data);
                static void cb_from_gdb(const char *a_str, void *a_data);


        private:

                //
                // Member variables
                //
                mi_h *gdb_handle;

        };

}


#endif
