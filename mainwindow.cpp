#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFile>

extern "C" {
    #include <libavdevice/avdevice.h>
    #include <libavformat/avformat.h>
    #include <libavutil/avutil.h>
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_audioButton_clicked()
{
    AVFormatContext *fmt_ctx = NULL;
    const char *devicename = "hw:1";
    // start record
    //2,
    const AVInputFormat *fmt =  av_find_input_format("alsa");

    if (!fmt) {
        qDebug() << "get input type error" << "alsa";
        return;
    }

    // 3. open devices
    int ret = avformat_open_input(&fmt_ctx, devicename, fmt, NULL);
    if (ret != 0) {
        return;
    }

    //4, audio collection

    const char *filename = "/tmp/out.pcm";
    QFile file(filename);


    if(!file.open(QIODeviceBase::OpenModeFlag::WriteOnly)) {

        avformat_close_input(&fmt_ctx);
        return;
    }

    int count = 50;

    AVPacket pkt;

    while (count-- > 0 && av_read_frame(fmt_ctx, &pkt) == 0) {
        file.write((const char *)pkt.data, pkt.size);
    }


    // 5, release resources

    file.close();
    avformat_close_input(&fmt_ctx);

}

