#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	<math.h>
#include	"struct.h"
#include	"prototype.h"


void Transpose(double **Matrix, int row, int column)
{
	int i,j;
	double **MT;

	MT = New_2D_doubleArr(MT,row,column);

	//開始轉換轉置矩陣
	for(i=0; i < row; i++)
	{
		for(j=0; j < column; j++)
		{
			MT[j][i] = Matrix[i][j];
		}
	}

#ifdef T	
	//把轉置矩陣印出來
	for(i=0; i < row, i++)
	{
		for(j=0; j < column; j++)
		{
          printf("%d ",MT[i][j]);
          printf("\n");
		}
    }
#endif
	
	for(i=0; i < row; i++)
	{
		for(j=0; j < column; j++)
		{
			Matrix[i][j] = MT[i][j];
		}
	}

#ifdef T
	//把轉置矩陣印出來
	for(i=0; i < row, i++)
	{
		for(j=0; j < column; j++)
		{
          printf("%d ",Matrix[i][j]);
          printf("\n");
		}
    }
#endif
	Free_2D_doubleArr(MT,column);
}
