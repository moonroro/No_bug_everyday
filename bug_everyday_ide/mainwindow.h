#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QTreeWidgetItem>
#include <myfile.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void OpenFile();  //打开文件
    void SaveFile(int);  //保存文件
    void Save_asFile(); //另存为文件
    void InitFileList(); //初始化文件列表
    void addFileList(MyFile); //添加文件列表
    void f();
public slots:
    void TreeWidgetClick(QTreeWidgetItem *item,int column);
private:
    Ui::MainWindow *ui;
    QTreeWidgetItem * FileList;
    bool isopenfile;
    bool issavefile;
    MyFile myfile[11];
    int filenum;
    int cus;
private slots:
        void on_copy();       //声明复制函数
        void select_all();     //声明全选函数函数
        void paste_it();       //声明粘贴函数
        void cut_it();           //声明剪切函数
        void redo_it();         //声明重做函数
        void reg_it();          //声明恢复函数
//        void edit_it();         //声明编译函数
//        void run_it();           //声明运行函数
        void ann_it();      //声明添加注释函数
        void cann_it();     //声明取消注释函数
        void ind_it();      //声明缩进函数
        void cind_it();      //声明取消缩进函数
};

#endif // MAINWINDOW_H
