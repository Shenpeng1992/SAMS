//如果使用VS编译器，需要将代码强制转换为UTF-8,并将文件保存为UTF-8编码，才能正确显示中文
#if defined(_MSC_VER)&&(_MSC_VER>=1600)
#pragma execution_character_set("utf-8")
#endif

#include "SAMCore.h"

#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QImage>

SAMCore::SAMCore()
{
    ////@系统log
//    QFile file("./SystemLog.log");
    file.setFileName("./SystemLog.log");
    file.open(QIODevice::WriteOnly | QIODevice::Truncate );

    QString LOG;
    LOG.append(QDateTime::currentDateTime().toString("yyyy.MM.dd;hh:mm:ss"));
    LOG.append("\t");LOG.append("Initialize Core");
    writeLog(LOG);

    unLoadAll();
    workFloder="./WorkSpace";
    productFloder=workFloder+"/ProductImg";
}

QStringList* SAMCore::getNameListL()
{
    return &NameListL;
}

QStringList* SAMCore::getNameListR()
{
    return &NameListR;
}

QStringList* SAMCore::getProductList()
{
    return &ProductList;
}

QString* SAMCore::getWorkFloder()
{
    return &workFloder;
}

QString* SAMCore::getProductFloder()
{
    return &productFloder;
}

QString* SAMCore::getCurrentL()
{
    return currentL;
}

QString* SAMCore::getCurrentR()
{
    return currentR;
}

QString* SAMCore::getCurrentProduct()
{
    return currentProduct;
}

void SAMCore::setNameListL(QStringList a)
{
    NameListL=a;
}

void SAMCore::setNameListR(QStringList a)
{
    NameListR=a;
}

void SAMCore::setProductList(QStringList a)
{
    ProductList=a;
}

void SAMCore::setWorkFloder()
{
    QString temp=QFileDialog::getExistingDirectory(0,"设置工作路径",workFloder,QFileDialog::ShowDirsOnly
                                      | QFileDialog::DontResolveSymlinks);
    if(!temp.isEmpty())
        workFloder=temp;

    //创建LRP文件夹
    QDir *dir = new QDir;
    bool exist = dir->exists(workFloder);
    if(!exist)  dir->mkdir(workFloder);
    exist = dir->exists(workFloder+"/LeftImg");
    if(!exist)  dir->mkdir(workFloder+"/LeftImg");
    exist = dir->exists(workFloder+"/RightImg");
    if(!exist)  dir->mkdir(workFloder+"/RightImg");
    exist = dir->exists(workFloder+"/ProductImg");
    if(!exist)  dir->mkdir(workFloder+"/ProductImg");

    productFloder=workFloder+"/ProductImg";
}

void SAMCore::setProductFloder()
{
    QString temp=QFileDialog::getExistingDirectory(0,"设置产品路径",productFloder,QFileDialog::ShowDirsOnly
                                      | QFileDialog::DontResolveSymlinks);
    if(!temp.isEmpty())
        productFloder=temp;

    //创建LRP文件夹
    QDir *dir = new QDir;
    bool exist = dir->exists(productFloder);
    if(!exist)  dir->mkdir(productFloder);
}

void SAMCore::setCurrentL(int a)
{
    if(a<0||a>=NameListL.size())    return;
    currentL=&NameListL[a];
}

void SAMCore::setCurrentR(int a)
{
    if(a<0||a>=NameListR.size())    return;
    currentR=&NameListR[a];
}

void SAMCore::setCurrentProduct(int a)
{
    if(a<0||a>=ProductList.size())    return;
    currentProduct=&ProductList[a];
}

void SAMCore::AddFile()//打开文件
{
    QStringList filenamelist;
    filenamelist=QFileDialog::getOpenFileNames(NULL,"打开产品",productFloder,"其他文件 (*.*);;JPG (*.jpg *.JPG);;PNG (*.png *.PNG);;BMP (*.bmp *.BMP);;点云文件 (*.pcs)");

    if(filenamelist.isEmpty())
        return;

    QStringList::Iterator it = filenamelist.begin(),itend = filenamelist.end();
    for(int i=0;it!=itend;i++,it++)
    {
        ProductList.append(filenamelist.at(i));
    }
}

