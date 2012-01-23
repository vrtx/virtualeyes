///////////////////////////////////////////////////////
// virtualeyes
//
// Copyright (c) 2011 - 2011 Benjamnin Becker
// All Rights Reserved
//
// @brief   This file defines the virtualeyes core singleton
// @author  ben
// @date    6/9/2011
///////////////////////////////////////////////////////

#ifndef VIRTUALEYES_HPP
#define VIRTUALEYES_HPP

#include "handle_base.hpp"
#include "handle.hpp"
#include "vscript.hpp"
#include "session.hpp"
#include <QObject>
#include <QThread>

namespace veyes {

    typedef map < QString, handle <realtime_feed> > rt_feed_map_t;
    class virtualeyes : public QObject,
                        public handle_base
    {
    Q_OBJECT
    public:
	    // Member Functions
	    virtualeyes();
	    virtual ~virtualeyes();
	    void initialize();
	    void finalize(int a_retval = 0);
        soft_handle<db> get_db();
        soft_handle<realtime_feed> init_rt_feed(const char *collection_name, int timeout = 50, bool load_initial = false);
	    // Core Singleton
	    static virtualeyes *instance;

	    // Composed Objects
	    handle <session> m_active_session;
	    handle <vscript> m_script_engine;
        handle <db> active_db;
    private:
        rt_feed_map_t m_rt_feeds;

    public slots:
        void new_session();             // register a new collection snapshot with the session

    signals:
        void update_active_session();   // signal new session creation

    };

}

#endif // VIRTUALEYES_HPP
