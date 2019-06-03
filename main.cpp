#include <QFile>
#include <QDebug>
#include <iostream>
#include <QByteArray>
#include <algorithm>


int main(int argc, char *argv[])
{
    if (argc<2) {
        qDebug()<<"Files not defined!"<<endl <<"Pres any key to continue...";
        char c;
        std::cin>>c;
        return 0;
    }
    QFile inputFile(argv[1]);
    if (!inputFile.open(QFile::ReadOnly)) {
        qDebug()<<"Input file can't be opened!"<<endl <<"Pres any key to continue...";
        char c;
        std::cin>>c;
        return 0;
    }
    auto all=inputFile.readAll();
    if (inputFile.error()!=QFile::NoError) {
        qDebug()<<"Error during reading input file!"<<endl <<"Pres any key to continue...";
        char c;
        std::cin>>c;
        return 0;
    }
    inputFile.close();

    QString text=QString::fromLocal8Bit(all);
    std::reverse(text.begin(), text.end());
    text.replace("\n\r","\r\n");
    bool isOutputFileDefined=argc>2;
    QFile outputFile;
    if (isOutputFileDefined) {
        outputFile.setFileName(argv[2]);
        if (!outputFile.open(QFile::WriteOnly)) {
            qDebug()<<"Output file can't be opened!"<<endl <<"Pres any key to continue...";
            char c;
            std::cin>>c;
            return 0;
        }
    }
    if (isOutputFileDefined) {
        outputFile.write(text.toLocal8Bit());
        outputFile.flush();
        if (outputFile.error()!=QFile::NoError) {
            qDebug()<<"Error during writing output file!"<<endl;
        }
        qDebug()<<"Pres any key to continue...";
        char c;
        std::cin>>c;
        return 0;
    }

    qDebug()<<text<<endl <<"Pres any key to continue...";
    char c;
    std::cin>>c;
    return 0;
}
