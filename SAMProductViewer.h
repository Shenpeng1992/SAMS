#ifndef SAMPRODUCTVIEWER_H
#define SAMPRODUCTVIEWER_H

#include <QObject>
#include <QWidget>

#include "glwiget.h"
#include "SAMImgViewer.h"
#include "SAMCore.h"
#include "QVBoxLayout"

class SAMProductViewer : public QWidget
{
    Q_OBJECT
public:
    SAMProductViewer(SAMCore *core);
private:
    enum LoadMode{
        IsImg=0,
        IsDEM=1
    }m_LoadMode;
    SAMCore *localCore;
    SAMImgViewer *viewer;
    vector<CDataStyle::points_xyz> point_cloud;
    vector<CDataStyle::points_xyz> all_point_cloud;
    glwiget *m_glWidget;
    QVBoxLayout *glLayout;
    QVBoxLayout *mainLayout;
public slots:
    void changeMode(LoadMode Mode);
    void loadPoints(QString pointFilrPath);
    void loadProduct(QString string);
signals:
    void modechanged(LoadMode);
};

#endif // SAMPRODUCTVIEWER_H
