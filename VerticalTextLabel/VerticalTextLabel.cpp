// Copyright (c) 2020 Mark Wilson, a.k.a. Mark V Technologies
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

#include <QFont>
#include <QFontMetrics>
#include <QPainter>
#include <QPaintEvent>
#include <QBrush>
#include <QTransform>
#include <QStyle>
#include <QStyleOption>
#include <QAbstractTextDocumentLayout>
#include <QDebug>

#include "VerticalTextLabel.h"

VerticalTextLabel::VerticalTextLabel(QWidget *parent) :
    QWidget(parent)
{
    calculateFontSize();
}

QString VerticalTextLabel::text() const
{
    return m_text;
}

Qt::Alignment VerticalTextLabel::alignment() const
{
    return m_alignment;
}

#if 0
int VerticalTextLabel::margins() const
{
    return m_margins;
}
#endif

void VerticalTextLabel::setText(const QString &text)
{
    if ( text == m_text )
        return;

    m_text = text;

    calculateFontSize();

    updateGeometry();
    update();

}

void VerticalTextLabel::setAlignment(const Qt::Alignment &alignment)
{
    if ( alignment == m_alignment )
        return;

    m_alignment = alignment;

    updateGeometry();
    update();
}

#if 0
void VerticalTextLabel::setMargins(int margins)
{
    if ( margins == m_margins )
        return;

    m_margins = margins;

    update();
}
#endif


QSize VerticalTextLabel::sizeHint() const
{
    return QSize(m_fontSize.height(), m_fontSize.width());
}

QSize VerticalTextLabel::minimumSizeHint() const
{
    return QSize(m_fontSize.height(), m_fontSize.width());
}

bool VerticalTextLabel::hasHeightForWidth() const
{
    return false;
}

int VerticalTextLabel::heightForWidth(int width) const
{
    Q_UNUSED(width)

    return m_fontSize.width();
}

void VerticalTextLabel::paintEvent(QPaintEvent *)
{
    QStyle* style = QWidget::style();

    QStyleOption opt;
    opt.initFrom(this);
    QAbstractTextDocumentLayout::PaintContext context;
    if ( foregroundRole() != QPalette::Text )
        context.palette.setColor(QPalette::Text, context.palette.color(foregroundRole()));

    QPainter p;

    QRectF cr = contentsRect();

    QRectF rect = QRectF(0, 0, cr.height(), m_fontSize.height());

    p.begin(this);

    //p.setFont(m_font);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setRenderHint(QPainter::TextAntialiasing, true);
    p.setRenderHint(QPainter::SmoothPixmapTransform, true);

    double x = (cr.width()-rect.height())/2+1;

    QTransform t;
    t.translate(x, m_fontSize.height());
    t.rotate(90);
    t.translate(-m_fontSize.height(), -m_fontSize.height());
    p.setTransform(t);

    p.setBrush(QBrush("black"));
    p.setPen(QPen("black"));

    QRectF br;
    //p.drawText(rect, m_alignment, m_text, &br);
    style->drawItemText(&p, rect.toRect(), m_alignment, opt.palette, false, m_text, foregroundRole());

    p.end();
}

void VerticalTextLabel::calculateFontSize()
{
    QFontMetrics fm(font());

    QSize qs;

    if ( m_text.contains("\n" ) )
        qs = fm.size(Qt::TextWordWrap, m_text);
    else
        qs = fm.size(Qt::TextSingleLine, m_text);

    m_fontSize = QSize(qs.width(), qs.height());
}


void VerticalTextLabel::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::FontChange )
    {
        calculateFontSize();
    }

    QWidget::changeEvent(event);
}
