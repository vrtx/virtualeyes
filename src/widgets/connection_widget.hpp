///////////////////////////////////////////////////////
// virtualeyes
//
// Copyright (c) 2011 - 2011 Benjamnin Becker
// All Rights Reserved
//
// @brief   Widgit indicating connectivity to realtime data
// @author  ben
// @date    1/21/2012
///////////////////////////////////////////////////////

#pragma once

#include "abstract_hud_widget.hpp"
#include "handle.hpp"
#include "handle_base.hpp"
#include <QtGui>

// Definitions

namespace veyes {

        // Type Definitions

        ///////////////////////////////////////////////////////
        /// @class   connection_widget
        /// @brief   View of collected data across time
        ///////////////////////////////////////////////////////
        class connection_widget : public abstract_hud_widget,
                                public handle_base
        {
        Q_OBJECT
        public:
                // Member Functions
                explicit connection_widget(QScrollArea *parent = 0);    // ctor
                virtual ~connection_widget();                           // dtor
                virtual void initialize();                              // set up the widget style
//              virtual void keyPressEvenst(QKeyEvent *a_event);        // keyboard event handler
                virtual void resizeEvent(QResizeEvent *a_event);        // resize the connection

        signals:
                void do_connect();          // connect to the db
                void do_disconnect();       // disconnect from the db

        public slots:
                void db_connected();        // db has connected
                void db_connecting();       // db is attempting to connect
                void db_disconnected();     // db has disconnected
                void button_click() {
                    if (!m_connected) 
                      emit do_connect(); 
                    else 
                      emit do_disconnect(); 
                    m_connected = !m_connected;
                }
        private:
                // Member Functions
                virtual QSize sizeHint() const;         // default window size
                virtual QSize minimumSize() const;      // min size of window
                virtual QSize maximumSize() const;      // max size of window

                // Member Variables
                QGraphicsRectItem *m_background;
                QPushButton *m_connect_button;          // db connection button
                QColor m_text_color;                    // foreground text color
                QColor m_connected_color;               // background text color
                QColor m_connecting_color;              // background text color
                QColor m_disconnected_color;            // background text color
                bool m_connected;

                // Embedded Icons
                QGraphicsPixmapItem *r_connected_icon;
                QGraphicsPixmapItem *r_connecting_icon;
                QGraphicsPixmapItem *r_disconnected_icon;

        };

}
