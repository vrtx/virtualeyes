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

#ifndef VIRTUALEYES_MEMORY_GRAPH_HPP
#define VIRTUALEYES_MEMORY_GRAPH_HPP

#include "common.hpp"
#include "memory_region.hpp"
#include <boost/graph/adjacency_list.hpp>

namespace virtualeyes
{

        //
        // forward declarations
        //
        class memroy_view;
        class memory_window;

        //
        // type definitions
        //

        // The main graph used to display memory relationships
        typedef boost::adjacency_list < boost::vecS,        // edge storage
                                        boost::vecS,        // vertex storage
                                        boost::directedS,   // directed graph
                                        memory_region,  // vertex property type
                                        boost::property <boost::edge_weight_t, double>,  // edge property type
                                        boost::property <boost::graph_name_t, string>    // graph property type
        > reference_graph_t;

        ///////////////////////////////////////////////////////
        //
        // @class   reference_graph
        // @brief   This class implements the main window, layout
        //          and global user-interface related logic.
        //
        ///////////////////////////////////////////////////////
        class reference_graph
        {

        public:

                // Member Functions
                reference_graph();
                virtual ~reference_graph();

                // add a new reference to the memory graph
                int add_reference(const memory_region &a_source_region, const memory_region &a_target_region);

        private:

                // Member variables
                reference_graph_t boost_graph;

        };

}

#endif
