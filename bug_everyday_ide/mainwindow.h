#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
 private slots:
        void on_copy();       //声明复制函数
        void select_all();     //声明全选函数函数
        void paste_it();       //声明粘贴函数
        void cut_it();           //声明剪切函数
        void redo_it();         //声明重做函数
        void reg_it();          //声明恢复函数
};

#endif // MAINWINDOW_H
