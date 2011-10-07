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

#ifndef VIRTUALEYES_SNAPSHOT_HPP
#define VIRTUALEYES_SNAPSHOT_HPP

//
// Includes
//
#include "common.hpp"
#include "memory_region.hpp"
#include "handle.hpp"
#include "soft_handle.hpp"
#include "handle_base.hpp"
#include <QTime>
#include <QObject>
#include <QRect>

namespace veyes
{

        // Forward Declarations
        class snapshot;
        class breakpoint;

        // Container Type Definitions
        typedef set <handle <snapshot>,
                     compare_time_less <handle <snapshot> > > snapshot_set_t;
        typedef set <soft_handle <snapshot>,
                     compare_time_less <soft_handle <snapshot> > > snapshot_soft_set_t;
        typedef snapshot_set_t owned_snapshots_t;
        typedef snapshot_soft_set_t soft_snapshots_t;

        ///////////////////////////////////////////////////////
        //
        /// @class   snapshot
        /// @brief   This class defines the memory and state information
        ///          collected on each breakpoint.
        //
        ///////////////////////////////////////////////////////
        class snapshot : public QObject,
                         public handle_base
        {
        Q_OBJECT

        public:

                // Member Variables
                QTime time;                                 // time the breakpoint was encountered
                QString snapshot_name;                      // user-defined name of the snapshot
                list <boost::any> registers;                // CPU register contents
                string stack_dump;                          // copy of the stack
                soft_handle <breakpoint> parent_bp;         // the breakpoint this snapshot was collected from
                owned_memory_regions_t memory_regions;      // memory regions captured in this snapshot

                // Member Functions
                snapshot();
                snapshot(const snapshot &a_snapshot);
                virtual ~snapshot();
                virtual void collect_using_template(const handle <snapshot> &a_template); // attempt to collect data from the supplied snapshot

                // Visualization
                void render_gl();
                void update_gl_dimensions(const QRect &a_dimension);

        private:
                QRect dimensions;


        };

}



#endif
