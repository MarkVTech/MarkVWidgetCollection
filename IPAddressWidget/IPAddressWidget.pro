CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(ipaddresswidgetplugin)
TEMPLATE    = lib

HEADERS     = IPAddressWidgetPlugin.h
SOURCES     = IPAddressWidgetPlugin.cpp
RESOURCES   = icons.qrc
LIBS        += -L. 

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += designer network
} else {
    CONFIG += designer network
}

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(IPAddressWidget.pri)
