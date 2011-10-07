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

#include "list_view.hpp"

list_view::list_view()
{

    setAttribute(Qt::WA_DeleteOnClose);

}

list_view::~list_view()
{

}

void list_view::close_event(QCloseEvent *event)
{

        // simply accept all close requests
        event->accept();

        // TODO: event->ignore() if the project is unsaved

}
