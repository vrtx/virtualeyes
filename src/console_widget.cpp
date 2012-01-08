///////////////////////////////////////////////////////
//
// virtualeyes
//
// Copyright (c) 2011 Benjamnin Becker
// All Rights Reserved
//
// @brief   This file defines the main window and layout
//
// @author  Ben Becker
// @date    2/3/11
//
///////////////////////////////////////////////////////

#include "common.hpp"
#include "console_widget.hpp"
#include "veye_scene.hpp"
#include "virtualeyes.hpp"
#include "session.hpp"
#include "widgets/style_mgr.hpp"
#include "main_view.hpp"
#include <QGLWidget>


// default ctor
console_widget::console_widget(QGraphicsWidget *parent) :
		QGraphicsWidget(parent),
		m_input_widget(new console_input_widget)  // add the input widget
{

    global <style_mgr> l_style_mgr;

    // handle mouse wheel events
    setFocusPolicy(Qt::WheelFocus);

    // set up the border
    setContentsMargins(0, 0, 0, 0);

    // add the overlayed console log
    // TODO: REFACTOR: subclass QTextEdit for m_backlog_widget
    m_backlog_widget = new QTextEdit;
    m_backlog_widget->setWindowOpacity(0.75f);
	// m_backlog_widget->setMinimumSize(640, 80);
	// m_backlog_widget->setMaximumSize(3200, 2000);
	// m_backlog_widget->setBaseSize(800, 300);
    m_backlog_widget->setReadOnly(true);
    m_backlog_widget->setCornerWidget(new QSizeGrip(m_backlog_widget));
    m_backlog_widget->cornerWidget()->hide();
    m_backlog_widget->setStyleSheet(l_style_mgr->text_input());
    m_backlog_widget->setFontFamily("courier");
    m_backlog_widget->setFontPointSize(12);
    m_backlog_proxy = global <main_view>()->m_veye_scene->addWidget(m_backlog_widget);
    m_backlog_proxy->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    m_backlog_proxy->setFocusPolicy(Qt::WheelFocus);
    m_backlog_widget->setText("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
                              "[Console Started]\n"
                              "Press Ctrl + Space to show/hide this console.\n");
    m_backlog_widget->moveCursor(QTextCursor::End);

    // add the subwidgets to the layout
    m_layout = new QGraphicsGridLayout;
    m_layout->setHorizontalSpacing(0);
    m_layout->setVerticalSpacing(0);
    m_layout->setMinimumHeight(80);
    m_layout->setMinimumWidth(640);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->addItem(m_backlog_proxy, 0, 0);
    m_layout->addItem(m_input_widget->m_proxy, 1, 0);
    QGraphicsWidget::setLayout(m_layout);
    // pass all keyboard events to the input box
    // TODO: FEATURE: pass copy/paste events to the backlog window.
	// setFocusProxy(m_input_widget->m_proxy);
	// setFlag(QGraphicsItem::ItemIsMovable);
	// m_backlog_proxy->setFocusProxy(m_input_widget->m_proxy);

}

// dtor
console_widget::~console_widget()
{

}

 /// @brief    Process keyboard input while this widget has focus
 void console_widget::keyPressEvent(QKeyEvent *a_event)
 {

	QScriptValue repl;
	switch (a_event->key()) {

	// console-specific hot keys
    case Qt::Key_Enter:
    case Qt::Key_Return:

	// if (a_event->modifiers() & Qt::ShiftModifier) {
		// done entering script

		// add the input to the console backlog
		m_backlog_widget->moveCursor(QTextCursor::End);
		append(QString("> ").append(m_input_widget->toPlainText()), text_format_t::SCRIPT_IN);

		// interpret the input
		repl = global <virtualeyes>()->m_script_engine->core.evaluate(m_input_widget->toPlainText());
		if (repl.isError())
			// unable to interpret
			append(repl.toString(), text_format_t::ERROR);
		else
			// add the repl evaluation response to the console backlog
			append(repl.toString(), text_format_t::SCRIPT_OUT);

		// clear the input line
		m_input_widget->clear();

	// } else {
	//      // new line
	// 
	// }
	// 
         // cleanup
         m_backlog_widget->verticalScrollBar()->setValue(m_backlog_widget->verticalScrollBar()->maximum());   // scroll backlog window to bottom
         break;
     case Qt::Key_Copy:
     case Qt::Key_Cut:
     case Qt::Key_Paste:
             // forward copy/cut/paste to backlog widget
             QCoreApplication::sendEvent(m_backlog_widget, a_event);
             break;
     default:
             // forward to input widget
             QCoreApplication::sendEvent(m_input_widget.raw_ptr, a_event);
             break;
     }
 }


/// @brief  Append a line of data to the console log
void console_widget::append(const QString &a_line, int a_format, int a_level)
{
    // helpers
    bool add_newline = true;

    m_backlog_widget->moveCursor(QTextCursor::End);
    if (a_format & text_format_t::PARTIAL) {
        a_format ^= text_format_t::PARTIAL;
        add_newline = false;
    }

    // format the text
    switch (a_format) {
    case text_format_t::UNKNOWN:
    case text_format_t::STANDARD:
        m_backlog_widget->setTextColor(QColor(0xa4, 0x96, 0x90));
        break;
    case text_format_t::SCRIPT_OUT:
        m_backlog_widget->setTextColor(QColor(0xf4, 0xf2, 0xf0));
        break;
    case text_format_t::SCRIPT_IN:
        m_backlog_widget->setTextColor(QColor(0xaa, 0xc2, 0xa5));
        break;
    case text_format_t::ERROR:
        m_backlog_widget->setTextColor(QColor(0xd4, 0x90, 0x8a));
        break;
    case text_format_t::DEBUG:
        m_backlog_widget->setTextColor(QColor(0xb4, 0xa6, 0xa0));
        break;
    case text_format_t::BACKGROUND:
        m_backlog_widget->setTextColor(QColor(0x94, 0x86, 0x80));
        break;
    default:
        m_backlog_widget->setTextColor(QColor(0xa4, 0x96, 0x90));
        break;
    }

    if (a_level) {
        // level has been set

        // decrease text brightness as level goes up
        m_backlog_widget->setTextColor(m_backlog_widget->textColor().darker(100 + (a_level * 5)));
    }

    m_backlog_widget->textCursor().insertText(add_newline ? a_line + "\n" : a_line);
    m_backlog_widget->setTextColor(QColor(0xc4, 0xb6, 0xb0));       // reset color
    m_backlog_widget->verticalScrollBar()->setValue(m_backlog_widget->verticalScrollBar()->maximum());   // scroll backlog window to bottom

}

/// @brief  Toggle the visibility of the console
void console_widget::toggle()
{
    if (isVisible()) {
        setVisible(false);
    } else {
        setVisible(true);
    }
}

/// @brief    Process mouse wheel events while this widget has focus
void console_widget::wheelEvent(QGraphicsSceneWheelEvent *a_event)
{
    QGraphicsWidget::wheelEvent(a_event);
    QApplication::sendEvent(m_backlog_proxy, a_event);
}

 /// @brief window resize event handler
 void console_widget::resize(QResizeEvent *event)
 {
//            // scroll to the bottom
//            m_backlog_widget->verticalScrollBar()->setValue(m_backlog_widget->verticalScrollBar()->maximum());   // scroll backlog window to bottom
 }

// Default Window Size
QSize console_widget::sizeHint() const
{
    return QSize(global <main_view>()->size().width(), 120);
}

// Minimum Window Size
QSize console_widget::minimumSizeHint() const
{
    return QSize(global <main_view>()->width(), 80);
}
