#include "SAMTerrianThread.h"
#include "QDebug"
#include <QThread>
#include <QDir>
#include <QMessageBox>

SAMTerrianThread::SAMTerrianThread(QStringList LList, QStringList RList, QString floder)
{
    if(LList.size()==0||RList.size()==0)  return;
    else {NameListL=LList;NameListR=RList;}
    if(floder.isEmpty()) return;
    else productFloder=floder;
}

void SAMTerrianThread::surfMatch(Mat leftImage1, Mat leftImage2, QString leftFileName1, QString leftFileName2,QString rightFileName1, QString rightFileName2, QString imageAbsolutePath)
{
    //m_mutex.lock();
    //SURF匹配的结果
    std::vector<cv::DMatch> matches;
    std::vector<cv::KeyPoint> keypoints1, keypoints2;

    keypoints1.clear();
    keypoints2.clear();
    matches.clear();

    if (leftImage1.data == NULL || leftImage2.data == NULL)
    {
        //QMessageBox::information(this,QStringLiteral("提示"), QStringLiteral("左序列影像打开错误！"));
        return;
    }

    RobustMatcher rmatcher;
    rmatcher.setConfidenceLevel(0.99); // confidence level (probability)
    rmatcher.setMinDistanceToEpipolar(1);// min distance to epipolar
    rmatcher.setRatio(0.6);// max ratio between 1st and 2nd NN
    cv::Ptr<cv::FeatureDetector> pfd= new cv::SurfFeatureDetector(10.0);
    rmatcher.setFeatureDetector(pfd);

    cv::Mat fundemental= rmatcher.match(leftImage1,leftImage2,matches, keypoints1, keypoints2);

    //////////////////////////////以文本存储匹配点///////////////////////////////////////
    //      ofstream ofile;
    //      QFileInfo info(openDlg->m_ImagePathList.at(0));
    //      QString path = info.absolutePath();
    //      path.append("\\").append(leftFileName1).append(leftFileName2).append("_SURFMatch.txt");
    //      ofile.open(path.toStdString().c_str(), ios_base::out);
    //      ofile<<matches.size()<<endl;
    //
    //      for (int i = 0; i < matches.size(); i++)
    //      {
    //          int m = matches[i].queryIdx;//左
    //          int n = matches[i].trainIdx;//右
    //          ofile<<keypoints1[m].pt.x<<" "<<keypoints1[m].pt.y<<" ";
    //          ofile<<keypoints2[n].pt.x<<" "<<keypoints2[n].pt.y;
    //          ofile<<endl;
    //      }


    ////////////////////////////////提取SURF匹配对应的三维点（二进制）///////////////////////////////////
    QString Points3dPath1 = imageAbsolutePath;
    Points3dPath1.append("\\").append(leftFileName1).append(rightFileName1).append("_SGBM_3d.pcs");
    ifstream file1;
     file1.open(Points3dPath1.toStdString().c_str(), ios::in|ios::binary);
    if (file1.is_open() == false)
    {
        //QMessageBox::information(this, "Tpis", "Open Failed1!");
        return;
    }

    QString Points3dPath2 = imageAbsolutePath;
    Points3dPath2.append("\\").append(leftFileName2).append(rightFileName2).append("_SGBM_3d.pcs");
    ifstream file2;
    file2.open(Points3dPath1.toStdString().c_str(), ios::in|ios::binary);
    if (file2.is_open() == false)
    {
        //QMessageBox::information(this, "Tpis", "Open Failed2!");
        return;
    }
    int numOf3d1,numOf3d2;
    file1.read((char*)&numOf3d1, sizeof(int));
    file2.read((char*)&numOf3d2, sizeof(int));
    int numOfPoints = matches.size();
    CDataStyle::PointandGray * d1 = new CDataStyle::PointandGray[numOf3d1];
    CDataStyle::PointandGray * d2 = new CDataStyle::PointandGray[numOf3d2];

    for (int i = 0; i < numOf3d1; i++)
    {
        file1.read((char*)&d1[i].x, sizeof(double));
        file1.read((char*)&d1[i].y, sizeof(double));
        file1.read((char*)&d1[i].z, sizeof(double));
    }
    for (int i = 0; i < numOf3d2; i++)
    {
        file2.read((char*)&d2[i].x, sizeof(double));
        file2.read((char*)&d2[i].y, sizeof(double));
        file2.read((char*)&d2[i].z, sizeof(double));
    }

    //////////////////////////////////提取SURF匹配对应的三维点（文本格式）///////////////////////////////////
    //QString Points3dPath1 = m_ImageAbosolutePath;
    //Points3dPath1.append("\\").append(m_FirstLeftImageName).append(m_FirstRightImageName).append("_SGBM_3d.txt");
    //ifstream file1;
    //file1.open(Points3dPath1.toStdString().c_str(), ios::in);
    //if (file1 == NULL)
    //{
    //    QMessageBox::information(this, "Tpis", "Open Failed1!");
    //    return;
    //}

    //QString Points3dPath2 = m_ImageAbosolutePath;
    //Points3dPath2.append("\\").append(m_SecondLeftImageName).append(m_SecondRightImageName).append("_SGBM_3d.txt");
    //ifstream file2;
    //file2.open(Points3dPath1.toStdString().c_str(), ios::in);
    //if (file2== NULL)
    //{
    //    QMessageBox::information(this, "Tpis", "Open Failed2!");
    //    return;
    //}

    //int numOf3d1,numOf3d2;
    //file1>>numOf3d1;
    //file2>>numOf3d2;
    //int numOfPoints = matches.size();
    //PointandGray * d1 = new PointandGray[numOf3d1];
    //PointandGray * d2 = new PointandGray[numOf3d2];
    //for (int i = 0; i < numOf3d1; i++)
    //{
    //    file1>>d1[i].x>>d1[i].y>>d1[i].z;
    //}
    //for (int i = 0; i < numOf3d2; i++)
    //{
    //    file2>>d2[i].x>>d2[i].y>>d2[i].z;
    //}
    //file1.close();
    //file2.close();

    int MatchPoints[4] = {0};
    std::vector<CDataStyle::RealMacthPoints> realPoints;
    CDataStyle::RealMacthPoints tempMatchPoint;
    QList<CDataStyle::PointandGray> list1;
    QList<CDataStyle::PointandGray> list2;
    QList<CDataStyle::PointandGray> newlist1;
    QList<CDataStyle::PointandGray> newlist2;
    for (int i = 0; i < numOfPoints; i++)
    {
        int m = matches[i].queryIdx;//左
        int n = matches[i].trainIdx;//右

        MatchPoints[0] = (int)(keypoints1[m].pt.x + 0.5f);
        MatchPoints[1] = (int)(keypoints1[m].pt.y + 0.5f);
        MatchPoints[2] = (int)(keypoints2[n].pt.x + 0.5f);
        MatchPoints[3] = (int)(keypoints2[n].pt.y + 0.5f);

        if (MatchPoints[0] <= 64 || MatchPoints[2] <= 64)
        {
            continue;
        }
        else
        {
            tempMatchPoint.x1 = MatchPoints[0];
            tempMatchPoint.y1 = MatchPoints[1];
            tempMatchPoint.x2 = MatchPoints[2];
            tempMatchPoint.y2 = MatchPoints[3];
            realPoints.push_back(tempMatchPoint);
        }
    }

    for (int i = 0; i < realPoints.size(); i++)
    {
        MatchPoints[0] = realPoints[i].x1;
        MatchPoints[1] = realPoints[i].y1;
        MatchPoints[2] = realPoints[i].x2;
        MatchPoints[3] = realPoints[i].y2;

        for (int j = 0; j < numOf3d1; j++)
        {
            if (MatchPoints[0] == (int)d1[j].x && MatchPoints[1] == (int)d1[j].y)
            {
                list1.append(d1[j]);
                break;
            }
        }

        for (int j = 0; j < numOf3d2; j++)
        {
            if (MatchPoints[2] == (int)d2[j].x && MatchPoints[3] == (int)d2[j].y)
            {
                list2.append(d2[j]);
                break;
            }
        }
    }

    if (list2.size() != list1.size())
        return;

    for (int j = 0; j < list1.size(); j++)
    {
        ////高程差小于阈值，才算精确匹配的点
        if (abs(list1[j].z - list2[j].z) < 3.0 )
        {
            newlist1.append(list1[j]);
            newlist2.append(list2[j]);
        }
    }
    delete []d1;
    delete []d2;

    //////////////////////////////////相对定向/////////////////////////////////
    //将模型坐标与控制点坐标整合到一块
    CDataStyle::EDATA *m_edData;
    m_edData=new CDataStyle::EDATA[newlist1.size()];

    for (int i=0;i<newlist1.size();i++)
    {
        m_edData[i].X=newlist2[i].x;
        m_edData[i].Y=newlist2[i].y;
        m_edData[i].Z=newlist2[i].z;
        m_edData[i].Xtp=newlist1[i].x;
        m_edData[i].Ytp=newlist1[i].y;
        m_edData[i].Ztp=newlist1[i].z;
    }

    double *m_absolute7para = new double[7];
    for (int i=0;i<7;i++)
    {
        m_absolute7para[i]=0;
    }

    AbsoluteOrient(m_edData,newlist1.size(),NULL,0,m_absolute7para);

    double fai,w,k,lamda,DetX,DetY,DetZ;
    fai=m_absolute7para[0];
    w=m_absolute7para[1];
    k=m_absolute7para[2];
    lamda=m_absolute7para[3];
    DetX=m_absolute7para[4];
    DetY=m_absolute7para[5];
    DetZ=m_absolute7para[6];


    ////导出绝对定向参数,二进制
    QString path3 = imageAbsolutePath;
    path3.append("\\").append(leftFileName1).append(leftFileName2).append("_absolute7para.txt");
    ofstream fileout;
    fileout.open(path3.toStdString().c_str(), ios::out|ios::binary);
    fileout.write((char*)&fai, sizeof(double));
    fileout.write((char*)&w, sizeof(double));
    fileout.write((char*)&k, sizeof(double));
    fileout.write((char*)&lamda, sizeof(double));
    fileout.write((char*)&DetX, sizeof(double));
    fileout.write((char*)&DetY, sizeof(double));
    fileout.write((char*)&DetZ, sizeof(double));
    fileout.close();

    ////导出绝对定向参数,以文本存储
    //     QString path3 = m_ImageAbosolutePath;
    //     path3.append("\\").append(m_FirstLeftImageName).append(m_SecondLeftImageName).append("_absolute7para.txt");
    //     FILE *fp_test=NULL;
    //     if((fp_test=fopen(path3.toStdString().c_str(),"w"))==NULL)
    //     {
    //         printf("\n Can't open this file!\n");
    //         exit(0);
    //     }
    //
    //     fprintf(fp_test,"%lf\n",fai);
    //     fprintf(fp_test,"%lf\n",w);
    //     fprintf(fp_test,"%lf\n",k);
    //     fprintf(fp_test,"%lf\n",lamda);
    //     fprintf(fp_test,"%lf\n",DetX);
    //     fprintf(fp_test,"%lf\n",DetY);
    //     fprintf(fp_test,"%lf\n",DetZ);
    //     fclose(fp_test);

    delete []m_absolute7para;
    //m_mutex.unlock();
}

