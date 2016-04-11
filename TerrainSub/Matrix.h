// Matrix.h: interface for the CMatrix class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATRIX_H__9F593245_9777_4924_A99F_1B2ED46DEB3B__INCLUDED_)
#define AFX_MATRIX_H__9F593245_9777_4924_A99F_1B2ED46DEB3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DataStyle.h"

class CMatrix  
{
public:
	CMatrix();
	virtual ~CMatrix();

	void mult(double *m1, double *m2, double *result, int i_1, int j_12, int j_2);
	void transpose(double *m1, double *m2, int m, int n);
	bool inv(double a[],int n);
	void transangle(double *n);
	void CalcGaussJordan(double **pArrayA, double *pArrayB, double *pArrayX, int n);
	void Calc2DTo1D(double **pArrayA, double *pArrayB, int iRowArrayA, double iColArrayA);
	void CalcTransposeMatrix(double **pArrayA, double **pTransposeArrayA, int iRowArrayA, int iColArrayA);
	void CalcMultiply(double **pArrayA, double **pArrayB, double **pArrayC, int iRowArrayA, int iColArrayA, int iColArrayB);
	void CalcDirectionCosY(double fPhi, double fOmega, double fKappa, double **pfRotationMatrix);

};

#endif // !defined(AFX_MATRIX_H__9F593245_9777_4924_A99F_1B2ED46DEB3B__INCLUDED_)
