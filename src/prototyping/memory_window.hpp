///////////////////////////////////////////////////////
//
// virtualeyes
//
// Copyright (c) 2011 Benjamnin Becker
// All Rights Reserved
//
/// @author  Ben Becker
/// @date    2/3/11
//
///////////////////////////////////////////////////////

#ifndef VIRTUALEYES_MEMORY_WINDOW_HPP
#define VIRTUALEYES_MEMORY_WINDOW_HPP

#include <QtGui>
#include <QTextEdit>
#include "common.hpp"

namespace virtualeyes 
{

        ///////////////////////////////////////////////////////
        //
        /// @class   memory_window
        /// @brief   This class implements the widget reponsible for
        //           displaying memory in hex, ascii, structure and assembly format.
        //
        ///////////////////////////////////////////////////////
        class memory_window : public QWidget
        {
        
                Q_OBJECT;

        public:

        	// Member Functions
                memory_window();
                virtual ~memory_window();

        	// Class variables

        protected:

                // handle a close event
                void close_event(QCloseEvent *event);

        private:

        	// Member variables

        };

}

#endif
