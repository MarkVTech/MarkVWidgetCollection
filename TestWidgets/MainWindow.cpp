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

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->v4IPAddressWidget, SIGNAL(validAddressStringEntered(QString)),
            this,                  SLOT(handleValidIPv4AddressEntered(QString)));
    connect(ui->v6IPAddressWidget, SIGNAL(validAddressStringEntered(QString)),
            this,                  SLOT(handleValidIPv6AddressEntered(QString)));

    connect(ui->v4IPAddressWidget, SIGNAL(invalidAddress()), this, SLOT(handleInvalidIPv4AddressEntered()));
    connect(ui->v6IPAddressWidget, SIGNAL(invalidAddress()), this, SLOT(handleInvalidIPv6AddressEntered()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_updateNeedleButton_clicked()
{
    ui->needleGauge->setValue(ui->needleValueSB->value());
}

void MainWindow::on_toggleAllButton_clicked()
{
    ui->ledWidget1->toggleState();
    ui->ledWidget2->toggleState();
    ui->ledWidget3->toggleState();
}

void MainWindow::on_allActiveButton_clicked()
{
    ui->ledWidget1->setState(true);
    ui->ledWidget2->setState(true);
    ui->ledWidget3->setState(true);
}

void MainWindow::on_allInactiveButton_clicked()
{
    ui->ledWidget1->setState(false);
    ui->ledWidget2->setState(false);
    ui->ledWidget3->setState(false);

}

void MainWindow::on_flashingCB_stateChanged(int state)
{
    if ( state == Qt::Checked )
    {
        ui->ledWidget1->setFlashing(true);
        ui->ledWidget2->setFlashing(true);
        ui->ledWidget3->setFlashing(true);

        ui->toggleAllButton->setEnabled(false);
        ui->allActiveButton->setEnabled(false);
        ui->allInactiveButton->setEnabled(false);
    }

    if ( state == Qt::Unchecked )
    {
        ui->ledWidget1->setFlashing(false);
        ui->ledWidget2->setFlashing(false);
        ui->ledWidget3->setFlashing(false);

        ui->toggleAllButton->setEnabled(true);
        ui->allActiveButton->setEnabled(true);
        ui->allInactiveButton->setEnabled(true);
    }

    ui->ledWidget1->setFlashRate(ui->rateSB->value());
    ui->ledWidget2->setFlashRate(ui->rateSB->value());
    ui->ledWidget3->setFlashRate(ui->rateSB->value());
}

void MainWindow::handleValidIPv4AddressEntered(const QString &address)
{
    Q_UNUSED(address)

    ui->validV4Indicator->setState(true);
}

void MainWindow::handleValidIPv6AddressEntered(const QString &address)
{
    Q_UNUSED(address)

    ui->validV6Indicator->setState(true);
}

void MainWindow::handleInvalidIPv4AddressEntered()
{
    ui->validV4Indicator->setState(false);
}

void MainWindow::handleInvalidIPv6AddressEntered()
{
    ui->validV6Indicator->setState(false);
}
