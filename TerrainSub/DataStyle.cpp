// DataStyle.cpp: implementation of the CDataStyle class.
//
//////////////////////////////////////////////////////////////////////

#include "DataStyle.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDataStyle::CDataStyle()
{

}

CDataStyle::~CDataStyle()
{

}

int CDataStyle::cvx_saveMat(CvMat *mat, const char *filename)
{
    int i, j;
    FILE *fp=fopen(filename, "wt");
    if (fp != NULL)
        fprintf(fp, "%d %d\n", mat->rows, mat->cols);
    for (i = 0; i < mat->rows; i++)
    {
        for (j = 0; j < mat->cols; j++)
        {
            fprintf(fp, "%lf\t", (mat->data.db + i*mat->step / 8)[j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
    return 0;
}
