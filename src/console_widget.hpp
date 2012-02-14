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

#ifndef VIRTUALEYES_CONSOLE_WIDGET_HPP
#define VIRTUALEYES_CONSOLE_WIDGET_HPP

#include <QtGui>
#include <QTextEdit>
#include <QLineEdit>
#include "common.hpp"
#include "handle_base.hpp"
#include "handle.hpp"
#include "console_input_widget.hpp"

namespace veyes
{
	struct text_format_t {
		enum category {
            STANDARD = 1 << 1,
            ERROR = 1 << 2,
            DEBUG = 1 << 3,
            SCRIPT_IN = 1 << 4,
            SCRIPT_OUT = 1 << 5,
            PARTIAL = 1 << 6,
            BACKGROUND = 1 << 7,
            UNKNOWN = 1 << 8
		};
    };

    ///////////////////////////////////////////////////////
    //
    /// @class   console_widget
    /// @brief   This class implements an interactive console widget
    //
    ///////////////////////////////////////////////////////
    class console_widget : public QGraphicsWidget,
                           public handle_base
    {
    Q_OBJECT

    public:
        // Member Variables
        handle <console_input_widget> m_input_widget;
        QGraphicsWidget *m_backlog_proxy;
        QTextEdit *m_backlog_widget;
        QGraphicsGridLayout *m_layout;
        bool is_open;

        // Member Functions
        console_widget(QGraphicsWidget *parent = NULL);
        virtual ~console_widget();
        virtual void append(const QString &a_line, int a_format = text_format_t::STANDARD, int a_level = 0);
        virtual void toggle();
        virtual void resize(QResizeEvent *event);
        virtual void keyPressEvent(QKeyEvent *a_event);

        // User I/O event handlers
        void wheelEvent(QGraphicsSceneWheelEvent *a_event);


        // Class Variables

    private:
        // // Member functions
        // QSize sizeHint() const;                 // default window size
        // QSize minimumSizeHint() const;          // minimum size of window
    };

}


#endif
