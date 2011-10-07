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

#include "console_widget.hpp"

console_widget::console_widget()
{

    setAttribute(Qt::WA_DeleteOnClose);

}

console_widget::~console_widget()
{

}

void console_widget::close_event(QCloseEvent *event)
{

        // simply accept all close requests
        event->accept();

        // TODO: event->ignore() if the project is unsaved

}
