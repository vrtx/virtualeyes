///////////////////////////////////////////////////////
// virtualeyes
//
// Copyright (c) 2011 Benjamnin Becker
// All Rights Reserved
//
/// @author  Ben Becker
/// @date    4/11/11
///////////////////////////////////////////////////////

#ifndef VIRTUALEYES_HANDLE_HPP
#define VIRTUALEYES_HANDLE_HPP

// Includes
#include "handle_base.hpp"
#include "common.hpp"
#include "debug.hpp"

#ifdef DEBUG_ALLOCATIONS
#  undef VREF_TRACE
#  define VREF_TRACE(...)  cout << debug_log::generate_prefix(__FILE__, __LINE__, __FUNCTION__).toStdString() << __VA_ARGS__ << endl;
#else
#  undef VREF_TRACE
#  define VREF_TRACE(...) do {} while (0)
#endif


namespace veyes
{

        template <typename _Tp>
        class soft_handle;

        ///////////////////////////////////////////////////////
        /// @class   handle
        /// @brief   This class defines the generic smart pointer implementation
        ///          for memeory refcounting and GC.  Reference counts are used to
        ///          form a simple 'chain of custody' for objects shared within the
        ///          the application.  The constructor and '=' operator take a pointer to
        ///          the object allocated on the heap.  It will be deleted/destructed
        ///          automatically once the last handle<> goes out of scope.
        ///
        ///          Use a soft_handle to reference an object that does not affect
        ///          the refrence count of a shared object.  This is useful for maintaining
        ///          backwards references when there is a clear chain of custody.  That is,
        ///          an object can create a child object that has a soft_handle to it's parent.
        ///          handle<>s and soft_handle<>s can be casted at any point, and all refcounts
        ///          will be updated.
        ///////////////////////////////////////////////////////
        template <typename _Tp>
        class handle
        {

        public:

                // Member Variables
                _Tp *raw_ptr;                           // underlying object the handle is for
                bool is_mutable;                        // is the object's handle mutable?
                int64_t id;                             // id of the object we have a handle to


                // Member Functions
                handle();                               // default ctor
                handle(_Tp *a_raw_object);              // initializing ctor
                virtual ~handle();                      // dtor
                handle(const handle <_Tp> &a_handle);   // copy ctor
                handle(const soft_handle <_Tp> &a_handle); // copy ctor
                bool is_valid() const;                  // is the referenced object valid?
                void fetch_mutable();                   // reference the object with write-safe access
                void fetch_immutable();                 // reference the object with read-only access
                virtual void inc_refcount();            // helper
                virtual void dec_refcount();            // helper


                // Operator Overloads
                inline _Tp &operator*() const;                                   // Dereference operator
                inline _Tp *operator->() const;                                  // Dereference operator
                virtual handle <_Tp> &operator=(const handle <_Tp> &a_rhs);      // Assignment operator (handle)
                virtual handle <_Tp> &operator=(const soft_handle <_Tp> &a_rhs); // Assignment operator (soft_handle)
                virtual handle <_Tp> &operator=(_Tp *a_rhs);                     // Assignment operator (raw pointer)
//                virtual handle <_Tp> &operator=(const _Tp *&a_rhs);            // Assignment operator (raw pointer)


        };

        /// @brief    Default constructor
        template <typename _Tp>
        handle <_Tp>::handle() :
                raw_ptr(NULL),
                is_mutable(false),
                id(0)
        {

        }

        /// @brief    Initializing constructor
        template <typename _Tp>
        handle <_Tp>::handle(_Tp *a_raw_object) :
                raw_ptr(a_raw_object),
                is_mutable(false),
                id(0)
        {

                // sanity check
                if (a_raw_object == NULL) {
                        // uninitialized pointer

                        // throw(vexcept("Unable to generate a handle to access NULL object"));

                } else {
                        // (seemingly) valid pointer

                        VREF_TRACE("  +REF: Accessing object: [type:" << typeid(_Tp).name() << "] [id:" << id << "] [addr:" << raw_ptr << "] via construction");
                        id = a_raw_object->v_id;
                        inc_refcount();

                }

        }

        /// @brief    Copy constructor
        template <typename _Tp>
        handle <_Tp>::handle(const handle <_Tp> &a_handle) :
                raw_ptr(a_handle.raw_ptr),
                is_mutable(a_handle.is_mutable),
                id(a_handle.id)
        {

                VREF_TRACE("  +REF: Copying and updating refcounts for object: [type:" << typeid(_Tp).name() << "] [id:" << id << "] [addr:" << raw_ptr << "]");
                inc_refcount();

        }

        /// @brief    Copy constructor
        template <typename _Tp>
        handle <_Tp>::handle(const soft_handle <_Tp> &a_handle) :
                raw_ptr(a_handle.raw_ptr),
                is_mutable(a_handle.is_mutable),
                id(a_handle.id)
        {

                // sanity check
                if (!a_handle.is_valid()) {

                        throw(vexcept("Unable to convert from an invalid soft_handle to a base handle.  Use the assignment operator if a soft_handle may be invalid."));

                }


                VREF_TRACE("  +REF: Copying and updating refcounts for object: [type:" << typeid(_Tp).name() << "] [id:" << id << "] [addr:" << raw_ptr << "]");
                inc_refcount();


        }

