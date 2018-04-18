#include	<stdio.h>
#include	<stdlib.h>
#include	<math.h>
#include	<limits.h>
#include	"struct.h"
#include	"prototype.h"

double SC(int k,struct data dataset[],struct center k_center[],struct config conf[])
{
	int	i,j,z;
	double	mx = (double)_I64_MIN;
	double	mi = (double)_I64_MAX;
	double	sum = 0.0;
	double	sum_pow = 0.0;//Li
	double	sum2 = 0.0;
	double	sum3 = 0.0;
	double	sumDown = 0.0;
	double	sumUp = 0.0;
	double	SC = 0.0;
	double  SC1 = 0.0;
	double  SC2 = 0.0;
	//double	*v_bar = malloc(sizeof(double));
	double	*v_bar = NULL;
	v_bar = New_1D_doubleArr(v_bar,conf[0].dim);


	//-----------------------------------------------------------------
	//calculate the center of the center of all (v_bar)	
	//cal_vbar_barycentre(conf[0].k, k_center, v_bar, conf);
	cal_vbar_allPointsCentre(dataset,v_bar,conf);


	//-----------------------------------------------------------------
	//calculate SC1
	//*******************
	//*	SC1 numerator	*
	//*******************
	
	for(i = 0; i < k; i++)
	{
		sum = sum + pow(point_distance(k_center[i].point, v_bar, conf), 2);
	}
	sumUp = sum / k;

	#if	(DEBUG_SC)
		printf("sum = %lf\n", sum);
		printf("sumUp = %lf\n", sumUp);
	#endif
	sum = 0;

	//*******************
	//*	SC1 denominator	*
	//*******************
	
	for(i = 0; i < k; i++)
	{
		for(j = 0; j < conf[0].datasize; j++)
		{
			sum2 = sum2 + pow(dataset[j].u[i],conf[0].m) * pow(point_distance(k_center[i].point,dataset[j].point,conf), 2);
			sum3 = sum3 + dataset[j].u[i];
		}
		sumDown = sumDown + (sum2 / sum3);
		sum2 = 0;
		sum3 = 0;
	}
	#if	(DEBUG_SC)
		printf("sumDown = %lf\n", sumDown);
	#endif

	SC1 = sumUp / sumDown;

	#if	(DEBUG_SC)
		printf("SC1 = %lf\n", SC1);
	#endif

	sumUp = 0.0;
	sumDown = 0.0;

	//-----------------------------------------------------------------
	//calculate SC2
	//*******************
	//*	SC2 numerator	*
	//*******************

	sum =  0.0;
	sum2 = 0.0;
	for(z=0; z < k-1; z++)
	{
		for(j=z+1; j < k; j++)
		{
			for(i=0; i < conf[0].datasize; i++)
			{
				sum = var_min(dataset[i].u[z], dataset[i].u[j]);
				sum_pow = pow(sum,2);
				sum2= sum2 + sum;
				sum3 = sum3 + sum_pow;
			#if	(DEBUG_SC)
				printf("%d\t%d\t%d\t%lf\n",z,j,i,sum);
				//printf("%d\t%d\t%d\t%lf\n",z,j,i,sum_pow);
			#endif
			}
		}
	}
	sumUp = sum3/sum2;

	#if	(DEBUG_SC)
		printf("sum2 = %lf\n", sum2);
		printf("sum3 = %lf\n", sum3);
		printf("sumUp = %lf\n", sumUp);
	#endif

	//*******************
	//*	SC2 denominator	*
	//*******************
	sum = 0.0;
	sum2 = 0.0;
	for(i=0; i < conf[0].datasize; i++)
	{
		mx = (double)_I64_MIN;
		for(z=0; z < k; z++)
		{
			mx = var_max(dataset[i].u[z],mx);
		}
	#if	(DEBUG_SC)
		printf("%d\t%d\tmx = %lf\n",i,z,mx);
	#endif
		sum = sum + pow(mx,2);	
		sum2 = sum2 + mx;
	}

	sumDown = sum / sum2;


	#if	(DEBUG_SC)
		printf("sum = %lf\n", sum);
		printf("sum2 = %lf\n", sum2);
		printf("sumDown = %lf\n", sumDown);
	#endif

	SC2 = sumUp / sumDown;
	#if	(DEBUG_SC)
		printf("SC2 = %lf\n", SC2);
	#endif
	
	//-----------------------------------------------------------------
	//calculate SC
	SC = SC1 - SC2;

	return SC;
}