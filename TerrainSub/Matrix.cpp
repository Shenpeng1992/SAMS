// Matrix.cpp: implementation of the CMatrix class.
//
//////////////////////////////////////////////////////////////////////

#include "Matrix.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#endif

#include <math.h>

#define PI 3.1415926535

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMatrix::CMatrix()
{

}

CMatrix::~CMatrix()
{

}

void CMatrix::transpose(double *m1, double *m2, int m, int n)  //矩阵转置m*n
{
	int i,j;
	for(i=0;i<m;i++)
		for(j=0;j<n;j++)
			m2[j*m+i]=m1[i*n+j];
		return;
		
}

void CMatrix::mult(double *m1, double *m2, double *result, int i_1, int j_12, int j_2)		//矩阵相乘
{
	int i,j,k; 
	for(i=0;i<i_1;i++)
        for(j=0;j<j_2;j++)
		{
			result[i*j_2+j]=0.0;
            for(k=0;k<j_12;k++)
				result[i*j_2+j]+=m1[i*j_12+k]*m2[j+k*j_2];
		}
		return;
		
}

bool CMatrix::inv(double a[],int n)
{ 
	int i,j,k,l,u,v;
	double d,p;
	int *is=new int[n];
    int *js=new int[n];
	for (k=0; k<=n-1; k++)
	{ 
		d=0.0;
		for (i=k; i<=n-1; i++)
		{
			for (j=k; j<=n-1; j++)
			{ 
				l=i*n+j; p=fabs(a[l]);
				if (p>d) 
				{ 
					d=p; 
					is[k]=i; 
					js[k]=j;
				}
			}
		}
		if (d+1.0==1.0)
		{ 
			delete is; 
			delete js;
			return 0;
		}
		if (is[k]!=k)
		{
			for (j=0; j<=n-1; j++)
			{ 
				u=k*n+j; v=is[k]*n+j;
				p=a[u]; a[u]=a[v]; a[v]=p;
			}
		}
		if (js[k]!=k)
		{
			for (i=0; i<=n-1; i++)
			{ 
				u=i*n+k; v=i*n+js[k];
				p=a[u]; a[u]=a[v]; a[v]=p;
			}
		}
		l=k*n+k;
		a[l]=1.0/a[l];
		for (j=0; j<=n-1; j++)
		{
			if (j!=k)
			{ 
				u=k*n+j; a[u]=a[u]*a[l];
			}
		}
		for (i=0; i<=n-1; i++)
		{
			if (i!=k)
			{
				for (j=0; j<=n-1; j++)
				{
					if (j!=k)
					{ 
						u=i*n+j;
						a[u]=a[u]-a[i*n+k]*a[k*n+j];
					}
				}
			}
		}
		for (i=0; i<=n-1; i++)
		{
			if (i!=k)
			{ 
				u=i*n+k; a[u]=-a[u]*a[l];
			}
			
		}
		
	}
	for (k=n-1; k>=0; k--)
	{ 
		if (js[k]!=k)
		{
			for (j=0; j<=n-1; j++)
			{ 
				u=k*n+j; v=js[k]*n+j;
				p=a[u]; a[u]=a[v]; a[v]=p;
			}
		}
		if (is[k]!=k)
		{
			for (i=0; i<=n-1; i++)
			{ 
				u=i*n+k; v=i*n+is[k];
				p=a[u]; a[u]=a[v]; a[v]=p;
			}
		}
	}
	delete is; 
	delete js;

	return 1;
}

//////////////////////////////////////////////////////////////////////////
//
//	转换角度，将角度转换到-P1~PI
//
/////////////////////////////////////////////////////////////////////////
void CMatrix::transangle(double *n)
{
	int i=(int)(*n/PI);
	*n-=i*PI;
	if (*n<0&&-*n>*n+PI)
		*n+=PI;
	if (*n>0&&*n>PI-*n)
		*n-=PI;
}

