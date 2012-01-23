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
    try {
        if (conn == NULL || !conn->ok()) {
            // create a new connection
            conn = new ScopedDbConnection(config.hostname + ":" + boost::lexical_cast <string>(config.port), timeout);
            emit connecting();
        }

    } catch(const DBException &e) {
        VDEBUG(2, "Database Exception: " << e.what());
        emit disconnected_error();
        return false;
    }

    if (is_ready())
        emit connected();

    return is_ready();
}

void db::disconnect(bool force)
{
    if (conn == NULL) {
        VDEBUG(5, "Cannot disconnect a null connection");
        return;
    }

    if (force)
        conn->kill();
    else
        conn->done();
    VDEBUG(9, "Disconnected from databasae");
    emit disconnected();
}

bool db::is_ready()
{
    return conn != NULL && conn->ok();
}

// Query the central DB
// BB TODO: clean up this wrapper
auto_ptr <DBClientCursor> db::query(const string &ns, Query query, int nToReturn,
                                    int nToSkip, const BSONObj *fieldsToReturn, 
                                    int queryOptions, int batchSize) {
    try {

        if (!is_ready())
            throw vexcept("Database connection is not ready");
        return conn->get()->query(ns, query, nToReturn, nToSkip, 
                                  fieldsToReturn, queryOptions, batchSize);

    } catch(const DBException &e) {
        emit disconnected_error();
        throw vexcept((string)"Database Exception: " + e.what());
    }

}
