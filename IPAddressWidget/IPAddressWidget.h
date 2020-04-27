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
#include <QRegularExpression>
#include <QHostAddress>
#include <QSpinBox>

class QLineEdit;
class QSpinBox;
class QRegularExpressionValidator;
class QLabel;
class QSettings;

class IPAddressWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString address READ address WRITE setAddress)
    Q_PROPERTY(AddressType addressType READ addressType WRITE setAddressType)

public:
    enum AddressType { IPV4, IPV6 };
    Q_ENUM(AddressType)

    IPAddressWidget(QWidget *parent = nullptr);

    QString address() const;
    AddressType addressType() const;

public slots:
    void setAddress(const QString& address);
    void setAddressType(AddressType addressType);

private slots:
    void handleEditingFinished();
    void handleTextChanged(const QString& text);

signals:
    void validHostAddressEntered(QHostAddress validAddress);
    void validAddressStringEntered(QString validAddress);

    void invalidAddress();

public:
    static void writeSettings(const IPAddressWidget *ipAddressWidget, QSettings *settings, const QString group="");
    static void readSettings(IPAddressWidget* ipAddressWidget, QSettings *settings, const QString group="");

private:
    void setLineEditSize();
    void setValidator();
    bool validateEntry(QString address);
    void indicateValid(bool valid);

    QString mIPv4Range = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    QString mIPv6Range ="(?:[A-Fa-f0-9]{1,4}?)";
    QRegularExpression mIPv4Regex;
    QRegularExpression mIPv6Regex;
    QRegularExpressionValidator* mIPv4Validator;
    QRegularExpressionValidator* mIPv6Validator;

    QLineEdit* mLineEdit=nullptr;
    QString mIpAddress;
    AddressType mAddressType = AddressType::IPV4;

    QString s = "(dfkalsfdsa)";

    QString mIPv6RegexString =
        "(([0-9a-fA-F]{1,4}:){7,7}[0-9a-fA-F]{1,4}|"
        "([0-9a-fA-F]{1,4}:){1,7}:|"
        "([0-9a-fA-F]{1,4}:){1,6}:[0-9a-fA-F]{1,4}|"
        "([0-9a-fA-F]{1,4}:){1,5}(:[0-9a-fA-F]{1,4}){1,2}|"
        "([0-9a-fA-F]{1,4}:){1,4}(:[0-9a-fA-F]{1,4}){1,3}|"
        "([0-9a-fA-F]{1,4}:){1,3}(:[0-9a-fA-F]{1,4}){1,4}|"
        "([0-9a-fA-F]{1,4}:){1,2}(:[0-9a-fA-F]{1,4}){1,5}|"
        "[0-9a-fA-F]{1,4}:((:[0-9a-fA-F]{1,4}){1,6})|"
        ":((:[0-9a-fA-F]{1,4}){1,7}|:)|"
        "fe80:(:[0-9a-fA-F]{0,4}){0,4}%[0-9a-zA-Z]{1,}|"
        "::(ffff(:0{1,4}){0,1}:){0,1}"
        "((25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9])\\.){3,3}"
        "(25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9])|"
        "([0-9a-fA-F]{1,4}:){1,4}:"
        "((25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9])\\.){3,3}"
        "(25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9])"
        ")";
};
