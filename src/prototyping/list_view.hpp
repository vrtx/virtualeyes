///////////////////////////////////////////////////////
//
// virtualeyes
//
// Copyright (c) 2011 Benjamnin Becker
// All Rights Reserved
//
// @author  Ben Becker
// @date    2/3/11
//
///////////////////////////////////////////////////////

#ifndef VIRTUALEYES_LIST_VIEW_HPP
#define VIRTUALEYES_LIST_VIEW_HPP

#include <QtGui>
#include <QListWidget>
#include "common.hpp"

namespace virtualeyes {

        ///////////////////////////////////////////////////////
        //
        /// @class   list_view
        /// @brief   This class implements a list-based view of all
        //           memory regions.
        //
        ///////////////////////////////////////////////////////
        class list_view : public QListWidget
        {

                Q_OBJECT;

        public:

                // Member Functions
                list_view();
                virtual ~list_view();

                // Class variables

        protected:

                // handle a close event
                void close_event(QCloseEvent *event);

        private:

                // Member variables

        };

}

#endif
