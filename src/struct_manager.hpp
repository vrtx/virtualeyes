///////////////////////////////////////////////////////
// virtualeyes
//
// Copyright (c) 2011 - 2011 Benjamnin Becker
// All Rights Reserved
//
// @brief   This file defines the main window and layout
// @author  ben
// @date    9/19/2011
///////////////////////////////////////////////////////

#ifndef STRUCT_MANAGER_HPP
#define STRUCT_MANAGER_HPP

#include "common.hpp"
#include "enum_convert.hpp"
//#include "struct_model.hpp"

namespace veyes {

// Type Defs
////////////

// struct defining a struct's member data
typedef struct {
    QString name;                  // member name
    int type;            		   // type (member_type_t enum) of the member  TODO: use type-safe enums when c++0x support is added to llvm
    uint16_t deref_depth;          // levels of indirection (e.g. char **a = 2)
    bool deref_is_array;           // is the member a reference to an array?
    bool is_array;                 // is the member an array?
    uint64_t offset;               // offset within region to the member
    uint64_t size;                 // size of the member entry within region
    QString value_as_text;         // value of the member in human-readable text
} struct_member_t;

// ordered container for struct members
typedef multiset <struct_member_t, compare_offset_less <struct_member_t> > struct_members_t;

// set of struct member names and region offsets
typedef struct _vstruct_t {
    string name;                   // name of the struct
    string uri;                    // logical organization of this and related structures (e.g. parsed from source, manual, local system, etc.)
    struct_members_t members;      // set of members within this struct
    vector <_vstruct_t> children;  // nested children of this struct
} struct_t;

//////////////////////////////////////////
///
/// @brief  NOTE: This class is to be instantiated using the global<> accessor.
///               e.g. global <struct_manager>().do_something();
///
//////////////////////////////////////////
class struct_manager
{
public:

    set <struct_t, comp_struct_locator <struct_t> > structs;

    struct_manager();
    virtual ~struct_manager();

    void init_store();
    void migrate_store();
    void add_struct(const struct_t &a_struct);
    void add_struct_from_string();

    // Class Variables
    static struct_manager *instance;  // singleton reference

};

}

#endif // STRUCT_MANAGER_HPP
