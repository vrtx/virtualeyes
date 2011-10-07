///////////////////////////////////////////////////////
// virtualeyes
//
// Copyright (c) 2011 - 2011 Benjamnin Becker
// All Rights Reserved
//
// @brief   This file defines the base class for all hud widgets
// @author  ben
// @date    7/11/2011
///////////////////////////////////////////////////////

#include "abstract_hud_widget.hpp"
#include "virtualeyes.hpp"
#include "main_view.hpp"
#include "widgets/style_mgr.hpp"

abstract_hud_widget::abstract_hud_widget(QScrollArea *parent) :
        QScrollArea(parent)
{
        // add widget to scene and create proxy
        proxy = global <main_view>()->m_veye_scene->addWidget(this);
        proxy->setFlag(QGraphicsItem::ItemIsMovable);
        proxy->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
}

/// @brief    Initialize the widget's behavior and style
void abstract_hud_widget::initialize()
{
        // Set up basic style
        setWindowOpacity(0.75f);
        setContentsMargins(0, 0, 0, 0);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setStyleSheet(global <style_mgr>()->widget());
        global <main_view> g_window;
        setBaseSize(g_window->size().width(), g_window->height() / 4);
}

///// @brief    Process keyboard input while this widget has focus
//void abstract_hud_widget::keyPressEvent(QKeyEvent *a_event)
//{
//        QWidget::keyPressEvent(a_event);
//}


// Default Window Size
QSize abstract_hud_widget::sizeHint() const
{
        global <main_view> g_window;
        return QSize(g_window->size().width(), g_window->height() / 4);
}

// Minimum Window Size
QSize abstract_hud_widget::minimumSize() const
{
        global <main_view> g_window;
        return QSize(g_window->size().width(), g_window->height() / 4);
}

// Maximum Window Size
QSize abstract_hud_widget::maximumSize() const
{
        global <main_view> g_window;
        return QSize(g_window->size().width(), g_window->height() / 4);
}
