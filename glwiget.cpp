#include "glwiget.h"
#include <gl/GLU.h>
#include <gl/glut.h>
#include <QDateTime>
#include <QDebug>

glwiget::glwiget(QWidget *parent)
	: QGLWidget(parent)
{
    QString LOG;
    LOG=QDateTime::currentDateTime().toString("yyyy.MM.dd;hh:mm:ss")+"\t"+"Initialize GLViewer";
    qDebug()<<LOG;

	z_position = -600.0;
	x_position = 0.0;
	y_position = 0.0;
	X_Angle = Y_Angle = zrot = 0.0;

	setAutoFillBackground(true);

    points = new vector<CDataStyle::points_xyz>;

	point_num = 0;
	x_mean  = 0;
	y_mean  = 0;
	z_mean  = 0;

	z_min = 0.0;
	z_distens = 0.0;

	for (int i=0;i<255;i++)
	{
		//////////////////////////////////////////////////////////////////////////
		                                                                    //RRR
		if (i<101)
		{
			R_Table[i] = 0;
		}
		else if(i<153)
		{
			R_Table[i] =  (180/52)*(i-100) ;

		}else
		{
			R_Table[i] = 180;
		}

		                                                                   //GGG
		if (i<55)
		{
			G_Table[i] = (180/55)*i;
		}
		else if(i<150)
		{
			G_Table[i] =  180;

		}else
		{
			G_Table[i] = 180/(255-150) * (255-i);
		}

		                                                                   //BBB
		if (i<54)
		{
			B_Table[i] = 180;
		}
		else if(i<101)
		{
			B_Table[i] =  180/47* (101-i);

		}else
		{
			B_Table[i] = 0;
		}
		//////////////////////////////////////////////////////////

	}

}

glwiget::~glwiget()
{

}
 
void glwiget::initializeGL()
{
	glClearColor(0.0,0.0,0.0,0.0);
	glShadeModel(GL_SMOOTH);
	glClearDepth(100.0);
	glEnable(GL_DEPTH_TEST);

// 	textures[0] = bindTexture(QPixmap("1.PNG"));
// 	if (textures[0] == NULL)
// 	{
// 		return;
// 	}
// 	textures[1] = bindTexture(QPixmap("2.PNG"));
// 	textures[2] = bindTexture(QPixmap("3.PNG"));
// 
// 	glEnable(GL_TEXTURE_2D);
}

