// DataStyle.h: interface for the CDataStyle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATASTYLE_H__EFA749C1_95E8_4ED7_8D99_DF25D8B7D8D5__INCLUDED_)
#define AFX_DATASTYLE_H__EFA749C1_95E8_4ED7_8D99_DF25D8B7D8D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <QString>
#include <cv.h>

class CDataStyle  
{
public:
	CDataStyle();
	virtual ~CDataStyle();
    static int cvx_saveMat(CvMat *mat, const char *filename);


    static struct Pixel_Color
    {
        uchar blue;
        uchar green;
        uchar red;
    };

    static struct Pixel_Color2
    {
        int blue;
        int green;
        int red;
    };

    static struct Cam_Para
    {
        double pixelsize;
        double pixelsize2;

        int height;
        int width;

        double x0;
        double y0;
        double f;

        double k1;
        double k2;
        double k3;
        double p1;
        double p2;
        double b1;
        double b2;

        double t;
        double w;
        double k;
        double Xs;
        double Ys;
        double Zs;
    };

    static struct Point_array2
    {
        QString name;

        double x;
        double y;

        double X;
        double Y;
        double Z;

        uchar red;
        uchar green;
        uchar blue;
    };

    static struct Point_array3
    {
        double X;
        double Y;
        double Z;

        int red;
        int green;
        int blue;
    };

    static struct ObjectPoint
    {
        QString name;
        double X;
        double Y;
        double Z;
        int red;
        int green;
        int blue;
    };

    static struct ObjectPoint3
    {
        double X;
        double Y;
        double Z;
        float red;
        float green;
        float blue;
    };

    static struct ObjectPoint2
    {
        QString name;
        double X;
        double Y;
        double Z;
        int hd;
    };

    static struct PicturePoint
    {
        QString name;
        double x;
        double y;
        uchar red;
        uchar green;
        uchar blue;
    };

    static struct PicturePoint2
    {
        QString name;
        double x;
        double y;
    };

    static struct EDATA
    {
        QString name;
        double X;
        double Y;
        double Z;
        double Xtp;
        double Ytp;
        double Ztp;
    };

    static struct HDATA
    {
        QString name;
        double X;
        double Y;
        double Z;
        double Ztp;
    };

    static struct Pixel_array
    {
        int x;
        int y;
        uchar red;
        uchar green;
        uchar blue;
    };

    static struct Pixel_array2
    {
        int X;
        int Y;
        int R;
        int G;
        int B;
    };

    static struct Point_array
    {
        int id;
        double x;
        double y;
        double radius;
    };

    static struct PixelPoint	//像素坐标
    {
        QString name;		//点名
        double	x;
        double	y;
        bool is;
    };

    static struct PointOne	//像素坐标
    {
        QString name;		//点名
        double	zhi;
    };

    static struct Code_point
    {
        Point_array m_centerpoint;
        Point_array m_roundpoint[7];
        Point_array m_A;
        Point_array m_B;
        Point_array m_C;
        Point_array m_D;
        Point_array m_XX[3];
        Point_array m_X[3];
        int id_code;
        QString Code;
    };

    static struct CodeP1
    {
        int num;
        double x;
        double y;
    };

    static struct CodeP2
    {
        int num;
        int id;
    };


    static struct points_xyz
    {
        double x;
        double y;
        double z;

        unsigned short   I;
        long J;
        long index;
        int w;
    };

    struct PointandGray
    {
        double x;
        double y;
        double z;
        int g;
    };

    struct RealMacthPoints
    {
        double x1;
        double y1;
        double x2;
        double y2;
    };

};

#endif // !defined(AFX_DATASTYLE_H__EFA749C1_95E8_4ED7_8D99_DF25D8B7D8D5__INCLUDED_)
