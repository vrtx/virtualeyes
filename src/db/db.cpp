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

using namespace veyes;

// Static Initializations

// singleton instance
virtualeyes *virtualeyes::instance = NULL;

virtualeyes::virtualeyes() :
    handle_base()
{

}

virtualeyes::~virtualeyes()
{

}

void virtualeyes::realtime_feed::t_feed()
{
    
	DBClientConnection conn;
	const char *ns = "test.realtime_feed";
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
		// signal new message
        cout << o.toString() << endl;
    }
}
