#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(1000,800);
    ui->splitter->setStretchFactor(0,1);
    ui->splitter->setStretchFactor(1,7);                  //设置splitter的比例为1:7 ,0表示右（上），1表示左（下）
    ui->splitter_2->setStretchFactor(0,6);
    ui->splitter_2->setStretchFactor(1,2);
}

MainWindow::~MainWindow()
{
    delete ui;
}
