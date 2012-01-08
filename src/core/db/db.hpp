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
#include <QObject>
#include <QThread>
#include <client/dbclient.h>
#include <client/connpool.h>
#include <util/goodies.h>

using namespace mongo;
using namespace boost;

namespace veyes {

	// Database configuration details
	typedef struct db_connect_config {
		string hostname;
		int port;
		string user;
		string pass;
		bool read_only;
		int timeout;
	} db_config_t;

	// Access the centralized database
    class db : public QObject,
			   public handle_base
    {
    public:
	    // Member Functions
	    db();
	    virtual ~db();
		void set_config(const db_connect_config &config);
		void disconnect(bool force = false);
		bool connect(int timeout = 0);
		bool is_ready();
		auto_ptr <DBClientCursor> query(const string &ns, Query query=Query(), int nToReturn=0,
										int nToSkip=0, const BSONObj *fieldsToReturn=0, 
										int queryOptions=0, int batchSize=0);
	private:
		bool is_configured;
		ScopedDbConnection *conn;
		db_config_t config;
    };

}

#endif // VEYE_DB_HPP
