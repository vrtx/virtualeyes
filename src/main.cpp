///////////////////////////////////////////////////////
//
// virtualeyes
//
// Copyright (c) 2011 Benjamnin Becker
// All Rights Reserved
//
// @brief   This file defines the main entry point into the virtualeyes
//          executable.
//
// @author  Ben Becker
// @date    2/3/11
//
///////////////////////////////////////////////////////


// Includes
#include <QtGui/QApplication>
#include "common.hpp"
#include "handle.hpp"
#include "session.hpp"
#include "virtualeyes.hpp"


// main entry point
int main(int argc, char *argv[])
{

        // Germinate the random seed
        qsrand(2);

        // Instantiate the Qt application
        QApplication l_application(argc, argv);  // BB TODO: customize argv's before release.
        QCoreApplication::setApplicationName("virtualeyes");
        global <virtualeyes> g_virtualeyes;

        // Initialize and run the main application event loop
        g_virtualeyes->initialize();
        int retval = l_application.exec();
        // QApplication has exited

        g_virtualeyes->finalize(retval);
        g_virtualeyes.destroy();

        return retval;

}
