#include "mainwindow.h"

#include <QApplication>
#include <QDebug>

extern "C" {
    #include <libavutil/avutil.h>
#include <libavdevice/avdevice.h>
}

int main(int argc, char *argv[])
{

    qDebug() << av_version_info();
    //1, register device
    avdevice_register_all();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
