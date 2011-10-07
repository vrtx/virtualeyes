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

#ifndef VEYE_ABSTRACT_HUD_WIDGET_HPP
#define VEYE_ABSTRACT_HUD_WIDGET_HPP

#include <QScrollArea>
#include <QGraphicsWidget>

namespace veyes {

        ///////////////////////////////////////////////////////
        /// @class   abstract_hud_widget
        /// @brief   Base class for all virtualeyes HUD widgets
        ///////////////////////////////////////////////////////
        class abstract_hud_widget : public QScrollArea
        {
        Q_OBJECT
        public:
                // Member Variables
                QGraphicsWidget *proxy;                                 // Graphics proxy

                // Member Functions
                explicit abstract_hud_widget(QScrollArea *parent = 0);  // ctor
//                virtual void keyPressEvent(QKeyEvent *a_event);       // keyboard event handler
                virtual void initialize();                              // set up the widget style

        signals:
        public slots:
        private:
                // Member functions
                virtual QSize sizeHint() const;         // default window size
                virtual QSize minimumSize() const;      // min size of window
                virtual QSize maximumSize() const;      // max size of window

        };



}

#endif
