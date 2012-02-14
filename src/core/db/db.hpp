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
#include <QMutex>
#include <client/dbclient.h>
#include <client/connpool.h>
#include <bson/bson.h>

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
    Q_OBJECT;
    public:
        db();
        virtual ~db();
        void set_config(const db_connect_config &config);
        bool is_ready();
        void connect_signals();
        auto_ptr <DBClientCursor> query(const string &ns, Query query=Query(), int nToReturn=0,
                                        int nToSkip=0, const BSONObj *fieldsToReturn=0, 
                                        int queryOptions=0, int batchSize=0);

    signals:
        void connecting();
        void connected();
        void disconnected();
        void disconnected_error();

    public slots:
        bool connect(int timeout = 0);
        void disconnect(bool force = false);

    private:
        bool is_configured;
        ScopedDbConnection *conn;
        db_config_t config;
        mutable QMutex db_mutex;
    };

}

#endif // VEYE_DB_HPP
