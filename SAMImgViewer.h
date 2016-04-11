#ifndef SAMIMGVIEWER_H
#define SAMIMGVIEWER_H

#include <QWidget>
#include <QToolBar>
#include <QAction>
#include <QLayout>
#include <QLabel>

#include "SAMPaintWidget.h"
#include "SAMCore.h"

class SAMImgViewer : public QWidget
{
    Q_OBJECT
private:
    //菜单和Toolbar功能
    QAction *actionEnlarge;
    QAction *actionNarrow;
    QAction *actionMove;
    QAction *actionRotation;

    QAction *actionOpen;
    QAction *actionCancel;

    QAction *actionRefresh;
    QAction *actionMinimap;

protected:
    QToolBar *toolbar;

public:
    explicit SAMImgViewer(SAMCore *core,QWidget *parent = 0);
    SAMCore *localcore;
    QHBoxLayout *layout;
    SAMPaintWidget *paintWidget;

public slots:
    void  setCore(SAMCore *core);
    void  createToolBar();
    void  createActions();
    void  openImg(QString a);

    void  ActionEnlarge();
    void  ActionNarrow();
    void  ActionMoveTo();

    void  ActionUnload();
    void  ActionLoad();

    void  ActionshowMiniMap();
    void  ActionRefresh();
};

#endif // SAMIMGVIEWER_H
