#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filedeal.h"    //文件处理头文件(打开\保存)
#include "find_dialog.h"


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
    connect(ui->actionrun,&QAction::triggered,this,[=](){SaveFile(cus);if(edit_it())run_it();});      //运行
    connect(ui->actionedit,&QAction::triggered,this,[=](){SaveFile(cus);edit_it();});          //编译
    connect(ui->actionann,SIGNAL(triggered()),this,SLOT(ann_it()));   //注释函数
    connect(ui->actioncann,SIGNAL(triggered()),this,SLOT(cann_it()));   //取消注释函数
    connect(ui->actionind,SIGNAL(triggered()),this,SLOT(ind_it()));   //缩进函数
    connect(ui->actioncind,SIGNAL(triggered()),this,SLOT(cind_it()));   //取消缩进函数
    connect(ui->actionfs,SIGNAL(triggered()),this,SLOT(full_screen()));    //全屏信号槽
    connect(ui->actionsrh,&QAction::triggered,this,&MainWindow::search_show);   //搜索
    connect(ui->treeWidget,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(TreeWidgetClick(QTreeWidgetItem *,int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sleep(unsigned int tim)        //延时函数
{
       QTime reachtime = QTime::currentTime().addMSecs(tim);        //获取当前时间加上你需要延时的时间
       while(QTime::currentTime()<reachtime)
       {
           QCoreApplication::processEvents(QEventLoop::AllEvents,100);   // 最小循环时间是0.1秒
       }
}

 void   MainWindow:: keyPressEvent(QKeyEvent *event)  //实现一些键盘操作
    {
        if(event->key()==Qt::Key_Escape&&Fullsize)
        {
            Fullsize = false;
            showNormal();
             ui->statusBar->showMessage(" ");   //清空状态栏中的信息
        }
    }

void MainWindow::on_copy()          //调用Qt中自带的拷贝函数
{
    ui->textEdit_2->copy();
    ui->statusBar->showMessage(tr("    拷贝成功"),1500);        //在状态栏中显示信息，时间为1.5秒
}
void MainWindow::select_all()       //调用Qt中自带的全选函数
{
    ui->textEdit_2->selectAll();
    ui->statusBar->showMessage(tr("    已经全部选择"),1500);
}
void MainWindow::cut_it()              //调用Qt中自带的剪切函数
{
    ui->textEdit_2->cut();
    ui->statusBar->showMessage(tr("    剪切成功"),1500);
}
void MainWindow::paste_it()         //调用Qt中自带的粘贴函数
{
    ui->textEdit_2->paste();
}
void MainWindow::redo_it()          //调用Qt中自带的重做函数
{
    ui->textEdit_2->redo();
    ui->statusBar->showMessage(tr("    成功还原上一步操作"),1500);
}
void MainWindow::reg_it()           //调用Qt中自带的恢复函数
{
    ui->textEdit_2->undo();
    ui->statusBar->showMessage(tr("    已经回到后一步操作"),1500);
}

void MainWindow::full_screen()
{
    showFullScreen();
    Fullsize = true;
    ui->statusBar->showMessage(tr("    已成功进入全屏模式"),1500);
    sleep(1500);
    ui->statusBar->showMessage(tr("    按下ESC按键退出全屏"));
}
bool MainWindow::edit_it()//编译
{
    QString destname = myfile[currentfile].Path;
    QString fpath = myfile[currentfile].Path;
    int edit_con = -50;
    destname.replace(".c",".exe");
    QString command = "gcc -o " + destname +" "+ fpath + " 2> error.txt";

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QFile file("error.txt");
    file.open(QIODevice::ReadWrite);
    QByteArray array = file.readAll();
    ui->textEdit_3->setText(codec->toUnicode(array));
    file.close();
    if(!array.isEmpty()){//编译错误
        qDebug()<<"edit error!";
        return false;
//        ui->setupUi(editerror);
    }
    else//编译成功
    {
        qDebug()<<"edit success!";
        return true;
    }
}
void MainWindow::run_it()//运行
{
    QString destname = myfile[currentfile].Path;
    destname.replace(".c",".exe");
    system(destname.toStdString().data());
    qDebug()<<"run success!";
}
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

void MainWindow::search_show(){  //搜索窗口
    find_dialog *find_dlg = new find_dialog();
    find_dlg->setAttribute(Qt::WA_DeleteOnClose);
    find_dlg->setWindowTitle(tr("查找"));
    connect(find_dlg,&find_dialog::start_search,this,[=](){search(find_dlg);});
    find_dlg->show();
}

void MainWindow::search(find_dialog *find_dlg)   //搜索
{
    QString str = find_dlg->find_text;
    bool isfind;
    if(find_dlg->distinguish)   //true区分大小写，false不区分
        isfind = ui->textEdit_2->find(str,QTextDocument::FindCaseSensitively);
    else
        isfind = ui->textEdit_2->find(str);
    if(!isfind)//查找不到
        qDebug()<<QString(tr("查找%1失败").arg(str));
    else
        qDebug()<<QString(tr("查找%1成功").arg(str));

}