void glwiget::setupviewport(int w,int h)
{
	glViewport(0,0,(GLint)(w),(GLint)(h));
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0,(GLfloat)(w)/(GLfloat)(h),0.001,100000000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void glwiget::resizeGL(int w,int h)
{
// 	glViewport(0,0,(GLint)(w),(GLint)(h));
// 	glMatrixMode(GL_PROJECTION);
// 	glLoadIdentity();
// 	gluPerspective(45.0,(GLfloat)(w)/(GLfloat)(h),0.1,100.0);
// 	glMatrixMode(GL_MODELVIEW);
// 	glLoadIdentity();

	setupviewport(w,h);

}

void glwiget::paintGL()
{
	double H;
    double S = 0.75;
    double I = 300;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glPushMatrix();
/*	glLoadIdentity();*/

	glTranslatef(0.0,0.0,z_position);
	glTranslatef(x_position,0.0,0.0);
	glTranslatef(0.0,y_position,0.0);


	glRotatef(X_Angle,1.0,0.0,0.0);
/*	glRotatef(yrot,0.0,1.0,0.0);*/
	glRotatef(Y_Angle,0.0,0.0,1.0);
	glPointSize(1.25);

	//------画点云
	glBegin(GL_POINTS);
	//glBegin(GL_)

	if (point_num!=0)
	{
		double R,G,B,f;
		int L;
		int ind;

		for (int i = 0;i<point_num;i++)
		{

			//////////////////////////////////////////////////////////////////////////

			//H = 220*(coordinates[2]-m_lidardata->m_lasheader.min_z)/(m_lidardata->m_lasheader.max_z-m_lidardata->m_lasheader.min_z);
// 			if (     ( (*points)[i] ).z  > PeakZ_max            )
// 			{
// 				R = 180;
// 				G = 0;
// 				B = 0;
// 			} 
// 			else if (( (*points)[i] ).z  < PeakZ_min   )
// 			{
// 				R = 0;
// 				G = 0;
// 				B = 180;
// 			}
// 			else
			/*
				{

				if(    (((*points)[i]).z) <= PeakZ_min          ) 
				{
					(((*points)[i]).z) = PeakZ_min  ;

				}
				if(    (((*points)[i]).z) >= PeakZ_max          ) 
				{
					(((*points)[i]).z) = PeakZ_max  ;
				}

				H = 300 * (((*points)[i]).z -z_min) / z_distens  ;//高程归一化


				H = 300 - H;

				if (H<0)
				{
					H = 0;
				}

				if ( 0 <= H && H <120)
				{
					//B = I * (1-S) ;
					B=0;
					R = I * (1+ (S * cos(H/180*314/100) )/ cos((60 - H)/180*314/100 )) ;
					G = (3 * (90) - ( R + B ) ) ;
				}
				else if (120 <= H && H <240 )
				{
					H -= 120;

					R = I * (1-S) ;
					G = I * (1+ (S * cos(H/180*314/100) )/ cos( (60 - H)/180*314/100 )) *1.2;
					B = (3 * (I) - ( R + G ) ) ;
				}
				else if (240 <= H && H < 360) 
				{
					H -= 240;

					G = I * (1-S) ;
					B = I * (1+ (S * cos (H/180*314/100) )/ cos( (60 - H)/180*314/100 )) ;
					R = (3 * (I) - ( G + B ) ) ;
				}
			}*/
			//////////////////////////////////////////////////////////////////////////
			/*
			if (     ( (*points)[i] ).z  > PeakZ_max            )
			{
				R = 180;
				G = 0;
				B = 0;
			} 
			else if (( (*points)[i] ).z  < PeakZ_min   )
			{
				R = 0;
				G = 0;
				B = 180;
			}
			else
			{
			
			//Sleep();
			f = 10* (((*points)[i]).z -PeakZ_min) / (PeakZ_max-PeakZ_min) ;//高程归一化
			L = 10;
			//red
// 			if (f<L/4)
// 				R = 0;
// 			if(f>=L/4 && f< 3*L/4)
// 				R = 2*(f-L/4);
// 			if(f>=3*L/4)
// 				R = L-1;
// 			//green
// 			if (f<L/4)
// 				G = 3*f;
// 			if(f>=L/4 && f<=3*L/4)
// 				G = L-1;
// 			if(f>3*L/4)
// 				G = 4*(L-f);
// 			//blue
// 			if (f<=L/3)
// 				B = L-1;
// 			if(f>L/3&&f<3*L/4)
// 				B = 6*(L/2-f);
// 			if(f>=3*L/4)
// 				B = 0;
			//////////////////////////////////////////////////////////////////////////
			if (f<(L*(10.8-6.5)/10.8))
				R = 0;
			if(f>=((L*(10.8-6.5)/10.8)) && (f<(L*(10.8-4.32)/10.8)))
	     		R = 180*( (f-(L*(10.8-6.5)/10.8)) / (((L*(10.8-4.32)/10.8)) -(L*(10.8-6.5)/10.8)));
			if((f>=(L*(10.8-4.32)/10.8)))
				R = 180;
			
			//green
			if (f<(L*(10.8-8.45)/10.8))
				  G = 180*( f /(L*(10.8-4.47)/10.8));
			
			if(f>=((L*(10.8-8.45)/10.8)) && (f<(L*(10.8-4.47)/10.8)) )
				G = 180;			
			if((f>=(L*(10.8-4.47)/10.8)))

			 	G = 180* ((L - f) / ((L -(L*(10.8-4.47)/10.8))));
			
			//blue
			if (f<(L*(10.8-8.7)/10.8))
				B = 180;
			if(f>=((L*(10.8-8.7)/10.8)) && (f<(L*(10.8-6.5)/10.8)) )
				B = 180*( ((L*(10.8-6.5)/10.8) - f ) / (((L*(10.8-6.5)/10.8)) -(L*(10.8-8.7)/10.8))  );
			if((f>=(L*(10.8-6.5)/10.8)))
				B = 0;
			///
			}*/
			//////////////////////////////////////////////////////////////////////////
			if (     ( (*points)[i] ).z  > PeakZ_max            )
			{
				R = 180;
				G = 0;
				B = 0;
			} 
			else if (( (*points)[i] ).z  < PeakZ_min   )
			{
				R = 0;
				G = 0;
				B = 180;
			}
			else
			{

				//Sleep();
				ind = 255* (((*points)[i]).z -PeakZ_min) / (PeakZ_max-PeakZ_min) ;//高程归一化
				
				R = R_Table[ind];
				G = G_Table[ind];
				B = B_Table[ind];
			
			}
//////////////////////////////////////////////////////////////////////////
			glColor3f(R/255.0,G/255.0,B/255.0);
			
			glVertex3f(((*points)[i]).x - x_mean ,
				       ((*points)[i]).y - y_mean ,
			           ((*points)[i]).z - z_mean  );
		}
	}		
	glEnd();	
	
	//坐标轴
	glBegin(GL_LINES);
	//z轴
	glColor3f(0,0,1);
	glVertex3f(0,0,0);
	glVertex3f(0,0,1);
	//x轴
	glColor3f(1,0,0);
	glVertex3f(0,0,0);
	glVertex3f(1,0,0);
	//y轴
	glColor3f(0,1,0);
	glVertex3f(0,0,0);
	glVertex3f(0,1,0);
	glEnd();
	glLineWidth(5);
	

	glPopMatrix();
	//glFlush();
}

void glwiget::keyPressEvent(QKeyEvent * event)
{
	switch(event->key())
	{
	case Qt::Key_Up:
//		xrot += 10.0;
		break;
	case Qt::Key_Down:
// 		translate -=1;
// 		if (translate <= -20)
// 		{
// 			translate = -1;
// 		}
	case Qt::Key_Left:
//		yrot +=10.0;
		break;
	case Qt::Key_Right:
		zrot +=10.0;
		break;
	} 
 	updateGL();
 	QGLWidget::keyPressEvent(event);
}

void glwiget::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton || event->button() == Qt::RightButton)
	{
		startpoint = event->pos();
	}
}