void SAMTerrianThread::SGBMMatch(Mat leftImage, Mat rightImage, QString leftName, QString rightName, QString imageAbsolutePath)
{
    //m_mutex.lock();
    if (leftImage.data == NULL || rightImage.data == NULL)
    {
        //QMessageBox::information(this,QStringLiteral("提示"), QStringLiteral("请先打开左右序列影像！"));
        return;
    }

    cv::StereoSGBM sgbm;
    int SADWindowSize = 9;
    sgbm.preFilterCap = 63;
    sgbm.SADWindowSize = SADWindowSize > 0 ? SADWindowSize : 3;
    int cn = leftImage.channels();
    int numberOfDisparities=64;
    sgbm.P1 = 8*cn*sgbm.SADWindowSize*sgbm.SADWindowSize;
    sgbm.P2 = 32*cn*sgbm.SADWindowSize*sgbm.SADWindowSize;
    sgbm.minDisparity = 0;
    sgbm.numberOfDisparities = numberOfDisparities;
    sgbm.uniquenessRatio = 10;//10
    sgbm.speckleWindowSize = 100;
    sgbm.speckleRange = 32;
    sgbm.disp12MaxDiff = 1;
    Mat disp, disp8;
    try
    {
        //gzx,disp is CV_32F,the dll is recompiled in both Debug and Release mode
        sgbm(leftImage, rightImage , disp);
    }
    catch(cv::Exception &e)
    {
        const char* ree_msg = e.what();
        //QMessageBox::information(this, tr("tip"), tr(ree_msg));
    }

    disp.convertTo(disp8, CV_8U, 2*255/(numberOfDisparities*256.));
    imwrite("qq.png", disp8);
    QString path1 = imageAbsolutePath+"/"+leftName+rightName+"_SGBM_3d.pcs";

    int num = 0;
    for(int y = 0; y < disp.rows; y++)
    {
        for(int x = numberOfDisparities; x < disp.cols; x++)
        {
            float d = disp.at<float>(y, x);
            if (d <= 0.0 || (x-d/256.)<0)
            {
                continue;
            }
            num++;
        }
    }

    ////////////////////////////////以二进制文件存储///////////////////////////////////
    ofstream fileout;
    fileout.open( path1.toStdString().c_str(), ios_base::out|ios_base::binary);
    fileout.write((char*)(&num) ,sizeof(num));
    for(int y = 0; y < disp.rows; y++)
    {
        for(int x = numberOfDisparities; x < disp.cols; x++)
        {
            float d = disp.at<float>(y, x);
            if (d <= 0.0 || (x-d/(256.))<0)
            {
                continue;
            }
            double tempx=x*1.0;
            double tempy=y*1.0;
            double tempd=d/6.0;
            fileout.write((char*)(&tempx) ,sizeof(tempx));
            fileout.write((char*)(&tempy) ,sizeof(tempy));
            fileout.write((char*)(&tempd) ,sizeof(tempd));
        }
    }
    fileout.close();

    //////////////////////////////////以文本格式存储///////////////////////////////////
    //     ofstream ofile;
    //     ofile.open(path1.toStdString().c_str(), ios_base::out);
    //    ofile<<num<<endl;
    //     for(int y = 0; y < disp.rows; y++)
    //     {
    //         for(int x = numberOfDisparities; x < disp.cols; x++)
    //         {
    //             float d = disp.at<float>(y, x);
    //             if (d <= 0.0 || (x-d/(256.))<0)
    //             {
    //                 continue;
    //             }
    //             ofile<<x*1.0<<" "<<y*1.0<<" "<<d/6.0<<endl;//disp.rows-1-y
    //         }
    //     }
    //     ofile.close();
    //m_mutex.unlock();
}

