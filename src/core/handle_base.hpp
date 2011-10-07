///////////////////////////////////////////////////////
//
// virtualeyes
//
// Copyright (c) 2011 Benjamnin Becker
// All Rights Reserved
//
/// @author  Ben Becker
/// @date    4/12/11
//
///////////////////////////////////////////////////////

#ifndef VIRTUALEYES_HANDLE_BASE_HPP
#define VIRTUALEYES_HANDLE_BASE_HPP

#include "common.hpp"

namespace veyes
{

        // Forward Declarations
        class handle_base;

        // Type Definitions
        typedef map <uint64_t, handle_base *> handle_map_t;

        class global_handle {
        public:
                // Class Variables
                static int64_t global_handle_index;
                static handle_map_t global_handle_map;
        };

        ///////////////////////////////////////////////////////
        //
        /// @class   handle_base
        /// @brief   This class defines the base class used to
        ///          control access to all handles in the session graph.
        //
        ///////////////////////////////////////////////////////
        class handle_base
        {

        public:
                // Member Variables
                uint64_t v_id;                               // unique, ordered id of this handle
                uint32_t v_read_count;                       // number of handles with read references
                uint32_t v_write_count;                      // number of handles with write references

                // Member Functions
                handle_base();
                handle_base(const handle_base &a_handle_base);
                virtual ~handle_base();

        private:

                // Member Variables

        };

}


#endif
