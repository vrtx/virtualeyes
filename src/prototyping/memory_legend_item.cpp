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

#include "memory_legend_item.hpp"
#include "reference_graph.hpp"

memory_legend_item::memory_legend_item(const QColor &color, int x, int y)
{
    this->x = x;
    this->y = y;
    this->color = color;
    setZValue((x + y) % 2);

    setFlags(ItemIsSelectable | ItemIsMovable);
    setAcceptsHoverEvents(true);
}

memory_legend_item::~memory_legend_item()
{

}


QRectF memory_legend_item::boundingRect() const
{
    return QRectF(0, 0, 140, 120);
}

QPainterPath memory_legend_item::shape() const
{
    QPainterPath path;
    path.addRect(0, 0, 140, 120);
    return path;
}

void memory_legend_item::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    QColor fillColor = (option->state & QStyle::State_Selected) ? color.dark(150) : color;
    if (option->state & QStyle::State_MouseOver)
        fillColor = fillColor.light(125);

    const qreal lod = option->levelOfDetailFromTransform(painter->worldTransform());
    if (lod < 0.2) {
        if (lod < 0.125) {
            painter->fillRect(QRectF(0, 0, 80, 20), fillColor);
            return;
        }

        QBrush b = painter->brush();
        painter->setBrush(fillColor);
        painter->drawRect(0, 0, 80, 20);
        painter->setBrush(b);
        return;
    }

    QPen oldPen = painter->pen();
    QPen pen = oldPen;
    int width = 0;
    if (option->state & QStyle::State_Selected)
        width += 2;

    pen.setWidth(width);
    QBrush b = painter->brush();
    painter->setBrush(QBrush(fillColor.dark(option->state & QStyle::State_Sunken ? 120 : 100)));

    painter->drawRect(QRect(0, 0, 80, 20));
    painter->setBrush(b);

    // Draw text
    if (lod >= 0.5) {
        QFont font("Monaco", 10);
        font.setStyleStrategy(QFont::ForceOutline);
        painter->setFont(font);
        painter->save();
        painter->scale(0.1, 0.1);
        painter->drawText(70, 80, QString("MemoryRegionName:  0x8012f000 - 0x8012ffff"));
        painter->restore();
    }

//    // Draw red ink
//    if (stuff.size() > 1) {
//        QPen p = painter->pen();
//        painter->setPen(QPen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
//        painter->setBrush(Qt::NoBrush);
//        QPainterPath path;
//        path.moveTo(stuff.first());
//        for (int i = 1; i < stuff.size(); ++i)
//            path.lineTo(stuff.at(i));
//        painter->drawPath(path);
//        painter->setPen(p);
//    }

}

void memory_legend_item::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    update();
}

void memory_legend_item::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->modifiers() & Qt::ShiftModifier) {
        stuff << event->pos();
        update();
        return;
    }
    QGraphicsItem::mouseMoveEvent(event);
}

void memory_legend_item::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    update();
}
