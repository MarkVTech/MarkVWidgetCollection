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

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_updateNeedleButton_clicked();
    void on_toggleAllButton_clicked();
    void on_allActiveButton_clicked();
    void on_allInactiveButton_clicked();
    void on_flashingCB_stateChanged(int state);

    void handleValidIPv4AddressEntered(const QString& address);
    void handleValidIPv6AddressEntered(const QString& address);
    void handleInvalidIPv4AddressEntered();
    void handleInvalidIPv6AddressEntered();

private:
    Ui::MainWindow *ui;
};