void SAMTerrianThread::AbsoluteOrient(CDataStyle::EDATA *edData,int nNumE,CDataStyle::HDATA *hdData,int nNumH,double *Absolute7Para)
{

    double a[3],b[3],c[3];
    double X[7];
    int i;
    for (i=0;i<7;i++)
        X[i]=1;

    //定义绝对定向参数
    double fai,w,k,lamda,DetX,DetY,DetZ;
    double xg,yg,zg,xtg,ytg,ztg;

    xg=yg=zg=xtg=ytg=ztg=0;

    //重心化处理
    if(0)
    {
        for (i=0;i<nNumE;i++)
        {
            xg+=edData[i].X;
            yg+=edData[i].Y;
            zg+=edData[i].Z;
        }
        for(i=0;i<nNumH;i++)
        {
            xg+=hdData[i].X;
            yg+=hdData[i].Y;
            zg+=hdData[i].Z;
        }
        xg=xg/(nNumE+nNumH);
        yg=yg/(nNumE+nNumH);
        zg=zg/(nNumE+nNumH);

        for (i=0;i<nNumE;i++)
        {
            edData[i].X=edData[i].X-xg;
            edData[i].Y=edData[i].Y-yg;
            edData[i].Z=edData[i].Z-zg;
        }
        for (i=0;i<nNumH;i++)
        {
            hdData[i].X=hdData[i].X-xg;
            hdData[i].Y=hdData[i].Y-yg;
            hdData[i].Z=hdData[i].Z-zg;
        }

        for (i=0;i<nNumE;i++)
        {
            xtg+=edData[i].Xtp;
            ytg+=edData[i].Ytp;
            ztg+=edData[i].Ztp;
        }
        xtg=xtg/nNumE;
        ytg=ytg/nNumE;

        for (i=0;i<nNumH;i++)
            ztg+=hdData[i].Ztp;

        ztg=ztg/(nNumE+nNumH);

        for (i=0;i<nNumE;i++)
        {
            edData[i].Xtp=edData[i].Xtp-xtg;
            edData[i].Ytp=edData[i].Ytp-ytg;
            edData[i].Ztp=edData[i].Ztp-ztg;

        }

        for (i=0;i<nNumH;i++)
            hdData[i].Ztp=hdData[i].Ztp-ztg;

    }


    //定义绝对定向相关参数
    double *X1,*Y1,*Z1;
    X1=new double[nNumE+nNumH];
    Y1=new double[nNumE+nNumH];
    Z1=new double[nNumE+nNumH];


    double *A,*L,*AT,ATA[49],ATL[7];
    A=new double[7*(3*nNumE+nNumH)];
    AT=new double[7*(3*nNumE+nNumH)];
    L=new double[3*nNumE+nNumH];

    fai=w=k=0;
    DetX=DetY=DetZ=0;
    lamda=1;

    while(!(fabs(X[4])<0.000029&&fabs(X[5])<0.000029&&fabs(X[6])<0.000029))
    {

        a[0]=cos(fai)*cos(k)-sin(fai)*sin(w)*sin(k);
        a[1]=-cos(fai)*sin(k)-sin(fai)*sin(w)*cos(k);
        a[2]=-sin(fai)*cos(w);
        b[0]=cos(w)*sin(k);
        b[1]=cos(w)*cos(k);
        b[2]=-sin(w);
        c[0]=sin(fai)*cos(k)+cos(fai)*sin(w)*sin(k);
        c[1]=-sin(fai)*sin(k)+cos(fai)*sin(w)*cos(k);
        c[2]=cos(fai)*cos(w);

        for(i=0;i<nNumE;i++)
        {
            X1[i]=a[0]*edData[i].X+a[1]*edData[i].Y+a[2]*edData[i].Z;
            Y1[i]=b[0]*edData[i].X+b[1]*edData[i].Y+b[2]*edData[i].Z;
            Z1[i]=c[0]*edData[i].X+c[1]*edData[i].Y+c[2]*edData[i].Z;

            L[3*i]=edData[i].Xtp-DetX-lamda*X1[i];
            L[3*i+1]=edData[i].Ytp-DetY-lamda*Y1[i];
            L[3*i+2]=edData[i].Ztp-DetZ-lamda*Z1[i];

            A[i*21]=1;
            A[i*21+1]=A[i*21+2]=0;
            A[i*21+3]=X1[i];
            A[i*21+4]=-lamda*Z1[i];
            A[i*21+5]=-lamda*Y1[i]*sin(fai);
            A[i*21+6]=-lamda*Y1[i]*cos(fai)*cos(w)-lamda*Z1[i]*sin(w);

            A[i*21+7]=0;
            A[i*21+8]=1;
            A[i*21+9]=0;
            A[i*21+10]=Y1[i];
            A[i*21+11]=0;
            A[i*21+12]=lamda*X1[i]*sin(fai)-lamda*Z1[i]*cos(fai);
            A[i*21+13]=lamda*(X1[i]*cos(fai)*cos(w)+Z1[i]*sin(fai)*cos(w));

            A[i*21+14]=A[i*21+15]=0;
            A[i*21+16]=1;
            A[i*21+17]=Z1[i];
            A[i*21+18]=lamda*X1[i];
            A[i*21+19]=lamda*Y1[i]*cos(fai);
            A[i*21+20]=lamda*(X1[i]*sin(w)-Y1[i]*sin(fai)*cos(w));
        }

        for (;i<(nNumE+nNumH);i++)
        {
            X1[i]=a[0]*hdData[i-nNumE].X+a[1]*hdData[i-nNumE].Y+a[2]*hdData[i-nNumE].Z;
            Y1[i]=b[0]*hdData[i-nNumE].X+b[1]*hdData[i-nNumE].Y+b[2]*hdData[i-nNumE].Z;
            Z1[i]=c[0]*hdData[i-nNumE].X+c[1]*hdData[i-nNumE].Y+c[2]*hdData[i-nNumE].Z;

            L[3*nNumE+i-nNumE]=hdData[i-nNumE].Ztp-DetZ-lamda*Z1[i];

            A[(i-nNumE)*7+21*nNumE]=A[(i-nNumE)*7+21*nNumE+1]=0;
            A[(i-nNumE)*7+2+21*nNumE]=1;
            A[(i-nNumE)*7+3+21*nNumE]=Z1[i];
            A[(i-nNumE)*7+4+21*nNumE]=lamda*X1[i];
            A[(i-nNumE)*7+5+21*nNumE]=lamda*Y1[i]*cos(fai);
            A[(i-nNumE)*7+6+21*nNumE]=lamda*(X1[i]*sin(w)-Y1[i]*sin(fai)*cos(w));

        }

        matrix.transpose(A,AT,3*nNumE+nNumH,7);
        matrix.mult(AT,A,ATA,7,3*nNumE+nNumH,7);
        matrix.inv(ATA,7);
        matrix.mult(AT,L,ATL,7,3*nNumE+nNumH,1);
        matrix.mult(ATA,ATL,X,7,7,1);

        DetX+=X[0];DetY+=X[1];DetZ+=X[2];
        lamda+=X[3];
        fai+=X[4];w+=X[5];k+=X[6];

        // 对角度的限制
        if(fai>6.2831852)
            fai = fai - int(fai/6.2831852)*6.2831852;
        if(fai<-6.2831852)
            fai = fai + int(fabs(fai)/6.2831852)*6.2831852;
        if(w>6.2831852)
            w = w - int(w/6.2831852)*6.2831852;
        if(w<-6.2831852)
            w = w + int(fabs(w)/6.2831852)*6.2831852;
        if(k>6.2831852)
            k = k - int(k/6.2831852)*6.2831852;
        if(k<-6.2831852)
            k = k + int(fabs(k)/6.2831852)*6.2831852;
    }

    //计算误差结果
    double *v;
    v=new double[3*nNumE+nNumH];
    matrix.mult(A,X,v,3*nNumE+nNumH,7,1);
    double VV=0.0;
    for (i=0;i<3*nNumE+nNumH;i++)
    {
        v[i]=v[i]-L[i];
        VV+=v[i]*v[i];
    }
    double mo;
    mo=VV/(3*nNumE+nNumH-7);
    mo=sqrt(mo);
    double singma[7];
    for (i=0;i<7;i++)
    {
        singma[i]=sqrt(ATA[8*i])*mo;
    }

    Absolute7Para[0]=fai;
    Absolute7Para[1]=w;
    Absolute7Para[2]=k;
    Absolute7Para[3]=lamda;
    Absolute7Para[4]=DetX;
    Absolute7Para[5]=DetY;
    Absolute7Para[6]=DetZ;

    delete []X1;delete []Y1;delete []Z1;
    delete []A;delete []AT;delete []L;
    delete []v;

}

