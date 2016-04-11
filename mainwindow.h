#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QSplitter>
#include <QMdiArea>
#include <QLabel>
#include <QDialog>
#include <QPushButton>
#include <QLineEdit>


#include "SAMCore.h"
#include "SAMFileDock.h"
#include "SAMInfoDock.h"
#include "SAMImgViewer.h"
#include "SAMProductViewer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void createFileDock();//创建文件Dock

    void createInfoDock();//创建信息Dock

    void createMdiArea();//创建主窗口

    void createCalibDlg();//创建标定对话框

    void on_action_SetWorkPath_triggered();

    void on_action_AddLFloder_triggered();

    void on_action_AddLImg_triggered();

    void on_action_AddRImg_triggered();

    void on_action_AddRFloder_triggered();

    void on_action_unloadL_triggered();

    void on_action_unloadR_triggered();

    void on_action_unloadAll_triggered();

    void on_action_unloadP_triggered();

    void on_action_OpenImg_triggered();

    void on_action_setProductFloder_triggered();

    void on_action_openFloder_triggered();

    void on_action_SaveWorkSpace_triggered();

    void on_action_LoadWorkSpace_triggered();

    void on_action_FileDlg_triggered(bool checked);

    void on_action_InfoDlg_triggered(bool checked);

    void on_action_LDlg_triggered(bool checked);

    void on_action_RDlg_triggered(bool checked);

    void on_action_PDlg_triggered(bool checked);

    void on_action_getCloud_triggered();

    void on_action_Calib_triggered();

    void CalibDlgAccepted();

private:
    Ui::MainWindow *ui;

    SAMCore *core;

    SAMFileDock *m_filedock;
    SAMInfoDock *m_infodock;
    SAMImgViewer *m_limgviewer;
    SAMImgViewer *m_rimgviewer;
    SAMProductViewer *m_pimgviewer;

    QSplitter *m_splitter;
    QSplitter *m_imgsplitter;

    QDialog *calibdlg;//标定对话框
    QLabel *calib_x;
    QLabel *calib_y;
    QLineEdit *calib_Lx;
    QLineEdit *calib_Ly;
    QPushButton *calib_OK;
    QPushButton *calib_Cancel;
    QVBoxLayout *vbox;
    QHBoxLayout *buttonbox;
};

#endif // MAINWINDOW_H
