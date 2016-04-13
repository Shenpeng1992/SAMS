#include "SAMProductViewer.h"

#include <QFileInfo>
#include <QMessageBox>
#include <QDebug>

SAMProductViewer::SAMProductViewer(SAMCore *core)
{
    m_LoadMode = IsImg;
    viewer=new SAMImgViewer(core);
    localCore=core;

    m_glWidget=new glwiget;
//    glLayout->addWidget(m_glWidget);

    mainLayout=new QVBoxLayout;

    changeMode(m_LoadMode);

    connect(this,SIGNAL(modechanged(LoadMode)),this,SLOT(changeMode(LoadMode)));
}

void SAMProductViewer::changeMode(LoadMode Mode)
{
    mainLayout->addWidget(viewer);
    mainLayout->addWidget(m_glWidget);

    switch(Mode)
    {
        case IsImg:
            qDebug()<<"img";
            m_glWidget->hide();
            viewer->show();
            break;
        case IsDEM:
            qDebug()<<"pcs";
            viewer->hide();
            m_glWidget->show();
            break;
    }
    this->setLayout(mainLayout);
}

void SAMProductViewer::loadPoints( QString pointFilrPath )
{
    point_cloud.clear();

    QString LOG;
    LOG=QDateTime::currentDateTime().toString("yyyy.MM.dd;hh:mm:ss")+"\t"+"View Point Clouds "+pointFilrPath;

    localCore->writeLog(LOG);


    //////////////////////////////以二进制文件读取模型文件/////////////////////////////////////
    ifstream filein;
    filein.open( pointFilrPath.toStdString().c_str(), ios::in|ios_base::binary);
    if (!filein.is_open())
    {
        QMessageBox *box=new QMessageBox(QMessageBox::Warning,QStringLiteral("读取点云文件"),QStringLiteral("读取点云文件失败！"));
        box->exec();
        return;
    }
    int numofPoints;
    filein.read((char*)&numofPoints, sizeof(int));
    CDataStyle::points_xyz point;
    for (int i=0;i<numofPoints;i++)
    {
            filein.read((char*)&point.x, sizeof(double));
            filein.read((char*)&point.y, sizeof(double));
            filein.read((char*)&point.z, sizeof(double));
            point_cloud.push_back(point);
            all_point_cloud.push_back(point);
    }
    filein.close();

    vector<int> hist(10,0);
    int his_intdex = 0;

    double x_max = -9999999.0;
    double x_min = 9999999.0;
    double y_max = -9999999.0;
    double y_min = 9999999.0;
    double z_max = -9999999.0;
    double z_min = 9999999.0;

    for (int i = 0; i < numofPoints; i++)
    {
        x_max = x_max>point_cloud[i].x?x_max:point_cloud[i].x;
        x_min = x_min<point_cloud[i].x?x_min:point_cloud[i].x;
        y_max = y_max>point_cloud[i].y?y_max:point_cloud[i].y;
        y_min = y_min<point_cloud[i].y?y_min:point_cloud[i].y;
        z_max = z_max>point_cloud[i].z?z_max:point_cloud[i].z;
        z_min = z_min<point_cloud[i].z?z_min:point_cloud[i].z;
    }

    double intera_Z = (z_max - z_min+1)/10;
    for (int i = 0; i < numofPoints; i++)
    {
        his_intdex =  (int) ((point_cloud[i].z - z_min) /intera_Z);
        hist[his_intdex]++;
    }

    m_glWidget->point_num = all_point_cloud.size();
    m_glWidget->x_mean =( x_max + x_min )/2;
    m_glWidget->y_mean =( y_max + y_min )/2;
    m_glWidget->z_mean =( z_max + z_min )/2;
    m_glWidget->z_distens = z_max - z_min;
    m_glWidget->z_min = z_min;

    m_glWidget->GetPeakZ(hist,m_glWidget->PeakZ_min,m_glWidget->PeakZ_max,intera_Z);
    m_glWidget->points = &all_point_cloud;

    m_glWidget->Refresh();
}

void SAMProductViewer::loadProduct(QString string)
{
    QFileInfo fi(string);
    if(fi.completeSuffix()=="pcs")
    {
        m_LoadMode=IsDEM;
        loadPoints(string);
        emit modechanged(m_LoadMode);
        return;
    }
    if(fi.completeSuffix()=="bmp")
    {
        m_LoadMode=IsImg;
        viewer->openImg(string);
        emit modechanged(m_LoadMode);
        return;
    }
    if(fi.completeSuffix()=="png")
    {
        m_LoadMode=IsImg;
        viewer->openImg(string);
        emit modechanged(m_LoadMode);
        return;
    }
    if(fi.completeSuffix()=="jpg")
    {
        m_LoadMode=IsImg;
        viewer->openImg(string);
        emit modechanged(m_LoadMode);
        return;
    }
}
