#include	<stdio.h>
#include	<stdlib.h>
#include	<math.h>
#include	"struct.h"
#include	"prototype.h"

//#define		Debug
/*------------------------------------------------------------------------------------
 CHI return Calinski-Harabasz index
//input 
 k - the number of clusters
 data - the number of data
 center - the number of center
 config - Initialize
------------------------------------------------------------------------------------*/
double CHI(int k,struct data dataset[],struct center k_center[],struct config conf[])
{
	int		i,j;													
	double	sum		= 0.0;
	double	sum2	= 0.0;
	double	CHI		= 0.0;
	double	sumDenominator  =0.0;
	double	sumMolecular	=0.0;
	//double	*v_bar=malloc(sizeof(double));
	double	*v_bar = NULL;
	v_bar = New_1D_doubleArr(v_bar,conf[0].dim);


	//-----------------------------------------------------------------
	//calculate the center of the center of all (v_bar)	
	//cal_vbar_barycentre(conf[0].k, k_center, v_bar, conf);
	cal_vbar_allPointsCentre(dataset,v_bar,conf);

	//-----------------------------------------------------------------
	//calculate Calinski-Harabasz index	
	//*******************
	//*	CHI Molecular	*
	//*******************
	
	for(i = 0; i < k; i++)
	{		
		sum = sum + k_center[i].count * pow(point_distance(k_center[i].point, v_bar, conf), 2);
	}

	sumMolecular = sumMolecular + (sum/(k-1)); 

	#ifdef	Debug
		printf("Molecular = %lf;\n",sum);
		printf("sumMolecular = %lf;\n",sumMolecular);
	#endif

	sum = 0;

	//***********************
	//*	CHI sumDenominator	*
	//***********************
	for(i = 0; i < k; i++)
	{
		for(j = 0; j < conf[0].datasize; j++)
		{
			if (dataset[j].cid == i)
			{
				sum2 = sum2 + pow(point_distance(k_center[i].point,dataset[j].point,conf),2);	
			}
		}
	}
	sumDenominator = sumDenominator + (sum2/(conf[0].datasize-k));
	#ifdef	Debug
		printf("Denominator = %lf;\n",sumDenominator);
	#endif

	sum2 = 0;

	CHI = sumMolecular / sumDenominator ;
	//printf("CHI = %lf\n", CHI);
	return CHI;
}