///////////////////////////////////////////////////////
// virtualeyes
//
// Copyright (c) 2011 Benjamnin Becker
// All Rights Reserved
//
// @brief   This file defines the main window and layout
// @author  Ben Becker
// @date    2/3/11
///////////////////////////////////////////////////////

#ifndef VIRTUALEYES_main_view_HPP
#define VIRTUALEYES_main_view_HPP

#include <QtGui>
#include "common.hpp"
#include "handle_base.hpp"
#include "handle.hpp"
#include "console_widget.hpp"
#include "snapshot.hpp"
#include "veye_scene.hpp"
#include "widgets/timeline_widget.hpp"

namespace veyes
{

    // forward declarations
    class session;

    ///////////////////////////////////////////////////////
    //
    /// @class   main_view
    /// @brief   This class implements the main window, layout
    ///          and global user-interface related logic.
    //
    ///////////////////////////////////////////////////////
    class main_view : public QGraphicsView,
                      public handle_base
    {
    Q_OBJECT

    public:

        // Member Variables
        veyes::handle <veye_scene> m_veye_scene;           // OpenGL scene (drawn in background)
        veyes::handle <console_widget> m_console_widget;   // interactive console
        veyes::handle <timeline_widget> m_timeline_widget; // timeline HUD component

        QTreeWidget *m_breakpoint_widget;                  // breakpoint list view
        QGraphicsProxyWidget *m_breakpoint_proxy;
        QGraphicsTextItem *m_cpu_state_widget;             // cpu state view
        QGraphicsProxyWidget *m_cpu_state_proxy;
        QTreeWidget *m_catchpoint_widget;                  // catchpoint list view
        QGraphicsProxyWidget *m_catchpoint_proxy;

        // Member Functions
        main_view(QGraphicsView *parent = NULL);
        virtual ~main_view();
        virtual void initialize();
        virtual void keyPressEvent(QKeyEvent *a_event);
        virtual void toggle_console();

        // Class Variables
        static main_view *instance;               // singleton reference to main view

    protected:
        // Event Handlers
        void resizeEvent(QResizeEvent *event);

    public slots:
        void add_snapshot(const veyes::handle <snapshot> &a_snapshot);

    private:
        // Member Variables
        QGraphicsGridLayout *m_layout;
        QGraphicsWidget *m_container;

        // Member functions
        QSize sizeHint() const;                 // default window size
        QSize minimumSizeHint() const;          // minimum size of window

    };

}


#endif