void glwiget::mouseMoveEvent(QMouseEvent *event)
{
	if (event->buttons() &  Qt::LeftButton)
	{
		endPoint = event->pos();
		Y_Angle += (endPoint.x() - startpoint.x())/10;
		X_Angle += (endPoint.y() - startpoint.y())/10;	
		updateGL();
	} 
	else if(event->buttons() &  Qt::RightButton )
	{
        endPoint = event->pos();
		x_position +=(GLdouble)(endPoint.x() - startpoint.x())/10;
		y_position +=(GLdouble)(startpoint.y() - endPoint.y())/10;
		//startpoint = event->pos();
		updateGL();
	}
	//swap_the_buffers();
	//glutSwapBuffers();
	//updateGL();

}

void glwiget::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton || event->button() == Qt::RightButton)
	{
		startpoint = QPoint(0.0,0.0);
		//startpoint = event->pos();
	}

}

void glwiget::wheelEvent(QWheelEvent *event)
{	
	z_position -= event->delta()/8.0;
	updateGL();
}

//计算高程两个峰值
void glwiget::GetPeakZ( vector<int> histZ,double &peakZ1,double &peakZ2,double interval_z )
{
	int sum = 0;
	for (int i=0;i<histZ.size();i++)
	{
		sum+=histZ[i];
	}


	int max_index1 = 0;
	int max_index2 = 0;

	int hist1,hist2;
	hist1 = histZ[0];
	hist2 = histZ[histZ.size()-1];
	int i;
	int j;
	vector<int> peaks;

	int sum_min = 0;
	int sum_max = 0;
	for(i=0; i<histZ.size(); i++)
	{
		sum_min+=histZ[i];
		
		if(( (float)sum_min/(float)(sum)) > 0.05)
		{
			max_index1 = i;
			break;
		}
	}

	for (j=histZ.size()-1;j>0;j--)
	{
		sum_max+=histZ[j];
        if(( (float)sum_max/(float)(sum)) > 0.05)
		{
			max_index2 = j;
			break;
		}
	}

	/*
	if(max_index1 >= 0)
		hist2 = max_index1+1;
	if(max_index1 == histZ.size()-1)
		hist2 = max_index1-1;

	for(i=0; i<10; i++)
	{
		if(i!=max_index1)
		{
			if(histZ[i] >= hist2)
			{
				hist2 = histZ[i];
				max_index2 = i;
			}
		}
	}	
	*/

	if(max_index1 < max_index2)
	{
		peakZ1 = (max_index1+0.5)*interval_z+z_min;
		peakZ2 = (max_index2+0.5)*interval_z+z_min;
	}

	if(max_index1 > max_index2)
	{
		peakZ1 = (max_index2+0.5)*interval_z+z_min;
		peakZ2 = (max_index1+0.5)*interval_z+z_min;
	}

	z_distens = peakZ2 - peakZ1;
}
/*
void glwiget::GetPeakI( unsigned short min_i,unsigned short max_i,unsigned short &peakI1,unsigned short &peakI2 )
{

	//强度直方图
	QVector<int> histI(1000,0);
	int i;
	double interval_I;
	interval_I = (double)(max_i-min_i)/999;
	double coordinates[3];
	LASpoint point;
	int step = m_lasheader.number_of_point_records/100;

	for(i=0; i<m_lasheader.number_of_point_records; i++)
	{
		GetPoint(i,point,coordinates);
		int index = (point.intensity - min_i)/interval_I;
		histI[index]++;

		if(i%step == 0)
			emit notify();
	}

	int sum1,sum2;
	sum1 = sum2 = 0;
	bool b1,b2;
	b1 = b2 = true;
	for(i=0; i<1000; i++)
	{
		if(b1)
			sum1 += histI[i];
		if(b2)
			sum2 += histI[999-i];

		if(sum1 >= m_lasheader.number_of_point_records*0.03)
		{
			peakI1 = i*interval_I+min_i;
			b1 = false;
			sum1 = 0;
		}
		if(sum2 >= m_lasheader.number_of_point_records*0.03)
		{
			peakI2 = (999-i)*interval_I+min_i;
			b2 = false;
			sum2 = 0;
		}

		if(!b1 && !b2)
			break;
	}

	histI.clear();
}
*/
/*
void glwiget::paintEvent(QPaintEvent*)
{
	QPainter painter(this);
	//painter.setRenderHint(QPainter::Antialiasing);
	painter.setBrush(Qt::red);
	painter.drawRect(0,0,100,100);
	painter.end();

	makeCurrent();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glClearColor(0.0,0.0,0.0,0.0);
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0);
	textures[0] = bindTexture(QPixmap("1.PNG"));
	if (textures[0] == NULL)
	{
		return;
	}
	textures[1] = bindTexture(QPixmap("2.PNG"));
	textures[2] = bindTexture(QPixmap("3.PNG"));

	glEnable(GL_TEXTURE_2D);

	setupviewport(width(),height());

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glLoadIdentity();

	glTranslatef(-0.0,0.0,z_position);
	glTranslatef(x_position,0.0,0.0);
	glTranslatef(0.0,y_position,0.0);
	
	glRotatef(xrot,1.0,0.0,0.0);
	glRotatef(yrot,0.0,-1.0,0.0);
	glRotatef(zrot,0.0,0.0,1.0);

	glBindTexture(GL_TEXTURE_2D,textures[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0,0.0);
	glVertex3f(1.0,1.0,1.0);
	glTexCoord2f(1.0,1.0);
	glVertex3f(1.0,1.0,-1.0);
	glTexCoord2f(0.0,1.0);
	glVertex3f(-1.0,1.0,-1.0);
	glTexCoord2f(0.0,0.0);
	glVertex3f(-1.0,1.0,1.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,textures[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0,0.0);
	glVertex3f(1.0,-1.0,1.0);
	glTexCoord2f(1.0,1.0);
	glVertex3f(1.0,-1.0,-1.0);
	glTexCoord2f(0.0,1.0);
	glVertex3f(-1.0,-1.0,-1.0);
	glTexCoord2f(0.0,0.0);
	glVertex3f(-1.0,-1.0,1.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,textures[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0,1.0);
	glVertex3f(1.0,1.0,1.0);
	glTexCoord2f(0.0,1.0);
	glVertex3f(-1.0,1.0,1.0);
	glTexCoord2f(0.0,0.0);
	glVertex3f(-1.0,-1.0,1.0);
	glTexCoord2f(1.0,0.0);
	glVertex3f(1.0,-1.0,1.0);
	glEnd();
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	
}*/
