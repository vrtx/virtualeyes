///////////////////////////////////////////////////////
// virtualeyes
//
// Copyright (c) 2011 Benjamnin Becker
// All Rights Reserved
//
/// @brief   This file defines the data region that represents a portion of
///          guest memory and various methods of displaying it (hex, ascii, structure and assembly).
/// @author  Ben Becker
/// @date    2/3/11
///////////////////////////////////////////////////////

#ifndef VIRTUALEYES_MEMORY_REGION_HPP
#define VIRTUALEYES_MEMORY_REGION_HPP

// Includes
///////////
#include "common.hpp"
#include "soft_handle.hpp"
#include "handle_base.hpp"
#include "struct_manager.hpp"

namespace veyes
{

//
// TODO: Left off here.  implement functions to save struct data (persistently).
//

// Example of adding a structure to storage:
// -----------------------------------------
//    NOTE: assumes this struct is loaded from '/abs/path/to/test.h' on local file system and the target host is x86_64
//
// struct example {
//     uint64_t index;                  // offset: 0  size: 8
//     string *name;                    // offset: 8  size: 8
//     struct nest {                    // offset: 16 size: 8
//         struct some_t *nested_ref;   // offset: 16 size: 8
//     }                                // offset: 24 size: 8
//     union u {                        // offset: 24 size: 8
//         struct some_t *some;         // offset: 24 size: 8
//         struct other_t *other;       // offset: 24 size: 8
//         char small;                  // offset: 24 size: 1
//     }
//     int fn(char *arg);
// }                                    // total size: 25 bytes (assumes packed)
//
//  Code for insertion (WIP):
//                                                                                                           // Data being stored:
//                                                                                                           // --------------------
//   memory_region->structure = new struct_t('example'); // TODO: hash?  uri?                                // struct:    example
//   global <struct_manager>()->add(memory_region->structure);                                               // struct:    example
//   // generate nested structure 'nest' if it doesn't exist
//   struct_t nested_struct;                                                                                 // struct:    nest
//   memory_region->structure.children[0] = nested_struct;                                                   // substruct: example.nest
//   nested_struct.name = "nest";
//   nested_struct.uri = "some/uri/";
//   global <struct_manager>()->add(nested_struct);                                                          // struct:    nest
//
//                                              name       type,    struct_id, offset, size
//                                              --------------------------------------------
//   nested_struct.members.insert(            { "nested_ref", e_ptr, 10,       16,     8    } );             // member:    nested_ref
//   memory_region->structure.members.insert( { "index",   e_int,    NULL,     0,      8    } );             // member:    index
//   memory_region->structure.members.insert( { "name",    e_ptr,    NULL,     8,      8    } );             // member:    name
//   memory_region->structure.members.insert( { "nest",    e_struct, 2,        16,     8    } );             // member:    nest
//   memory_region->structure.members.insert( { "u",       e_union,  NULL,     24,     8    } );             // member:    u
//   memory_region->structure.members.insert( { "some",    e_ptr,    2,        24,     8    } );             // member:    some
//   memory_region->structure.members.insert( { "other",   e_ptr,    3,        24,     8    } );             // member:    other
//   memory_region->structure.members.insert( { "small",   e_char,   NULL,     24,     1    } );             // member:    small
//
//   // collect and reference any foriegn memory regions for 'name'
//   if (!(refd_region = memory_region::store.find( /* 'name' pointer */, sizeof(string) )))                 // value:     *name
//       refd_region = vm_iface->collect_region(memory_region->raw.data().substr(8, 8), 8);                  // value:     *name
//   memory_region->references.insert(pair(8, refd_region));                                                 // ref:       name -> mr
//
//   // collect and reference any foriegn memory regions for 'nested_ref'
//   if (!(refd_region = memory_region::store.find( /* nest.nested_ref ptr */, sizeof(some_t) )))            // value:     *nest.nested_ref
//       refd_region = vm_iface->collect_region(memory_region->raw.data().substr(16, 8), nested_struct.size);// value:     *nest.nested_ref
//   memory_region->references.insert(pair(16, refd_region));                                                // ref:       nest.nested_ref -> mr
//
//   // collect and reference any foriegn memory regions for 'u':
//   union_max = MAX(sizeof(some_t), sizeof(other_t));
//   if (!(refd_region = memory_region::store.find( /* (ptr)u.* */, union_max )))                            // value:     *u.some, *u.other
//       refd_region = vm_iface->collect_region(memory_region->raw.data().substr(24, 8), union_max);         // value:     *u.some, *u.other
//   memory_region->references.insert(pair(24, refd_region));                                                // ref:       u.some or u.other -> mr

// Forward Declarations
class memory_region;

// Type definitions
typedef map <uint64_t, soft_handle <memory_region> >                foriegn_reference_map_t;   // map of references from local offset to memory region

// Container Type Definitions
typedef set <handle <memory_region>,
             compare_address_less <handle <memory_region> > >       memory_region_set_t;
typedef set <soft_handle <memory_region>,
             compare_address_less <soft_handle <memory_region> > >  memory_region_soft_set_t;
typedef memory_region_set_t                                         owned_memory_regions_t;
typedef memory_region_soft_set_t                                    soft_memory_regions_t;


///////////////////////////////////////////////////////
/// @class   memory_region
/// @brief   This class represents a region of memory and implements
///          support for the various representations of the data, eg.
///          hex, ascii, structure, disassembly, etc.
///////////////////////////////////////////////////////
class memory_region : public handle_base
{

public:

