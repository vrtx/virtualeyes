///////////////////////////////////////////////////////
//
// virtualeyes
//
// Copyright (c) 2011 Benjamnin Becker
// All Rights Reserved
//
/// @author  Ben Becker
/// @date    3/6/11
//
///////////////////////////////////////////////////////

#ifndef VIRTUALEYES_X86_32_HPP
#define VIRTUALEYES_X86_32_HPP

//
// Includes
//
#include "common.hpp"
#include "opsys/os_none.hpp"

namespace veyes 
{

        ///////////////////////////////////////////////////////
        //
        /// @class   x86_32
        /// @brief   This class defines the 32-bit x86 hardware and data structures.
        /// @detail  This is a policy host for the _OS type as well as a policy 
        ///          class for target_host.
        //
        ///////////////////////////////////////////////////////
        class x86_32
        {
        public:

                //
                // Type Definitions
                //

                // target-specific type definitions
                typedef uint32_t word_size_t;

                // structure representing 32-bit x86 cpu registers
                typedef struct x86_cpu_register_t {

                        word_size_t eip;
                        word_size_t eax;
                        word_size_t ecx;
                        word_size_t edx;
                        word_size_t ebx;
                        word_size_t esp;
                        word_size_t ebp;
                        word_size_t esi;
                        word_size_t edi;

                        // segment registers
                        word_size_t es;
                        word_size_t cs;
                        word_size_t ss;
                        word_size_t ds;
                        word_size_t fs;
                        word_size_t gs;
                        word_size_t tr;
                        word_size_t ldtr;

                        // MSRs
                        word_size_t cr0;
                        word_size_t cr2;
                        word_size_t cr3;
                        word_size_t cr4;
                        word_size_t cr8;

                        // BB TODO: sse/additional registers

                } cpu_registers_t;

                //
                // Member Variables
                //

                // static values defining the target
                static const bool is_bigendian = false;
                static const uint16_t word_size = sizeof(word_size_t);
                static const uint16_t bootstrap_va = 0x7c00;


        };

}

#endif