void SAMCore::AddLImg()//打开单片
{
    QStringList filenamelist;
    filenamelist=QFileDialog::getOpenFileNames(NULL,"打开左片",workFloder+"/LeftImg","其他文件 (*.*);;JPG (*.jpg *.JPG);;PNG (*.png *.PNG);;BMP (*.bmp *.BMP)");

    if(filenamelist.isEmpty())
        return;

    QStringList::Iterator it = filenamelist.begin(),itend = filenamelist.end();
    for(int i=0;it!=itend;i++,it++)
    {
        NameListL.append(filenamelist.at(i));
    }
}

void SAMCore::AddRImg()
{
    QStringList filenamelist;
    filenamelist=QFileDialog::getOpenFileNames(NULL,"打开右片",workFloder+"/RightImg","其他文件 (*.*);;JPG (*.jpg *.JPG);;PNG (*.png *.PNG);;BMP (*.bmp *.BMP)");

    if(filenamelist.isEmpty())
        return;

    QStringList::Iterator it = filenamelist.begin(),itend = filenamelist.end();
    for(int i=0;it!=itend;i++,it++)
    {
        NameListR.append(filenamelist.at(i));
    }
}

void SAMCore::AddLFloder()//打开文件夹
{
    QString temp=QFileDialog::getExistingDirectory(0,"获取左片路径",workFloder,QFileDialog::ShowDirsOnly
                                      | QFileDialog::DontResolveSymlinks);
    if(temp.isEmpty())
        return;

    //遍历文件夹并过滤出图像
    QDir *dir = new QDir(temp);

    QStringList filters;
    filters<<"*.jpg"<<"*.png"<<"*.bmp"<<"*.JPG"<<"*.PNG"<<"*.BMP";
    dir->setNameFilters(filters);
    QFileInfoList filist=dir->entryInfoList();

    //入队列
    for(int i=0;i<filist.size();i++)
    NameListL.append(filist.at(i).absoluteFilePath());
}

void SAMCore::AddRFloder()
{
    QString temp=QFileDialog::getExistingDirectory(0,"获取右片路径",workFloder,QFileDialog::ShowDirsOnly
                                      | QFileDialog::DontResolveSymlinks);
    if(temp.isEmpty())
        return;

    //遍历文件夹并过滤出图像
    QDir *dir = new QDir(temp);

    QStringList filters;
    filters<<"*.jpg"<<"*.png"<<"*.bmp"<<"*.JPG"<<"*.PNG"<<"*.BMP";
    dir->setNameFilters(filters);
    QFileInfoList filist=dir->entryInfoList();

    //入队列
    for(int i=0;i<filist.size();i++)
    NameListR.append(filist.at(i).absoluteFilePath());
}

void SAMCore::AddPFloder()
{
    QString temp=QFileDialog::getExistingDirectory(0,"获取路径",productFloder,QFileDialog::ShowDirsOnly
                                      | QFileDialog::DontResolveSymlinks);
    if(temp.isEmpty())
        return;

    //遍历文件夹并过滤出图像
    QDir *dir = new QDir(temp);

    QStringList filters;
    filters<<"*.jpg"<<"*.png"<<"*.bmp"<<"*.JPG"<<"*.PNG"<<"*.BMP";
    dir->setNameFilters(filters);
    QFileInfoList filist=dir->entryInfoList();

    //入队列
    for(int i=0;i<filist.size();i++)
    ProductList.append(filist.at(i).absoluteFilePath());
}


void SAMCore::unloadL()//取消目录
{
    NameListL.clear();

    QString LOG;
    LOG=QDateTime::currentDateTime().toString("yyyy.MM.dd;hh:mm:ss")+"\t"+"UnLoad LeftList";

    writeLog(LOG);
    qDebug()<<LOG;
}

void SAMCore::unloadR()
{
    NameListR.clear();

    QString LOG;
    LOG=QDateTime::currentDateTime().toString("yyyy.MM.dd;hh:mm:ss")+"\t"+"UnLoad RightList";

    writeLog(LOG);
    qDebug()<<LOG;
}

