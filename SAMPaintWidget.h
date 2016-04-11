#ifndef SAMPAINTWIDGET_H
#define SAMPAINTWIDGET_H

#include <QWidget>
#include <QString>
#include <QPixmap>
#include <QPixmap>
#include <QPainter>
#include <QMouseEvent>

class SAMPaintWidget : public QWidget
{
    Q_OBJECT
private:
    QImage *img;
    QImage *mini;
    QImage *big;

    bool imgloaded;
    bool ifminimap;

    void paintEvent(QPaintEvent *event);
    void freshMiniMap();
    void freshBigMap();

    int imgw;
    int imgh;

    int minimapFrameLX;
    int minimapFrameLY;
    int minimapFrameRX;
    int minimapFrameRY;
    double minimapScale;

    int LX;
    int LY;
    double scale;

    QPoint currentPoint;

    int enlarge;
    int narrow;

public:
    explicit SAMPaintWidget(QWidget *parent = 0);

signals:

public slots:
    void loadImg(QString a);
    void changeMinimap();
    void RefreshImg();
    void MinimapFrame();
    void ActionEnLarge();
    void ActionNarrow();
    void move(int x,int y);
    void moveTo(int x,int y);
    void Unload();

    bool isLoaded();

    void  mousePressEvent(QMouseEvent *event);
    void  mouseMoveEvent(QMouseEvent *event);
    void  mouseReleaseEvent(QMouseEvent *event);
    void  wheelEvent(QWheelEvent *event);
};

#endif // SAMPAINTWIDGET_H
