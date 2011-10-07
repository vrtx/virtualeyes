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

#include "console_input_widget.hpp"
#include "virtualeyes.hpp"
#include "widgets/style_mgr.hpp"
#include "main_view.hpp"

console_input_widget::console_input_widget(QWidget *parent) :
    QTextEdit(parent)
{

        // add the overlayed console input box
        setWindowOpacity(0.75f);
        setMinimumSize(640, 20);
        setMaximumSize(3200, 20);
        setContentsMargins(0, 0, 0, 0);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setStyleSheet(global <style_mgr>()->line_input());
        m_proxy = global <main_view>()->m_veye_scene->addWidget(this);
//        m_proxy->setFlag(QGraphicsItem::ItemIsMovable);
        m_proxy->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
        setFocus();

}


/// @brief    Process keyboard input while this widget has focus
void console_input_widget::keyPressEvent(QKeyEvent *a_event)
{

    QScriptValue repl;
    switch (a_event->key()) {

    // key event handler overrides for input
    case Qt::Key_Copy:
    case Qt::Key_Cut:
    case Qt::Key_Paste:
        // forward copy/cut/paste to backlog widget
        QCoreApplication::sendEvent(global <main_view>()->m_console_widget->m_backlog_widget, a_event);
    case Qt::Key_Enter:
    case Qt::Key_Return:
        // process input on newline
        // send to console_widget key press handler
        if (toPlainText().size() > 0)
            global <main_view>()->m_console_widget->keyPressEvent(a_event);
        break;
    default:
        QTextEdit::keyPressEvent(a_event);
        a_event->accept();
        break;
    }
}


// Default Window Size
QSize console_input_widget::sizeHint() const
{
        return QSize(5000, 2600);
}

// Minimum Window Size
QSize console_input_widget::minimumSizeHint() const
{
        return QSize(800, 20);
}