void SAMCore::unloadP()
{
    ProductList.clear();

    QString LOG;
    LOG=QDateTime::currentDateTime().toString("yyyy.MM.dd;hh:mm:ss")+"\t"+"UnLoad ProductList";

    writeLog(LOG);
    qDebug()<<LOG;
}

void SAMCore::unLoadAll()
{
    NameListL.clear();
    NameListR.clear();
    ProductList.clear();
}

void SAMCore::LoadWorkSpace()//加载工作区
{
    QString temp=QFileDialog::getOpenFileName(0,"选择打开工作区",workFloder,"SAM (*.sam)");

    if(temp.isEmpty())  return;

    QFile file(temp);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    int flag=0;

    //读取两个目录
    workFloder=file.readLine();
    productFloder=file.readLine();
    workFloder=workFloder.trimmed();
    productFloder=productFloder.trimmed();
    QString line=file.readLine();

    unLoadAll();

    //读取文件
    while(!line.isEmpty())
    {
        if(line=="L\n"||line=="R\n"||line=="P\n")
            {flag++;    line=file.readLine();       continue;}

        switch(flag)
        {
        case 1:
            NameListL.append(line.trimmed());break;
        case 2:
            NameListR.append(line.trimmed());break;
        case 3:
            ProductList.append(line.trimmed());break;
        }

        line=file.readLine();
    }

    QString LOG;

    LOG=QDateTime::currentDateTime().toString("yyyy.MM.dd;hh:mm:ss")+"\t"+"Load Workspace";
    writeLog(LOG);
}

void SAMCore::SaveWorkSpace()
{
    QString temp=QFileDialog::getSaveFileName(0,"选择储存工作区",workFloder,"SAM (*.sam)");

    if(temp.isEmpty())  return;

    QFile file(temp);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    //写入两个目录
    QTextStream out(&file);
    if(!workFloder.endsWith("\n")) {
        out<<workFloder<<endl;
    }else
    out<<workFloder ;


    if(!productFloder.endsWith("\n")) {
        out<<productFloder<<endl;
    }else
    out<<productFloder ;

    //写入文件串
    out<<"L"<<"\n" ;
    for(int i=0;i<NameListL.size();i++)
    {
        if(!NameListL.at(i).endsWith("\n")) {
            out<<NameListL.at(i)<<endl;
        }else
        out<<NameListL.at(i) ;
    }
    out<<"R"<<"\n";
    for(int i=0;i<NameListR.size();i++)
    {
        if(!NameListR.at(i).endsWith("\n")) {
            out<<NameListR.at(i)<<endl;
        }else
        out<<NameListR.at(i) ;
    }
    out<<"P"<<"\n";
    for(int i=0;i<ProductList.size();i++)
    {
        if(!ProductList.at(i).endsWith("\n")) {
            out<<ProductList.at(i)<<endl;
        }else
        out<<ProductList.at(i) ;
    }

    file.close();
}

void SAMCore::AddLLine(int a)//插入行
{
    if(a<0||a>NameListL.size()) return;
    NameListL.insert(a,"未定义文件");
}

void SAMCore::AddRLine(int a)//插入行
{
    if(a<0||a>NameListR.size()) return;
    NameListR.insert(a,"未定义文件");
}

void SAMCore::AddLRLine(int a)//插入行
{
    if(a<0||a>NameListL.size()) return;
    else NameListL.insert(a,"未定义文件");

    if(a<0||a>NameListR.size()) return;
    else NameListR.insert(a,"未定义文件");
}

void SAMCore::AddPLine(int a)//插入行
{
    if(a<0||a>ProductList.size()) return;
    ProductList.insert(a,"未定义文件");
}

void SAMCore::delLLine(int a)//删除行
{
    if(a<0||a>=NameListL.size()) return;
    NameListL.removeAt(a);
}

void SAMCore::delRLine(int a)//删除行
{
    if(a<0||a>=NameListR.size()) return;
    NameListR.removeAt(a);
}

