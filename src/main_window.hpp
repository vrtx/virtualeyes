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

#ifndef VIRTUALEYES_main_window_HPP
#define VIRTUALEYES_main_window_HPP

#include <QtGui>
#include <QMainWindow>
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
    /// @class   main_window
    /// @brief   This class implements the main window, which contains
    ///          the main_view as the centerWidget.
    //
    ///////////////////////////////////////////////////////
    class main_window : public QMainWindow,
                        public handle_base
    {
    Q_OBJECT

    public:

        // Member Variables

        // Member Functions
        main_window(QMainWindow *parent = NULL);
        virtual ~main_window();
        virtual void initialize();
        virtual void keyPressEvent(QKeyEvent *a_event);

        // Class Variables
        static main_window *instance;               // singleton reference to main window

    protected:
        // Event Handlers
        void resizeEvent(QResizeEvent *event);
        // void closeEvent(QCloseEvent *event);

    private:
        // Member Functions
        QSize sizeHint() const;                 // default window size
        QSize minimumSizeHint() const;          // minimum size of window

    };

}


#endif
