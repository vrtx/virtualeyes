///////////////////////////////////////////////////////
// virtualeyes
//
// Copyright (c) 2011 Benjamnin Becker
// All Rights Reserved
//
// @brief   This file defines the main view and layout
//
// @author  Ben Becker
// @date    2/3/11
///////////////////////////////////////////////////////

#include "main_view.hpp"
#include "veye_scene.hpp"
#include "virtualeyes.hpp"
#include "session.hpp"
#include "widgets/style_mgr.hpp"
#include <QGLWidget>
#include <QGraphicsTextItem>

// Statics
main_view *main_view::instance = NULL;

// default ctor
main_view::main_view(QGraphicsView *parent) :
    QGraphicsView(parent),
    m_veye_scene(new veye_scene("Workspace", this))
{
    setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setScene(m_veye_scene.raw_ptr);
}

// dtor
main_view::~main_view()
{

}

/// @brief  Initialize the main window
void main_view::initialize()
{
    // get the global style object
    global <style_mgr> g_style_mgr;

    // create the container for overlayed widgets
    m_container = new QGraphicsWidget;

    // create the main layout
    m_layout = new QGraphicsGridLayout(m_container);

    // create the console widget
    m_console_widget = veyes::handle <console_widget>(new console_widget);
    m_console_widget->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum));
    m_console_widget->m_input_widget->setFocus();
    m_console_widget->show();

    // add the overlayed breakpoint list
    QStringList l_column_names;
    l_column_names.push_back(QString("Address"));
    l_column_names.push_back(QString("Symbol"));
    l_column_names.push_back(QString("Name"));
    m_breakpoint_widget = new QTreeWidget;
    // m_breakpoint_widget->setAlternatingRowColors(true);
    m_breakpoint_widget->setHeaderLabels(l_column_names);
    m_breakpoint_widget->setMinimumSize(140, 120);
    m_breakpoint_widget->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::MinimumExpanding);
    m_breakpoint_widget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_breakpoint_widget->header()->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_breakpoint_widget->setCornerWidget(new QSizeGrip(m_breakpoint_widget));
    m_breakpoint_widget->cornerWidget()->hide();
    m_breakpoint_widget->setStyleSheet(g_style_mgr->qtree());
    m_breakpoint_widget->setWindowOpacity(0.75);
    m_breakpoint_widget->setColumnWidth(0, 100);
    m_breakpoint_widget->setColumnWidth(1, 50);
    m_breakpoint_widget->setColumnWidth(2, 50);
    m_breakpoint_proxy = m_veye_scene->addWidget(m_breakpoint_widget);
//    m_breakpoint_proxy->setFlag(QGraphicsItem::ItemIsMovable);
//    m_breakpoint_proxy->setCacheMode(QGraphicsItem::DeviceCoordinateCache);

    m_cpu_state_widget = new QGraphicsTextItem;
    g_style_mgr->stylize_text_overlay(m_cpu_state_widget);
    m_veye_scene->addItem(m_cpu_state_widget);
    m_cpu_state_widget->setPos(width(), height() / 8);
    //        m_cpu_state_widget->setFlag(QGraphicsItem::ItemIsMovable);
    m_cpu_state_widget->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    // m_cpu_state_widget->setPlainText("Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.");
    m_cpu_state_widget->hide();

    // create the timeline widget
    // m_timeline_widget = new timeline_widget;
    // m_timeline_widget->initialize();
    // m_timeline_widget->hide();
    // create the connection button
    m_connection_widget = new connection_widget;
    m_connection_widget->initialize();
    // m_connection_widget->hide();

    // prettify the layout
    m_layout->setHorizontalSpacing(0);
    m_layout->setVerticalSpacing(0);
    m_container->setContentsMargins(0, 0, 0, 0);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setRowStretchFactor(0, 0);
    m_layout->setRowMaximumHeight(2, 220);
    m_layout->setColumnMaximumWidth(0, 160);
    m_layout->setColumnStretchFactor(1, 1);
    // m_layout->addItem(m_timeline_widget->proxy, 0, 0, 1, 2);
    m_layout->addItem(m_connection_widget->proxy, 0, 0, 1, 2);
    m_layout->addItem(m_breakpoint_proxy, 1, 0, 1, 1);
    m_layout->addItem(m_console_widget.raw_ptr, 2, 0, 1, 2);
    // m_layout->addItem(m_catchpoint_proxy, 2, 0);
    m_container->setLayout(m_layout);
    m_veye_scene->addItem(m_container);
    setCornerWidget(new QSizeGrip(this));
    show();
}