void SAMTerrianThread::transPoints( QString pointFilePath, QStringList ParaFilePathList, QString transPointFilePath )
{
    //m_mutex.lock();
    vector<CDataStyle::ObjectPoint2> d_model;
    //////////////////////////////以二进制文件读取模型文件/////////////////////////////////////
    ifstream filein;
    filein.open( pointFilePath.toStdString().c_str(), ios::in|ios_base::binary);
    if (filein.is_open() == false)
    {
        //QMessageBox::information(this,QStringLiteral("提示"), QStringLiteral("模型数据出错！"));
        return;
    }
    int num_model;
    filein.read((char*)&num_model, sizeof(int));
    CDataStyle::ObjectPoint2 temp_d_model;
    for (int i=0;i<num_model;i++)
    {
        filein.read((char*)&temp_d_model.X, sizeof(double));
        filein.read((char*)&temp_d_model.Y, sizeof(double));
        filein.read((char*)&temp_d_model.Z, sizeof(double));
        if (i%5==0)
            d_model.push_back(temp_d_model);
    }
    filein.close();

    //////////////////////////////以文本格式读取模型文件/////////////////////////////////////
    //     FILE *fp=NULL;
    //     if((fp=fopen(pointFilePath.toStdString().c_str(),"r"))==NULL)
    //     {
    //         QMessageBox::information(this,QStringLiteral("提示"), QStringLiteral("模型数据出错！"));
    //         return;
    //     }
    //     int num_model;
    //     fscanf(fp,"%d",&num_model);
    //
    //     for (int i=0;i<num_model;i=i+5)
    //     {
    //         ObjectPoint2 temp_d_model;
    //         for (int j = 0; j < 5; j++)
    //         {
    //             fscanf(fp,"%lf %lf %lf",
    //                 &temp_d_model.X,
    //                 &temp_d_model.Y,
    //                 &temp_d_model.Z);
    //         }
    //         d_model.push_back(temp_d_model);
    //     }
    //     fclose(fp);
    double	m_f;
    double	m_w;
    double	m_k;
    double	m_lamda;
    double	m_X;
    double	m_Y;
    double	m_Z;
    for (int i = 0; i < ParaFilePathList.size(); i++)
    {
        //读取参数文件,二进制
        ifstream filein;
        filein.open(ParaFilePathList.at(ParaFilePathList.size()-1-i).toStdString().c_str(), ios::in|ios::binary);
        if (filein.is_open() == false)
        {
            //QMessageBox::information(this,QStringLiteral("提示"), QStringLiteral("参数文件出错！"));
            return;
        }
        filein.read((char*)&m_f, sizeof(double));
        filein.read((char*)&m_w, sizeof(double));
        filein.read((char*)&m_k, sizeof(double));
        filein.read((char*)&m_lamda, sizeof(double));
        filein.read((char*)&m_X, sizeof(double));
        filein.read((char*)&m_Y, sizeof(double));
        filein.read((char*)&m_Z, sizeof(double));
        filein.close();

        //读取参数文件,文本格式
        //         FILE *fp_para=NULL;
        //         if((fp_para=fopen(ParaFilePathList.at(ParaFilePathList.size()-1-i).toStdString().c_str(),"r"))==NULL)
        //         {
        //             QMessageBox::information(this,QStringLiteral("提示"), QStringLiteral("参数文件出错！"));
        //             return;
        //         }
        //         fscanf(fp_para,"%lf",&m_f);
        //         fscanf(fp_para,"%lf",&m_w);
        //         fscanf(fp_para,"%lf",&m_k);
        //         fscanf(fp_para,"%lf",&m_lamda);
        //         fscanf(fp_para,"%lf",&m_X);
        //         fscanf(fp_para,"%lf",&m_Y);
        //         fscanf(fp_para,"%lf",&m_Z);
        //         fclose(fp_para);

        double a[3],b[3],c[3];

        a[0]=cos(m_f)*cos(m_k)-sin(m_f)*sin(m_w)*sin(m_k);
        a[1]=-cos(m_f)*sin(m_k)-sin(m_f)*sin(m_w)*cos(m_k);
        a[2]=-sin(m_f)*cos(m_w);
        b[0]=cos(m_w)*sin(m_k);
        b[1]=cos(m_w)*cos(m_k);
        b[2]=-sin(m_w);
        c[0]=sin(m_f)*cos(m_k)+cos(m_f)*sin(m_w)*sin(m_k);
        c[1]=-sin(m_f)*sin(m_k)+cos(m_f)*sin(m_w)*cos(m_k);
        c[2]=cos(m_f)*cos(m_w);

        for (int i=0;i<d_model.size();i++)
        {
            double _x=m_lamda*(a[0]*d_model[i].X+a[1]*d_model[i].Y+a[2]*d_model[i].Z)+m_X;
            double _y=m_lamda*(b[0]*d_model[i].X+b[1]*d_model[i].Y+b[2]*d_model[i].Z)+m_Y;
            double _z=m_lamda*(c[0]*d_model[i].X+c[1]*d_model[i].Y+c[2]*d_model[i].Z)+m_Z;

            d_model[i].X=_x;
            d_model[i].Y=_y;
            d_model[i].Z=_z;
        }
    }
    //////////////////////////////以二进制文件输出转换后的模型/////////////////////////////////////
    ofstream fileout;
    fileout.open( transPointFilePath.toStdString().c_str(), ios::out|ios_base::binary);
    int num_trans_model=d_model.size();
    fileout.write((char*)&num_trans_model, sizeof(int));
    for (int i=0;i<num_trans_model;i++)
    {
        fileout.write((char*)&(d_model[i].X), sizeof(double));
        fileout.write((char*)&(d_model[i].Y), sizeof(double));
        fileout.write((char*)&(d_model[i].Z), sizeof(double));
    }
    fileout.close();

    //////////////////////////////以文本格式输出转换后的模型/////////////////////////////////////
    //     FILE *fp_out=NULL;
    //     if ((fp_out=fopen(transPointFilePath.toStdString().c_str(),"w"))==NULL)
    //     {
    //         QMessageBox::information(this,QStringLiteral("提示"), QStringLiteral("文件输出出错！"));
    //         return;
    //     }
    //     fprintf(fp_out,"%d\n",d_model.size());
    //
    //     for (int i=0;i<d_model.size();i++)
    //     {
    //         fprintf(fp_out,"%lf  %lf  %lf\n",d_model[i].X,d_model[i].Y,d_model[i].Z);
    //     }
    //     fclose(fp_out);
    //m_mutex.unlock();
}

