///////////////////////////////////////////////////////
// db
//
// Copyright (c) 2011 - 2011 Benjamnin Becker
// All Rights Reserved
//
// @brief   This file defines the main window and layout
// @author  ben
// @date    6/9/2011
///////////////////////////////////////////////////////

#include "realtime_feed.hpp"
#include "common.hpp"

#include "main_view.hpp"

using namespace veyes;

// ctor
realtime_feed::realtime_feed(const soft_handle<db> &a_db, const QString &a_collection) :
	active_db(a_db),
	collection(a_collection) 
{ 
}

// dtor
realtime_feed::~realtime_feed()
{	
}

void realtime_feed::run() {
	t_feed();
    // exec(); // start qt event loop for this thread
}

// get a realtime feed (runs in it's own thread)
void realtime_feed::t_feed()
{	
	// set up the connection
	if (!active_db->is_ready())
		return;
	
    BSONElement lastId = minKey.firstElement();
    Query query = Query();

    auto_ptr<DBClientCursor> c = active_db->query(collection.toStdString(), query, 0, 0, 0, QueryOption_CursorTailable);

    while (true) {
		// while new data can be read
        if (!c->more()) {
            if (c->isDead())
                break;    // cursor inactive; retry

            // all available data has been read.  busywait.
            sleep(1);
            continue;
        }

        BSONObj o = c->next();
        lastId = o["_id"];
		// log results to console
        global <main_view>()->m_console_widget->append(QString(o.toString().c_str()), text_format_t::STANDARD, 1);
    }

}
