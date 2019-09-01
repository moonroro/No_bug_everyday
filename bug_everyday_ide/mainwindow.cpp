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

//打开文件函数
void MainWindow::OpenFile()
{
    QString path=QFileDialog::getOpenFileName(this, tr("打开文件"),
                                              "C:\\Users\\Administrator\\Documents\\QT\\QTPublic_Compile",
                                              tr("Text or C files (*.txt *.c *.cpp)"));   //选择文件，存入文件路径
    fpath = path;           //类成员存储文件路径
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");   //文件编码方式
    QFile file(path);     //生成QFile类文件
    file.open(QIODevice::ReadWrite);   //以只读方式打开
    QByteArray array = file.readAll();  //读写文件信息存入QByteArray类
    ui->textEdit_2->setText(codec->toUnicode(array));  //在编辑窗口显示
    isopenfile=1;  //文件是否成功打开变量
    file.close();  //关闭文件
    qDebug() << path;
}

//关闭文件函数
void MainWindow::SaveFile(int isopenfile,QString fpath)   //关闭文件函数
{
    //判断文件是否打开，若未打开文件，错误警告
    if(!isopenfile)
    {
        QMessageBox::critical(this,"错误","尚未打开任何文件");
        qDebug()<<"there is not any file being opened!";
        return;
    }
    qDebug() << fpath;
    //存入打开的文件
    QFile file;
    file.setFileName(fpath);
    //只读方式打开
    file.open(QIODevice::WriteOnly);
    //读取编辑区文字
    QString str=ui->textEdit_2->toPlainText();
    //以UTF-8编码方式写入文件
    file.write(str.toUtf8());
    qDebug()<<"writing succeed!";
    file.close(); //关闭文件
}
