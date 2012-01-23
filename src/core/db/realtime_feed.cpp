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
#include "virtualeyes.hpp"
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

    // connect Qt signals
	connect(this, SIGNAL(new_event(const BSONObj)),
            global <virtualeyes>()->m_active_session.raw_ptr, SLOT(process_new_event(const BSONObj)));

    BSONElement lastId = minKey.firstElement();

    while ( true ) {
        // until thread is canceled

        try {

            if (!active_db->is_ready()) {
                // db error; sleep until reconnected
                // active_db->connect();
                QThread::msleep(500);
                continue;
            }

            auto_ptr<DBClientCursor> c = active_db->query(collection.toStdString(), QUERY("_id" << GTE << lastId), 
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
                if (o.isValid()) {
                    lastId = o["_id"];
                    BSONObj ev_o = o.copy();
                    emit new_event(ev_o);  // emit the event
                }
            }

        } catch(const DBException &e) {
            // VDEBUG(0, "Database Error: " << e.what());
        }

        // db disconnect or failed read. sleep and retry
        QThread::msleep(500);

    }

}
