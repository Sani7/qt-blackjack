#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , playwindow(new playWindow)
{
    ui->setupUi(this);
    connect(ui->playButton, &QPushButton::clicked, this, [=]{
    playwindow->show();
    this->hide();});
}

MainWindow::~MainWindow()
{
    delete ui;
}

