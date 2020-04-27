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

#include "IPAddressWidget.h"
#include "IPAddressWidgetPlugin.h"

#include <QtPlugin>

IPAddressWidgetPlugin::IPAddressWidgetPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void IPAddressWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool IPAddressWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *IPAddressWidgetPlugin::createWidget(QWidget *parent)
{
    return new IPAddressWidget(parent);
}

QString IPAddressWidgetPlugin::name() const
{
    return QLatin1String("IPAddressWidget");
}

QString IPAddressWidgetPlugin::group() const
{
    return QLatin1String("MarkV Widgets");
}

QIcon IPAddressWidgetPlugin::icon() const
{
    return QIcon();
}

QString IPAddressWidgetPlugin::toolTip() const
{
    return QLatin1String("");
}

QString IPAddressWidgetPlugin::whatsThis() const
{
    return QLatin1String("A widget for entering an IP address and optional port number");
}

bool IPAddressWidgetPlugin::isContainer() const
{
    return false;
}

QString IPAddressWidgetPlugin::domXml() const
{
    return QLatin1String("<widget class=\"IPAddressWidget\" name=\"ipAddressWidget\">\n</widget>\n");
}

QString IPAddressWidgetPlugin::includeFile() const
{
    return QLatin1String("IPAddressWidget.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(ipaddresswidgetplugin, IPAddressWidgetPlugin)
#endif // QT_VERSION < 0x050000
