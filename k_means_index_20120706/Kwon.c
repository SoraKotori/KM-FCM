/*2010.12.10*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	<math.h>
#include	<limits.h>
#include	"struct.h"
#include	"prototype.h"

//#define		calcTime
//#define		Debug


/* Kwon extends the index of Xie and Beni's validity function */
double	Kwon(int k,struct data dataset[],struct center k_center[],struct config conf[])
{
	// Variable Declared
	int		i,j;
	double	dist;
	double	*v_bar = NULL;
	double	sum;
	double	sumF;
	double	sumB;
	double	min_dist;
	double	Kwon;

#ifdef calcTime
	float	c1, c2;//Time
#endif
	v_bar = New_1D_doubleArr(v_bar,conf[0].dim);

	// Initialize variables
	sum		=	0.0;
	sumF	=	0.0;
	sumB	=	0.0;
	dist	=	0.0;
	Kwon		=	0.0;
	min_dist=	(double)_I64_MAX;
	
#ifdef calcTime
	c1=clock();
#endif

	for(i = 0;i < conf[0].dim; i++)
	{
		v_bar[i] = 0.0;
	}

//---------------------------------------------------------------------------------------------
//  Calculate Numerator
//---------------------------------------------------------------------------------------------

//Formula Forward
	//for(k = 0;k < conf[0].k; k++)
	for(i = 0;i < conf[0].datasize; i++)
	{
		//for(i = 0;i < conf[0].datasize;i++)
		for(j = 0;j < k; j++)		
		{
			dist	=	pow(dataset[i].u[j],2) * pow( point_distance(dataset[i].point, k_center[j].point,conf), 2);
			sumF		=	sumF	+ dist;	
		}
	}
#ifdef Debug
	printf("\nFormula Forward = %lf\n",sumF);
#endif

//Formula Back
	// Calculate vbar (Calculate the center of all points)
	cal_vbar_allPointsCentre(dataset,v_bar,conf);

	for(j = 0; j < k; j++)
	{
		sumB = sumB + pow( point_distance(k_center[j].point, v_bar, conf), 2 );
	}

#ifdef Debug
	printf("\nCalculate vbar = ( %lf, %lf)\n",v_bar[0],v_bar[1]);
	printf("\nFormula Back sum= %lf\n",sumB);
#endif
	sumB = sumB / k;

#ifdef Debug
	printf("\nsumB = %lf\n",sumB);
#endif

	sum = sumF + sumB;

#ifdef Debug
	printf("\nsum = %lf\n",sum);
#endif

//---------------------------------------------------------------------------------------------
//  Calculate Denominator
//---------------------------------------------------------------------------------------------	
	dist = 0.0;
	for(j = 0; j < k; j++)
	{
		dist = 0.0;
		for(i = 0; i< k; i++)
		{
			if(i != j)
			{
				dist = pow( point_distance(k_center[i].point,k_center[j].point,conf), 2);

				if(dist <= min_dist)
				{
					min_dist = dist;
				}
			}
		}
	}

#ifdef Debug
	printf("\nmin_dist = %lf\n",min_dist);
#endif

	Kwon =	sum/min_dist;

#ifdef calcTime
	c2=clock();
	printf("\nKwon總共花費時間：%g秒\n",(c2-c1)/CLK_TCK);
#endif

	free(v_bar);
	return Kwon;	
}

