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

#ifndef VIRTUALEYES_TARGET_HOST_HPP
#define VIRTUALEYES_TARGET_HOST_HPP

//
// Includes
//
#include "common.hpp"


namespace veyes 
{

        ///////////////////////////////////////////////////////
        //
        /// @class   target_host
        /// @brief   This policy class defines the environment
        ///          of the target virtual machine,
        //
        ///////////////////////////////////////////////////////
        template <typename _Platform, typename _OS>
        class target_host : public _Platform,
                            public _OS
        {

        public:
                //
                // Memeber Variables
                //

                // structure representing cpu registers
                typename _Platform::cpu_registers_t cpu_registers;

                //
                // Member Functions
                //

                // default ctor
                target_host() :
                        _Platform(),
                        _OS()
                {

                };

                // dtor
                virtual ~target_host()
                {

                };

                // copy ctor
                target_host(const target_host &a_target_host);

                // generic fetch routines
                uint8_t fetch_uint8(const uint64_t &a_address);
                uint16_t fetch_uint16(const uint64_t &a_address);
                uint32_t fetch_uint32(const uint64_t &a_address);
                uint64_t fetch_uint64(const uint64_t &a_address);

                // kernel/boot addr fetch routines
                static typename _Platform::word_size_t fetch_kernel_base_va();
                static typename _Platform::word_size_t fetch_kernel_entry_va();

        };

}


#endif
