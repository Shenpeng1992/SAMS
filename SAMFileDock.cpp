//如果使用VS编译器，需要将代码强制转换为UTF-8,并将文件保存为UTF-8编码，才能正确显示中文
#if defined(_MSC_VER)&&(_MSC_VER>=1600)
#pragma execution_character_set("utf-8")
#endif

#include "SAMFileDock.h"

#include <QVBoxLayout>
#include <QHeaderView>
#include <QDebug>

SAMFileDock::SAMFileDock(QWidget *parent) :
    QDockWidget(parent)
{
    this->setMaximumWidth(300);
    QString LOG;
    LOG=QDateTime::currentDateTime().toString("yyyy.MM.dd;hh:mm:ss")+"\t"+"Initialize FileDock";
    qDebug()<<LOG;

    ////@S1 建立UI
    createRightMenu();

    tab=new QTabWidget;

//    setWindowFlags(Qt::FramelessWindowHint);
    setWindowTitle("文件管理");

    table=new QTableWidget;
    table->verticalHeader()->setVisible(false);
    QStringList headname;
    headname.append("左片");
    headname.append("右片");
    table->setColumnCount(2);
    table->setColumnWidth(0,125);
    table->setColumnWidth(1,125);
    table->setHorizontalHeaderLabels(headname);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
//    table->horizontalHeader()->setVisible(false);
    table->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(table,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(tableRightClicked(const QPoint)));
    connect(table,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(tableClicked(QTableWidgetItem*)));
    connect(table,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(tableDoubleClicked(QTableWidgetItem*)));

    production=new QTableWidget;
    production->verticalHeader()->setVisible(false);
    headname.clear();
    headname.append("产品目录");
    production->setColumnCount(1);
    production->setColumnWidth(0,250);
    production->setHorizontalHeaderLabels(headname);
    production->setEditTriggers(QAbstractItemView::NoEditTriggers);
//    production->horizontalHeader()->setVisible(false);
    production->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(production,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(productionRightClicked(const QPoint)));
    connect(production,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(productionClicked(QTableWidgetItem*)));
    connect(production,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(productionDoubleClicked(QTableWidgetItem*)));

    //取消边框与子格线
    table->setFrameShape(QFrame::NoFrame);
    production->setFrameShape(QFrame::NoFrame);
    table->setShowGrid(false);
    production->setShowGrid(false);

    //加入tabWidget
    tab->addTab(table,QIcon(":/bin/Data/Icon/Img.png"),"立体像对");
    tab->addTab(production,QIcon(":/bin/Data/Icon/Product.png"),"产品目录");

    QVBoxLayout *mainLayout=new QVBoxLayout;

    mainLayout->addWidget(tab);

    mainWidget=new QWidget;
    mainWidget->setLayout(mainLayout);

    this->setWidget(mainWidget);
}

SAMFileDock::~SAMFileDock()
{
}

QString SAMFileDock::getShortName(QString longname)//获取短名
{
    QStringList namelist=longname.split("/");
    return namelist.at(namelist.size()-1);
}

void SAMFileDock::refresh(SAMCore *core)
{
    localcore=core;
    QStringList *currentListL;
    QStringList *currentListR;
    QStringList *currentListP;

    ////@进行影像菜单刷新
    //设定行数
    currentListL=core->getNameListL();
    currentListR=core->getNameListR();

    int columnL,columnR;
    columnL=currentListL->size();columnR=currentListR->size();

    int column=columnL>columnR?columnL:columnR;

    table->clearContents();
    table->setRowCount(column);

    //逐行读取数据
    for(int i=0;i<column;i++)
    {
        if(i<columnL)        table->setItem(i,0,new QTableWidgetItem(getShortName(currentListL->at(i))));
        if(i<columnR)        table->setItem(i,1,new QTableWidgetItem(getShortName(currentListR->at(i))));
    }

    ////@进行产品菜单刷新
    //设定行数
    currentListP=core->getProductList();
    column=currentListP->size();
    production->clearContents();
    production->setRowCount(column);

    //逐行读取数据
    for(int i=0;i<column;i++)
    {
        production->setItem(i,0,new QTableWidgetItem(getShortName(currentListP->at(i))));
    }
}

