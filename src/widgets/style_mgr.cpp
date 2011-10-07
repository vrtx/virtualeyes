#include "style_mgr.hpp"
#include <QFont>
#include <QGraphicsDropShadowEffect>

style_mgr *style_mgr::instance = NULL;

/// @brief   Default constructor
style_mgr::style_mgr()
{

    // set up the fonts
    m_timeline_font.setFamily("arial");
    m_timeline_font.setPixelSize(10);
    m_timeline_font.setLetterSpacing(QFont::AbsoluteSpacing, 1);
    m_timeline_font.setFixedPitch(true);

    m_clock_font.setFamily("arial");
    m_clock_font.setPixelSize(12);
    m_clock_font.setLetterSpacing(QFont::PercentageSpacing, 115.0f);
    m_clock_font.setFixedPitch(true);

    // set up the colors
    m_default_font_pen_color = QColor(0xa4, 0xa2, 0xa0, 0x20);
    m_default_font_brush_color = QColor(0xb4, 0xb2, 0xb0, 0xa0);
    m_clock_font_pen_color = QColor(0xaa, 0xa3, 0xa0, 0x50);
    m_clock_font_brush_color = QColor(0xaa, 0xa3, 0xa0, 0x80);

    // set up the style sheets
    m_background =
            "QWidget { "
            "    color: #b4b2b0; "
            "    background: qlineargradient(x1: 0, y1: 0, x2: 0.3, y2: 1, stop: 0 #646260 stop: 1 #444240); "
            "    selection-background-color: rgba(60, 90, 200, 90);"
            "    border: 0px;"
            "    padding: 0px; "
            "} ";

    m_font =
            "* {"
            "    font-size: 10px; "
            "} ";

    m_vert_scrollbar =
            "QScrollBar:vertical { "
            "    background: qlineargradient(x1: 0, y1: 0, x2: 0.4, y2: 0, stop: 0 #949290 stop: 1 #a4a2a0); "
            "    width: 15px; "
            "    margin: 17px 0px 17px 0px; "
            "    border: 0px;"
            "    padding: 1px; "
            "    border-left: 1px solid #2a2826; "
            "    border-right: 1px solid #2a2826; "
            "} "

            "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical { "
            "    background: qlineargradient(x1: 0, y1: 0, x2: 0.4, y2: 0, stop: 0 #949290 stop: 1 #a4a2a0); "
            "} "

            "QScrollBar::handle:vertical { "
            "    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #848280 stop: 1 #646260); "
            "    border-radius: 3px; "
            "    border: 1px solid #242220; "
            "    min-height: 20px; "
            "} "

            "QScrollBar::add-line:vertical { "
            "    border: 1px solid #2a2826; "
            "    border-bottom-left-radius: 6px; "
            "    border-bottom-right-radius: 6px; "
            "    background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1, stop: 0 #4a4846 stop: 1 #949290); "
            "    height: 15px; "
            "    subcontrol-position: bottom; "
            "    subcontrol-origin: margin; "
            "} "

            "QScrollBar::sub-line:vertical { "
            "    border: 1px solid #2a2826; "
            "    border-top-left-radius: 6px; "
            "    border-top-right-radius: 6px; "
            "    background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1, stop: 0 #4a4846 stop: 1 #949290); "
            "    height: 15px; "
            "    subcontrol-position: top; "
            "    subcontrol-origin: margin; "
            "} "

            "QScrollBar:down-arrow:vertical, QScrollBar::up-arrow:vertical { "
            "    width: 13px; "
            "    height: 13x; "
//            "    background: #a4a2a0; "
            "    background: url(':/icons/scroll_arrow_vert_tan.png');"
            "}";

    m_horiz_scrollbar =
            "QScrollBar:horizontal { "
            "    background: qlineargradient(x1: 0, y1: 0, x2: 0.4, y2: 0, stop: 0 #949290 stop: 1 #a4a2a0); "
            "    width: 15px; "
            "    margin: 17px 0px 17px 0px; "
            "    padding: 1px; "
            "    border: 0px; "
            "    border-left: 1px solid #2a2826; "
            "    border-right: 1px solid #2a2826; "
            "} "

            "QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal { "
            "    background: qlineargradient(x1: 0, y1: 0, x2: 0.4, y2: 0, stop: 0 #949290 stop: 1 #a4a2a0); "
            "} "

            "QScrollBar::handle:horizontal { "
            "    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #848280 stop: 1 #646260); "
            "    border-radius: 3px; "
            "    border: 1px solid #242220; "
            "    min-height: 20px; "
            "} "

            "QScrollBar::add-line:horizontal { "
            "    border: 1px solid #2a2826; "
            "    border-bottom-left-radius: 6px; "
            "    border-bottom-right-radius: 6px; "
            "    background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1, stop: 0 #4a4846 stop: 1 #949290); "
            "    height: 15px; "
            "    subcontrol-position: bottom; "
            "    subcontrol-origin: margin; "
            "} "

            "QScrollBar::sub-line:horizontal { "
            "    border: 1px solid #2a2826; "
            "    border-top-left-radius: 6px; "
            "    border-top-right-radius: 6px; "
            "    background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1, stop: 0 #4a4846 stop: 1 #949290); "
            "    height: 15px; "
            "    subcontrol-position: top; "
            "    subcontrol-origin: margin; "
            "} "

            "QScrollBar:down-arrow:horizontal, QScrollBar::up-arrow:horizontal { "
            "    width: 3px; "
            "    height: 3px; "
            "    background: #a4a2a0; "
            "}";

    m_button =
            m_background;

    m_table_header =
            "QHeaderView::section { "
            "     color: #d4d2d0; "
            "     background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1.6, stop: 0 #949290 stop: 1 #4a4846); "
            "     padding-left: 4px; "
            "     padding-right: 4px; "
            "     padding-bottom: 1px; "
            "     padding-top: 1px; "
            "     border-bottom: 1px solid #4a4846; "
            "     border-left: 0px; "
            "     border-right: 1px solid #4a4846; "
            "     border-top: 0px; "
            "} ";

    m_qtree_widget =
            "QTreeView::item:selected {"
            "     border-bottom: 0px; "
            "     background-color: rgba(60, 90, 200, 90);"
            "} "

            "QTreeView::corner { "
            "     background-color: #4a4846; "
            "     border: 1px solid #2a2826; "
            "} ";

//            "QTreeView {"
//            "}"

//            "QTreeView::item {"
//            "     border-bottom: 1px solid rgba(0, 0, 0, 30); "
//            "     border-left: 1px solid rgba(0, 0, 0, 30); "
//            "} "

//            "QTreeView::item::alternate {"
//            "     background: qlineargradient(x1: 0, y1: 0, x2: 0.3, y2: 1, stop: 0 #545250 stop: 1 #444240); "
//            "     border-bottom: 1px solid #4a4846; "
//            "} "

//            "QTreeView::branch { "
//            "} "

    m_text_input =
            "QTextEdit::corner {"
            "     background-color: #4a4846;"
            "     border: 1px solid #2a2826; "
            "} ";

    m_line_input =
            "QTextEdit { "
            "     color: #e4d6d0;"
            "     background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #444240 stop: 1 #343230);"
            "     border-top: 1px solid qlineargradient(x1: 0, y1: 0, x2: 0.75, y2: 0, stop: 0 #c4c2c0 stop: 1 #444240);"
            "     border-width: 1px;"
            "} ";

}