bool SAMTerrianThread::loadImages( QString leftImage, QString rightImage )
{
    leftsrcImage = imread(leftImage.toStdString().c_str(), 1);
    if (leftsrcImage.data == NULL)
    {
        QMessageBox::information(0,QStringLiteral("提示"), QStringLiteral("打开影像失败"));
        return false;
    }
    leftsrcWidth = leftsrcImage.cols;
    leftsrcHeight = leftsrcImage.rows;

    rightsrcImage = imread(rightImage.toStdString().c_str(), 1);
    if (rightsrcImage.data == NULL)
    {
        QMessageBox::information(0,QStringLiteral("提示"), QStringLiteral("打开影像失败"));
        return false;
    }
    rightsrcWidth = rightsrcImage.cols;
    rightsrcHeight = rightsrcImage.rows;
    return true;
}

QString SAMTerrianThread::getShortName(QString fullname)
{
    QFileInfo fi3(fullname);
    return fi3.baseName();
}

void SAMTerrianThread::getTerrianCloud()//获取地形点云
{
    qDebug()<<"Sub thread:" <<QThread::currentThreadId();

    int leftStartNum=0;//影像计数开始
    int rightStartNum=0;

    ////S2 检查影像，并初始化模块
    if(NameListL.size()!=NameListR.size())  return;

    QString m_1Lpath;
    QString m_1Rpath;
    QString m_2Lpath;
    QString m_2Rpath;

    QString m_1LName;
    QString m_1RName;
    QString m_2LName;
    QString m_2RName;

    ///////////////////////////////////写首个绝对变换参数//////////////////////////////////
    QString path = productFloder+"/"+"_absolute7para.txt";
    ofstream fileout;
    fileout.open(path.toStdString().c_str(), ios::out|ios::binary);
    double a=0.,b=1.;
    fileout.write((char*)&a, sizeof(double));
    fileout.write((char*)&a, sizeof(double));
    fileout.write((char*)&a, sizeof(double));
    fileout.write((char*)&b, sizeof(double));
    fileout.write((char*)&a, sizeof(double));
    fileout.write((char*)&a, sizeof(double));
    fileout.write((char*)&a, sizeof(double));
    fileout.close();
    m_ParaList<<path;
    ///////////////////////////////////写首个绝对变换参数//////////////////////////////////
    ////S3 逐像对生成地形
    for(int i=0;i<NameListL.size();i++)
    {
        emit FreshProgress(i);
        ////@S4 解析文件名
        m_1Lpath = NameListL.at(i);
        m_1Rpath = NameListR.at(i);

        m_1LName = getShortName(m_1Lpath);
        m_1RName = getShortName(m_1Rpath);
        ////S5 执行SGB匹配并写LOG

        if(loadImages(m_1Lpath, m_1Rpath)==false)    return;
        SGBMMatch(leftsrcImage, rightsrcImage, m_1LName, m_1RName, productFloder);

        if (i>0)
        {
            ////@S6 执行surf匹配并写LOG
            m_2Lpath = NameListL.at(i-1);
            m_2Rpath = NameListR.at(i-1);
            m_2LName = getShortName(m_2Lpath);
            m_2RName = getShortName(m_2Rpath);

            leftsrcBefore=imread(m_2Lpath.toStdString().c_str(), 1);
            surfMatch(leftsrcBefore , leftsrcImage ,m_2LName ,m_1LName ,
                                    m_2RName ,m_1RName ,productFloder);
        }

        QString path1 = productFloder;
        path1.append("\\").append(m_1LName).append(m_1RName).append("_SGBM_3d.pcs");
        QString path2 = productFloder;
        if(i!=0){
            path2.append("\\").append(m_2LName).append(m_1LName).append("_absolute7para.txt");
            m_ParaList << path2;
        }
        QString path3 = productFloder;
        path3.append("\\").append("transed_").append(m_1LName).append(m_1RName).append("_SGBM_3d.pcs");

        transPoints(path1, m_ParaList, path3);

        if (leftStartNum < NameListL.size()-1)
        {
            ++leftStartNum;
            ++rightStartNum;
            m_2Lpath = NameListL.at(leftStartNum);
            QFileInfo fi3(m_2Lpath);
            m_2LName = fi3.baseName();
            m_2Rpath = NameListR.at(rightStartNum);
            QFileInfo fi4(m_2Rpath);
            m_2RName = fi4.baseName();
        }
        emit ShowPoints(path3);
    }
    m_ParaList.clear();
    emit Finished();
}
