///////////////////////////////////////////////////////
// virtualeyes
//
// Copyright (c) 2011 Benjamnin Becker
// All Rights Reserved
//
/// @author  Ben Becker
/// @date    7/9/11
///////////////////////////////////////////////////////

#ifndef VIRTUALEYES_GLOBAL_HPP
#define VIRTUALEYES_GLOBAL_HPP

#include "vexcept.hpp"
#define PTR_INVALID 1

namespace veyes
{

        ///////////////////////////////////////////////////////
        /// @class   global
        /// @brief   This template defines a wrapper for classes that
        ///          nomally follow the singleton pattern.  This interface
        ///          is used instead of the traditional '::instance' method
        ///          so the logic can be changed at any time.
        ///
        ///          NOTE:  The templated class should define private
        ///          constructor(s), destructor(s), and a static 'instance' pointer.
        ///
        ///          For efficiency, when accessing a global<>'s methods multiple
        ///          times, create a local global<>, then use the dereference (->)
        ///          operator for subsequent calls.  e.g.
        ///          @code
        ///              global <my_manager> mgr;
        ///              mgr->give_riase();
        ///              mgr->add_carrot();
        ///              ...
        ///          @endcode
        ///          RATIONALE:
        ///          thread-safety and centralized logic for modifying DCLP or similar
        ///          patterns.
        ///////////////////////////////////////////////////////
        template <typename _Tp>
        class global
        {

        public:
                // Member Variables
                _Tp *raw_ptr;                           // underlying object to wrap

                // Member Functions
                global();                               // default ctor
                virtual ~global();                      // dtor
                virtual void destroy();                 // destroy the singleton/global object
                inline _Tp *operator->() const;         // dereference operator
                bool is_valid() const;                  // is the global object valid?

        };

        /// @brief    Default constructor
        template <typename _Tp>
        global <_Tp>::global()
        {

                // create a new instance
                if (_Tp::instance == NULL) {
                        _Tp::instance = new _Tp;
                }

                // cache the pointer
                raw_ptr = _Tp::instance;

        }


        /// @brief    Destructor
        template <typename _Tp>
        global <_Tp>::~global()
        {

            // this could handle a refcount or scoped locking in the future...

        }

        /// @brief    Destroyer -- destroy the allocated global
        template <typename _Tp>
        void global <_Tp>::destroy()
        {

            if (_Tp::instance != NULL) {
                delete _Tp::instance;
                _Tp::instance = reinterpret_cast <_Tp *>(PTR_INVALID);
            }

        }

        /// @brief    Check if a global object is valid
        template <typename _Tp>
        bool global <_Tp>::is_valid() const
        {
                return (reinterpret_cast <void *>(raw_ptr) != reinterpret_cast <void *>(PTR_INVALID));
        }

        /// @brief    Dereference operator
        template <typename _Tp>
        _Tp *global <_Tp>::operator->() const
        {
                if (raw_ptr != reinterpret_cast <void *>(PTR_INVALID)) {
                        return raw_ptr;
                } else {
                        string err = "Error: Unable to dereference global object ";
                        err += typeid(_Tp).name();
                        err += ".  Reason: Object was already destroyed!";
                        throw(vexcept(err));
                }
        }

}


#endif
