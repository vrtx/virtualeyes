///////////////////////////////////////////////////////
// virtualeyes
//
// Copyright (c) 2011 - 2012 Benjamnin Becker
// All Rights Reserved
//
// @brief   This file defines the range_map core singleton
// @author  ben
// @date    4/30/2012
///////////////////////////////////////////////////////

#ifndef RANGE_MAP_HPP
#define RANGE_MAP_HPP

#include "handle_base.hpp"
#include "handle.hpp"
#include "vscript.hpp"
#include "session.hpp"
#include <QObject>
#include <QThread>
#include <QFile>

namespace veyes {

    class range_map : public QObject,
                      public handle_base
    {
    Q_OBJECT
    public:
	    // Member Functions
	    range_map();
	    virtual ~range_map();

        void parse_file(const QString &fname) {
            QFile f(fname);
            QTextStream in(&f);
            QString line = in.readLine();
            while (!line.isNull()) {
                addrs.insert(1ULL);
                line = in.readLine();
            }
        }

	    // Core Singleton
	    static range_map *instance;

    private:
        set <uint64_t> addrs;
    public slots:
 
    signals:
 
    };

}

#endif // range_map_HPP
