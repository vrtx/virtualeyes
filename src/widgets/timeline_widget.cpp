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

#include "widgets/timeline_widget.hpp"
#include "handle.hpp"
#include "virtualeyes.hpp"
#include "main_view.hpp"
#include "widgets/style_mgr.hpp"
#include "breakpoint.hpp"
#include "snapshot.hpp"
#include "vm_run.hpp"
#include "session.hpp"


/// @brief      Constructor
timeline_widget::timeline_widget(QScrollArea *parent) :
        handle_base()
{

}

/// @brief      Destructor
timeline_widget::~timeline_widget()
{

        // disconnect all signals
        disconnect(this, 0, 0, 0);

}

/// @brief    Initialize the widget's behavior and style
void timeline_widget::connect_session()
{
        // add listeners for new runs, snapshots, breakpoints, etc.
        connect(global <virtualeyes>()->m_active_session.raw_ptr, SIGNAL(snapshot_added(const veyes::handle <snapshot> &)),
                this, SLOT(add_snapshot(const veyes::handle <snapshot> &)));
        connect(global <virtualeyes>()->m_active_session.raw_ptr, SIGNAL(breakpoint_added(const veyes::handle <breakpoint> &)),
                this, SLOT(add_breakpoint(const veyes::handle <breakpoint> &)));
        connect(global <virtualeyes>()->m_active_session.raw_ptr, SIGNAL(vm_run_added(const veyes::handle <vm_run> &)),
                this, SLOT(add_vm_run(const veyes::handle <vm_run> &)));
}

/// @brief    Initialize the widget's behavior and style
void timeline_widget::initialize()
{
        // Helpers
        global <style_mgr> g_style_mgr;
        global <main_view> g_main_view;

        // Include Base style
        abstract_hud_widget::initialize();

        // Set up basic style
        m_text_fg_color = QColor(0xa5, 0xa3, 0xa0, 0xc0);
        m_text_bg_color = QColor(0xa5, 0xa3, 0xa0, 0x70);
        setWindowOpacity(0.0f);
        setContentsMargins(0, 0, 0, 0);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setStyleSheet(g_style_mgr->widget());

        // load the icons
        // r_expand =      new QGraphicsPixmapItem(QPixmap(":/icons/scroll_arrow_vert_tan.png"));
        // r_collapse =    new QGraphicsPixmapItem(QPixmap(":/icons/iconic/black/cog_alt_32x32.png"));
        // r_snapshot =    new QGraphicsPixmapItem(QPixmap(":/icons/iconic/black/cog_alt_32x32.png"));
        // r_breakpoint =  new QGraphicsPixmapItem(QPixmap(":/icons/iconic/blue/fork_28x32.png"));
        // r_watchpoint =  new QGraphicsPixmapItem(QPixmap(":/icons/scroll_arrow_vert_tan.png"));
        // r_start =       new QGraphicsPixmapItem(QPixmap(":/icons/scroll_arrow_vert_tan.png"));
        // r_stop =        new QGraphicsPixmapItem(QPixmap(":/icons/scroll_arrow_vert_tan.png"));
        // r_notes =       new QGraphicsPixmapItem(QPixmap(":/icons/scroll_arrow_vert_tan.png"));
        r_playhead =    new QGraphicsPixmapItem(QPixmap(":/timeline/iconic/green/first_8x8.png"));
        r_clock_icon =  new QGraphicsPixmapItem(QPixmap(":/timeline/iconic/gray_light/clock_12x12.png"));

        // initialize timeline header items
        m_timeline_header = new QGraphicsRectItem(0, 0,
                                                  width(), TIMELINE_HEADER_HEIGHT,
                                                  proxy, g_main_view->m_veye_scene.raw_ptr);
        m_timeline_header->setBrush(QBrush(QColor(0x60, 0x60, 0x60, 0x40)));
        m_timeline_header->setPen(QPen(QColor(0x00, 0x00, 0x00, 0x40)));

//        m_timeline_start_label = new QGraphicsSimpleTextItem(QDateTime::currentDateTime().toString("M/d/yy hh:mm:ss.zzz"), m_timeline_header,
//                                                             g_main_view->m_veye_scene.raw_ptr);
//        m_timeline_start_label->setPen(QPen(global <style_mgr>()->m_clock_font_pen_color));
//        m_timeline_start_label->setBrush(QBrush(global <style_mgr>()->m_clock_font_brush_color));
//        m_timeline_start_label->setFont(global <style_mgr>()->m_clock_font);
//        m_timeline_start_label->setToolTip(QDateTime::currentDateTime().toString("ddd MMMM d, yyyy   h:m:s.zzz ap"));
//        m_timeline_start_label->setPos(25, 4);
//        m_timeline_end_label = new QGraphicsSimpleTextItem(QDateTime::currentDateTime().toString("hh:mm:ss.zzz"), m_timeline_header,
//                                                           g_main_view->m_veye_scene.raw_ptr);
//        m_timeline_end_label->setPen(QPen(m_text_bg_color));
//        m_timeline_end_label->setBrush(QBrush(m_text_fg_color));
//        m_timeline_end_label->setFont(QFont("courier", 10));
//        m_timeline_end_label->setPos(width() - m_timeline_end_label->boundingRect().width(), 1);


        // Add icons to the scene
        // g_main_view->m_veye_scene->addItem(r_playhead);
        // g_main_view->m_veye_scene->addItem(r_clock_icon);

        // Position the icons
        // r_playhead->setOpacity(0.6f);
        // r_playhead->rotate(90);
        // r_playhead->setPos(width() / 2, 0);
        // r_playhead->setFlag(QGraphicsItem::ItemIsMovable);
        // r_clock_icon->setOpacity(0.4f);
        // r_clock_icon->setPos(4, 3);
        // r_clock_icon->setToolTip(QDateTime::currentDateTime().toString("ddd MMMM d, yyyy   h:m:s.zzz ap"));

//        int cur_pos = width();
//        r_expand->setPos(cur_pos -= r_expand->boundingRect().width(), 0);
//        r_expand->show();
//        r_collapse->setPos(80, 60);
//        r_collapse->show();
//        r_snapshot->setPos(100, 100);
//        r_snapshot->show();
//        r_breakpoint->show();

}

