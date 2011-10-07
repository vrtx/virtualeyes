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

#ifndef VIRTUALEYES_OS_NONE_POLICY_HPP
#define VIRTUALEYES_OS_NONE_POLICY_HPP

//
// Includes
//
#include "common.hpp"
#include "enum_convert.hpp"

namespace veyes
{

        ///////////////////////////////////////////////////////
        //
        /// @class   os_none
        /// @brief   This policy class defines the interface to an undefined or
        ///          nonexistent guest operating system.
        //
        ///////////////////////////////////////////////////////
        class os_none
        {
        public:

                //
                // Constant Declarations
                //
                static const opsys_t os_type = opsys_t::none;
                static const uint32_t os_version = 0;
                static const uint32_t os_version_minor = 0;

        };

}


#endif
