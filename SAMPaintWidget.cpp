#include "SAMPaintWidget.h"

#include <QDebug>

SAMPaintWidget::SAMPaintWidget(QWidget *parent) : QWidget(parent)
{
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(255,255,255));
    this->setPalette(palette);
    imgloaded=false;
    ifminimap=true;
    LX=0;
    LY=0;
    scale=1;
    setMouseTracking(true);
}

void SAMPaintWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if(!imgloaded)    return;

    int w=this->width();
    int h=this->height();


    ////@S1 在主窗口加载主图片
    painter.drawImage(0,0,*big);

    if(!ifminimap)    return;
    ////@S2 加右下角载缩略图
    painter.drawImage(double((double)4/(double)5)*double(w),double((double)4/(double)5)*(double)h,*mini);
}

void SAMPaintWidget::loadImg(QString a)
{
    img=new QImage;
    imgloaded=img->load(a);

    imgw=img->width();
    imgh=img->height();

    RefreshImg();
}

void SAMPaintWidget::changeMinimap()
{
    ifminimap=!ifminimap;

    RefreshImg();
}

void SAMPaintWidget::freshBigMap()
{
    ////@S1 计算图框
    //Widget边框
    int w=this->width();
    int h=this->height();
    //图边框
    int FrameX=w;
    int FrameY=h;
    big=new QImage(FrameX,FrameY,QImage::Format_RGB888);

    ////S2 反差数据
    //框中所对宽高
    int scaledOriW=FrameX/scale;
    int scaledOriH=FrameY/scale;

    QImage scaled;
    scaled=img->convertToFormat(QImage::Format_RGB888).copy(LX,LY,scaledOriW,scaledOriH).scaled(FrameX,FrameY);

    ////@S3 构建图
    int scount=0;
    for(int y=0;y<FrameY;y++)
    for(int x=0;x<FrameX;x++)
    {
        int sy=scount/(FrameX);int sx=scount%(FrameX);
        QRgb pixel=scaled.pixel(sx,sy);

        if(pixel==4278190080)
            pixel=qRgb(255,255,255);//PNG 去黑底

        big->setPixel(x,y,pixel);
        scount++;
    }

}

void SAMPaintWidget::freshMiniMap()
{
    ////@S1 计算图框
    //Widget边框
    int w=this->width();
    int h=this->height();
    //图边框
    int FrameX;
    int FrameY;

    FrameX=(double)w/(double)5;
    FrameY=(double)h/(double)5;
    mini=new QImage(FrameX,FrameY,QImage::Format_RGB888);
    //实际图框
    int tw;
    int th;

    tw=FrameX;th=(double)(double(imgh)/(double)imgw)*(double)tw;
    if(tw>FrameX||th>FrameY)   {th=FrameY-2;tw=(double)(double(imgw)/(double)imgh)*(double)th;}

    minimapScale=(double)tw/(double)imgw;
    ////@S2 将大影像缩小
    QImage scaled;
    scaled=img->convertToFormat(QImage::Format_RGB888).scaled(tw,th);

    ////@S3 构建缩略图
    int scount=0;
    minimapFrameLX=FrameX/2-tw/2;
    minimapFrameRX=FrameX/2+tw/2;
    minimapFrameLY=FrameY/2-th/2;
    minimapFrameRY=FrameY/2+th/2;
    int sx=0;int sy=0;
    for(int y=0;y<FrameY;y++)
    {
        for(int x=0;x<FrameX;x++)
        {
            if((x>=minimapFrameLX)&&(x<minimapFrameRX)&&(y>=minimapFrameLY)&&(y<minimapFrameRY))
            {
                if(sx<scaled.width()&&sy<scaled.height())
                {
                    QRgb pixel=scaled.pixel(sx,sy);

                    if(pixel==4278190080)
                        pixel=qRgb(255,255,255);//PNG 去黑底

                    mini->setPixel(x,y,pixel);
                    sx++;
                }

            }
            else
                mini->setPixel(x,y,qRgb(125,125,125));
        }
        sx=0;
        sy++;
    }


    ////@S4 缩略图描黑边
    for(int y=0;y<FrameY;y++)
    {mini->setPixel(0,y,qRgb(0,0,0));   mini->setPixel(FrameX-1,y,qRgb(0,0,0));   }
    for(int x=0;x<FrameX;x++)
    {mini->setPixel(x,0,qRgb(0,0,0));   mini->setPixel(x,FrameY-1,qRgb(0,0,0));   }

    MinimapFrame();
}

