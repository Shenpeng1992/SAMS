#ifndef SAMTERRIANTHREAD_H
#define SAMTERRIANTHREAD_H

#include <QObject>
#include <QList>
#include <QStringList>

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
    SAMTerrianThread();

public slots:
    void surfMatch(Mat leftImage1, Mat leftImage2, QString leftFileName1, QString leftFileName2,QString rightFileName1, QString rightFileName2, QString imageAbsolutePath);
    void SGBMMatch(Mat leftImage, Mat rightImage, QString leftName, QString rightName, QString imageAbsolutePath);
    void AbsoluteOrient(CDataStyle::EDATA *edData,int nNumE,CDataStyle::HDATA *hdData,int nNumH,double *Absolute7Para);
    void transPoints(QString pointFilePath, QStringList ParaFilePathList, QString transPointFilePath);

private:
    CMatrix matrix;
};

#endif // QTERRIANTHREAD_H
