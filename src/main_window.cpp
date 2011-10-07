///////////////////////////////////////////////////////
// virtualeyes
//
// Copyright (c) 2011 Benjamnin Becker
// All Rights Reserved
//
// @brief   This file defines the main window
//
// @author  Ben Becker
// @date    2/3/11
///////////////////////////////////////////////////////

#include "main_window.hpp"
#include "virtualeyes.hpp"
#include "main_view.hpp"
#include <QtGui>

// Statics
main_window *main_window::instance = NULL;

// default ctor
main_window::main_window(QMainWindow *parent) :
    QMainWindow(parent)
{
    setWindowTitle("virtualeyes");
    setAttribute(Qt::WA_NoSystemBackground);
    setCentralWidget(global <main_view>().raw_ptr);
}

// dtor
main_window::~main_window()
{

}

/// @brief  Initialize the main window
void main_window::initialize()
{
    show();
}

/// @brief    Process keyboard input while this widget has focus
void main_window::keyPressEvent(QKeyEvent *a_event)
{
    switch (a_event->key()) {
    case Qt::Key_1:
        if (a_event->modifiers() & Qt::MetaModifier ||
            a_event->modifiers() & Qt::ControlModifier) {
            // Control-1 -- add a test breakpoint
            veyes::handle <breakpoint> l_bp(new breakpoint);
            l_bp->breakpoint_name = "test";
            l_bp->handle_bp();

            // add to list widget
            QList <QTreeWidgetItem *> tree_items;
            tree_items.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("Synth BP ").append(QString(boost::lexical_cast <string>(l_bp.id).c_str())))));
            global <main_view>()->m_breakpoint_widget->insertTopLevelItems(0, tree_items);
            VDEBUG(3, "Breakpiont [" << QString(boost::lexical_cast <string>(l_bp.id).c_str()) << "] Added");
            global <main_view>()->m_veye_scene->update();
            a_event->accept();
        }
        break;
    case Qt::Key_Space:
        if (a_event->modifiers() & Qt::MetaModifier ||
            a_event->modifiers() & Qt::ControlModifier) {
            // Alt-Space pressed -- toggle the console
            global <main_view>()->toggle_console();
            global <main_view>()->m_veye_scene->update();
            a_event->accept();
        }
        break;
    default:
        break;
    }

}

/// @brief window resize event handler
void main_window::resizeEvent(QResizeEvent *event)
{
    // update non-qt objects

    // update the QMainWindow
    QMainWindow::resizeEvent(event);
}

//void main_window::closeEvent(QCloseEvent *event)
//{
//}


// Default Window Size
QSize main_window::sizeHint() const
{
    return QSize(1920, 1200);
}

// Minimum Window Size
QSize main_window::minimumSizeHint() const
{
    return QSize(800, 600);
}


//
// The Attic
//


//         // add widgets to the window
//         mdi_area = new QMdiArea;
//         mdi_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
//         mdi_area->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
//         setCentralWidget(mdi_area);
//
// //        // connect the signals to the mdi subwindows and widgets
// //        connect(mdi_area, SIGNAL(subWindowActivated(QMdiSubWindow*)),
// //                this, SLOT(updateMenus()));
//         window_mapper = new QSignalMapper(this);
//         connect(window_mapper, SIGNAL(mapped(QWidget*)),
//                 this, SLOT(set_active_sub_window(QWidget*)));
//
// //        list_view *list_window = create_list_view();
// //        list_window->show();
//
//        memory_window *initial_window = create_memory_window();
//        initial_window->show();
//



