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

#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>
#include <QGridLayout>
#include <QRegularExpressionValidator>
#include <QFontMetrics>
#include <QRect>
#include <QSettings>
#include <QDebug>

#include "IPAddressWidget.h"

IPAddressWidget::IPAddressWidget(QWidget *parent) :
    QWidget(parent),
    mIPv4Regex( ("^" + mIPv4Range
         + "\\." + mIPv4Range
         + "\\." + mIPv4Range
         + "\\." + mIPv4Range + "$") ),
    mIPv4Validator(new QRegularExpressionValidator(mIPv4Regex, this)),
    mLineEdit(new QLineEdit(this))
{
    mIPv6Regex = QRegularExpression("^" + mIPv6RegexString +"$");
    mIPv6Validator = new QRegularExpressionValidator(mIPv6Regex, this);

    QGridLayout *layout = new QGridLayout(this);
    layout->setContentsMargins(3, 3, 3, 3);
    layout->setSpacing(3);
    layout->addWidget(mLineEdit, 0, 0);

    connect(mLineEdit, SIGNAL(editingFinished()), this, SLOT(handleEditingFinished()));
    connect(mLineEdit, SIGNAL(textChanged(QString)), this, SLOT(handleTextChanged(QString)));

    setLineEditSize();
    setValidator();
}

QString IPAddressWidget::address() const
{
    return mLineEdit->text();
}

IPAddressWidget::AddressType IPAddressWidget::addressType() const
{
    return mAddressType;
}

void IPAddressWidget::setAddress(const QString &address)
{
    validateEntry(address);

    mIpAddress = address;

    mLineEdit->setText(mIpAddress);

    emit validAddressStringEntered(mIpAddress);
}

void IPAddressWidget::setAddressType(IPAddressWidget::AddressType addressType)
{
    if ( addressType == mAddressType )
        return;

    mAddressType = addressType;

    setValidator();
    setLineEditSize();

}

void IPAddressWidget::handleEditingFinished()
{
    validateEntry(mLineEdit->text());
    emit validHostAddressEntered(QHostAddress(mLineEdit->text()));
    emit validAddressStringEntered(mLineEdit->text());
}

void IPAddressWidget::handleTextChanged(const QString &text)
{
    if ( !mLineEdit->hasAcceptableInput() )
        emit invalidAddress();
    else
        emit validAddressStringEntered(text);
}

void IPAddressWidget::writeSettings(const IPAddressWidget *ipAddressWidget, QSettings *settings, const QString group)
{
    if ( !group.isEmpty() )
        settings->beginGroup(group);


    settings->setValue("ipAddress", ipAddressWidget->address());

    if ( !group.isEmpty() )
        settings->endGroup();
}

void IPAddressWidget::readSettings(IPAddressWidget* ipAddressWidget, QSettings *settings, const QString group)
{
    if ( !group.isEmpty() )
    {
        settings->beginGroup(group);
    }

    ipAddressWidget->setAddress(settings->value("ipAddress", QVariant::fromValue(QString("0.0.0.0"))).toString());

    if ( !group.isEmpty() )
        settings->endGroup();
}

void IPAddressWidget::setLineEditSize()
{
    QFontMetrics fm = mLineEdit->fontMetrics();
    QRect rect;

    if ( mAddressType == AddressType::IPV4 )
    {
        rect = fm.boundingRect("255.255.255.255");
    }
    else
    {
        rect = fm.boundingRect("AAAA:AAAA:AAAA:AAAA:AAAA:AAAA:AAAA:AAAA");
    }

    mLineEdit->setFixedWidth(rect.width());

    adjustSize();
}

void IPAddressWidget::setValidator()
{
    if ( mAddressType == AddressType::IPV4 )
    {
        mLineEdit->setValidator(mIPv4Validator);
        mLineEdit->setToolTip("Enter IPv4 Address in form [0-255].[0-255].[0-255].[0-255]");
        mLineEdit->setText("0.0.0.0");
    }
    else
    {
        mLineEdit->setValidator(mIPv6Validator);
        mLineEdit->setToolTip("Enter IPv6 Address in form [0-FFFF]:[0-FFFF]:[0-FFFF]:[0-FFFF]:[0-FFFF]:[0-FFFF]:[0-FFFF]:[0-FFFF");
        mLineEdit->setText("0:0:0:0:0:0:0:0");
    }
}

bool IPAddressWidget::validateEntry(QString address)
{
    int pos;

    if ( mAddressType == AddressType::IPV4 )
    {
        if ( !mIPv4Validator->validate(address, pos) )
        {
            qWarning() << "[IPAddressWidget::validateEntry] Invalid IP v4 address " << address << " passed";
            indicateValid(false);
            emit invalidAddress();
            return false;
        }
        else
        {
            indicateValid(true);
            return true;
        }
    }
    else
    {
        if ( !mIPv6Validator->validate(address, pos) )
        {
            qWarning() << "[IPAddressWidget::validateEntry] Invalid IP v6 address " << address << " passed";
            indicateValid(false);
            emit invalidAddress();
            return false;
        }
        else
        {
            indicateValid(true);
            return true;
        }
    }
}

void IPAddressWidget::indicateValid(bool valid)
{
    if ( valid )
        mLineEdit->setStyleSheet("border: 1px solid black;");
    else
        mLineEdit->setStyleSheet("border: 1px solid red;");
}