void SAMFileDock::refresh()//刷新队列
{
    if(localcore==NULL) return;

    QStringList *currentListL;
    QStringList *currentListR;
    QStringList *currentListP;

    ////@进行影像菜单刷新
    //设定行数
    currentListL=localcore->getNameListL();
    currentListR=localcore->getNameListR();

    int columnL,columnR;
    columnL=currentListL->size();columnR=currentListR->size();

    int column=columnL>columnR?columnL:columnR;

    table->clearContents();
    table->setRowCount(column);

    //逐行读取数据
    for(int i=0;i<column;i++)
    {
        if(i<columnL)        table->setItem(i,0,new QTableWidgetItem(getShortName(currentListL->at(i))));
        if(i<columnR)        table->setItem(i,1,new QTableWidgetItem(getShortName(currentListR->at(i))));
    }


    ////@进行产品菜单刷新
    //设定行数
    currentListP=localcore->getProductList();
    column=currentListP->size();
    production->clearContents();
    production->setRowCount(column);

    //逐行读取数据
    for(int i=0;i<column;i++)
    {
        production->setItem(i,0,new QTableWidgetItem(getShortName(currentListP->at(i))));
    }
}

void SAMFileDock::createRightMenu()
{
    ////@S1声明菜单
    //@左列右击菜单
    LMenu=new QMenu(this);
    AddLLine=new QAction(QIcon(":/bin/Data/Icon/add.png"),"插入",0);
    delLLine=new QAction(QIcon(":/bin/Data/Icon/removeI.png"),"删除",0);
    upLLine=new QAction(QIcon(":/bin/Data/Icon/up.png"),"上调",0);
    downLLine=new QAction(QIcon(":/bin/Data/Icon/down.png"),"下调",0);
    //@右列右击菜单
    RMenu=new QMenu(this);
    AddRLine=new QAction(QIcon(":/bin/Data/Icon/add.png"),"插入",0);
    delRLine=new QAction(QIcon(":/bin/Data/Icon/removeI.png"),"删除",0);
    upRLine=new QAction(QIcon(":/bin/Data/Icon/up.png"),"上调",0);
    downRLine=new QAction(QIcon(":/bin/Data/Icon/down.png"),"下调",0);
    //@产品列右击菜单
    PMenu=new QMenu(this);
    AddPLine=new QAction(QIcon(":/bin/Data/Icon/add.png"),"插入",0);
    delPLine=new QAction(QIcon(":/bin/Data/Icon/removeI.png"),"删除",0);
    upPLine=new QAction(QIcon(":/bin/Data/Icon/up.png"),"上调",0);
    downPLine=new QAction(QIcon(":/bin/Data/Icon/down.png"),"下调",0);
    //@公用Action
    AddLRLine=new QAction(QIcon(":/bin/Data/Icon/add.png"),"插入行",0);
    delLRLine=new QAction(QIcon(":/bin/Data/Icon/removeI.png"),"删除行",0);
    upLRLine=new QAction(QIcon(":/bin/Data/Icon/up.png"),"上调行",0);
    downLRLine=new QAction(QIcon(":/bin/Data/Icon/down.png"),"下调行",0);
    changeLRPath=new QAction(QIcon(":/bin/Data/Icon/fresh.png"),"从文件选择",0);
    changePPath=new QAction(QIcon(":/bin/Data/Icon/fresh.png"),"从文件选择",0);

    ////@S2组件菜单
    //////////////////////////////////////////////
    LMenu->clear();
    LMenu->addAction(AddLLine);
    LMenu->addAction(AddLRLine);
    LMenu->addAction(delLLine);
    LMenu->addAction(delLRLine);
    LMenu->addSeparator();

    LMenu->addAction(upLLine);
    LMenu->addAction(upLRLine);
    LMenu->addAction(downLLine);
    LMenu->addAction(downLRLine);
    LMenu->addSeparator();

    LMenu->addAction(changeLRPath);
    //////////////////////////////////////////////
    RMenu->clear();
    RMenu->addAction(AddRLine);
    RMenu->addAction(AddLRLine);
    RMenu->addAction(delRLine);
    RMenu->addAction(delLRLine);
    RMenu->addSeparator();

    RMenu->addAction(upRLine);
    RMenu->addAction(upLRLine);
    RMenu->addAction(downRLine);
    RMenu->addAction(downLRLine);
    RMenu->addSeparator();

    RMenu->addAction(changeLRPath);
    //////////////////////////////////////////////
    PMenu->clear();
    PMenu->addAction(AddPLine);
    PMenu->addAction(delPLine);
    PMenu->addSeparator();

    PMenu->addAction(upPLine);
    PMenu->addAction(downPLine);
    PMenu->addSeparator();

    PMenu->addAction(changePPath);

    ////@S3关联菜单信号
    connect(AddLLine,SIGNAL(triggered(bool)),this,SLOT(actionAddLLine()));
    connect(AddRLine,SIGNAL(triggered(bool)),this,SLOT(actionAddRLine()));
    connect(AddLRLine,SIGNAL(triggered(bool)),this,SLOT(actionAddLRLine()));
    connect(AddPLine,SIGNAL(triggered(bool)),this,SLOT(actionAddPLine()));

    connect(delLLine,SIGNAL(triggered(bool)),this,SLOT(actiondelLLine()));
    connect(delRLine,SIGNAL(triggered(bool)),this,SLOT(actiondelRLine()));
    connect(delLRLine,SIGNAL(triggered(bool)),this,SLOT(actiondelLRLine()));
    connect(delPLine,SIGNAL(triggered(bool)),this,SLOT(actiondelPLine()));

    connect(upLLine,SIGNAL(triggered(bool)),this,SLOT(actionupLLine()));
    connect(upRLine,SIGNAL(triggered(bool)),this,SLOT(actionupRLine()));
    connect(upLRLine,SIGNAL(triggered(bool)),this,SLOT(actionupLRLine()));
    connect(upPLine,SIGNAL(triggered(bool)),this,SLOT(actionupPLine()));

    connect(downLLine,SIGNAL(triggered(bool)),this,SLOT(actiondownLLine()));
    connect(downRLine,SIGNAL(triggered(bool)),this,SLOT(actiondownRLine()));
    connect(downLRLine,SIGNAL(triggered(bool)),this,SLOT(actiondownLRLine()));
    connect(downPLine,SIGNAL(triggered(bool)),this,SLOT(actiondownPLine()));

    connect(changeLRPath,SIGNAL(triggered(bool)),this,SLOT(actionchangeLRPath()));
    connect(changePPath,SIGNAL(triggered(bool)),this,SLOT(actionchangePPath()));
}

