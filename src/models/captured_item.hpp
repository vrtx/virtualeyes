///////////////////////////////////////////////////////
// virtualeyes
//
// Copyright (c) 2011 - 2011 Benjamnin Becker
// All Rights Reserved
//
// @brief   This file defines the model for a captured item
// @author  ben becker
// @date    9/17/2011
///////////////////////////////////////////////////////

#ifndef CAPTURED_ITEM_HPP
#define CAPTURED_ITEM_HPP

#include <QObject>
#include "handle.hpp"
#include "handle_base.hpp"

namespace veyes {

    enum class item_t  : uint8_t
    {
        memory_region = 0,
        memory_address,
        memory,
        disk_region,
        disk_address,
        disk,
        file_region,
        file_offset,
        file,
        process,
        thread,
        interrupt_handler,
        kernel_base_struct,
        cpu,
        reg,
        stack,
        video,
        keyboard,
        mouse
    };

    class captured_item : public QObject
    {
        Q_OBJECT
    public:
        explicit captured_item(QObject *parent = 0);

    signals:

    public slots:

    };

    class file : public captured_item,
                 public handle_base {
        string path;
        set <soft_handle <file_region>,     // container of all regions, ordered by offset then time.
             compare_time_offset_less <soft_handle <file_region> > > regions;
        uint64_t absolute_size;
        uint64_t estimated_size;
        string raw_struct;                  // raw file struct as reported by the OS.  TODO: convert to memory_region
        // setters/getters with parent/child traversal
    };

    class file_region : public captured_item
                        public handle_base {
    public:
        handle <file> parent_file;
        uint64_t offset_begin;
        uint64_t offset_end;
    };


}

#endif // CAPTURED_ITEM_HPP