///// @brief    Process keyboard input while this widget has focus
//void timeline_widget::keyPressEvent(QKeyEvent *a_event)
//{
//        QWidget::keyPressEvent(a_event);
//}


/// @brief Default Window Size
QSize timeline_widget::sizeHint() const
{
        global <main_view> g_window;
        return QSize(g_window->size().width(), 25);
}

/// @brief Minimum Window Size
QSize timeline_widget::minimumSize() const
{
        return QSize(0, 25);
}

/// @brief Maximum Window Size
QSize timeline_widget::maximumSize() const
{
        return QSize(0, 0);
}


/// @brief Handle the resize event and recalculate the timeline
void timeline_widget::resizeEvent(QResizeEvent *a_event)
{
    // recalculate the width of the timeline and ticks
    m_timeline_header->setRect(0, 0, width(), TIMELINE_HEADER_HEIGHT);
//    m_timeline_end_label->setPos(width() - m_timeline_end_label->boundingRect().width() - 1, 4);
    update_timeline_width(a_event->size().width());
    r_playhead->setPos(width() / 2, 0);

    QScrollArea::resizeEvent(a_event);
}

/// @brief Recalculate the timeline based on the supplied width
void timeline_widget::update_timeline_width(quint32 a_width)
{
    // helpers
    global <main_view> g_main_view;

    // number of ticks to draw
    quint32 num_ticks = (a_width -
                         TIMELINE_COLUMN_WIDTH) /
                        TIMELINE_TICK_WIDTH;

    // TODO: OPTIMIZE:  don't do anything if the timeline hasn't changed sufficiently

    // purge old data
    for (line_item_vector_t::iterator i_item = m_visible_ticks.begin();
         i_item != m_visible_ticks.end();
         ++i_item) {
        // remove each old item from the scene and delete
        g_main_view->m_veye_scene->removeItem(*i_item);
        delete *i_item;
    }
    for (text_item_vector_t::iterator i_item = m_visible_tick_labels.begin();
         i_item != m_visible_tick_labels.end();
         ++i_item) {
        // remove each old item from the scene and delete
        g_main_view->m_veye_scene->removeItem(*i_item);
        delete *i_item;
    }
    m_visible_ticks.clear();
    m_visible_tick_labels.clear();

    // add updated ticks to the scene
    for (quint32 i = 0; i < num_ticks; ++i) {
        // for each tick
        QGraphicsLineItem * l_tick;
        if (i % 10 == 0) {
            // every 10th tick
            l_tick = new QGraphicsLineItem(TIMELINE_COLUMN_WIDTH + i * TIMELINE_TICK_WIDTH, 1,
                                           TIMELINE_COLUMN_WIDTH + i * TIMELINE_TICK_WIDTH, TIMELINE_HEADER_HEIGHT / 3, NULL, g_main_view->m_veye_scene.raw_ptr);
            // draw a label
            // QGraphicsSimpleTextItem *l_label = new QGraphicsSimpleTextItem(QDateTime::currentDateTime().toString("hh:mm:ss.zzz"), NULL,
            //                                                                g_main_view->m_veye_scene.raw_ptr);
            QGraphicsSimpleTextItem *l_label = new QGraphicsSimpleTextItem("00:00:01", NULL, g_main_view->m_veye_scene.raw_ptr);
            l_label->setPen(QPen(global <style_mgr>()->m_default_font_pen_color));
            l_label->setBrush(QBrush(global <style_mgr>()->m_default_font_brush_color));
            l_label->setFont(global <style_mgr>()->m_timeline_font);
            l_label->setPos(TIMELINE_COLUMN_WIDTH + 4 + i * TIMELINE_TICK_WIDTH, 5);
            m_visible_tick_labels.push_back(l_label);
        } else {
            // draw a normal tick
            l_tick = new QGraphicsLineItem(TIMELINE_COLUMN_WIDTH + i * TIMELINE_TICK_WIDTH, 1,
                                           TIMELINE_COLUMN_WIDTH + i * TIMELINE_TICK_WIDTH, TIMELINE_HEADER_HEIGHT / 6, NULL, g_main_view->m_veye_scene.raw_ptr);
        }

        l_tick->setPen(QPen(m_text_bg_color));
        m_visible_ticks.push_back(l_tick);
    }

}



