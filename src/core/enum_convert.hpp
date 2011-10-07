///////////////////////////////////////////////////////
// virtualeyes
//
// Copyright (c) 2011 - 2011 Benjamnin Becker
// All Rights Reserved
//
/// @brief   This file defines utilities for converting lightweight typesafe enums
///          to other representations.  e.g.  enum_convert <opsys_t>::to_string(opsys_t::winnt);
/// @note    The easiest way to add a new translation is to:
///          1) add the enum definition to this header (convention: keep all reusable enums in this file)
///          2) declare the the string representation of the enum in enum_convert.cpp
///             using the ADD_TRANSLATIONS() macro.
///          3) add a call to the new enum's init function in enum_initializer::init()
/// @todo    Remove step 3 and generate init function list dynamically
/// @author  ben
/// @date    9/25/2011
///////////////////////////////////////////////////////

#ifndef ENUM_CONVERT_HPP
#define ENUM_CONVERT_HPP

#include "common.hpp"
#include <QString>
#include <boost/bimap.hpp>

#define MAX_ENUM_TYPES 128

namespace veyes
{

// Type Definitions
typedef uint16_t enum_idx_t;
typedef boost::bimap <enum_idx_t, QString> enum_map_t;
typedef enum_map_t::value_type enum_pair_t;


////////////////////////////////////
//
// Global enum declarations go here:
//
////////////////////////////////////

// type of resource a memory region was acquired from
enum class region_type_t : enum_idx_t
{
    guest_virtual = 0,
    guest_physical,
    guest_disk,
    guest_cpu,
    host_virtual,
    host_physical,
    host_file,
    host_disk,
    max_enum = 0xdead
};

// enumeration of data types that can be members of a struct
enum class member_type_t : enum_idx_t
{
    e_int = 0,
    e_uint,
    e_float,
    e_ufloat,
    e_bool,
    e_char,
    e_struct,
    e_union,
    e_unknown,
    max_enum = 0xdead
};

// guest operating system type
enum class opsys_t : enum_idx_t
{
    none = 0,
    bare,
    linux,
    bsd,
    winnt,
    mach_o,
    max_enum = 0xdead
};


// Class Definition
///////////////////

/// @class enum_convert Convert the supplied type-safe enum to and from a string.
template <typename _Tp>
class enum_convert
{
public:

    // initialize all members for the given type
    static void init();

    // convert enum to a string
    static const QString to_string(const _Tp a_enum_idx);

    // convert a string to an enum
    static const _Tp from_string(const QString &a_enum_str);

private:
    // storage for enum <-> string translations
    static enum_map_t enum_map;

};

// helper function to initialize all enums.
void enum_initializer();

// Template Definitions
///////////////////////

/// @brief   Specialized Map Initialization Function
template <typename _Tp>
void enum_convert <_Tp>::init()
{
    //
    // NOTE: init() specializations are defined in enum_convert.cpp using ADD_TRANSLATIONS.
    //
    VDEBUG(0, "WARNING: attempted to initialize an enum convert without a valid specialization!");
}

template <typename _Tp>
const QString enum_convert <_Tp>::to_string(const _Tp a_enum_idx)
{
    // lookup and return the value from the left side of the bimap
    try {
        return enum_map.left.at(static_cast <enum_idx_t>(a_enum_idx));
    } catch (out_of_range e) {
        return "UNKNOWN";
    }
}

template <typename _Tp>
const _Tp enum_convert <_Tp>::from_string(const QString &a_enum_str)
{

    // lookup and return the value from the right side of the bimap
    try {
        return enum_map.right.find(a_enum_str)->first();
    } catch (out_of_range e) {
        return 0xdead;
    }

}


} // namespace


#endif // ENUM_CONVERT_HPP
