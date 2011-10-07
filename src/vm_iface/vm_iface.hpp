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

#ifndef VIRTUALEYES_VM_IFACE_HPP
#define VIRTUALEYES_VM_IFACE_HPP

//
// Includes
//
#include "common.hpp"
#include "handle_base.hpp"

namespace veyes
{

        //
        // Forward Declarations
        //
        class breakpoint;


        ///////////////////////////////////////////////////////
        //
        /// @class   vm_iface
        /// @brief   This class defines the abstract base for the VM debugger.
        //
        ///////////////////////////////////////////////////////
        class vm_iface : public handle_base
        {

        public:

                //
                // Member Functions
                //

                // default ctor
                vm_iface();

                // copy ctor
                vm_iface(const vm_iface &a_vm_iface);

                // dtor
                virtual ~vm_iface();

                // connect to the VM debugger
                virtual int connect();

                // disconnect from the VM debugger
                virtual int disconnect();

                // add a breakpoint
                virtual int register_breakpoint(breakpoint *a_breakpoint);

                // delete a breakpoint
                virtual int unregister_breakpoint(const breakpoint *a_breakpoint);

                // pause the VM
                virtual int pause();

                // create a snapshot from the current state
                virtual int collect_snapshot();

                // resume the VM
                virtual int resume();

                // step into the next instruction (or a_step_count instructions), then pause the VM
                virtual int step(uint64_t a_step_count = 1);

                // resume the VM until the next instance of a_breakpoint
                virtual int resume_until_bp(const breakpoint &a_breakpoint);

               // // resume the VM until return of the current function
               // virtual int resume_until_return();



        };

}

#endif
