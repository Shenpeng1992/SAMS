#ifndef SAMTERRIANTHREAD_H
#define SAMTERRIANTHREAD_H

#include <QObject>
#include <QList>
#include <QStringList>
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QProgressBar>
#include <QPushButton>

#include <cv.h>
#include <highgui.h>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/legacy/legacy.hpp>

#include <fstream>
#include <iostream>

#include "TerrainSub/matcher.h"
#include "TerrainSub/DataStyle.h"
#include "TerrainSub/Matrix.h"

using namespace cv;
using namespace std;

class SAMTerrianThread : public QObject
{
    Q_OBJECT
public:
    SAMTerrianThread(QStringList LList, QStringList RList, QString floder);
private:
    QStringList NameListL;
    QStringList NameListR;
    QString productFloder;

    //原始影像参数
    Mat leftsrcImage,rightsrcImage;
    int leftsrcWidth,leftsrcHeight,rightsrcWidth,rightsrcHeight;
    Mat leftsrcBefore;

    QStringList m_ParaList;
public slots:

    void surfMatch(Mat leftImage1, Mat leftImage2, QString leftFileName1, QString leftFileName2,QString rightFileName1, QString rightFileName2, QString imageAbsolutePath);
    void SGBMMatch(Mat leftImage, Mat rightImage, QString leftName, QString rightName, QString imageAbsolutePath);
    void AbsoluteOrient(CDataStyle::EDATA *edData,int nNumE,CDataStyle::HDATA *hdData,int nNumH,double *Absolute7Para);
    void transPoints(QString pointFilePath, QStringList ParaFilePathList, QString transPointFilePath);
    bool loadImages(QString leftImage, QString rightImage);
    QString getShortName(QString fullname);
    void getTerrianCloud();//获取地形点云

private:
    CMatrix matrix;
signals:
    void ShowPoints(QString);
    void FreshProgress(int);
    void Finished();
};

#endif // QTERRIANTHREAD_H
