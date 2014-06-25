///////////////////////////////////////////////////////
// range_map
//
// Copyright (c) 2011 - 2011 Benjamnin Becker
// All Rights Reserved
//
// @brief   This file defines the main window and layout
// @author  ben
// @date    6/9/2011
///////////////////////////////////////////////////////

#include "range_map.hpp"
#include "main_view.hpp"
#include "main_window.hpp"
#include "common.hpp"
#include "session.hpp"
#include "widgets/style_mgr.hpp"
#include "core/enum_convert.hpp"

using namespace veyes;

// Static Initializations

// singleton instance
range_map *range_map::instance = NULL;

range_map::range_map() :
    handle_base()
{

}


range_map::~range_map()
{

}