/// @brief    Process keyboard input while this widget has focus
void main_view::keyPressEvent(QKeyEvent *a_event)
{
    // ignore any events handed to the background view
    QApplication::sendEvent(global <main_view>()->m_console_widget->m_input_widget.raw_ptr, a_event);
    a_event->ignore();
}

/// @brief window resize event handler
void main_view::resizeEvent(QResizeEvent *event)
{
    // update the display
    m_veye_scene->setSceneRect(QRect(QPoint(0, 0), event->size()));
    m_console_widget->m_backlog_widget->ensureCursorVisible();      // scroll the console
    m_container->resize(event->size());                             // resize the containing widget
    m_layout->setPreferredSize(event->size());                      // update the layout's size
    m_layout->updateGeometry();                                     // recalculate the layout so all children are updated

    // update manually placed items
    m_cpu_state_widget->setPos(event->size().width() - m_cpu_state_widget->boundingRect().width(), event->size().height() / 8);

    // update view layout
    QGraphicsView::resizeEvent(event);
}

/// @brief    Add a snapshot to the veye_scene
void main_view::add_snapshot(const veyes::handle <snapshot> &a_snapshot)
{
    VDEBUG(10, "Adding snapshot to veye_scene");
    m_veye_scene->update();
}

/// @brief  Toggle the visibility of the console
void main_view::toggle_console()
{
    if (m_console_widget->isVisible()) {
        // item is visible; hide it
//        m_console_widget->hide();
//        m_console_widget->setVisible(false);
//        m_console_widget->setPreferredSize(0, 0);

         // ** LEAK **
        QPropertyAnimation *animation = new QPropertyAnimation(global <main_view>()->m_console_widget->m_backlog_widget, "geometry");
        animation->setDuration(300);
        animation->setStartValue(global <main_view>()->m_console_widget->m_backlog_widget->geometry());
        animation->setEndValue(global <main_view>()->m_console_widget->m_backlog_widget->geometry().adjusted(0, global <main_view>()->m_console_widget->m_backlog_widget->size().height() - 30,
                                                                                                             0, global <main_view>()->m_console_widget->m_backlog_widget->size().height() - 30));
        animation->setEasingCurve(QEasingCurve::OutBounce);
        animation->start();

    } else {
        // widget is hidden; restore visibility
        m_console_widget->setVisible(true);
        m_console_widget->m_input_widget->setFocus();
        m_console_widget->setPreferredSize(width(), height() / 3);
        m_console_widget->show();
        QPropertyAnimation *animation = new QPropertyAnimation(global <main_view>()->m_console_widget->m_backlog_widget, "geometry");
        animation->setDuration(300);
        animation->setStartValue(global <main_view>()->m_console_widget->m_backlog_widget->geometry());
        animation->setEndValue(global <main_view>()->m_console_widget->m_backlog_widget->geometry().adjusted(0, global <main_view>()->m_console_widget->m_backlog_widget->size().height() + 30,
                                                                                                             0, global <main_view>()->m_console_widget->m_backlog_widget->size().height() + 30));
        animation->setEasingCurve(QEasingCurve::OutBounce);
        animation->start();

    }

}

// Default Window Size
QSize main_view::sizeHint() const
{
    return QSize(1920, 1200);
}

// Minimum Window Size
QSize main_view::minimumSizeHint() const
{
    return QSize(800, 600);
}

