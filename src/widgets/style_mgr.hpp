///////////////////////////////////////////////////////
// virtualeyes
//
// Copyright (c) 2011 Benjamnin Becker
// All Rights Reserved
//
// @author  Ben Becker
// @date    7/9/11
///////////////////////////////////////////////////////

#ifndef VIRTUALEYES_STYLE_MGR_HPP
#define VIRTUALEYES_STYLE_MGR_HPP

#include "common.hpp"
#include <QString>
#include <QGraphicsTextItem>
#include <QFont>
#include <QColor>

namespace veyes {


        ///////////////////////////////////////////////////////
        //
        // @class   stlye
        // @brief   This global<> class defines how all of the widgets are
        //          styled using Qt StyleSheets, QFonts and QColors.
        //
        ///////////////////////////////////////////////////////
        class style_mgr
        {

        public:
                // Get widget-specific style sheet data
                QString widget() const;       // get the default style for a widget
                QString qtree() const;        // get the style for a qtree widget
                QString scrollbars() const;   // get the style definition for scrollbars
                QString button() const;       // get the style definition for buttons
                QString text_overlay() const; // get the style definition for text overlayed on the screen
                QString text_input() const;   // get the style definition for widgets accepting text input
                QString line_input() const;   // get the stule definition for a single-line text input widget

                // Factory style methods for non-CSS classes
                void stylize_text_overlay(QGraphicsTextItem *text_item) const;    // Text overlay graphics item

                // Fonts
                QFont m_timeline_font;              // timeline font
                QFont m_clock_font;                 // larger current-time clock

                // Colors
                QColor m_default_font_pen_color;    // foreground font color
                QColor m_default_font_brush_color;  // foreground font color
                QColor m_clock_font_pen_color;    // foreground font color
                QColor m_clock_font_brush_color;  // foreground font color

                // Friendship
                friend class global <style_mgr>;    // access private ctor/dtor

        private:
                // hidden constructors
                style_mgr();
                virtual ~style_mgr();

                // Class Variables
                static style_mgr *instance;

                // Member Variables
                QString m_vert_scrollbar;
                QString m_horiz_scrollbar;
                QString m_line_input;
                QString m_text_input;
                QString m_background;
                QString m_button;
                QString m_table_header;
                QString m_qtree_widget;
                QString m_font;

        };

}


#endif
