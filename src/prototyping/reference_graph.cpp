///////////////////////////////////////////////////////
//
// virtualeyes
//
// Copyright (c) 2011 Benjamnin Becker
// All Rights Reserved
//
// @brief   This file defines the data widget reponsible for
//          displaying memory in hex, ascii, structure and assembly format.
//
// @author  Ben Becker
// @date    2/9/11
//
///////////////////////////////////////////////////////

#include <QtOpenGL>
#include "reference_graph.hpp"
#include "memory_legend_item.hpp"

reference_graph::reference_graph()
{

}

reference_graph::~reference_graph()
{

}

/// @brief      Add a reference from one memory region to another
/// @param[in]  a_source_region   The region of memory creating the reference
/// @param[in]  a_target_region   The region of memory that's the subject of the reference
int reference_graph::add_reference(const memory_region &a_source_region, const memory_region &a_target_region)
{

        // add the vertices 
        reference_graph_t::vertex_descriptor l_source_region = boost::add_vertex(a_source_region, boost_graph);
        reference_graph_t::vertex_descriptor l_target_region = boost::add_vertex(a_target_region, boost_graph);

        // add the directed edge
        boost::add_edge(l_source_region, l_target_region, 0.5, boost_graph);

        return 0;

}

