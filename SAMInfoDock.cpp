#include "SAMInfoDock.h"

#include <QDebug>
#include <QFile>
#include <QImage>

SAMInfoDock::SAMInfoDock(QWidget *parent) :
    QDockWidget(parent)
{
    this->setMaximumWidth(300);

    QString LOG;
    LOG=QDateTime::currentDateTime().toString("yyyy.MM.dd;hh:mm:ss")+"\t"+"Initialize InfoDock";
    qDebug()<<LOG;

    ////@S1 建立UI
    setWindowTitle(QStringLiteral("信息窗口"));
//    setWindowFlags(Qt::FramelessWindowHint);

    mainWidget=new QTabWidget;
    mainLayout=new QVBoxLayout;
    w=new QWidget;

    SysLog=new QLabel;
    ImgInfo=new QLabel;

    SysArea=new QScrollArea;
    ImgArea=new QScrollArea;

    SysArea->setWidget(SysLog);
    ImgArea->setWidget(ImgInfo);

    SysArea->setFrameShape(QFrame::NoFrame);
    ImgArea->setFrameShape(QFrame::NoFrame);
    SysArea->setAutoFillBackground(true);
    ImgArea->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(255,255,255));
    SysArea->setPalette(palette);
    ImgArea->setPalette(palette);

    mainWidget->addTab(SysArea,QIcon(":/bin/Data/Icon/SysLog.png"),QStringLiteral("系统日志"));
    mainWidget->addTab(ImgArea,QIcon(":/bin/Data/Icon/ImgInfo.png"),QStringLiteral("图片信息"));

    mainLayout->addWidget(mainWidget);
    w->setLayout(mainLayout);

    this->setWidget(w);

    ////@S2 执行其他构造功能
    RefreshLog();
}

SAMInfoDock::~SAMInfoDock()
{
}

void SAMInfoDock::RefreshInfo(const QString a)
{
    QImage InfoImg;
    if(InfoImg.load(a)==false)  return;

    QString Info;
    Info="\n\n\n\nFile Name : "+a+"\n";
    Info=Info+"\nSize : "+QString::number(InfoImg.width(),10)+"*"+QString::number(InfoImg.height(),10)+"\n";
    Info=Info+"\nDepth : "+QString::number(InfoImg.depth(),10)+"\n";

    ImgInfo->setText(Info);
    ImgInfo->adjustSize();
}

void SAMInfoDock::RefreshLog()
{
    QFile file("./SystemLog.log");
    file.open(QIODevice::ReadOnly);

    if(!file.isOpen())  return;

    QString log;
    log.append("\n");
    while(!file.atEnd())
    {
        log.append(" ");
        log.append(file.readLine());
        log.append("\n");
    }
    SysLog->setText(log);
    SysLog->adjustSize();
}

void SAMInfoDock::setCore(SAMCore *core)
{
    localcore=core;
}