void CMatrix::CalcDirectionCosY(double fPhi, double fOmega, double fKappa, double **pfRotationMatrix)
{
	pfRotationMatrix[0][0]=((cos(fPhi))*(cos(fKappa)))-((sin(fPhi))*(sin(fOmega))*(sin(fKappa)));
	pfRotationMatrix[0][1]=-((cos(fPhi))*(sin(fKappa)))-((sin(fPhi))*(sin(fOmega))*(cos(fKappa)));
	pfRotationMatrix[0][2]=-(sin(fPhi))*(cos(fOmega));
	pfRotationMatrix[1][0]=(cos(fOmega))*(sin(fKappa));
	pfRotationMatrix[1][1]=(cos(fOmega))*(cos(fKappa));
	pfRotationMatrix[1][2]=-sin(fOmega);
	pfRotationMatrix[2][0]=((sin(fPhi))*(cos(fKappa)))+((cos(fPhi))*(sin(fOmega))*(sin(fKappa)));
	pfRotationMatrix[2][1]=-((sin(fPhi))*(sin(fKappa)))+((cos(fPhi))*(sin(fOmega))*(cos(fKappa)));
	pfRotationMatrix[2][2]=(cos(fPhi))*(cos(fOmega));
}

void CMatrix::CalcMultiply(double **pArrayA, double **pArrayB, double **pArrayC, int iRowArrayA, int iColArrayA, int iColArrayB)
{
	for(int i=0;i<iRowArrayA;i++)
	{
		for(int j=0;j<iColArrayB;j++)
		{
			pArrayC[i][j]=0;
		}
	}
	for(int i=0;i<iRowArrayA;i++)
	{
		for(int j=0;j<iColArrayB;j++)
		{
			for(int k=0;k<iColArrayA;k++)
			{
				pArrayC[i][j]=pArrayC[i][j]+pArrayA[i][k]*pArrayB[k][j];
			}
		}
	}
}

void CMatrix::CalcTransposeMatrix(double **pArrayA, double **pTransposeArrayA, int iRowArrayA, int iColArrayA)
{
	for(int i = 0;i < iRowArrayA; i++)
		for(int j = 0; j < iColArrayA; j++)
		{
			pTransposeArrayA[j][i] = pArrayA[i][j];
		}
}

void CMatrix::Calc2DTo1D(double **pArrayA, double *pArrayB, int iRowArrayA, double iColArrayA)
{
	for(int i = 0; i < iRowArrayA; i++)
		for(int j = 0; j < iColArrayA; j++)
			pArrayB[i+j] = pArrayA[i][j];
}

void CMatrix::CalcGaussJordan(double **pArrayA, double *pArrayB, double *pArrayX, int n)
{
	for(int k = 0;k < (n - 1);k++)
	{
		for(int i = k+1;i < n;i++)
		{
			double buff = 0.0;
			buff = pArrayA[i][k]/pArrayA[k][k];
			pArrayB[i] = pArrayB[i] - pArrayB[k] * pArrayA[i][k]/pArrayA[k][k];
			
			for(int j = k;j < n;j++)
			{
				pArrayA[i][j] = pArrayA[i][j] - pArrayA[k][j] * buff;
			}
		}
	}// 此处for循环完全结束，可循环输出上三角矩阵，如果要输出的话要定义到底是按行输出还是按列输出
	
	// 以下为高斯回带过程
	for(int m = 0; m < n; m++)
	{
		if(pArrayA[m][m] == 0)
		{
			return;
		}
	}
	
	pArrayB[n -1] = pArrayB[n -1]/pArrayA[n -1][ n -1];
	
	for(int k = n -2;k >= 0;k--)
	{
		int l = k+1;
		double temp = 0.0;
		while(l <= n -1)
		{
			temp = temp + pArrayA[k][l]*pArrayB[l];
			l++;
		}
		pArrayB[k] = (pArrayB[k] - temp)/pArrayA[k][k];
	}
	
	for(int i = 0;i <= n -1;i++)
	{
		pArrayX[i] = pArrayB[i];
	}
}