// Rendering:

//// paint a minor tick at a_point
// void timeline_widget::paint_minor_tick(QPoint &a_point) const;

//// paint a tick at a_point
// void timeline_widget::paint_major_tick(QPoint &a_point) const;

//// paint the playhead
// void timeline_widget::paint_playhead(QPoint &a_point) const;

// void timeline_widget::paint_tick_labels() const;
// {
//  - tick_width = 20px
//  - # ticks visible @ LoD = (width() -
//                             widthof(start_time) -
//                             widthof(end_time)) / tick_width
// }

//// Calculate ideal LoD:
//void timeline_widget::calculate_ideal_lod()
//{

//}



// Levels of Detail
// - 1 tick per 1ms
// - 1 tick per 10ms
// - 1 tick per 100ms
// - 1 tick per second
// - 1 tick per minute
// - 1 tick per hour
// - 1 tick per day


// Note: Timeline is always in VM system time
// Draw VM settings text [name, image path, OS, start time, current VM time, current time]
//  - VM Name
//  - Image File Name
//  - OS Name
//  - Current Host Clock
//  - Selected VM Time (current while machine is running).
//  - VM Initial Start Time
// Draw timeline track background:
//  - Track Header
//    - Borders
//    - Run Name
//    - Breakpoint icon -- icon with proportional color for each BP encountered
// Draw horizontal scrollbar
// Draw timeline header within bounding rect
//  - Draw label for start time
//  - Draw label for end time
//  - Draw interval ticks according to LOD
// Draw timestamp every 10th tick
// Draw line in each track from [start_time, end_time]
// Draw branch lines
// Draw node icons
// Draw edge indicators/effects
// Draw expand button

// Event transitions:
//  On Resize:
//    - update visible timeline ticks
//  On Hover
//  On Click
//  On ScrollWheel

// Node types:
// -----------
// Full VM Snapshot
// Full Memory Snapshot
// Disk Snapshot


// On selection of new [breakpoint, snapshot,


// @brief      Add a new snapshot to the timeline widget
// @param[in]  a_snapshot   The snapshot object to add to the timeline widget
void timeline_widget::add_snapshot(const veyes::handle <snapshot> &a_snapshot)
{
        VDEBUG(0, "added new snapshot to the timeline_widget's list");
//        QGraphicsPixmapItem *l_snapshot_img = new QGraphicsPixmapItem(QPixmap(":/icons/iconic/blue/fork_28x32.png"), proxy, global <main_view>()->m_veye_scene.raw_ptr);
//        l_snapshot_img->rotate(270);
//        l_snapshot_img->setOpacity(0.75f);
//        l_snapshot_img->setPos((a_snapshot.id - 4) * (l_snapshot_img->boundingRect().width() / 2), (a_snapshot.id - 4) * (l_snapshot_img->boundingRect().height() / 4));
}

// @brief      Add a new breakpoint to the timeline widget
// @param[in]  a_breakpoint   The breakpoint object to add to the timeline widget
void timeline_widget::add_breakpoint(const veyes::handle <breakpoint> &a_breakpoint)
{
        VDEBUG(0, "added new breakpoint to the timeline_widget's list");
}

// @brief      Add a new vm_run to the timeline widget
// @param[in]  a_vm_run   The vm_run object to add to the timeline widget
void timeline_widget::add_vm_run(const veyes::handle <vm_run> &a_vm_run)
{
        VDEBUG(0, "added new vm run to the timeline_widget's list");
}

