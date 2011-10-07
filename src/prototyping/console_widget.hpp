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

#ifndef VIRTUALEYES_CONSOLE_WINDOW_HPP
#define VIRTUALEYES_CONSOLE_WINDOW_HPP

#include <QtGui>
#include <QTextEdit>
#include "common.hpp"

namespace virtualeyes 
{

        ///////////////////////////////////////////////////////
        //
        /// @class   console_widget
        /// @brief   This class implements the widget reponsible for
        //           console interaction with virtualeyes.
        //
        ///////////////////////////////////////////////////////
        class console_widget : public QWidget
        {
        
                Q_OBJECT;

        public:

        	// Member Functions
                console_widget();
                virtual ~console_widget();

        	// Class variables

        protected:

                // handle a close event
                void close_event(QCloseEvent *event);

        private:

        	// Member variables

        };

}

#endif
