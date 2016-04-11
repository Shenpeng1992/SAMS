#include <QDateTime>
#include <QDebug>
#include <QPushButton>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QFileDialog>

#include "SAMImgViewer.h"

SAMImgViewer::SAMImgViewer(SAMCore *core,QWidget *parent) : QWidget(parent)
{
    localcore=core;
    QString LOG;
    LOG=QDateTime::currentDateTime().toString("yyyy.MM.dd;hh:mm:ss")+"\t"+"Initialize ImgViewer";
    qDebug()<<LOG;

    layout=new QHBoxLayout;

    createActions();
    createToolBar();

    paintWidget=new SAMPaintWidget;
    layout->addWidget(paintWidget);

    this->setLayout(layout);
}

void  SAMImgViewer::createActions()
{
    actionEnlarge=new QAction(QIcon(":/bin/Data/Icon/enlarge.png"),QStringLiteral("放大"),0);
    actionNarrow=new QAction(QIcon(":/bin/Data/Icon/narrow.png"),QStringLiteral("缩小"),0);
    actionMove=new QAction(QIcon(":/bin/Data/Icon/move.png"),QStringLiteral("移动到"),0);
    actionRotation=new QAction(QIcon(":/bin/Data/Icon/rotate.png"),QStringLiteral("旋转"),0);

    actionOpen=new QAction(QIcon(":/bin/Data/Icon/open.png"),QStringLiteral("打开"),0);
    actionCancel=new QAction(QIcon(":/bin/Data/Icon/cancel.png"),QStringLiteral("取消"),0);

    actionRefresh=new QAction(QIcon(":/bin/Data/Icon/fresh.png"),QStringLiteral("刷新"),0);
    actionMinimap=new QAction(QIcon(":/bin/Data/Icon/minimap.png"),QStringLiteral("缩略图"),0);

    actionEnlarge->setEnabled(false);
    actionNarrow->setEnabled(false);
    actionMove->setEnabled(false);
    actionRotation->setEnabled(false);
//    actionOpen->setEnabled(false);
    actionCancel->setEnabled(false);
    actionRefresh->setEnabled(false);
    actionMinimap->setEnabled(false);

    connect(actionEnlarge,SIGNAL(triggered(bool)),this,SLOT(ActionEnlarge()));
    connect(actionNarrow,SIGNAL(triggered(bool)),this,SLOT(ActionNarrow()));
    connect(actionMove,SIGNAL(triggered(bool)),this,SLOT(ActionMoveTo()));

    connect(actionOpen,SIGNAL(triggered(bool)),this,SLOT(ActionLoad()));
    connect(actionCancel,SIGNAL(triggered(bool)),this,SLOT(ActionUnload()));

    connect(actionMinimap,SIGNAL(triggered(bool)),this,SLOT(ActionshowMiniMap()));
    connect(actionRefresh,SIGNAL(triggered(bool)),this,SLOT(ActionRefresh()));
}

void  SAMImgViewer::createToolBar()
{
    toolbar=new QToolBar;
    toolbar->setOrientation(Qt::Vertical);
    toolbar->setMovable(true);

    toolbar->addAction(actionEnlarge);
    toolbar->addAction(actionNarrow);
    toolbar->addAction(actionMove);
    toolbar->addAction(actionRotation);
    toolbar->addSeparator();

    toolbar->addAction(actionOpen);
    toolbar->addAction(actionCancel);
    toolbar->addSeparator();

    toolbar->addAction(actionRefresh);
    toolbar->addAction(actionMinimap);

    layout->addWidget(toolbar);
}

void  SAMImgViewer::setCore(SAMCore *core)
{
    localcore=core;
}

void  SAMImgViewer::openImg(QString a)
{
    paintWidget->loadImg(a);

    QString LOG;
    LOG=QDateTime::currentDateTime().toString("yyyy.MM.dd;hh:mm:ss")+"\t"+"View Image "+a;

    localcore->writeLog(LOG);

    if(paintWidget->isLoaded())
    {
        actionEnlarge->setEnabled(true);
        actionNarrow->setEnabled(true);
        actionMove->setEnabled(true);
        actionRotation->setEnabled(true);
//        actionOpen->setEnabled(true);
        actionCancel->setEnabled(true);
        actionRefresh->setEnabled(true);
        actionMinimap->setEnabled(true);
    }
}

