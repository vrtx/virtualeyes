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

#ifndef VIRTUALEYES_MEMORY_LEGEND_ITEM_HPP
#define VIRTUALEYES_MEMORY_LEGEND_ITEM_HPP

#include <QColor>
#include <QGraphicsItem>
#include <QtGui>

namespace virtualeyes
{

        ///////////////////////////////////////////////////////
        //
        // @class   memory_legend_item
        // @brief   This class represents the memory region in the legend view
        //
        ///////////////////////////////////////////////////////
        class memory_legend_item : public QGraphicsItem
        {

        public:

                // Member Functions
                memory_legend_item(const QColor &color, int x, int y);
                virtual ~memory_legend_item();

                QRectF boundingRect() const;
                QPainterPath shape() const;
                void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);

                // Class variables

        protected:
                void mousePressEvent(QGraphicsSceneMouseEvent *event);
                void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
                void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);


        private:

                // Member variables
                int x, y;
                QColor color;
                QList<QPointF> stuff;

        };

}


#endif