/// @brief   Default destructor
style_mgr::~style_mgr()
{

}

/// @brief    Generate the style sheet for a default widget
QString style_mgr::widget() const
{

    return m_background +
           m_font +
           m_horiz_scrollbar +
           m_vert_scrollbar;

}

/// @brief    Generate the style sheet for a QTreeWidget
QString style_mgr::qtree() const
{

    return m_background +
           m_font +
           m_horiz_scrollbar +
           m_vert_scrollbar +
           m_qtree_widget +
           m_table_header;

}

/// @brief    Generate the style sheet for a default widget
QString style_mgr::scrollbars() const
{

    return m_horiz_scrollbar +
           m_vert_scrollbar;

}

/// @brief    Generate the style sheet for a standard button
QString style_mgr::button() const
{

    return m_font +
           m_background;

}

/// @brief    Generate the style sheet text input
QString style_mgr::text_input() const
{

    return m_background +
           m_font +
           m_horiz_scrollbar +
           m_vert_scrollbar +
           m_text_input;

}

/// @brief    Generate the style sheet text input
QString style_mgr::line_input() const
{

    return m_line_input +
           m_font;

}


/// @brief    Generate the style sheet for a text overlay
void style_mgr::stylize_text_overlay(QGraphicsTextItem *text_item) const
{
        text_item->setOpacity(0.9);
        text_item->setDefaultTextColor(QColor(0xf4, 0xe6, 0xe0));
        text_item->setFont(QFont("courier", 12));
        QGraphicsDropShadowEffect *text_smooth = new QGraphicsDropShadowEffect(text_item);
        text_smooth->setBlurRadius(8);
        text_smooth->setColor(QColor(0x14, 0x12, 0x10));
        text_smooth->setXOffset((0));
        text_smooth->setYOffset((0));
        text_item->setGraphicsEffect(text_smooth);
}


