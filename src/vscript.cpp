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

#include "common.hpp"
#include "vscript.hpp"
#include "virtualeyes.hpp"
#include "range_map.hpp"

/// @brief  ctor
vscript::vscript() :
        handle_base()
{

        // Create the object bindings
        QScriptValue b_session = core.newQObject(global <virtualeyes>()->m_active_session.raw_ptr);
        core.globalObject().setProperty("session", b_session);

        QScriptValue b_range_map = core.newQObject(global <range_map>().raw_ptr);
        core.globalObject().setProperty("range_map", b_range_map);


//        QScriptValue b_session = core.newQObject(global <virtualeyes>()->m_active_session.raw_ptr);
//        core.globalObject().setProperty("session", b_session);


}

/// @brief  dtor
vscript::~vscript()
{

}



