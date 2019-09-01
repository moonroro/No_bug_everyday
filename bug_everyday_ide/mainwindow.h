#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QFile>
#include<QFileDialog>
#include<QFileInfo>
#include<QDebug>
#include<QByteArray>
#include<QTextCodec>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString OpenFile();  //打开文件
    void SaveFile(int,QString);  //保存文件
private:
    Ui::MainWindow *ui;
    int isopenfile;
    QString fpath;
private slots:
        void on_copy();       //声明复制函数
        void select_all();     //声明全选函数函数
        void paste_it();       //声明粘贴函数
        void cut_it();           //声明剪切函数
        void redo_it();         //声明重做函数
        void reg_it();          //声明恢复函数
        void edit_it();      //编译
        void run_it();      //运行
};

#endif // MAINWINDOW_H
