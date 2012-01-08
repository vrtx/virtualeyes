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

#ifndef FEED_DB_HPP
#define FEED_DB_HPP

#include "handle_base.hpp"
#include "handle.hpp"
#include "soft_handle.hpp"
#include <QObject>
#include <QThread>
#include "db.hpp"

namespace veyes {

	class realtime_feed : public QThread,
						  public handle_base
	{
	public:
		realtime_feed(const soft_handle<db> &a_db, const QString &a_collection, int a_interval = 1);
		virtual ~realtime_feed();			
	    virtual void run();

	private:
		void t_feed();
		soft_handle<db> active_db;
		QString collection;
		int interval;

	};

}

#endif // FEED_DB_HPP
