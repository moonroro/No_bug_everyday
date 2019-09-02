#ifndef FILEDEAL_H
#define FILEDEAL_H
#include "mainwindow.h"
#include "ui_mainwindow.h"
//打开文件函数
void MainWindow::OpenFile()
{
    if(cus>10) return ;
    QString path=QFileDialog::getOpenFileName(this, tr("打开文件"),"",tr("Text or C files (*.txt *.c *.cpp *.h);; " "All Files(*)"));   //选择文件，存入文件路径
    if(!path.count()){
        qDebug()<<"用户取消";
        return ;
    }
    myfile[cus].no = cus;
    myfile[cus].Path = path;           //类成员存储文件路径
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");   //文件编码方式
    myfile[cus].File=new QFile(path); //生成QFile类文件
    myfile[cus].Info=new QFileInfo(path);
    myfile[cus].File->open(QIODevice::ReadWrite);   //以只读方式打开
    myfile[cus].Array= myfile[cus].File->readAll();  //读写文件信息存入QByteArray类
    ui->textEdit_2->setText(codec->toUnicode(myfile[cus].Array));  //在编辑窗口显示
    myfile[cus].isopenfile=true;  //文件是否成功打开变量
    addFileList(myfile[cus]);
    myfile[cus].File->close();  //关闭文件
    cus++;
}
//保存文件函数
void MainWindow::SaveFile(int currentfile)
{
    //判断文件是否打开，若未打开文件，错误警告
    if(currentfile==0)
    {
        Save_asFile();
        qDebug()<<"there is not any file being opened!";
        return;
    }
    QFile file;
    file.setFileName(myfile[currentfile].Path); //存入打开的文件
    file.open(QIODevice::WriteOnly); //只读方式打开
    QString str=ui->textEdit_2->toPlainText(); //读取编辑区文字
    file.write(str.toUtf8()); //以UTF-8编码方式写入文件
    qDebug()<<"save succeed!";
    file.close(); //关闭文件
}
void MainWindow::Save_asFile()   //另存为文件函数
{
    QString path = QFileDialog::getSaveFileName(this, tr("保存文件"),"/home",tr("Text (*.txt);;C files (*.c );;C++ files (*.cpp )"));
    if(!path.count()){
        qDebug()<<"用户取消";
        return ;
    }
    QFile file;
    file.setFileName(path); //存入打开的文件
    file.open(QIODevice::WriteOnly); //以写方式打开
    QString str=ui->textEdit_2->toPlainText(); //读取编辑区文字
    file.write(str.toUtf8()); //以UTF-8编码方式写入文件
    qDebug()<<"另存为文件成功";
    file.close(); //关闭文件
}
//增加文件至窗口树
void MainWindow::addFileList(MyFile File){
    QTreeWidgetItem *newfile=new QTreeWidgetItem();
    newfile->setText(0,File.Info->fileName());
    newfile->setText(1,File.Path);
    newfile->setText(2,QString::number(File.no));
    qDebug() << File.no <<File.Info->fileName();
    ui->treeWidget->addTopLevelItem(newfile);
}
void MainWindow::TreeWidgetClick(QTreeWidgetItem *item,int column){
    qDebug() << item->text(0) << item->text(1);
    if(item->text(1)==""){return;}
    QFile CurrentFile(item->text(1));
    currentfile=item->text(2).toInt();
    CurrentFile.open(QIODevice::ReadWrite);
    QByteArray array= CurrentFile.readAll();
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");   //文件编码方式
    ui->textEdit_2->setText(codec->toUnicode(array));
    CurrentFile.close();
}
#endif // FILEDEAL_H
