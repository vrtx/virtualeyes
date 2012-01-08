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

#include "db.hpp"
#include "common.hpp"
#include "core/enum_convert.hpp"

using namespace veyes;

// Static Initializations

// ctor
db::db() :
	handle_base(),
	is_configured(false),
	conn(NULL),
	config()
{
}

// dtor
db::~db()
{
}

void db::set_config(const db_connect_config &a_config)
{
	config = a_config;
	is_configured = true;
}

// connect to the db
/// @return  true on success, false on failure
bool db::connect(int timeout)
{
	conn = new ScopedDbConnection(config.hostname + ":" + boost::lexical_cast <string>(config.port), timeout);
	return is_ready();
}

void db::disconnect(bool force)
{
	if (force)
		conn->kill();
	else
		conn->done();
}

bool db::is_ready()
{
	return conn->ok();
}

// Query the central DB
// BB TODO: clean up this wrapper
auto_ptr <DBClientCursor> db::query(const string &ns, Query query, int nToReturn,
									int nToSkip, const BSONObj *fieldsToReturn, 
									int queryOptions, int batchSize) {
	if (!is_ready())
		throw vexcept("Database connection is not ready");

	return conn->get()->query(ns, query, nToReturn, nToSkip, 
							  fieldsToReturn, queryOptions, batchSize);
}
