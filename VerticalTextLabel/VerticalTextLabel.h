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

#pragma once

#include <QWidget>
#include <QLabel>


class VerticalTextLabel : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(Qt::Alignment alignment READ alignment WRITE setAlignment)
    //Q_PROPERTY(int margins READ margins WRITE setMargins)

public:
    VerticalTextLabel(QWidget *parent = 0);

    QString text() const;
    Qt::Alignment alignment() const;
    //int margins() const;

public slots:
    void setText(const QString& text);
    void setAlignment(const Qt::Alignment& alignment);
    //void setMargins(int margins);


private:
    QString m_text = "Text";
    QSize m_fontSize;
    Qt::Alignment m_alignment;
    //int m_margins = 20;

    // QWidget interface
    void calculateFontSize();

public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    int heightForWidth(int width) const override;

protected:
    void paintEvent(QPaintEvent *) override;

    // QWidget interface
public:
    bool hasHeightForWidth() const override;

    // QWidget interface
protected:
    void changeEvent(QEvent *event) override;
};
