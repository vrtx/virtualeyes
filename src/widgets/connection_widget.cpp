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

#include "widgets/connection_widget.hpp"
#include "handle.hpp"
#include "virtualeyes.hpp"
#include "main_view.hpp"
#include "widgets/style_mgr.hpp"
#include "breakpoint.hpp"
#include "snapshot.hpp"
#include "vm_run.hpp"


/// @brief      Constructor
connection_widget::connection_widget(QScrollArea *parent) :
        handle_base(),
        m_connected(false)
{

}

/// @brief      Destructor
connection_widget::~connection_widget()
{
    // disconnect all signals
    disconnect(this, 0, 0, 0);
}

/// Handle the db has connected
void connection_widget::db_connected()
{
    m_connected = true;
}

/// Handle that the db is connecting
void connection_widget::db_connecting()
{
    m_connected = true;
}

/// Handle that the db has disconnected
void connection_widget::db_disconnected()
{
    m_connected = false;
}


/// @brief    Initialize the widget's behavior and style
void connection_widget::initialize()
{
        // Helpers
        global <style_mgr> g_style_mgr;
        global <main_view> g_main_view;

        // Include Base style
        abstract_hud_widget::initialize();

        // render background
        m_background = new QGraphicsRectItem(0, 0,
                                             25, 50,
                                             proxy, g_main_view->m_veye_scene.raw_ptr);
        m_background->setBrush(QBrush(QColor(0x60, 0x60, 0x60, 0x40)));
        m_background->setPen(QPen(QColor(0x00, 0x00, 0x00, 0x40)));

        // Set up basic style
        m_text_color = QColor(0xa5, 0xa3, 0xa0, 0xc0);
        m_connected_color = QColor(0xa5, 0xa3, 0xa0, 0x70);
        m_connecting_color = QColor(0xa5, 0xa3, 0xa0, 0x70);
        m_disconnected_color = QColor(0xa5, 0xa3, 0xa0, 0x70);
        r_connected_icon = new QGraphicsPixmapItem(QPixmap(":/connection/iconic/gray_light/clock_12x12.png"));
        r_connecting_icon = new QGraphicsPixmapItem(QPixmap(":/connection/iconic/gray_light/clock_12x12.png"));
        r_disconnected_icon = new QGraphicsPixmapItem(QPixmap(":/connection/iconic/gray_light/clock_12x12.png"));

        m_connect_button = new QPushButton("RT");
        // m_connect_button->setCheckable(true);
        m_connect_button->setDefault(false);
        proxy = g_main_view->m_veye_scene->addWidget(m_connect_button);
        connect(m_connect_button, SIGNAL(clicked()),
                this, SLOT(button_click()));

        setWindowOpacity(0.0f);
        setContentsMargins(0, 0, 0, 0);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setStyleSheet(g_style_mgr->button());
}

/// @brief Default Window Size
QSize connection_widget::sizeHint() const
{
        return QSize(50, 25);
}

/// @brief Minimum Window Size
QSize connection_widget::minimumSize() const
{
        return QSize(50, 25);
}

/// @brief Maximum Window Size
QSize connection_widget::maximumSize() const
{
        return QSize(0, 0);
}


/// @brief Handle the resize event and recalculate the connection
void connection_widget::resizeEvent(QResizeEvent *a_event)
{
    m_background->setRect(0, 0, width(), TIMELINE_HEADER_HEIGHT);
    QScrollArea::resizeEvent(a_event);
}
