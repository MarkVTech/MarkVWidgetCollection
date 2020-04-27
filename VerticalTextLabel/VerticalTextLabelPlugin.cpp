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

#include "VerticalTextLabel.h"
#include "VerticalTextLabelPlugin.h"

#include <QtPlugin>

VerticalTextLabelPlugin::VerticalTextLabelPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void VerticalTextLabelPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool VerticalTextLabelPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *VerticalTextLabelPlugin::createWidget(QWidget *parent)
{
    return new VerticalTextLabel(parent);
}

QString VerticalTextLabelPlugin::name() const
{
    return QLatin1String("VerticalTextLabel");
}

QString VerticalTextLabelPlugin::group() const
{
    return QLatin1String("MarkV Widgets");
}

QIcon VerticalTextLabelPlugin::icon() const
{
    return QIcon();
}

QString VerticalTextLabelPlugin::toolTip() const
{
    return QLatin1String("");
}

QString VerticalTextLabelPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool VerticalTextLabelPlugin::isContainer() const
{
    return false;
}

QString VerticalTextLabelPlugin::domXml() const
{
    return QLatin1String("<widget class=\"VerticalTextLabel\" name=\"verticalTextLabel\">\n</widget>\n");
}

QString VerticalTextLabelPlugin::includeFile() const
{
    return QLatin1String("VerticalTextLabel.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(verticallabelplugin, VerticalTextLabelPlugin)
#endif // QT_VERSION < 0x050000
