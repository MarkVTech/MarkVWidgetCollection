#include "NeedleGauge.h"
#include "NeedleGaugePlugin.h"

#include <QtPlugin>

NeedleGaugePlugin::NeedleGaugePlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void NeedleGaugePlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool NeedleGaugePlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *NeedleGaugePlugin::createWidget(QWidget *parent)
{
    return new NeedleGauge(parent);
}

QString NeedleGaugePlugin::name() const
{
    return QLatin1String("NeedleGauge");
}

QString NeedleGaugePlugin::group() const
{
    return QLatin1String("MarkV Widgets");
}

QIcon NeedleGaugePlugin::icon() const
{
    return QIcon();
}

QString NeedleGaugePlugin::toolTip() const
{
    return QLatin1String("");
}

QString NeedleGaugePlugin::whatsThis() const
{
    return QLatin1String("");
}

bool NeedleGaugePlugin::isContainer() const
{
    return false;
}

QString NeedleGaugePlugin::domXml() const
{
    return QLatin1String("<widget class=\"NeedleGauge\" name=\"needleGauge\">\n</widget>\n");
}

QString NeedleGaugePlugin::includeFile() const
{
    return QLatin1String("NeedleGauge.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(needlegaugeplugin, NeedleGaugePlugin)
#endif // QT_VERSION < 0x050000
