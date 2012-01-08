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

#include "handle_base.hpp"
#include "debug.hpp"

int64_t global_handle::global_handle_index = 0;
handle_map_t global_handle::global_handle_map;

#ifdef DEBUG_ALLOCATIONS
#  undef VREF_TRACE
#  define VREF_TRACE(...)  cout << debug_log::generate_prefix(__FILE__, __LINE__, __FUNCTION__).toStdString() << __VA_ARGS__ << endl;
#else
#  define VREF_TRACE(...) do {} while (0)
#endif

// Member Functions
handle_base::handle_base() :
        v_id(--global_handle::global_handle_index),
        v_read_count(0),
        v_write_count(0)
{
        global_handle::global_handle_map.insert(pair <int64_t, handle_base *>(v_id, this));
        VREF_TRACE("*ALLOC: Allocating object [type:" << typeid(*this).name() << "] [id:" << v_id << "] [addr:" << this << "]");
}

handle_base::handle_base(const handle_base &a_handle_base) :
        v_id(a_handle_base.v_id),
        v_read_count(a_handle_base.v_read_count),
        v_write_count(a_handle_base.v_write_count)
{

}

handle_base::~handle_base()
{
        // remove the handle from global list
        global_handle::global_handle_map.erase(v_id);
}
