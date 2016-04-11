#ifndef SAMINFODOCK_H
#define SAMINFODOCK_H

#include "SAMCore.h"

#include <QDockWidget>
#include <QTabWidget>
#include <QLabel>
#include <QLayout>
#include <QScrollArea>

class SAMInfoDock : public QDockWidget
{
    Q_OBJECT
public:
    explicit SAMInfoDock(QWidget *parent = 0);
    ~SAMInfoDock();
private:
    SAMCore *localcore;

    QTabWidget *mainWidget;
    QVBoxLayout *mainLayout;
    QWidget *w;

    QScrollArea *SysArea;
    QScrollArea *ImgArea;
    QVBoxLayout *sys;
    QVBoxLayout *inf;
    QLabel* SysLog;
    QLabel* ImgInfo;
public slots:
    void setCore(SAMCore *core);
    void RefreshInfo(const QString a);
    void RefreshLog();
};

#endif // SAMINFODOCK_H
