///////////////////////////////////////////////////////
//
// virtualeyes
//
// Copyright (c) 2011 Benjamnin Becker
// All Rights Reserved
//
/// @brief   This file defines the data region that represents a portion of
///          guest memory and various methods of displaying it (hex, ascii, structure and assembly).
//
/// @author  Ben Becker
/// @date    2/3/11
//
///////////////////////////////////////////////////////

#include "memory_region.hpp"

/// @brief   Default constructor
memory_region::memory_region() :
    time(0),
    start_address(0),
    region_name(),
    raw(),
    disassembly(),
    disassembly_start(-1)
{

}

/// @brief   Initializing constructor
/// @param[in]   a_guest_virtual_address  Guest virtual address to copy this region from
/// @param[in]   a_size                   Size of the memory region
/// @param[in]   a_breakpoint_id          ID of the breakpoint this region was collected on
memory_region::memory_region(void *a_guest_virtual_address, uint64_t a_size, uint64_t a_breakpoint_id) :
    time(0),
    start_address(reinterpret_cast <uint64_t>(a_guest_virtual_address)),
    region_name(),
    raw(),
    disassembly(),
    disassembly_start(-1)
{

    // BB TODO:
    // gdb_iface::core->copy_memory_range(&raw, a_guest_virtual_address, a_size);

}

/// @brief   Copy constructor
memory_region::memory_region(const memory_region &a_memory_region):
    time(a_memory_region.time),
    start_address(a_memory_region.start_address),
    region_name(a_memory_region.region_name),
    raw(a_memory_region.raw),
    disassembly(a_memory_region.disassembly),
    disassembly_start(a_memory_region.disassembly_start)
{

}

/// @brief   Destructor
memory_region::~memory_region()
{

}

// interpret this memory region as the given c struct
int memory_region::load_as_struct(const QString &a_struct)
{

    // parse fields from struct

    // determine field boundries based on:
    //    guest arch + os?
    //    live-data heuristic?

    region_name = "parsed_struct_name";
    structure.name = "kern_struct";
    structure.uri = "/0xFFDF000/";

    // for each member:
    struct_member_t l_member = { 0 };
    struct_member_t l_member2 = { 0 };
    l_member.name = "base_address";
    l_member.type = member_type_t::e_int;
    l_member.deref_depth = 0;
    l_member.size = 4;
    l_member.offset = 8;
    l_member.value_as_text = "0x800000000";
    l_member2.name = "eproc";
    l_member2.type = member_type_t::e_char;
    l_member2.deref_depth = 1;
    l_member2.size = 8;
    l_member2.offset = 0;
    l_member2.deref_is_array = true;
    l_member2.value_as_text = "Process";
    structure.members.insert(l_member);
    structure.members.insert(l_member2);
    return 0;
}

// get a structured representation of this region
QString memory_region::get_as_structured_text()
{
    QString l_tmp;
    QTextStream struct_string(&l_tmp);
    int depth = 1;

    struct_string.setFieldAlignment(QTextStream::AlignLeft);
    struct_string << "Struct: " << region_name << endl;
    for (struct_members_t::const_iterator it = structure.members.begin();
         it != structure.members.end();
         ++it) {
        // for each member

        // genereate indrection depth
        QString derefs;
        for (int i = 0; i < it->deref_depth; ++i)
            derefs.append("ptr to ");

        // print 'field: value [type]'
        struct_string << "  " << qSetFieldWidth(12 + (depth * 2)) << left
                      << it->name + ":"
                      << qSetFieldWidth(20) << it->value_as_text
                      << qSetFieldWidth(0) << left
                      <<  " [" << it->size << "-byte "
                      << (derefs.length() ? derefs : "")
                      << (it->is_array ? "array of " : "")
                      << enum_convert <member_type_t>::to_string(it->type)
                      << (it->deref_is_array ? " array" : "")
                      << "]" << endl;
    }
    struct_string << left << "Total Size: " << raw.length() << " bytes" << endl << endl;
    return l_tmp;
}
