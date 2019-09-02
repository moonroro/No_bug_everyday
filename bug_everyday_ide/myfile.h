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
    QString Path;
    QFile *File;
    QFileInfo *Info;
    QByteArray Array;
    int no;
    bool isopenfile;
    bool isopenned;
    bool issavefile;
};
#endif // MYFILE_H
