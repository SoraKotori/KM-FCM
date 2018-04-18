#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	<math.h>
#include	<limits.h>
#include	"struct.h"
#include	"prototype.h"
//#define		calcTime

double	PCAES_k(int cnt_k,int k,struct data dataset[],struct center k_center[],struct config conf[]);
double	uM(int k,struct data dataset[],struct config conf[]);
double	BetaT(int k,struct center k_center[],struct config conf[]);

/****************************************************************************************
*	Calculate Partition coefficient and exponential separation (PCAES) index            *                                                                      *
*****************************************************************************************/
double	PCAESI(int k,struct data dataset[],struct center k_center[],struct config conf[])
{
	// Variable Declared
	int cnt_k;
	double PCAES;

#ifdef calcTime
	float	c1, c2;//Time
#endif

	// Initialize variables
	PCAES = 0.0;

	
#ifdef calcTime
		c1=clock();
#endif

	for(cnt_k = 0; cnt_k < k;  cnt_k++)
	{
		PCAES = PCAES + PCAES_k(cnt_k,k,dataset,k_center,conf);
	}
    
#ifdef calcTime
		c2=clock();
		printf("\n總共花費時間：%g秒\n",(c2-c1)/CLK_TCK);
#endif

	return PCAES;
}

/****************************************************************************************
*	Calculate PCAES_k                                                                   *
*****************************************************************************************/
double	PCAES_k(int cnt_k,int k,struct data dataset[],struct center k_center[],struct config conf[])
{
// Variable Declared
	int		i;
	double	um;
	double	betaT;
	double	pcaes_a;
	double	pcaes_b;
	double	dist;
	double	min_center_dist;
	double	sum;
	double	pcaes;

// Initialize variables
	pcaes_a	=	0.0;
	pcaes_b	=	0.0;
	dist	=	0.0;
	min_center_dist =	(double)_I64_MAX;
	sum		=	0.0;

//---------------------------------------------------------------------------------------------
//  Formula Forward
//---------------------------------------------------------------------------------------------
	// Calculate uM
	um = uM(k,dataset,conf);
	
	for(i = 0;i < conf[0].datasize;i++)
	{
			pcaes_a	= pcaes_a + ( pow(dataset[i].u[cnt_k],2) / um );
	}

//---------------------------------------------------------------------------------------------
//  Formula Back
//---------------------------------------------------------------------------------------------
	for(i = 0; i < k; i++)
	{
		if(i != cnt_k)
		{
			dist =	pow( point_distance(k_center[cnt_k].point,	k_center[i].point,	conf),	2 );
			min_center_dist	= var_min(dist,min_center_dist);
		}
	}
	// Calculate BetaT
	betaT = BetaT(k,k_center,conf);
	pcaes_b	= exp( (-1) * ( min_center_dist / betaT ) );
//---------------------------------------------------------------------------------------------
//  Formula
//---------------------------------------------------------------------------------------------
	pcaes =	pcaes_a - pcaes_b;

	return pcaes;
}

/****************************************************************************************
*	Calculate uM                                                                        *
*****************************************************************************************/
double	uM(int k,struct data dataset[],struct config conf[])
{
	// Variable Declared
	int		i,j;
	double	u;
	double	min_u;

	// Initialize variables
	u = 0.0;
	min_u	=	(double)_I64_MAX;


	for(j = 0;j < k; j++)
	{
		u = 0.0;
		for(i = 0;i < conf[0].datasize;i++)
		{
			u =	u +	pow(dataset[i].u[j],2);
	
		}
		min_u =	var_min(u,min_u);
	}

	return min_u;
}

/****************************************************************************************
*	Calculate Beta_T                                                                    *
*****************************************************************************************/
double	BetaT(int k,struct center k_center[],struct config conf[])
{
	// Variable Declared
	int		i,j;
	double	*	v_bar =	NULL;
	double		sum;

	v_bar = New_1D_doubleArr(v_bar,conf[0].dim);

	// Initialize variables
	sum		=	0.0;
	for(i = 0;i < conf[0].dim; i++)
	{
		v_bar[i] = 0.0;
	}

	// Calculate vbar (Calculate the center of all centers of clusters)
	cal_vbar_barycentre(k,k_center,v_bar,conf);


	for(j = 0;j < k; j++)
	{
		sum	= sum + pow( point_distance(k_center[j].point, v_bar, conf), 2 );
	}

	sum = sum / k;
	
	free(v_bar);

	return sum;
}
