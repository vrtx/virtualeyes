///////////////////////////////////////////////////////
// virtualeyes
//
// Copyright (c) 2011 - 2011 Benjamnin Becker
// All Rights Reserved
//
// @brief   database interface (including real-time tailable collections)
// @author  ben
// @date    1/7/12
///////////////////////////////////////////////////////

#ifndef VEYE_DB_HPP
#define VEYE_DB_HPP

#include "handle_base.hpp"
#include "handle.hpp"
#include "session.hpp"
#include <QObject>
#include <QThread>
#include <client/dbclient.h>
#include <util/goodies.h>

using namespace mongo;

namespace veyes {

    class db : public QOBJECT,
			   public handle_base
    {
	QOBJECT
    public:
	    // Member Functions
	    db();
	    virtual ~db();
	    void connect();
	    void disconnect(int active_count = 0);
		
	public:
		// nested realtime data colletion thread
		class realtime_feed : public QThread
		{
		public:
		    void run()
			{
				t_feed();
			    // exec(); // start qt event loop for this thread
			}
		private:
			void t_feed();

		};

		realtime_feed test_feed;

    };

}

#endif // VEYE_DB_HPP
