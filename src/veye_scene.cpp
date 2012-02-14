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
// @date    2/5/11
//
///////////////////////////////////////////////////////

#include <QtGui>
#include <QtOpenGL>
#include <QList>
#include "common.hpp"
#include "main_view.hpp"
#include "veye_scene.hpp"
#include "breakpoint.hpp"
#include "virtualeyes.hpp"
#include <QScriptEngine>

#define PI_OVER_360 0.008726646259972

/// @brief    Default ctor
veye_scene::veye_scene(const QString &name, QWidget *parent) :
    zoom(1.0f),
    center_x(-1.5f),
    center_y(1.5f),
    rotate_deg(0),
    bg_red(0.13f), bg_green(0.127f), bg_blue(0.125f),
    window_color(0x35, 0x35, 0x35),
    text_color(0xe4, 0xe0, 0xd0),
    aspect_ratio(16/9)
{

}

/// @brief    Default dtor
veye_scene::~veye_scene()
{

}


/// @brief    Paint the opengl graphics scene background
void veye_scene::drawBackground(QPainter *painter, const QRectF &)
{

    // reset the openGL state
    global <virtualeyes> g_virtualeyes;

    // clear the background
    glClearColor(bg_red, bg_green, bg_blue, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearDepth(1.0f);
    glEnable(GL_MULTISAMPLE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    // set up the scene in modelview mode
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glFrustum(-2.66f, 2.66f, -1.5f, 1.5f, 0.1f, 150.0f);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glRotatef(rotate_deg, 0, 1.0f, 0);
    glTranslatef(0.0 - center_x, 0.0 - center_y, -2.0f - zoom);
    // glScalef(1.0f * aspect_ratio, 1.0f, 1.0f);

    // paint some markers for testing
    // glColor4f(0.0f, 0.2f, 0.0f, 0.2f);
    // glBegin(GL_QUADS);
    //     glVertex3f(-500.0f, -1.0f, 500.0f);
    //     glVertex3f(500.0f,  -1.0f, 500.0f);
    //     glVertex3f(500.0f,  -1.0f, -500.0f);
    //     glVertex3f(-500.0f, -1.0f, -500.0f);
    // glEnd();
    // glColor4f(0.2f, 0.0f, 0.0f, 0.2f);
    // glBegin(GL_QUADS);
    //     glVertex3f(-1.0f, -500.0f, 500.0f);
    //     glVertex3f(-1.0f, 500.0f,  500.0f);
    //     glVertex3f(-1.0f, 500.0f,  -500.0f);
    //     glVertex3f(-1.0f, -500.0f, -500.0f);
    // glEnd();

    // paint the snapshots and their nested elements (if within the FOV)

    // layout datastructs:
    // session
    //   \__> background binary image
    //   \__> snapshot
    //      \__> snapshot -> memory region edges
    //      \__> memory regions
    //         \__> memory region -> struct edges
    //         \__> structs
    // layout strtegies:
    //   temporal proximity         (update reorganize the nearest X items ordered by time, non-normalized)
    //   same breakpoint            (removes snapshots from other breakpoints and condenses/normalizes on the Z axis)
    //   other regions with struct  (update results in matching snapshots having the same struct; clustered closer together based on values?)
    //   similar memory subregion   (update results in matching memory regions being lined up by search string on the Z axis)
    //   realtime                   (update results in applying basic layout _only_ when the layout has changed; 'add' simply adds the item to the next avaialable place on the Z axis)


    if (g_virtualeyes->m_active_session.is_valid()) {
        int test_i = 0;
        int depth = 0;
        int last_depth_x = 0;
        int last_depth_y = 0;

        for (owned_snapshots_t::const_iterator i_snap = g_virtualeyes->m_active_session->m_snapshots.begin();
             i_snap != g_virtualeyes->m_active_session->m_snapshots.end();
             ++i_snap, ++test_i) {
            // for each snapshot

            int i_color = (5 + test_i) % 5;

            // pick node color
            switch (i_color) {
                case 0:
                last_depth_x = 1.0f + i_snap->id + 20;
                last_depth_y = depth * 4;
                ++depth;    // increment depth every 4 nodes
                glColor4f(0.9, 0.4, 0.2, ((float)i_snap->id / global_handle::global_handle_index));
                break;
                case 1:
                glColor4f(0.8, 0.8, 0.1, ((float)i_snap->id / global_handle::global_handle_index));
                break;
                case 2:
                glColor4f(0.2, 0.8, 0.3, ((float)i_snap->id / global_handle::global_handle_index));
                break;
                case 3:
                glColor4f(0.1, 0.3, 0.8, ((float)i_snap->id / global_handle::global_handle_index));
                break;
                default:
                glColor4f(1.0, 0.98, 0.95, ((float)i_snap->id / global_handle::global_handle_index));
            };

            // draw node
            glBegin(GL_QUADS);
            glVertex3f(-1.0f + i_snap->id + 20 + depth * 3, 0.0f + (depth * 4), depth / 4);
            glVertex3f( 1.0f + i_snap->id + 20 + depth * 3, 0.0f + (depth * 4), depth / 4);
            glVertex3f( 1.0f + i_snap->id + 20 + depth * 3, -1.0f + (depth * 4), depth / 4);
            glVertex3f(-1.0f + i_snap->id + 20 + depth * 3, -1.0f + (depth * 4), depth / 4);
            glEnd();

            // draw edge to parent node
            glColor4f(0.60, 0.55, 0.45, ((float)i_snap->id / global_handle::global_handle_index) );
            glBegin(GL_LINES);
            glVertex3f(-0.04f + i_snap->id + 20 + depth * 3,  -1.0f + (depth * 4), depth / 4);      // origin of the line
            glVertex3f(0.01f + last_depth_x + depth * 3 - 1,  last_depth_y, (depth - 1) / 4);       // ending point of the line
            glEnd();
        }

    }

    glColor4f(0.1, 0.2, 0.4, 0.5 );
    glBegin(GL_QUADS);
    glVertex3f(-500, 0, -500);
    glVertex3f(500,  0, -500);
    glVertex3f(500,  0, 500);
    glVertex3f(-500, 0, 500);
    glEnd();
    

    // reset the openGL state for the QPainter
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    // glFlush();
}

/// @brief   Reset the OpenGL view and texture options
void veye_scene::reset_gl()
{



}


////////////////////////////////////////
//
// Event and Qt Window Handling
//
////////////////////////////////////////

/// @brief    Process mouse wheel events while this widget has focus
void veye_scene::mousePressEvent(QGraphicsSceneMouseEvent *a_event)
{

    QGraphicsScene::mousePressEvent(a_event);
    if (!a_event->isAccepted()) {
        // accept the event
        VDEBUG(0, "Mouse click at \t X: " << a_event->pos().x() << " \t Y: " << a_event->pos().y());
        a_event->accept();
    }
    update();
}


/// @brief    Process mouse wheel events while this widget has focus
void veye_scene::wheelEvent(QGraphicsSceneWheelEvent *a_event)
{

    QGraphicsScene::wheelEvent(a_event);
    if (a_event->isAccepted()) {
        // wheel event already handled
        return;
    }

    if (a_event->orientation() == Qt::Vertical) {
        // vertical scroll wheel event

        if (a_event->modifiers() & Qt::ShiftModifier)
            // zoom in/out
            zoom += (float)a_event->delta() / 900;
        else
            // camera up/down
            center_y += (float)a_event->delta() / 100;

    } else if (a_event->orientation() == Qt::Horizontal) {
        // horizontal scroll wheel

        if (a_event->modifiers() & Qt::ControlModifier)
            // rotate left/right
            rotate_deg += (float)a_event->delta() / 100;
        else
            // pan left/right
            center_x -= (float)a_event->delta() / 80;

    }

    // cout << "scroll delta is " << a_event->delta() << endl;

    // update the view
    a_event->accept();
    update();

}

/// @brief    Default Window Size hint
QSize veye_scene::sizeHint() const
{
    return QSize(1920, 1200);
}

/// @brief    Minimum Window Size hint
QSize veye_scene::minimumSizeHint() const
{
    return QSize(640, 480);
}


//
// The Attic
//

// // bind a texture for testing
// // test_texture = bindTexture(QImage("test.jpg"));
// QGLFormat pbufferFormat = format();
// pbufferFormat.setSampleBuffers(false);
// test_pb = new QGLPixelBuffer(QSize(1024, 512), pbufferFormat, this);
// test_pb->makeCurrent();
// test_texture = test_pb->generateDynamicTexture();
// test_brush = new QBrush(QColor(0xc1, 0xbc, 0xb0));
// test_painter = new QPainter(test_pb);
// test_painter->fillRect(0, 0, 1024, 512, *test_brush);
// makeCurrent();
// test_pb->updateDynamicTexture(test_texture);
// test1 = false;













