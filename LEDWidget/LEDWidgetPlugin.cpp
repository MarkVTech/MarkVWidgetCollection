#include "LEDWidget.h"
#include "LEDWidgetPlugin.h"

#include <QtPlugin>

LEDWidgetPlugin::LEDWidgetPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void LEDWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool LEDWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *LEDWidgetPlugin::createWidget(QWidget *parent)
{
    return new LEDWidget(parent);
}

QString LEDWidgetPlugin::name() const
{
    return QLatin1String("LEDWidget");
}

QString LEDWidgetPlugin::group() const
{
    return QLatin1String("MarkV Widgets");
}

QIcon LEDWidgetPlugin::icon() const
{
    return QIcon();
}

QString LEDWidgetPlugin::toolTip() const
{
    return QLatin1String("");
}

QString LEDWidgetPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool LEDWidgetPlugin::isContainer() const
{
    return false;
}

QString LEDWidgetPlugin::domXml() const
{
    return QLatin1String("<widget class=\"LEDWidget\" name=\"lEDWidget\">\n</widget>\n");
}

QString LEDWidgetPlugin::includeFile() const
{
    return QLatin1String("LEDWidget.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(ledwidgetplugin, LEDWidgetPlugin)
#endif // QT_VERSION < 0x050000
