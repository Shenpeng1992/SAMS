#ifndef GLWIGET_H
#define GLWIGET_H

#include <QGLWidget>
#include <QtGui/QKeyEvent>
#include <QtCore/QPoint>
#include <vector>
#include "TerrainSub/DataStyle.h"
#include <QtCore/QPoint>

using namespace std;

class glwiget : public QGLWidget
{
	Q_OBJECT

public:
	glwiget(QWidget *parent=0);
	~glwiget();

private:

	void initializeGL();
	void resizeGL(int w,int h);
	void setupviewport(int w,int h);

	void paintGL();
	void keyPressEvent(QKeyEvent *);

	void mousePressEvent(QMouseEvent *);	
	void mouseMoveEvent(QMouseEvent *);
	void mouseReleaseEvent(QMouseEvent *);

	void wheelEvent(QWheelEvent *);

public:

	//计算直方图的两个峰值
	void GetPeakZ(vector<int> histZ,double &peakZ1,double &peakZ2,double interval_z);
	//void GetPeakI(unsigned short min_i,unsigned short max_i,unsigned short &peakI1,unsigned short &peakI2);

	GLfloat X_Angle,Y_Angle,zrot;
	GLfloat x_position,y_position,z_position;

	GLuint textures[3];

	QPoint startpoint;
	QPoint endPoint;

    vector<CDataStyle::points_xyz> *points;
	int point_num;
	double x_mean;
	double y_mean;
	double z_mean;

	double z_distens;
	double z_min;

	vector<int> *hist_Z;
	
	double PeakZ_min;
	double PeakZ_max;
	
	int R_Table[255];
	int G_Table[255];
    int B_Table[255];
public slots:
    void Refresh();
};

#endif // GLWIGET_H
