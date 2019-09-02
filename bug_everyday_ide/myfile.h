#ifndef MYFILE_H
#define MYFILE_H
#include <QFile>
#include <QFileInfo>
#include <QByteArray>
#include <QTextCodec>
#include <QString>
class MyFile{
public:
    MyFile():isopenfile(false),isopenned(false),issavefile(false){}
    QString Path;      //文件路径
    QFile *File;       //Q文件指针
    QFileInfo *Info;   //文件信息指针
    QByteArray Array;   //文件存储
    int no;
    bool isopenfile;
    bool isopenned;
    bool issavefile;
};
#endif // MYFILE_H
