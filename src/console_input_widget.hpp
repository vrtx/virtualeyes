///////////////////////////////////////////////////////
// virtualeyes
//
// Copyright (c) 2011 - 2011 Benjamnin Becker
// All Rights Reserved
//
// @brief   This file defines the main window and layout
// @author  ben
// @date    7/2/2011
///////////////////////////////////////////////////////

#ifndef CONSOLE_INPUT_WIDGET_HPP
#define CONSOLE_INPUT_WIDGET_HPP

#include <QTextEdit>
#include <QGraphicsWidget>
#include "handle_base.hpp"

namespace veyes {

        class console_input_widget : public QTextEdit,
                                     public handle_base
        {
        Q_OBJECT

        public:
                // Member Variables
                QGraphicsWidget *m_proxy;          // Graphics proxy

                // Member Functions
                explicit console_input_widget(QWidget *parent = 0);     // ctor
                virtual void keyPressEvent(QKeyEvent *a_event);         // keyboard event handler


        signals:

        public slots:

        private:
                // Member functions
                QSize sizeHint() const;                 // default window size
                QSize minimumSizeHint() const;          // minimum size of window

        };

}


#endif // CONSOLE_INPUT_WIDGET_HPP
