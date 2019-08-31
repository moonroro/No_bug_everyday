#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QTextCodec>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->pushButton,&QPushButton::clicked,[=](){
        QString path=QFileDialog::getOpenFileName(this,"打开文件","C:\\Users\\Administrator\\Desktop");
        QTextCodec *codec = QTextCodec::codecForName("UTF-8");

        ui->lineEdit->setText(path);
        QFile file(path);
        file.open(QIODevice::ReadOnly);
        QByteArray array = file.readAll();
        //ui->textEdit->setText(array);
        ui->textEdit->setText(codec->toUnicode(array));
        file.close();
        file.open(QIODevice::Append);
        file.write("aaaaaaaa");
        file.close();
    });

}

Widget::~Widget()
{
    delete ui;
}
