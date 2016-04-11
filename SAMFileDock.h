#ifndef SAMFILEDOCK_H
#define SAMFILEDOCK_H

#include "SAMCore.h"

#include <QWidget>
#include <QTableWidget>
#include <QString>
#include <QLabel>
#include <QAction>
#include <QMenu>
#include <QDockWidget>
#include <QTabWidget>

class SAMFileDock : public QDockWidget
{
    Q_OBJECT

private:

    int currentTableColumn;
    int currentTableRow;
    int currentProjectRow;
    SAMCore *localcore;
    ////@左列右击菜单
    QMenu *LMenu;
    QAction *AddLLine;
    QAction *delLLine;
    QAction *upLLine;
    QAction *downLLine;
    ////@右列右击菜单
    QMenu *RMenu;
    QAction *AddRLine;
    QAction *delRLine;
    QAction *upRLine;
    QAction *downRLine;
    ////@产品列右击菜单
    QMenu *PMenu;
    QAction *AddPLine;
    QAction *delPLine;
    QAction *upPLine;
    QAction *downPLine;
    ////@公用Action
    QAction *AddLRLine;
    QAction *delLRLine;
    QAction *upLRLine;
    QAction *downLRLine;
    QAction *changeLRPath;
    QAction *changePPath;

public:

    explicit SAMFileDock(QWidget *parent = 0);
    ~SAMFileDock();

    QTabWidget *tab;
    QTableWidget *table;//影像对表
    QTableWidget *production;//产品表
    QWidget *mainWidget;

    QString getShortName(QString longname);//获取短名

public slots:

    void refresh(SAMCore *core);//刷新队列
    void refresh();//刷新队列

    void createRightMenu();

    void tableRightClicked(const QPoint &a);
    void tableClicked(QTableWidgetItem* a);
    void tableDoubleClicked(QTableWidgetItem* a);
    void productionRightClicked(const QPoint &a);
    void productionClicked(QTableWidgetItem* a);
    void productionDoubleClicked(QTableWidgetItem* a);

    void actionAddLLine();
    void actionAddRLine();
    void actionAddLRLine();
    void actionAddPLine();

    void actiondelLLine();
    void actiondelRLine();
    void actiondelLRLine();
    void actiondelPLine();

    void actionupLLine();
    void actionupRLine();
    void actionupLRLine();
    void actionupPLine();

    void actiondownLLine();
    void actiondownRLine();
    void actiondownLRLine();
    void actiondownPLine();

    void actionchangeLRPath();
    void actionchangePPath();

signals:
    void InfoRefresh(const QString filepath);
    void ShowLImg(const QString filepath);
    void ShowRImg(const QString filepath);
    void ShowP(const QString filepath);

};

#endif // SAMFILEDOCK_H
