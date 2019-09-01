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
    isopenfile=0;

    /*以下部分是函数信号槽*/
    connect(ui->actioncpy,SIGNAL(triggered()),this,SLOT(on_copy()));
    connect(ui->actioncut,SIGNAL(triggered()),this,SLOT(cut_it()));
    connect(ui->actionpst,SIGNAL(triggered()),this,SLOT(paste_it()));
    connect(ui->actionsal,SIGNAL(triggered()),this,SLOT(select_all()));
    connect(ui->action_redo,SIGNAL(triggered()),this,SLOT(redo_it()));
    connect(ui->actionreg,SIGNAL(triggered()),this,SLOT(reg_it()));
    connect(ui->actionrun,&QAction::triggered,this,[=](){SaveFile(isopenfile,fpath);edit_it();run_it();});
    connect(ui->actionedit,&QAction::triggered,this,[=](){SaveFile(isopenfile,fpath);edit_it();});
    connect(ui->action_op,&QAction::triggered,this,[=](){OpenFile();});
    connect(ui->action_save,&QAction::triggered,this,[=](){SaveFile(isopenfile,fpath);});
}

MainWindow::~MainWindow()
{
    delete ui;
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

QString MainWindow::OpenFile()
{
    QString path=QFileDialog::getOpenFileName(this,"打开文件","E:\\QTPublic_Compile");
    fpath = path;
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QFile file(path);
    file.open(QIODevice::ReadWrite);
    QByteArray array = file.readAll();
    ui->textEdit_2->setText(codec->toUnicode(array));
    isopenfile=1;
    file.close();
    qDebug() << path;
    return path;
}

void MainWindow::SaveFile(int isopenfile,QString path)
{
    if(!isopenfile)
    {
        qDebug()<<"there is not any file being opened!";
        return;
    }
    qDebug() << path;
    QFile file;
    file.setFileName(path);
    file.open(QIODevice::WriteOnly);
    QString str=ui->textEdit_2->toPlainText();
    file.write(str.toUtf8());
    qDebug()<<"writing succeed!";
    file.close();
}
void MainWindow::edit_it()
{
    QString destname = fpath;
    destname.replace(".c",".exe");
    QString command = "gcc -o " + destname +" "+ fpath;
    system(command.toStdString().data());
}
void MainWindow::run_it()
{
    QString destname = fpath;
    destname.replace(".c",".exe");
    system(destname.toStdString().data());
}
