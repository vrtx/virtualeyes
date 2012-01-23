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
/// @param a_db		db to connect to
/// @param a_ns		namespace to read from (eg. database.collection)
realtime_feed::realtime_feed(const soft_handle<db> &a_db, const QString &a_ns, int a_interval_ms) :
	active_db(a_db),
	collection(a_ns),
	interval(a_interval_ms)
{ 
}

// dtor
realtime_feed::~realtime_feed()
{	
}

void realtime_feed::run() 
{
	t_feed();
    // exec(); // start qt event loop for this thread
}

// get a realtime feed (runs in it's own thread)
void realtime_feed::t_feed()
{
    BSONElement lastId = minKey.firstElement();
    Query query = Query();  // load everything (TODO:  set realtime feed instance's collection and query)

    while ( true ) {
        // until thread is canceled

        try {

            if (!active_db->is_ready()) {
                // db error; sleep and retry
                active_db->connect();
                // QThread::msleep(500);
                continue;
            }

            auto_ptr<DBClientCursor> c = active_db->query(collection.toStdString(), query, 
                                                          0, 0, 
                                                          0, QueryOption_CursorTailable);

            while (active_db->is_ready()) {
        		// while new data can be read
                // TODO: create async-friendly db iface
                if (!c->more()) {
                    if (c->isDead())
                        break;    // cursor inactive; retry

                    // all available data has been read.  busywait.
                    QThread::msleep(interval);
                    continue;
                }

                BSONObj o = c->next();
                lastId = o["_id"];
                VDEBUG(0, o.toString().c_str());
                // emit new_event(o);  // emit the event
            }

        } catch(const DBException &e) {
            VDEBUG(0, "Database Error: " << e.what());
        }

        // db disconnect or failed read. sleep and retry
        QThread::msleep(500);

    }

}