void SAMFileDock::tableRightClicked(const QPoint &a)
{
    //获取当前行列
    QTableWidgetItem *currentItem;
    currentItem=table->itemAt(a);

    if(currentItem==NULL)
    {//条目不存在则返回
        return;
    }

    currentTableColumn=currentItem->column();
    currentTableRow=currentItem->row();

    switch(currentTableColumn)//根据列号判断右键菜单
    {
        case 0:
            LMenu->exec(QCursor::pos());
            break;//左影像菜单加载
        case 1:
            RMenu->exec(QCursor::pos());
            break;//右影像菜单加载
    }
}

void SAMFileDock::productionRightClicked(const QPoint &a)
{
    //获取当前行列
    QTableWidgetItem *currentItem;
    currentItem=production->itemAt(a);

    if(currentItem==NULL)
    {//条目不存在则返回
        return;
    }

    currentProjectRow=currentItem->row();

    PMenu->exec(QCursor::pos());
}

void SAMFileDock::actionAddLLine()
{
    if(currentTableColumn==0)
    {
        localcore->AddLLine(currentTableRow);
        refresh();
    }
    else return;
}

void SAMFileDock::actionAddRLine()
{
    if(currentTableColumn==1)
    {
        localcore->AddRLine(currentTableRow);
        refresh();
    }
    else return;
}

