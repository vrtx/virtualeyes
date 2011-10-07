///////////////////////////////////////////////////////
// virtualeyes
//
// Copyright (c) 2011 - 2011 Benjamnin Becker
// All Rights Reserved
//
// @brief   This file defines the base class for all virtualeyes HUD widgets
// @author  ben
// @date    7/11/2011
///////////////////////////////////////////////////////

#ifndef VEYE_TIMELINE_WIDGET_HPP
#define VEYE_TIMELINE_WIDGET_HPP

#include "abstract_hud_widget.hpp"
#include "handle.hpp"
#include "handle_base.hpp"
#include "vm_run.hpp"
#include "snapshot.hpp"
#include "breakpoint.hpp"
#include <QGraphicsPixmapItem>
#include <QPixmap>

// Definitions
#define TIMELINE_TICK_WIDTH    15    // width of each tick in the timeline (in pixels)
#define TIMELINE_HEADER_HEIGHT 19    // height of the timeline
#define TIMELINE_COLUMN_WIDTH  22    // width of the first timeline column

namespace veyes {

        // Type Definitions
        typedef QVector <QGraphicsSimpleTextItem *> text_item_vector_t;
        typedef QVector <QGraphicsLineItem *> line_item_vector_t;

        ///////////////////////////////////////////////////////
        /// @class   timeline_widget
        /// @brief   View of collected data across time
        ///////////////////////////////////////////////////////
        class timeline_widget : public abstract_hud_widget,
                                public handle_base
        {
        Q_OBJECT
        public:
                // Member Functions
                explicit timeline_widget(QScrollArea *parent = 0);   // ctor
                virtual ~timeline_widget();                          // dtor
                virtual void initialize();                           // set up the widget style
                virtual void update_timeline_width(quint32 a_width); // update the timeline for the given width
                void connect_session();                              // new session creation signal
//              virtual void keyPressEvenst(QKeyEvent *a_event);     // keyboard event handler
                virtual void resizeEvent(QResizeEvent *a_event);     // resize the timeline

        signals:
        public slots:
                void add_snapshot(const veyes::handle <snapshot> &a_snapshot);        // register a new collection snapshot with the widget
                void add_breakpoint(const veyes::handle <breakpoint> &a_breakpoint);  // register a new breakpoint with the session
                void add_vm_run(const veyes::handle <vm_run> &a_vm_run);              // register a new vm_run with the session

        private:
                // Member Functions
                virtual QSize sizeHint() const;                     // default window size
                virtual QSize minimumSize() const;                  // min size of window
                virtual QSize maximumSize() const;                  // max size of window

                // Member Variables
                QGraphicsRectItem *m_timeline_header;               // container for all timeline header items
                QGraphicsSimpleTextItem *m_timeline_start_label;    // label at start of timeline
                QGraphicsSimpleTextItem *m_timeline_end_label;      // label at end of timeline
                text_item_vector_t m_visible_tick_labels;           // array of visible tick labels
                line_item_vector_t m_visible_ticks;                 // array of visible ticks
                QColor m_text_fg_color;                             // foreground text color
                QColor m_text_bg_color;                             // background text color

                // Embedded Icons
                QGraphicsPixmapItem *r_expand;
                QGraphicsPixmapItem *r_collapse;
                QGraphicsPixmapItem *r_snapshot;
                QGraphicsPixmapItem *r_breakpoint;
                QGraphicsPixmapItem *r_watchpoint;
                QGraphicsPixmapItem *r_start;
                QGraphicsPixmapItem *r_stop;
                QGraphicsPixmapItem *r_notes;
                QGraphicsPixmapItem *r_playhead;
                QGraphicsPixmapItem *r_clock_icon;

        };

}

#endif