    // Member Variables
    ///////////////////
    uint64_t time;                      // time the memory region was collected
    uint64_t start_address;             // starting address of the memory region (usually guest virtual memory)
    foriegn_reference_map_t references; // map of references to foriegn memory regions
    struct_t structure;                 // container of all struct properties

    // Static Variables
    ///////////////////
    const static char enum_table[30][32];               // 30 enums srings, 32 chars long


    // Member Functions
    ///////////////////

    // default ctor
    memory_region();

    // initializing ctor
    memory_region(void *a_guest_virtual_address, uint64_t a_size, uint64_t a_breakpoint_id);

    // dtor
    virtual ~memory_region();

    // copy ctor
    memory_region(const memory_region &a_memory_region);

    // get a raw hex string of this (sub)region
    QString get_as_hex(int begin = 0, int end = 0);

    // get a structured representation of this region
    QString get_as_structured_text();

    // get the disassembled output from this region of memory
    string get_disassembly();

    // get region from member name
    // get region from local offset
    // add mapping to memory region from local offset (and optionally member name)

    // interpret this memory region as the given c struct
    int load_as_struct(const QString &a_struct);

    // native access: get a pointer to this region as type <_Struct>
    template <typename _Struct>
    const _Struct *cast_to_struct(const uint64_t a_offset = 0) const;

    // native access: return a newly allocated copy of the this region as type <_Struct>
    template <typename _Struct>
    _Struct fetch_struct(uint64_t a_offset = 0) const;

private:

    // Member Variables
    ///////////////////
    QString region_name;                    // user-defined name
    string raw;                             // copy of the raw data
    string disassembly;                     // string representation of disassembly
    uint64_t disassembly_start;             // address indicating start of disassembly
    region_type_t region_type;              // type of region (disk/file/physical/virtual/etc.)

public:

    // Visualization Functions
    //////////////////////////

    // render the current scene
    int render();


    // Testing
    /////////////
    void load_sample_data() {
        struct_member_t *a_test = new struct_member_t;  // leak
        a_test->name = "test_struct_member_t";
        a_test->offset = 8;
        a_test->size = 4;
        a_test->type = member_type_t::e_struct;
        raw = string(reinterpret_cast <char *>(a_test), sizeof(struct_member_t));
    }

};

// Generic Functions
////////////////////

/// @brief       Get a pointer to this region as <_Struct>
//               NOTE: memory is owned by the memory_region instance, and is only valid until
//                     the first call to a non-const member of raw_data.
/// @param[in]   a_offset    Offset into the memory region to cast as a struct
/// @return      The memory region cast to a _Struct
template <typename _Struct>
const _Struct *memory_region::cast_to_struct(const uint64_t a_offset) const
{
    // BB TODO:  Add sanity check for region bounds

    const _Struct *l_retval = new(raw.data() + a_offset) _Struct;
    return l_retval;
}

/// @brief       Get a copy of this region as <_Struct>
/// @param[in]   a_offset    Offset into the memory region to start copying from
/// @return      The memory region cast to a _Struct
template <typename _Struct>
_Struct memory_region::fetch_struct(uint64_t a_offset) const
{
    // BB TODO:  Add sanity check for region bounds

    _Struct l_retval;

    // create a copy of the struct
    l_retval = *reinterpret_cast <_Struct *>(raw.data() + a_offset);

    return l_retval;

}

}  // end namespace

#endif