void SAMFileDock::actionAddLRLine()
{
    localcore->AddLRLine(currentTableRow);
    refresh();
}

void SAMFileDock::actionAddPLine()
{
    localcore->AddPLine(currentProjectRow);
    refresh();
}

void SAMFileDock::actiondelLLine()
{
    if(currentTableColumn==0)
    {
        localcore->delLLine(currentTableRow);
        refresh();
    }
    else return;
}

void SAMFileDock::actiondelRLine()
{
    if(currentTableColumn==1)
    {
        localcore->delRLine(currentTableRow);
        refresh();
    }
    else return;
}

void SAMFileDock::actiondelLRLine()
{
    localcore->delLRLine(currentTableRow);
    refresh();
}

void SAMFileDock::actiondelPLine()
{
    localcore->delPLine(currentProjectRow);
    refresh();
}

void SAMFileDock::actionupLLine()
{
    if(currentTableColumn==0)
    {
        localcore->upLLine(currentTableRow);
        refresh();
    }
    else return;
}

void SAMFileDock::actionupRLine()
{
    if(currentTableColumn==1)
    {
        localcore->upRLine(currentTableRow);
        refresh();
    }
    else return;
}

void SAMFileDock::actionupLRLine()
{
    localcore->upLRLine(currentTableRow);
    refresh();
}

void SAMFileDock::actionupPLine()
{
    localcore->upPLine(currentProjectRow);
    refresh();
}

void SAMFileDock::actiondownLLine()
{
    localcore->downLLine(currentTableRow);
    refresh();
}

void SAMFileDock::actiondownRLine()
{
    localcore->downRLine(currentTableRow);
    refresh();
}

void SAMFileDock::actiondownLRLine()
{
    localcore->downLRLine(currentTableRow);
    refresh();
}

void SAMFileDock::actiondownPLine()
{
    localcore->downPLine(currentProjectRow);
    refresh();
}

void SAMFileDock::actionchangeLRPath()
{
    localcore->changeLRPath(currentTableColumn,currentTableRow);
    refresh();
}

void SAMFileDock::actionchangePPath()
{
    localcore->changePPath(currentProjectRow);
    refresh();
}

void SAMFileDock::tableClicked(QTableWidgetItem* a)
{
    if(a==NULL)
    {//条目不存在则返回
        return;
    }

    currentTableColumn=a->column();
    currentTableRow=a->row();

    switch(currentTableColumn)//根据列号判断右键菜单
    {
        case 0:
            localcore->setCurrentL(currentTableRow);
            emit InfoRefresh(*localcore->getCurrentL());
            break;//左影像
        case 1:
            localcore->setCurrentR(currentTableRow);
            emit InfoRefresh(*localcore->getCurrentR());
            break;//右影像
    }
}

void SAMFileDock::productionClicked(QTableWidgetItem* a)
{
    if(a==NULL)
    {//条目不存在则返回
        return;
    }

    currentProjectRow=a->row();

    localcore->setCurrentProduct(currentProjectRow);
    emit InfoRefresh(*localcore->getCurrentProduct());
}

void SAMFileDock::tableDoubleClicked(QTableWidgetItem* a)
{
    if(a==NULL)
    {//条目不存在则返回
        return;
    }

    currentTableColumn=a->column();
    currentTableRow=a->row();

    switch(currentTableColumn)//根据列号判断右键菜单
    {
        case 0:
            localcore->setCurrentL(currentTableRow);
            emit ShowLImg(*localcore->getCurrentL());
            break;//左影像
        case 1:
            localcore->setCurrentR(currentTableRow);
            emit ShowRImg(*localcore->getCurrentR());
            break;//右影像
    }
}

void SAMFileDock::productionDoubleClicked(QTableWidgetItem* a)
{
    if(a==NULL)
    {//条目不存在则返回
        return;
    }

    currentProjectRow=a->row();

    localcore->setCurrentProduct(currentProjectRow);
    emit ShowP(*localcore->getCurrentProduct());
}
