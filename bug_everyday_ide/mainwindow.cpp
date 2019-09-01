#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->splitter->setStretchFactor(0,1);             //设置splitter的两个框的比例为 ,0表示右（上），1表示左（下） 右边表示1:7
    ui->splitter->setStretchFactor(1,7);
    ui->splitter_2->setStretchFactor(0,6);
    ui->splitter_2->setStretchFactor(1,2);

    /*以下部分是函数信号槽*/
    connect(ui->actioncpy,SIGNAL(triggered()),this,SLOT(on_copy()));
    connect(ui->actioncut,SIGNAL(triggered()),this,SLOT(cut_it()));
    connect(ui->actionpst,SIGNAL(triggered()),this,SLOT(paste_it()));
    connect(ui->actionsal,SIGNAL(triggered()),this,SLOT(select_all()));
    connect(ui->action_redo,SIGNAL(triggered()),this,SLOT(redo_it()));
    connect(ui->actionreg,SIGNAL(triggered()),this,SLOT(reg_it()));
}

void MainWindow::on_copy()          //以下调用Qt中自带的拷贝、剪切、粘贴等函数
{
    ui->textEdit_2->copy();
}
void MainWindow::select_all()
{
    ui->textEdit_2->selectAll();
}
void MainWindow::cut_it()
{
    ui->textEdit_2->cut();
}
void MainWindow::paste_it()
{
    ui->textEdit_2->paste();
}
void MainWindow::redo_it()
{
    ui->textEdit_2->redo();
}
void MainWindow::reg_it()
{
    ui->textEdit_2->undo();
}


MainWindow::~MainWindow()
{
    delete ui;
}
