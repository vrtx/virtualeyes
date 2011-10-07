///////////////////////////////////////////////////////
//
// virtualeyes
//
// Copyright (c) 2011 Benjamnin Becker
// All Rights Reserved
//
/// @author  Ben Becker
/// @date    4/17/11
//
///////////////////////////////////////////////////////

#ifndef VIRTUALEYES_SOFT_HANDLE_HPP
#define VIRTUALEYES_SOFT_HANDLE_HPP

// Includes
#include "handle.hpp"

namespace veyes
{

        ///////////////////////////////////////////////////////
        //
        /// @class   handle
        /// @brief   This class defines the generic container for
        ///          all soft_handles in the session (that is, handles
        ///          that do not affect reference counting).
        //
        ///////////////////////////////////////////////////////
        template <typename _Tp>
        class soft_handle : public handle <_Tp>
        {

        public:
                soft_handle() :                                  // default ctor
                        handle <_Tp>() {};
                soft_handle(_Tp *a_raw_object) :                 // initializing ctor
                        handle <_Tp>(a_raw_object) {};
                soft_handle(const soft_handle <_Tp> &a_soft_handle) :  // copy ctor (from soft_handle)
                        handle <_Tp>(a_soft_handle) {};
                soft_handle(const handle <_Tp> &a_handle) :      // copy ctor (from handle)
                        handle <_Tp>(a_handle) {};

                virtual void inc_refcount();                     // helper
                virtual void dec_refcount();                     // helper

        };

        /// @brief    Decrement the reference count based on mutability (NOTE: this is not done for soft handles)
        template <typename _Tp>
        void soft_handle <_Tp>::dec_refcount()
        {

                // VDEBUG(9, "Removing SOFT handle reference from base object.");
                // if (is_vald())
                //         VDEBUG(9, "Reference counts: READ: " << raw_ptr->read_count << " WRITE: " << raw_ptr->write_count);

        }

        /// @brief    Decrement the reference count based on mutability (NOTE: this is not done for soft handles)
        template <typename _Tp>
        void soft_handle <_Tp>::inc_refcount()
        {


                // VDEBUG(9, "Adding SOFT handle reference from base object.");
                // if (is_vald())
                //         VDEBUG(9, "Reference counts: READ: " << raw_ptr->read_count << " WRITE: " << raw_ptr->write_count);

        }

}


#endif
