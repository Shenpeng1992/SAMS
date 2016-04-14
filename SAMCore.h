#ifndef SAMCORE_H
#define SAMCORE_H

#include <QString>
#include <QStringList>
#include <QObject>
#include <QTextStream>
#include <QTime>
#include <QFile>
#include <QProgressBar>
#include <QLabel>
#include <QVBoxLayout>
#include <QThread>

#include <cv.h>
#include <highgui.h>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/legacy/legacy.hpp>

#include "SAMTerrianThread.h"

using namespace cv;
using namespace std;

class SAMCore : public QObject
{
    Q_OBJECT
private:
    QFile file;

    QString workFloder;//工作路径
    QString productFloder;//产品目录

    QStringList NameListL;//左影像队列
    QStringList NameListR;//右影像队列
    QStringList ProductList;//产品队列

    QString *currentL;//当前L
    QString *currentR;//当前R
    QString *currentProduct;//当前产品

    SAMTerrianThread *m_subThread;//处理地形子进程
    QThread *sub_thread;

    QDialog *progressdlg;//进度GUI
    QLabel *labtext;
    QVBoxLayout *vbox;
    QProgressBar *bar;
    QPushButton *OK;

public:
    //队列与条目获取
    QStringList* getNameListL();
    QStringList* getNameListR();
    QStringList* getProductList();

    QString* getWorkFloder();
    QString* getProductFloder();

    QString* getCurrentL();
    QString* getCurrentR();
    QString* getCurrentProduct();

    //队列与条目设置
    void setNameListL(QStringList a);
    void setNameListR(QStringList a);
    void setProductList(QStringList a);

    void setWorkFloder();
    void setProductFloder();

    void setCurrentL(int a);
    void setCurrentR(int a);
    void setCurrentProduct(int a);

public slots:
    void AddFile();//打开文件

    void AddLImg();//打开单片
    void AddRImg();

    void AddLFloder();//打开文件夹
    void AddRFloder();
    void AddPFloder();

    void unloadL();//取消目录
    void unloadR();
    void unloadP();
    void unLoadAll();

    void LoadWorkSpace();//加载工作区
    void SaveWorkSpace();

    void AddLLine(int a);//插入行
    void AddRLine(int a);
    void AddLRLine(int a);
    void AddPLine(int a);

    void delLLine(int a);//删除行
    void delRLine(int a);
    void delLRLine(int a);
    void delPLine(int a);

    void upLLine(int a);//上调
    void upRLine(int a);
    void upLRLine(int a);
    void upPLine(int a);

    void downLLine(int a);//下调
    void downRLine(int a);
    void downLRLine(int a);
    void downPLine(int a);

    void changeLRPath(int c, int r);//改变路径
    void changePPath(int r);

    void writeLog(QString a);

    void getTerrianCloud();//获取地形点云

    void createProcessDlg();//创建进度对话框
    void changeProcessDlg();

    void createTerrianThread();

    void cameraCalibration(int nx,int ny);

    void Showproducts(QString product);
public:
    SAMCore();

signals:
    void writeLog();

    void getTerrianCloudSignals();

    void showproducts(QString);
};


#endif // SAMCORE_H
