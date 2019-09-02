#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filedeal.h"    //文件处理头文件(打开\保存)
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->splitter->setStretchFactor(0,1);
    ui->splitter->setStretchFactor(1,6);
    ui->splitter_2->setStretchFactor(0,4);
    ui->splitter_2->setStretchFactor(1,1);          //设置splitter的两个框的比例为 ,0表示右（上），1表示左（下） 右边表示1:7
    filenum=0;
    cus=1;
    /*以下部分是函数信号槽*/
    connect(ui->actioncpy,SIGNAL(triggered()),this,SLOT(on_copy()));        //复制
    connect(ui->actioncut,SIGNAL(triggered()),this,SLOT(cut_it()));             //剪切
    connect(ui->actionpst,SIGNAL(triggered()),this,SLOT(paste_it()));           //粘贴
    connect(ui->actionsal,SIGNAL(triggered()),this,SLOT(select_all()));         //全选
    connect(ui->action_redo,SIGNAL(triggered()),this,SLOT(redo_it()));      //重做
    connect(ui->actionreg,SIGNAL(triggered()),this,SLOT(reg_it()));             //恢复
    connect(ui->action_op,&QAction::triggered,this,[=](){OpenFile();});         //打开文件
    connect(ui->action_save,&QAction::triggered,this,[=](){SaveFile(cus);});        //保存文件
    connect(ui->action_sava,&QAction::triggered,this,[=](){Save_asFile();});        //另存为文件
 //   connect(ui->actionrun,&QAction::triggered,this,[=](){SaveFile(isopenfile,fpath);edit_it();run_it();});      //运行
 //   connect(ui->actionedit,&QAction::triggered,this,[=](){SaveFile(isopenfile,fpath);edit_it();});          //编译
    connect(ui->actionann,SIGNAL(triggered()),this,SLOT(ann_it()));   //注释函数
    connect(ui->actioncann,SIGNAL(triggered()),this,SLOT(cann_it()));   //取消注释函数
    connect(ui->actionind,SIGNAL(triggered()),this,SLOT(ind_it()));   //缩进函数
    connect(ui->actioncind,SIGNAL(triggered()),this,SLOT(cind_it()));   //取消缩进函数
    connect(ui->treeWidget,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(TreeWidgetClick(QTreeWidgetItem *,int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_copy()          //调用Qt中自带的拷贝函数
{
    ui->textEdit_2->copy();
}
void MainWindow::select_all()       //调用Qt中自带的全选函数
{
    ui->textEdit_2->selectAll();
}
void MainWindow::cut_it()              //调用Qt中自带的剪切函数
{
    ui->textEdit_2->cut();
}
void MainWindow::paste_it()         //调用Qt中自带的粘贴函数
{
    ui->textEdit_2->paste();
}
void MainWindow::redo_it()          //调用Qt中自带的重做函数
{
    ui->textEdit_2->redo();
}
void MainWindow::reg_it()           //调用Qt中自带的恢复函数
{
    ui->textEdit_2->undo();
}
//void MainWindow::edit_it()      //编译
//{
//    QString destname = fpath;
//    destname.replace(".c",".exe");
//    QString command = "gcc -o " + destname +" "+ fpath;
//    system(command.toStdString().data());
//}

//void MainWindow::run_it()       //运行
//{
//    QString destname = fpath;
//    destname.replace(".c",".exe");
//    system(destname.toStdString().data());
//}

void MainWindow::ann_it()     //添加注释的功能
{
//    QString text="/*\n */ ";
//    ui->textEdit_2->textCursor().insertText(text);
}
void MainWindow::cann_it()    //取消注释
{

}
void MainWindow::ind_it()     //添加缩进的功能
{
//    ui->textEdit_2 =  new QTextEdit(this);
//    QTextCursor cursor = ui->textEdit_2->textCursor();

}
void MainWindow::cind_it()   //取消缩进
{

}
