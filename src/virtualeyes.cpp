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
using namespace mongo;

// Static Initializations

// singleton instance
virtualeyes *virtualeyes::instance = NULL;

virtualeyes::virtualeyes() :
    handle_base()
{

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
    //        g_main_window->showMaximized();  // start fullscreen
    // TODO: FEATURE: save window geom state on exit and restore here.

    // init blank session
    m_active_session = handle <session>(new session);
    m_active_session->attach("localhost:1234");

    g_main_view->m_timeline_widget->connect_session();

    // connect the snapshot -> veye_scene signal indicating a snapshot has been added
    connect(m_active_session.raw_ptr, SIGNAL(snapshot_added(const veyes::handle <snapshot> &)),
            g_main_view.raw_ptr, SLOT(add_snapshot(const veyes::handle <snapshot> &)));

    // initialize the interpreter
    m_script_engine = handle <vscript>(new vscript);
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

	test_feed.start();
}



void virtualeyes::realtime_feed::t_feed()
{
    
	DBClientConnection conn;
	const char *ns = "realtime_feed";
    string errmsg;

    if (!conn.connect(string( "127.0.0.1:27017") , errmsg )) {
        cout << "couldn't connect : " << errmsg << endl;
        throw -11;
    }
	
    BSONElement lastId = minKey.firstElement();
    Query query = Query();

    auto_ptr<DBClientCursor> c =
        conn.query(ns, query, 0, 0, 0, QueryOption_CursorTailable);

    while( 1 ) {
        if( !c->more() ) {
            if( c->isDead() ) {
                break;    // we need to requery
            }

            // all data (so far) exhausted, wait for more
            sleepsecs(1);
            continue;
        }
        BSONObj o = c->next();
        lastId = o["_id"];
        cout << o.toString() << endl;
    }
}
