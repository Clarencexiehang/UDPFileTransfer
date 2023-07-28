#include "mainwindow.h"
#include <QApplication>
#include<QFile>
#include<QTextStream>
#include<QLibrary>

MainWindow *w;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    w = new MainWindow;



    QLibrary *libcrypto_3_x64 = new QLibrary(":/lib/lib/libcrypto-3-x64.dll");
    libcrypto_3_x64->load();

    QLibrary *ws2_32 = new QLibrary(":/lib/lib/ws2_32.dll");
    ws2_32->load();

    QLibrary *libssl_3_x64 = new QLibrary(":/lib/lib/libssl-3-x64.dll");
    libssl_3_x64->load();

    QLibrary *zlibwapi = new QLibrary(":/lib/lib/zlibwapi.dll");
    zlibwapi->load();


    w->show();
    return a.exec();
}
