//如果使用VS编译器，需要将代码强制转换为UTF-8,并将文件保存为UTF-8编码，才能正确显示中文
#if defined(_MSC_VER)&&(_MSC_VER>=1600)
#pragma execution_character_set("utf-8")
#endif

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowIcon(QIcon(":/bin/Data/Icon/dialog.png"));
    this->setWindowTitle("空间抵近测量系统 - Space Approaching Measurement System");
    ////@S1 初始化核心组件
    core=new SAMCore;

    ////@S2 创建MDI区域
    createMdiArea();

    ////@S3 创建窗口
    createFileDock();
    createInfoDock();

    this->setWindowState(Qt::WindowMaximized);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_SetWorkPath_triggered()
{
    core->setWorkFloder();
}

void MainWindow::createFileDock()//创建文件Dock
{
    m_filedock=new SAMFileDock(this);
    m_filedock->refresh(core);
    this->addDockWidget(Qt::LeftDockWidgetArea,m_filedock);
    connect(m_filedock,SIGNAL(ShowLImg(QString)),m_limgviewer,SLOT(openImg(QString)));
    connect(m_filedock,SIGNAL(ShowRImg(QString)),m_rimgviewer,SLOT(openImg(QString)));
    connect(m_filedock,SIGNAL(ShowP(QString)),m_pimgviewer,SLOT(loadProduct(QString)));
}

void MainWindow::createInfoDock()//创建文件Dock
{
    m_infodock=new SAMInfoDock(this);
//    m_infodock->refresh(core);
    m_infodock->setCore(core);
    this->addDockWidget(Qt::LeftDockWidgetArea,m_infodock);
    connect(m_filedock,SIGNAL(InfoRefresh(QString)),m_infodock,SLOT(RefreshInfo(QString)));

    connect(core,SIGNAL(writeLog()),m_infodock,SLOT(RefreshLog()));
}

void MainWindow::createMdiArea()//创建主窗口
{
    m_splitter=new QSplitter(Qt::Vertical);
    m_imgsplitter=new QSplitter(Qt::Horizontal);

    m_splitter->setOpaqueResize(false);
    m_imgsplitter->setOpaqueResize(false);

    m_limgviewer=new SAMImgViewer(core);
    m_rimgviewer=new SAMImgViewer(core);

    m_imgsplitter->addWidget(m_limgviewer);
    m_imgsplitter->addWidget(m_rimgviewer);

    m_pimgviewer=new SAMProductViewer(core);
    m_splitter->addWidget(m_imgsplitter);
    m_splitter->addWidget(m_pimgviewer);
    connect(core,SIGNAL(showproducts(QString)),m_pimgviewer,SLOT(loadProduct(QString)));

    this->setCentralWidget(m_splitter);

    m_splitter->show();
}

void MainWindow::on_action_AddLFloder_triggered()
{
    core->AddLFloder();
     m_filedock->refresh(core);
}

void MainWindow::on_action_AddLImg_triggered()
{
    core->AddLImg();
     m_filedock->refresh(core);
}

void MainWindow::on_action_AddRImg_triggered()
{
    core->AddRImg();
     m_filedock->refresh(core);
}

void MainWindow::on_action_AddRFloder_triggered()
{
    core->AddRFloder();
     m_filedock->refresh(core);
}

void MainWindow::on_action_unloadL_triggered()
{
    core->unloadL();
     m_filedock->refresh(core);
}

void MainWindow::on_action_unloadR_triggered()
{
    core->unloadR();
     m_filedock->refresh(core);
}

void MainWindow::on_action_unloadAll_triggered()
{
    core->unLoadAll();
     m_filedock->refresh(core);
}

void MainWindow::on_action_unloadP_triggered()
{
    core->unloadP();
     m_filedock->refresh(core);
}

void MainWindow::on_action_OpenImg_triggered()
{
    core->AddFile();
     m_filedock->refresh(core);
}

void MainWindow::on_action_setProductFloder_triggered()
{
    core->setProductFloder();
}

void MainWindow::on_action_openFloder_triggered()
{
    core->AddPFloder();
     m_filedock->refresh(core);
}

void MainWindow::on_action_SaveWorkSpace_triggered()
{
    core->SaveWorkSpace();
     m_filedock->refresh(core);
}

void MainWindow::on_action_LoadWorkSpace_triggered()
{
    core->LoadWorkSpace();
     m_filedock->refresh(core);
}

void MainWindow::on_action_FileDlg_triggered(bool checked)
{
    switch(checked)
    {
        case true:
           m_filedock->show();
           break;
        case false:
           m_filedock->hide();
           break;
    }
}

void MainWindow::on_action_InfoDlg_triggered(bool checked)
{
    switch(checked)
    {
        case true:
           m_infodock->show();
           break;
        case false:
           m_infodock->hide();
           break;
    }
}

void MainWindow::on_action_LDlg_triggered(bool checked)
{
    switch(checked)
    {
        case true:
           m_limgviewer->show();
           break;
        case false:
           m_limgviewer->hide();
           break;
    }
}

void MainWindow::on_action_RDlg_triggered(bool checked)
{
    switch(checked)
    {
        case true:
           m_rimgviewer->show();
           break;
        case false:
           m_rimgviewer->hide();
           break;
    }
}

void MainWindow::on_action_PDlg_triggered(bool checked)
{
    switch(checked)
    {
        case true:
           m_pimgviewer->show();
           break;
        case false:
           m_pimgviewer->hide();
           break;
    }
}

void MainWindow::on_action_getCloud_triggered()
{
    core->getTerrianCloud();
}

void MainWindow::on_action_Calib_triggered()
{
    createCalibDlg();
}

void MainWindow::createCalibDlg()//创建标定对话框
{
    calibdlg=new QDialog(this);
    calibdlg->setWindowTitle("设置标定参数");

    calib_x=new QLabel("X方向标定点个数");
    calib_y=new QLabel("Y方向标定点个数");
    calib_Lx=new QLineEdit("0");
    calib_Ly=new QLineEdit("0");
    calib_OK=new QPushButton("OK");
    calib_Cancel=new QPushButton("Cancel");

    vbox=new QVBoxLayout;\
    buttonbox=new QHBoxLayout;

    buttonbox->addWidget(calib_OK);
    buttonbox->addWidget(calib_Cancel);

    vbox->addWidget(calib_x);
    vbox->addWidget(calib_Lx);
    vbox->addWidget(calib_y);
    vbox->addWidget(calib_Ly);
    vbox->addLayout(buttonbox);

    calibdlg->setLayout(vbox);

    connect(calib_OK,SIGNAL(clicked(bool)),calibdlg,SLOT(accept()));
    connect(calib_Cancel,SIGNAL(clicked(bool)),calibdlg,SLOT(reject()));
    connect(calibdlg,SIGNAL(accepted()),this,SLOT(CalibDlgAccepted()));

    calibdlg->show();
}

void MainWindow::CalibDlgAccepted()
{
    int nx;
    int ny;
    nx=calib_Lx->text().toInt();
    ny=calib_Ly->text().toInt();

    core->cameraCalibration(nx,ny);

}

void MainWindow::on_action_SwitchAdd_triggered(bool checked)
{
    qDebug()<<checked;
    m_pimgviewer->isAdded=checked;
}