void SAMCore::delLRLine(int a)//删除行
{
    if(a<0||a>=NameListL.size()) return;
    else NameListL.removeAt(a);

    if(a<0||a>=NameListR.size()) return;
    else NameListR.removeAt(a);
}

void SAMCore::delPLine(int a)//删除行
{
    if(a<0||a>=ProductList.size()) return;
    ProductList.removeAt(a);
}

void SAMCore::upLLine(int a)//上调
{
    if(a<1||a>NameListL.size()) return;
    NameListL.swap(a,a-1);
}

void SAMCore::upRLine(int a)//上调
{
    if(a<1||a>NameListR.size()) return;
    NameListR.swap(a,a-1);
}

void SAMCore::upLRLine(int a)//上调
{
    if(a<1||a>=NameListL.size()) return;
    else NameListL.swap(a,a-1);

    if(a<1||a>=NameListR.size()) return;
    else NameListR.swap(a,a-1);
}

void SAMCore::upPLine(int a)//上调
{
    if(a<1||a>ProductList.size()) return;
    ProductList.swap(a,a-1);
}
void SAMCore::downLLine(int a)//下调
{
    if(a<0||a>=NameListL.size()-1) return;
    NameListL.swap(a,a+1);
}

void SAMCore::downRLine(int a)//下调
{
    if(a<0||a>=NameListR.size()-1) return;
    NameListR.swap(a,a+1);
}

void SAMCore::downLRLine(int a)//下调
{
    if(a<0||a>=NameListL.size()-1) return;
    NameListL.swap(a,a+1);

    if(a<0||a>=NameListR.size()-1) return;
    NameListR.swap(a,a+1);
}

void SAMCore::downPLine(int a)//上调
{
    if(a<0||a>=ProductList.size()-1) return;
    ProductList.swap(a,a+1);
}

void SAMCore::changeLRPath(int c,int r)//改变路径
{
    //判断是否在队列范围内
    if(c<0||c>=2)  return;
    switch(c)
    {
    case 0:
        if(r>=0||r<NameListL.size())
        {
            QString filename;
            filename=QFileDialog::getOpenFileName(NULL,"打开产品",productFloder,"其他文件 (*.*);;JPG (*.jpg *.JPG);;PNG (*.png *.PNG);;BMP (*.bmp *.BMP)");

            if(filename.isEmpty())
                return;

            NameListL.replace(r,filename);
        }
        break;
    case 1:
        if(r>=0||r<NameListR.size())
        {
            QString filename;
            filename=QFileDialog::getOpenFileName(NULL,"打开产品",productFloder,"其他文件 (*.*);;JPG (*.jpg *.JPG);;PNG (*.png *.PNG);;BMP (*.bmp *.BMP)");

            if(filename.isEmpty())
                return;

            NameListR.replace(r,filename);
        }
        break;
    }
}

void SAMCore::changePPath(int r)
{
    //判断是否在队列范围内
    if(r<0||r>=ProductList.size())  return;

    //打开文件
    QString filename;
    filename=QFileDialog::getOpenFileName(NULL,"打开产品",productFloder,"其他文件 (*.*);;JPG (*.jpg *.JPG);;PNG (*.png *.PNG);;BMP (*.bmp *.BMP)");

    if(filename.isEmpty())
        return;

    ProductList.replace(r,filename);
}

void SAMCore::writeLog(QString a)
{
    QTextStream log;
    log.setDevice(&file);

    log<<a<<endl;
    qDebug()<<a;
    emit writeLog();
}

void SAMCore::getTerrianCloud()//获取地形点云
{
    ////S1 写Log
    QString LOG;
    LOG=QDateTime::currentDateTime().toString("yyyy.MM.dd;hh:mm:ss")+"\t"+"Start processing stero-images";
    writeLog(LOG);

    qDebug()<<"Main thread:" <<QThread::currentThreadId();

    createTerrianThread();
    createProcessDlg();

    emit getTerrianCloudSignals();
}

