///////////////////////////////////////////////////////
//
// virtualeyes
//
// Copyright (c) 2011 Benjamnin Becker
// All Rights Reserved
//
/// @brief   This file defines the class and types used to store
//           the vm snapshot on a breakpoint.
//
/// @author  Ben Becker
/// @date    2/13/11
//
///////////////////////////////////////////////////////

#include "snapshot.hpp"
#include "breakpoint.hpp"

/// @brief   Default constructor
snapshot::snapshot() :
        handle_base(),
        time(),
        snapshot_name(),
        registers(),
        stack_dump()
{

    // test for memory region
    handle <memory_region> test_region = new memory_region;
    test_region->load_sample_data();
    test_region->load_as_struct("struct testing_type { "
                                "  member_type_t type; "
                                "  uint64_t offset; "
                                "  uint64_t size; "
                                "} ");
    VDEBUG(0, "Dumping test struct to console:" << endl << test_region->get_as_structured_text());

}

/// @brief   Copy constructor
snapshot::snapshot(const snapshot &a_snapshot) :
        handle_base(a_snapshot),
        time(a_snapshot.time),
        snapshot_name(a_snapshot.snapshot_name),
        registers(a_snapshot.registers),
        stack_dump(a_snapshot.stack_dump)
{

}

/// @brief   Destructor
snapshot::~snapshot()
{

}


/// @brief    Attempt to collect the same data that was collected
///           and traversed in the previous snapshot
void snapshot::collect_using_template(const handle <snapshot> &a_template)
{



}