void  SAMImgViewer::ActionshowMiniMap()
{
    ////@S1 写入Log
    QString LOG;
    LOG=QDateTime::currentDateTime().toString("yyyy.MM.dd;hh:mm:ss")+"\t"+"Open/Cancel Minimap";

    localcore->writeLog(LOG);

    ////@S2 绘图Widget执行操作
    paintWidget->changeMinimap();
}

void  SAMImgViewer::ActionEnlarge()
{
    ////@S1 写入Log
    QString LOG;
    LOG=QDateTime::currentDateTime().toString("yyyy.MM.dd;hh:mm:ss")+"\t"+"Enlarge Map";

    localcore->writeLog(LOG);

    ////@S2 绘图Widget执行操作
    paintWidget->ActionEnLarge();
}

void  SAMImgViewer::ActionNarrow()
{
    ////@S1 写入Log
    QString LOG;
    LOG=QDateTime::currentDateTime().toString("yyyy.MM.dd;hh:mm:ss")+"\t"+"Narrow Map";

    localcore->writeLog(LOG);

    ////@S2 绘图Widget执行操作
    paintWidget->ActionNarrow();
}

void  SAMImgViewer::ActionMoveTo()
{
    QDialog moveTo(this);

    moveTo.setWindowTitle(QStringLiteral("请输入最终左上角坐标:"));
    QPushButton OK(QStringLiteral("确定"));
    QPushButton Cancel(QStringLiteral("取消"));

    QLabel X(QStringLiteral("X:"));
    QLabel Y(QStringLiteral("Y:"));

    QLineEdit EditX;
    QLineEdit EditY;

    QGridLayout a;
    a.addWidget(&X,0,0);
    a.addWidget(&Y,1,0);
    a.addWidget(&EditX,0,1);
    a.addWidget(&EditY,1,1);
    a.addWidget(&OK,2,0);
    a.addWidget(&Cancel,2,1);

    moveTo.setLayout(&a);
    connect(&OK,SIGNAL(clicked(bool)),&moveTo,SLOT(accept()));
    connect(&Cancel,SIGNAL(clicked(bool)),&moveTo,SLOT(reject()));
    moveTo.exec();

    if(moveTo.result()==QDialog::Accepted)
    {
        ////@S1 写入Log
        QString LOG;
        LOG=QDateTime::currentDateTime().toString("yyyy.MM.dd;hh:mm:ss")+"\t"+"Move";

        localcore->writeLog(LOG);

        ////@S2 绘图Widget执行操作
        paintWidget->moveTo(EditX.text().toInt(),EditY.text().toInt());
    }
}

void  SAMImgViewer::ActionRefresh()
{
    ////@S1 写入Log
    QString LOG;
    LOG=QDateTime::currentDateTime().toString("yyyy.MM.dd;hh:mm:ss")+"\t"+"Refresh";

    localcore->writeLog(LOG);

    ////@S2 绘图Widget执行操作
    paintWidget->RefreshImg();
}

void  SAMImgViewer::ActionUnload()
{
    ////@S1 写入Log
    QString LOG;
    LOG=QDateTime::currentDateTime().toString("yyyy.MM.dd;hh:mm:ss")+"\t"+"Unload Image";

    localcore->writeLog(LOG);

    ////@S2 绘图Widget执行操作
    paintWidget->Unload();
}

void  SAMImgViewer::ActionLoad()
{
    QString filename;
    filename=QFileDialog::getOpenFileName(NULL,QStringLiteral("打开"),*localcore->getWorkFloder(),QStringLiteral("其他文件 (*.*);;JPG (*.jpg *.JPG);;PNG (*.png *.PNG);;BMP (*.bmp *.BMP)"));

    if(filename.isEmpty())
        return;

    this->openImg(filename);
}