// // create a new child of the MDI
// memory_window *main_window::create_memory_window()
// {
//
//     // add a new window to the MDI area
//     memory_window *h_child = new memory_window;
//     mdi_area->addSubWindow(h_child);
//     return h_child;
//
// }
//
// // create the main window list view
// list_view *main_window::create_list_view()
// {
//
//     // add a new window to the MDI area
//     list_view *h_child = new list_view;
//     mdi_area->addSubWindow(h_child);
//
//     return h_child;
//
// }
//
// // create the graph view
// veye_scene *main_window::create_veye_scene()
// {
//
//     // add a new window to the MDI area
//     veye_scene *h_child = new veye_scene("", this);
// //    mdi_area->addSubWindow(h_child);
//     return h_child;
//
// }
//
// // create the interpreter interface
// console_widget *main_window::create_console_view()
// {
//
//     // add a new window to the MDI area
//     console_widget *h_child = new console_widget;
//     mdi_area->addSubWindow(h_child);
//
//     return h_child;
//


// // handle a close event
// void main_window::close_event(QCloseEvent *event)
// {
//
//     mdi_area->closeAllSubWindows();
//     if (mdi_area->currentSubWindow()) {
//         event->ignore();
//     } else {
// //        writeSettings();
//         event->accept();
//     }
//
// }
//
//
// // find a child window by name
// QMdiSubWindow *main_window::find_memory_window(const QString &fileName)
// {
//
// //    QString canonicalFilePath = QFileInfo(fileName).canonicalFilePath();
//
// //    foreach (QMdiSubWindow *window, mdi_area->subWindowList()) {
// //        memory_window *memory_window = qobject_cast<memory_window *>(window->widget());
// //        if (memory_window->currentFile() == canonicalFilePath)
// //            return window;
// //    }
//
//     return NULL;
//
// }
//
// // activate a subwindow
// void main_window::set_active_sub_window(QWidget *window)
// {
//
//     // sanity check
//     if (!window)
//         return;
//
//     mdi_area->setActiveSubWindow(qobject_cast<QMdiSubWindow *>(window));
//
// }
//
// memory_window *main_window::active_memory_window()
// {
//
//     if (QMdiSubWindow *active_sub_window = mdi_area->activeSubWindow())
//         return qobject_cast<memory_window *>(active_sub_window->widget());
//
//     return 0;
//
// }


///// @brief    Process keyboard input while this widget has focus
//void main_window::keyPressEvent(QKeyEvent *a_event)
//{
//        switch (a_event->key()) {
//
//        case '+':
//        case '=':
//                m_veye_scene->zoom += 2;
//                m_veye_scene->update();
//                break;
//        case 'Z':
//        case '-':
//        case '_':
//                m_veye_scene->zoom -= 2;
//                m_veye_scene->update();
//                break;
//        case 'Q':
//                {
//                        veyes::handle <breakpoint> l_bp(new breakpoint);
//                        l_bp->breakpoint_name = "test";
//                        l_bp->handle_bp();

//                        // add to list widget
//                        QList <QTreeWidgetItem *> tree_items;
//                        tree_items.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("Synth BP ").append(QString(boost::lexical_cast <string>(l_bp.id).c_str())))));
//                        m_breakpoint_widget->insertTopLevelItems(0, tree_items);
//                        VDEBUG(3, "Breakpiont [" << QString(boost::lexical_cast <string>(l_bp.id).c_str()) << "] Added");
//                }
//                m_veye_scene->update();
//                break;
//        case Qt::Key_Space:
//                if (a_event->modifiers() & Qt::MetaModifier ||
//                    a_event->modifiers() & Qt::AltModifier) {
//                            global <main_window>()->toggle_console();
//                            m_veye_scene->update();
//                }
//                break;
//        case 'A':
//        case Qt::Key_Left:
//                m_veye_scene->center_x -= 0.1;
//                m_veye_scene->update();
//                break;
//        case 'D':
//        case Qt::Key_Right:
//                m_veye_scene->center_x += 0.1;
//                m_veye_scene->update();
//                break;
//        case 'W':
//        case Qt::Key_Up:
//                m_veye_scene->center_y += 0.1;
//                m_veye_scene->update();
//                break;
//        case 'S':
//        case Qt::Key_Down:
//                m_veye_scene->center_y -= 0.1;
//                m_veye_scene->update();
//                break;
//        default:
//                break;
//        }

//        // call the base key event handler
//        QGraphicsView::keyPressEvent(a_event);

//}
