///////////////////////////////////////////////////////
//
// virtualeyes
//
// Copyright (c) 2011 Benjamnin Becker
// All Rights Reserved
//
// @author  Ben Becker
// @date    2/5/11
//
///////////////////////////////////////////////////////

#ifndef VIRTUALEYES_veye_scene_HPP
#define VIRTUALEYES_veye_scene_HPP

#include "soft_handle.hpp"
#include "common.hpp"
#include "handle.hpp"
#include "breakpoint.hpp"
#include <QGraphicsScene>
#include <QGLWidget>

//
// forward declarations
//
class QGraphicsView;
class QLabel;
class QSlider;
class QToolButton;
class QGLPixelBuffer;
class QGLFramebufferObject;
class QTreeWidget;
class QTextEdit;

namespace veyes {

        ///////////////////////////////////////////////////////
        //
        // @class   veye_scene
        // @brief   This class implements the navigational legend as a
        //          directed graph of memory references with certain
        //          conditions applied (e.g. regions per breakpoint, snapshot, etc.)
        //
        ///////////////////////////////////////////////////////
        class veye_scene : public QGraphicsScene,
                           public handle_base
        {
        Q_OBJECT

        public:
                // Member Variables
                float zoom;
                float center_x;
                float center_y;
                float rotate_deg;

                // Member Functions
                veye_scene(const QString &name, QWidget *parent = 0);
                virtual ~veye_scene();

                // Keyboard and mouse event handlers
                void mousePressEvent(QGraphicsSceneMouseEvent *a_event);
                virtual void wheelEvent(QGraphicsSceneWheelEvent *a_event);

        protected:

                void paintGL();                         // GL paint routine  (override)
                void drawBackground(QPainter *painter, const QRectF &);

        private:

                // Member variables
                qreal bg_red;
                qreal bg_green;
                qreal bg_blue;
                QColor window_color;
                QColor text_color;
                GLuint test_texture;
                qreal aspect_ratio;
                float view_matrix[16];

                // Member Functions
                inline void reset_gl();

                // General Qt Overrides
                QSize sizeHint() const;                 // default window size
                QSize minimumSizeHint() const;          // minimum size of window

        };

}


#endif
