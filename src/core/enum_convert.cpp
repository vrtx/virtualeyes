///////////////////////////////////////////////////////
// virtualeyes
//
// Copyright (c) 2011 - 2011 Benjamnin Becker
// All Rights Reserved
//
// @brief   This file defines the main window and layout
// @author  ben
// @date    9/25/2011
///////////////////////////////////////////////////////

#include "enum_convert.hpp"

namespace veyes {

// Helper: add the key and value of an enum translation:  ENUM_PAIR(0, "Something");
#define ENUM_PAIR(eidx, estr)                                               \
    enum_map.insert(enum_pair_t(static_cast <enum_idx_t>(eidx), estr))      \

// Helper: specialized map initialization functions
#define ADD_TRANSLATIONS(a_enum_type, ...)                                  \
                                                                            \
    /* create the map for the given enum */                                 \
    template <>                                                             \
    enum_map_t enum_convert <a_enum_type>::enum_map = enum_map_t();         \
                                                                            \
    /* create the map for the given enum */                                 \
    template <>                                                             \
    void enum_convert <a_enum_type>::init() { __VA_ARGS__ }                 \


//////////////////////////////////////////
//
// Add All Enum Translation Mappings Here:
//
//////////////////////////////////////////

// member_type_t
ADD_TRANSLATIONS(member_type_t, {
    ENUM_PAIR(member_type_t::e_int,    "signed int");
    ENUM_PAIR(member_type_t::e_uint,   "unsigned int");
    ENUM_PAIR(member_type_t::e_float,  "signed float");
    ENUM_PAIR(member_type_t::e_ufloat, "unsigned float");
    ENUM_PAIR(member_type_t::e_bool,   "bool");
    ENUM_PAIR(member_type_t::e_char,   "char");
    ENUM_PAIR(member_type_t::e_struct, "struct");
    ENUM_PAIR(member_type_t::e_union,  "union");
})

// region_type_t
ADD_TRANSLATIONS(region_type_t, {
    ENUM_PAIR(region_type_t::guest_virtual,  "Guest Virtual Memory");
    ENUM_PAIR(region_type_t::guest_physical, "Guest Physical Memory");
    ENUM_PAIR(region_type_t::guest_disk,     "Guest Disk");
    ENUM_PAIR(region_type_t::guest_cpu,      "Guest CPU");
    ENUM_PAIR(region_type_t::host_virtual,   "Host Virtual");
    ENUM_PAIR(region_type_t::host_physical,  "Host Physical");
    ENUM_PAIR(region_type_t::host_file,      "Host File");
    ENUM_PAIR(region_type_t::host_disk,      "Host Disk");
})

// opsys_t
ADD_TRANSLATIONS(opsys_t, {
    ENUM_PAIR(opsys_t::none,   "No Operating System Detected");
    ENUM_PAIR(opsys_t::bare,   "Bare Metal Operating System");
    ENUM_PAIR(opsys_t::linux,  "Linux");
    ENUM_PAIR(opsys_t::bsd,    "BSD");
    ENUM_PAIR(opsys_t::winnt,  "Windows NT-based");
    ENUM_PAIR(opsys_t::mach_o, "Mac OS X or Mach-O");
})

/// @brief Initialize all of the enum mappings
void enum_initializer()
{

    /////////////////////////////////////////
    //
    // Initialize Enum Translation Maps Here:
    //
    /////////////////////////////////////////

    enum_convert <member_type_t>::init();
    enum_convert <region_type_t>::init();
    enum_convert <opsys_t>::init();

} // end enum init

} // namespace

#undef ENUM_PAIR
#undef ADD_TRANSLATIONS


