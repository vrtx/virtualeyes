///////////////////////////////////////////////////////
// virtualeyes
//
// Copyright (c) 2011 - 2011 Benjamnin Becker
// All Rights Reserved
//
// @brief   This file defines the main window and layout
// @author  ben
// @date    6/9/2011
///////////////////////////////////////////////////////

#include "virtualeyes.hpp"
#include "main_view.hpp"
#include "main_window.hpp"
#include "common.hpp"
#include "session.hpp"
#include "widgets/style_mgr.hpp"
#include "core/enum_convert.hpp"

#include <client/dbclient.h>
#include <util/goodies.h>

using namespace veyes;

// Static Initializations

// singleton instance
virtualeyes *virtualeyes::instance = NULL;

virtualeyes::virtualeyes() :
    handle_base()
{

}

// @brief      Get the active DB connection
soft_handle<db> virtualeyes::get_db()
{
	if (active_db.is_valid())
		// connection exists
		return active_db;
    return (db*)NULL;
}

// @brief      Add a new realtime feed to this session
// @param[in]  a_snapshot   The snapshot object to add to the session
soft_handle <realtime_feed> virtualeyes::init_rt_feed(const char *collection_name, int timeout, bool load_initial)
{
    handle <realtime_feed> retval = new realtime_feed(get_db(), collection_name, timeout);
    m_rt_feeds.insert(pair <const char *, handle <realtime_feed> >(collection_name, retval));
    retval->start();

    return retval;
}

void virtualeyes::initialize()
{
    // initialize the enum maps
    enum_initializer();

    // initialize the main window and view
    global <main_window> g_main_window;
    global <main_view> g_main_view;
    g_main_view->initialize();
    g_main_window->initialize();

    g_main_window->showMaximized();  // start fullscreen
    // TODO: FEATURE: save window geom state on exit and restore here.

    // init blank session
    m_active_session = handle <session>(new session);
    m_active_session->attach("localhost:1234");

    // initialize the db
    qRegisterMetaType <BSONObj>("BSONObj");
    db_config_t db_config;
    db_config.hostname="localhost";
    db_config.port=27017;
    db_config.read_only=true;
    active_db = new db;
    active_db->set_config(db_config);

    // g_main_view->m_timeline_widget->connect_session();

    // connect the snapshot -> veye_scene signal indicating a snapshot has been added
    connect(m_active_session.raw_ptr, SIGNAL(snapshot_added(const veyes::handle <snapshot> &)),
            g_main_view.raw_ptr, SLOT(add_snapshot(const veyes::handle <snapshot> &)));

    // connect the db signals
    connect(active_db.raw_ptr, SIGNAL(connected()),
            g_main_view->m_connection_widget.raw_ptr, SLOT(db_connected()));
    connect(active_db.raw_ptr, SIGNAL(connecting()),
            g_main_view->m_connection_widget.raw_ptr, SLOT(db_connecting()));
    connect(active_db.raw_ptr, SIGNAL(disconnected()),
            g_main_view->m_connection_widget.raw_ptr, SLOT(db_disconnected()));
    connect(active_db.raw_ptr, SIGNAL(disconnected_error()),
            g_main_view->m_connection_widget.raw_ptr, SLOT(db_disconnected())); // TODO: db connection error signal

    // db buttons
    connect(active_db.raw_ptr, SIGNAL(connected()),
            g_main_view->m_connection_widget.raw_ptr, SLOT(db_connected()));
    connect(active_db.raw_ptr, SIGNAL(connected()),
            g_main_view->m_connection_widget.raw_ptr, SLOT(db_connected()));

    connect(g_main_view->m_connection_widget.raw_ptr, SIGNAL(do_connect()),
            active_db.raw_ptr, SLOT(connect()));
    connect(g_main_view->m_connection_widget.raw_ptr, SIGNAL(do_disconnect()),
            active_db.raw_ptr, SLOT(disconnect()));

    // initialize the interpreter
    m_script_engine = handle <vscript>(new vscript);

    // connect to the db
    active_db->connect();

    // create a new realtime feed
	init_rt_feed("test.realtime_feed", 50);

}

void virtualeyes::finalize(int a_retval)
{
//    if (m_script_engine.is_valid()) {
//            m_script_engine->core.abortEvaluation();
//    }

    // destroy the globals
    global <main_view>().destroy();
    global <main_window>().destroy();
    global <style_mgr>().destroy();

}

virtualeyes::~virtualeyes()
{

}

/// @brief      New session created (slot)
void virtualeyes::new_session()
{
    emit update_active_session();
}
