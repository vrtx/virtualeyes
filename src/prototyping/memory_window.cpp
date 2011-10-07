///////////////////////////////////////////////////////
//
// virtualeyes
//
// Copyright (c) 2011 Benjamnin Becker
// All Rights Reserved
//
// @brief   This file defines the data widget reponsible for
//          displaying memory in hex, ascii, structure and assembly format.
//
// @author  Ben Becker
// @date    2/3/11
//
///////////////////////////////////////////////////////

#include "memory_window.hpp"

memory_window::memory_window()
{

    setAttribute(Qt::WA_DeleteOnClose);

}

memory_window::~memory_window()
{

}

void memory_window::close_event(QCloseEvent *event)
{

        // simply accept all close requests
        event->accept();

        // TODO: event->ignore() if the project is unsaved

}