        /// @brief    Destructor
        template <typename _Tp>
        handle <_Tp>::~handle()
        {

                // sanity check
                if (!is_valid() || raw_ptr == NULL)
                        // attempt to free an uninitialized handle
                        return;

                VREF_TRACE("  -REF: Removing reference to object: [type:" << typeid(_Tp).name() << "] [id:" << id << "] [addr:" << raw_ptr << "].");
                dec_refcount();

                // free the object if there are no more references
                if (raw_ptr->v_read_count == 0 &&
                    raw_ptr->v_write_count == 0) {
                        // object has no more references

                        VREF_TRACE("~DALOC: Final reference removed.  Freeing object [type:" << typeid(_Tp).name() << "] [id:" << id << "] [addr:" << raw_ptr << "].");
                        delete raw_ptr;

                }

        }

        /// @brief    Dereference operator
        template <typename _Tp>
        _Tp *handle <_Tp>::operator->() const {
                return raw_ptr;
        }

        /// @brief    Dereference operator
        template <typename _Tp>
        _Tp &handle <_Tp>::operator*() const {
                return *raw_ptr;
        }

        /// @brief     Assignment operator (handle)
        template <typename _Tp>
        handle <_Tp> &handle <_Tp>::operator=(const handle <_Tp> &a_rhs) {
                // copy the handle values

                raw_ptr = a_rhs.raw_ptr;
                is_mutable = a_rhs.is_mutable;
                id = a_rhs.id;
                VREF_TRACE("  +REF: Assigning and updating refcounts for object: [type:" << typeid(_Tp).name() << "] [id:" << id << "] [addr:" << raw_ptr << "]");
                inc_refcount();

                return *this;

        }

        /// @brief     Assignment operator (soft_handle)
        template <typename _Tp>
        handle <_Tp> &handle <_Tp>::operator=(const soft_handle <_Tp> &a_rhs) {
                // copy the handle values

                return operator=(a_rhs);

        }

        /// @brief     Assignment operator (raw pointer)
        template <typename _Tp>
        handle <_Tp> &handle <_Tp>::operator=(_Tp *a_rhs) {

                // copy the raw pointer and populate 'this' handle
                raw_ptr = a_rhs;
                is_mutable = false;

                // sanity check
                if (raw_ptr == NULL) {
                        // uninitialized pointer

                        id = 0;
                        // throw(vexcept("Unable to generate a handle to access NULL object"));

                } else {
                        // (seemingly) valid pointer

                        id = raw_ptr->v_id;
                        VREF_TRACE("  +REF:  Assigning reference to object: [type:" << typeid(_Tp).name() << "] [id:" << id << "] [addr:" << raw_ptr << "] from raw pointer.");
                        inc_refcount();

                }

                return *this;

        }

        /// @brief    is this handle valid?
        template <typename _Tp>
        bool handle <_Tp>::is_valid() const
        {

                return (id == 0 ? false : (global_handle::global_handle_map.find(id) != global_handle::global_handle_map.end()));

        }

        /// @brief    make this handle mutable
        template <typename _Tp>
        void handle <_Tp>::fetch_mutable()
        {

                if (is_valid() &&
                    !is_mutable &&
                    raw_ptr != NULL) {
                        // referenced object is valid and immutable

                        // TODO: for concurrency, we need to wait here until all read locks are freed.

                        ++raw_ptr->v_write_count;
                        --raw_ptr->v_read_count;
                        is_mutable = true;
                        VREF_TRACE("=REFERENCE_SWAP: Fetching mutabile version of " << typeid(_Tp).name() << " @ " << raw_ptr
                              << ".  WRITE count: " << raw_ptr->v_write_count
                              << ".  READ count: " << raw_ptr->v_read_count);

                }

        }

        /// @brief    make this handle mutable
        template <typename _Tp>
        void handle <_Tp>::fetch_immutable()
        {

                if (is_valid() &&
                    is_mutable &&
                    raw_ptr != NULL) {
                        // referenced object is valid and mutable

                        --raw_ptr->v_write_count;
                        ++raw_ptr->v_read_count;
                        is_mutable = false;
                        VREF_TRACE("=REFERENCE_SWAP: Fetching immutabile version of " << typeid(_Tp).name() << " @ " << raw_ptr
                              << ".  WRITE count: " << raw_ptr->v_write_count
                              << ".  READ count: " << raw_ptr->v_read_count);

                }

        }

        /// @brief    Decrement the reference count based on mutability
        template <typename _Tp>
        void handle <_Tp>::dec_refcount()
        {

                if (is_valid() && raw_ptr != NULL) {
                        // referenced object is valid

                        if (is_mutable)
                                // decerement write count
                                --raw_ptr->v_write_count;
                        else
                                // decrement read count
                                --raw_ptr->v_read_count;

                }

                VREF_TRACE("  \\_____[refcount read=" << raw_ptr->v_read_count << " write=" << raw_ptr->v_write_count << "]");

        }

        /// @brief    Decrement the reference count based on mutability
        template <typename _Tp>
        void handle <_Tp>::inc_refcount()
        {

                if (is_valid() && raw_ptr != NULL) {
                        // referenced object is valid

                        if (is_mutable)
                                // decerement write count
                                ++raw_ptr->v_write_count;
                        else
                                // decrement read count
                                ++raw_ptr->v_read_count;

                }

                VREF_TRACE("  \\_____[refcount read=" << raw_ptr->v_read_count << " write=" << raw_ptr->v_write_count << "]");

        }

}


#endif
