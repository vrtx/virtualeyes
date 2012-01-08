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

#ifndef VIRTUALEYES_WIN2K8_POLICY_HPP
#define VIRTUALEYES_WIN2K8_POLICY_HPP

//
// Includes
//
#include "common.hpp"
#include "enum_convert.hpp"

namespace veyes
{

        ///////////////////////////////////////////////////////
        //
        /// @class   win2k8
        /// @brief   This policy class defines the interface to the Windows Server 2008
        ///          guest operating system.
        //
        ///////////////////////////////////////////////////////
        class win2k8
        {
        public:

                //
                // Constant Declarations
                //
                static const int os_type = opsys_t::winnt;
                static const uint32_t os_version = 6;
                static const uint32_t os_version_minor = 0;

        };

}


#endif
