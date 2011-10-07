///////////////////////////////////////////////////////
// virtualeyes
//
// Copyright (c) 2011 - 2011 Benjamnin Becker
// All Rights Reserved
//
// @brief   This file defines the main window and layout
// @author  ben
// @date    6/25/2011
///////////////////////////////////////////////////////

#ifndef VEYE_VSCRIPT_HPP
#define VEYE_VSCRIPT_HPP

#include <QScriptEngine>
#include <handle_base.hpp>

namespace veyes {

        class vscript : public handle_base
        {

        public:
            vscript();
            ~vscript();

            QScriptEngine core;

        signals:


        public slots:

        };

}

#endif // VSCRIPT_HPP