void SAMCore::createTerrianThread()
{
    m_subThread = new SAMTerrianThread(NameListL,NameListR,productFloder);

    sub_thread=new QThread;
    m_subThread->moveToThread(sub_thread);

    connect(this,SIGNAL(getTerrianCloudSignals()),m_subThread,SLOT(getTerrianCloud()));
    sub_thread->start();
}

void SAMCore::cameraCalibration(int nx, int ny)    ////@相机定标
{
    if(NameListL.size()!=NameListR.size())  return;
    if(NameListL.size()==0) return;

    ////@S1 写出LOG
    QString LOG;
    LOG=LOG+QDateTime::currentDateTime().toString("yyyy.MM.dd;hh:mm:ss")+"\t"+"Camera Calibration";
    writeLog(LOG);

    ////@S2 定义变量
    int i, j, lr, nframes, n = nx*ny , N = 0;
    int useUncalibrated=1;

//    int displayCorners = 0;
    int showUndistorted = 1;
    bool isVerticalStereo = false;
    const int maxScale = 1;
    const float squareSize = 30.f;//设置成真实孔径

    vector<string> imageNames[2];
    vector<CvPoint3D32f> objectPoints;
    vector<CvPoint2D32f> points[2];
    vector<int> npoints;
    vector<uchar> active[2];
    vector<CvPoint2D32f> temp(n);
    CvSize imageSize = { 0, 0 };


    //向量和矩阵
    double M1[3][3], M2[3][3], D1[5], D2[5];
    double R[3][3], T[3], E[3][3], F[3][3];
    CvMat _M1 = cvMat(3, 3, CV_64F, M1);
    CvMat _M2 = cvMat(3, 3, CV_64F, M2);
    CvMat _D1 = cvMat(1, 5, CV_64F, D1);
    CvMat _D2 = cvMat(1, 5, CV_64F, D2);
    CvMat _R = cvMat(3, 3, CV_64F, R);
    CvMat _T = cvMat(3, 1, CV_64F, T);
    CvMat _E = cvMat(3, 3, CV_64F, E);
    CvMat _F = cvMat(3, 3, CV_64F, F);

    ////@S3 标定板亚像素坐标的读取
    //读标定板
    for (i = 0;i<NameListL.size()*2;i++)
    {
        //获取文件名加载图像
        int count = 0, result = 0;
        lr = i % 2;
        vector<CvPoint2D32f>& pts = points[lr];

        QString name;
        if(lr==0){
            name=NameListL.at(i/2).trimmed();
        }else{
            name=NameListR.at(i/2).trimmed();
        }

        IplImage *img = cvLoadImage(name.toStdString().c_str(), 0);
        if (!img)
            break;
        imageSize = cvGetSize(img);
        //////////////////////////////////////////////////////////////////////////
        ////@S4 提取角点
        for (int s = 1; s <= maxScale; s++)
        {
            IplImage *timg = img;
            if (s > 1)
            {
                timg = cvCreateImage(cvSize(img->width*s, img->height*s), img->depth, img->nChannels);
                cvResize(img, timg, CV_INTER_CUBIC);
            }
            result = cvFindChessboardCorners(timg, cvSize(nx, ny), &temp[0], &count, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_NORMALIZE_IMAGE);
            if (timg != img)
                cvReleaseImage(&timg);
            if (result || s == maxScale)
            for (j = 0; j < count; j++)
            {
                temp[j].x /= s;
                temp[j].y /= s;
            }
            if (result)
                break;
        }
        //////////////////////////////////////////////////////////////////////////
        N = pts.size();
        pts.resize(N + n, cvPoint2D32f(0, 0));
        active[lr].push_back((uchar)result);
        //////////////////////////////////////////////////////////////////////////
        //精确到亚像素级
        if (result)
        {
            cvFindCornerSubPix(img, &temp[0], count, cvSize(11, 11), cvSize(-1, -1), cvTermCriteria(CV_TERMCRIT_ITER + CV_TERMCRIT_EPS, 30, 0.01));
            copy(temp.begin(), temp.end(), pts.begin() + N);
        }
        cvReleaseImage(&img);
    }

    //////////////////////////////////////////////////////////////////////////
    ////@S5 获得三维定标板像点
    nframes = active[0].size();//优质棋盘角点数量
    objectPoints.resize(nframes*n);
    for (i = 0; i < ny;i++)
    for (j = 0; j < nx; j++)
        objectPoints[i*nx + j] = cvPoint3D32f(i*squareSize, j*squareSize, 0);
    for (i = 1; i < nframes; i++)
        copy(objectPoints.begin(), objectPoints.begin() + n, objectPoints.begin() + i*n);
    npoints.resize(nframes, n);

    N = nframes*n;
    CvMat _objectPoints = cvMat(1, N, CV_32FC3, &objectPoints[0]);
    CvMat _imagePoints1 = cvMat(1, N, CV_32FC2, &points[0][0]);
    CvMat _imagePoints2 = cvMat(1, N, CV_32FC2, &points[1][0]);
    CvMat _npoints = cvMat(1, npoints.size(), CV_32S, &npoints[0]);
    cvSetIdentity(&_M1);
    cvSetIdentity(&_M2);
    cvZero(&_D1);
    cvZero(&_D2);

    ////@S6 标定立体相机
    fflush(stdout);
    cvStereoCalibrate(&_objectPoints, &_imagePoints1, &_imagePoints2,
        &_npoints, &_M1, &_D1, &_M2, &_D2,
        imageSize, &_R, &_T, &_E, &_F,
        cvTermCriteria(CV_TERMCRIT_ITER + CV_TERMCRIT_EPS, 100, 1e-5),
        CV_CALIB_FIX_ASPECT_RATIO + CV_CALIB_ZERO_TANGENT_DIST + CV_CALIB_SAME_FOCAL_LENGTH);

    ////@S7 输出矩阵文件
    QString outputpath;
    outputpath=productFloder+"/CalibParas/"+"_M1";
    CDataStyle::cvx_saveMat(&_M1, outputpath.toStdString().data());

    outputpath=productFloder+"/CalibParas/"+"_M2";
    CDataStyle::cvx_saveMat(&_M2, outputpath.toStdString().data());

    outputpath=productFloder+"/CalibParas/"+"_D1";
    CDataStyle::cvx_saveMat(&_D1, outputpath.toStdString().data());

    outputpath=productFloder+"/CalibParas/"+"_D2";
    CDataStyle::cvx_saveMat(&_D2, outputpath.toStdString().data());

    outputpath=productFloder+"/CalibParas/"+"_R";
    CDataStyle::cvx_saveMat(&_R, outputpath.toStdString().data());

    outputpath=productFloder+"/CalibParas/"+"_T";
    CDataStyle::cvx_saveMat(&_T, outputpath.toStdString().data());

    outputpath=productFloder+"/CalibParas/"+"_E";
    CDataStyle::cvx_saveMat(&_E, outputpath.toStdString().data());

    outputpath=productFloder+"/CalibParas/"+"_F";
    CDataStyle::cvx_saveMat(&_F, outputpath.toStdString().data());
    ////@S8 标定精度检测
    vector<CvPoint3D32f> lines[2];
    points[0].resize(N);
    points[1].resize(N);
    _imagePoints1 = cvMat(1, N, CV_32FC2, &points[0][0]);
    _imagePoints2 = cvMat(1, N, CV_32FC2, &points[1][0]);
    lines[0].resize(N);
    lines[1].resize(N);
    CvMat _L1 = cvMat(1, N, CV_32FC3, &lines[0][0]);
    CvMat _L2 = cvMat(1, N, CV_32FC3, &lines[1][0]);
    ////@S9 使用标定后的像点
    cvUndistortPoints(&_imagePoints1, &_imagePoints1, &_M1, &_D1, 0, &_M1);
    cvUndistortPoints(&_imagePoints2, &_imagePoints2, &_M2, &_D2, 0, &_M2);
    cvComputeCorrespondEpilines(&_imagePoints1, 1, &_F, &_L1);
    cvComputeCorrespondEpilines(&_imagePoints2, 2, &_F, &_L2);
    double avgErr = 0;
    for (i = 0; i < N; i++)
    {
        double err = fabs(points[0][i].x*lines[1][i].x + points[0][i].y*lines[1][i].y + lines[1][i].z)
                    +fabs(points[1][i].x*lines[0][i].x + points[1][i].y*lines[0][i].y + lines[0][i].z);
        avgErr += err;
    }

    //////////////////////////////////////////////////////////////////////////
    ////S10 计算并显示映射
    if (showUndistorted)
    {
        CvMat *mx1 = cvCreateMat(imageSize.height, imageSize.width, CV_32F);
        CvMat *my1 = cvCreateMat(imageSize.height, imageSize.width, CV_32F);
        CvMat *mx2 = cvCreateMat(imageSize.height, imageSize.width, CV_32F);
        CvMat *my2 = cvCreateMat(imageSize.height, imageSize.width, CV_32F);
        CvMat *img1r = cvCreateMat(imageSize.height, imageSize.width, CV_8U);
        CvMat *img2r = cvCreateMat(imageSize.height, imageSize.width, CV_8U);
        CvMat *disp = cvCreateMat(imageSize.height, imageSize.width, CV_16S);
        CvMat *vdisp = cvCreateMat(imageSize.height, imageSize.width, CV_8U);

        CvMat *left_disp = cvCreateMat(imageSize.height, imageSize.width, CV_16S);
        CvMat *right_disp = cvCreateMat(imageSize.height, imageSize.width, CV_16S);

        CvMat *pair;
        double R1[3][3], R2[3][3], P1[3][4], P2[3][4];
        CvMat _R1 = cvMat(3, 3, CV_64F, R1);
        CvMat _R2 = cvMat(3, 3, CV_64F, R2);
        if (useUncalibrated == 0)
            assert(0);
        else if (useUncalibrated == 1 || useUncalibrated == 2)
        {
            double H1[3][3], H2[3][3], iM[3][3];
            CvMat _H1 = cvMat(3, 3, CV_64F, H1);
            CvMat _H2 = cvMat(3, 3, CV_64F, H2);
            CvMat _iM = cvMat(3, 3, CV_64F, iM);
            if (useUncalibrated == 2)
                cvFindFundamentalMat(&_imagePoints1, &_imagePoints2, &_F);
            cvStereoRectifyUncalibrated(&_imagePoints1, &_imagePoints2, &_F, imageSize, &_H1, &_H2, 3);
            cvInvert(&_M1, &_iM);
            cvMatMul(&_H1, &_M1, &_R1);
            cvMatMul(&_iM, &_R1, &_R1);
            cvInvert(&_M2, &_iM);
            cvMatMul(&_H2, &_M2, &_R2);
            cvMatMul(&_iM, &_R2, &_R2);
            //为cvRemap函数预计算大小
            cvInitUndistortRectifyMap(&_M1, &_D1, &_R1, &_M1, mx1, my1);
            cvInitUndistortRectifyMap(&_M2, &_D1, &_R2, &_M2, mx2, my2);
        }
        else
            assert(0);
    }
}

void SAMCore::createProcessDlg()//获取地形点云
{
    progressdlg=new QDialog;
    labtext=new QLabel("地形点云进度");
    vbox=new QVBoxLayout;
    bar=new QProgressBar;
    OK= new QPushButton("OK");

    progressdlg->setWindowTitle("正在生成地形点云");

    vbox->removeWidget(bar);

    vbox->addWidget(labtext);
    vbox->addWidget(bar);

    bar->setRange(0,NameListL.size());

    connect(OK,SIGNAL(clicked(bool)),progressdlg,SLOT(accept()));
    connect(m_subThread,SIGNAL(FreshProgress(int)),bar,SLOT(setValue(int)));
    connect(m_subThread,SIGNAL(Finished()),this,SLOT(changeProcessDlg()));
    progressdlg->setLayout(vbox);
    progressdlg->show();
}

void SAMCore::changeProcessDlg()//获取地形点云
{
    vbox->removeWidget(bar);
    vbox->addWidget(OK);
}