void SAMPaintWidget::RefreshImg()
{
    if(!isLoaded()) return;

    freshBigMap();
    if(ifminimap)   freshMiniMap();

    this->update();
}

bool SAMPaintWidget::isLoaded()
{
    return imgloaded;
}

void SAMPaintWidget::MinimapFrame()
{
    ////@缩略图上勾勒预览框
    //大图框架大小
    int FrameX=this->width();
    int FrameY=this->height();
    //框中所对宽高
    int scaledOriW=(double)minimapScale*(double)FrameX/(double)scale;
    int scaledOriH=(double)minimapScale*(double)FrameY/(double)scale;

    int LPX=(double)minimapScale*(double)LX+minimapFrameLX;
    int LPY=(double)minimapScale*(double)LY+minimapFrameLY;

    for(int x=LPX;x<LPX+scaledOriW;x++)
    {
        int y=LPY;
        if(x>=0&&x<mini->width()&&y>=0&&y<mini->height())
            mini->setPixel(x,y,qRgb(0,0,0));
        y=LPY+scaledOriH;
        if(x>=0&&x<mini->width()&&y>=0&&y<mini->height())
            mini->setPixel(x,y,qRgb(0,0,0));
    }
    for(int y=LPY;y<LPY+scaledOriH;y++)
    {
        int x=LPX;
        if(x>=0&&x<mini->width()&&y>=0&&y<mini->height())
            mini->setPixel(x,y,qRgb(0,0,0));
        x=LPX+scaledOriW;
        if(x>=0&&x<mini->width()&&y>=0&&y<mini->height())
            mini->setPixel(x,y,qRgb(0,0,0));
    }

}

void  SAMPaintWidget::mousePressEvent(QMouseEvent *event)
{
    currentPoint=event->pos();
}

void  SAMPaintWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()==Qt::LeftButton&&isLoaded())
    {
        move(currentPoint.x()-event->pos().x(),currentPoint.y()-event->pos().y());
        currentPoint=event->pos();
    }
}

void SAMPaintWidget::mouseReleaseEvent(QMouseEvent *event)
{
    RefreshImg();
}

void SAMPaintWidget::wheelEvent(QWheelEvent *event)
{
    if(!isLoaded()) return;
    int numSteps=event->delta()/8/15;
    if(numSteps>0)  ActionEnLarge();
    if(numSteps<0)  ActionNarrow();
}

void SAMPaintWidget::ActionEnLarge()
{
    scale=scale+0.5;
    RefreshImg();
}

void SAMPaintWidget::ActionNarrow()
{
    scale=scale/1.1;
    RefreshImg();
}

void SAMPaintWidget::move(int x,int y)
{
    LX=LX+x;
    LY=LY+y;
    if(LX>=img->width())    LX=LX-x;
    if(LY>=img->height())    LY=LY-y;
    freshBigMap();
    update();
}

void SAMPaintWidget::moveTo(int x,int y)
{
    LX=x;LY=y;
    ////@S1 边缘检查
    if(LX>=img->width())    LX=img->width()-1;
    if(LY>=img->height())    LY=img->height()-1;
    if(LX<0)    LX=0;
    if(LY<0)    LY=0;
    ////@S2 刷新
    RefreshImg();
}

void SAMPaintWidget::Unload()
{
    imgloaded=false;
    delete img;
    delete mini;
    delete big;
    update();
}
