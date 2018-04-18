/*******************************************************************************
 *   Argument variable  
 *   dataset         = dataset variable array 
 *   conf            = config variable array   
 *
 *   Dunn_index variable
 *   i,j,a are counter  
 *   dist  are distance 
 *   min_dist are temporary minimum distance  
 *   minD  are minimum distance
 *   max_k_dist[] are temporary maximum distance  
 *	 maxD  are maximum distance
 *   conf[].k        = number of cluster
 *   conf[].datasize = number of datasize 
 *   dataset[].cid		 = cluster 
 *   di              = Dunn'sindex variable 
 ******************************************************************************/    
#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	<math.h>
#include	<limits.h>
#include	"struct.h"
#include	"prototype.h"
//#define		calcTime
//#define		Debug

double delta_Centre_ST(struct data dataset[],struct config conf[]);
double delta_Centre_S(int k,struct data dataset[],struct config conf[]);

/****************************************************************************************
*	Calculate Dunn's Index                                                              *
*****************************************************************************************/
double	DunnI(int k,struct data dataset[],struct config conf[])
{
	// Variable Declared
	double		di;
	double		molecular;	//¤À¤l
	double		denominator;//¤À¥À

	// Initialize variables
	di = 0.0;
	//printf("-----------------------------------\n");
	//printf("DunnI\n");

	// Calculate
	molecular = delta_Centre_ST(dataset,conf);
	denominator = delta_Centre_S(k,dataset,conf);
	di	= molecular / denominator;
	//di = delta_Centre_ST(dataset,conf)/delta_Centre_S(k,dataset,conf);
	
	return di;
}

/****************************************************************************************
*	Calculate the smallest distance of a different cluster of any two points            *
*****************************************************************************************/
double delta_Centre_ST(struct data dataset[],struct config conf[])
{
	// Variable Declared
	int			i,j;
	double		dist;
	double		min_dist;
	
	// Initialize variables
	dist	=	0.0;
	min_dist=	(double)_I64_MAX;

	// Calculate
	for(i = 0;i < conf[0].datasize; i++)
	{	
		for(j = i+1; j < conf[0].datasize; j++)
		{	
			if(dataset[i].cid != dataset[j].cid)
			{
				dist = point_distance(dataset[i].point,dataset[j].point,conf);
				min_dist=var_min(dist,min_dist);
			}
		}
	}

	//printf("delta_Centre_ST_Over\n");

	return min_dist;
}

/****************************************************************************************
*	1. Calculate maximum distance of the same cluster of any two points                 * 
	2. Calculate the maximum distance of all cluster                                    *
*****************************************************************************************/
double delta_Centre_S(int k,struct data dataset[],struct config conf[])
{
	// Variable Declared
	int			i,j,a;
	double		dist;
	double	*	max_k_dist = NULL;
	double		maxD;

	max_k_dist	=	New_1D_doubleArr(max_k_dist,k);

	// Initialize variables
	for(i = 0;i < k; i++)
	{
		max_k_dist[i] =	(double)_I64_MIN;
	}
	dist	=	0.0;
	maxD = (double)_I64_MIN;

	// Calculate
	for(a = 0;a < k; a++)
	{
		max_k_dist[a]=0;
		for(i = 0;i < conf[0].datasize; i++)
		{
			for(j = i+1; j < conf[0].datasize; j++)
			{
				if(dataset[i].cid == a && dataset[j].cid == a)
				{
					dist = point_distance(dataset[i].point,dataset[j].point,conf);
					max_k_dist[a]=var_max(dist,max_k_dist[a]);
				}
			}
		}
		maxD=var_max(max_k_dist[a],maxD);
	}

	free(max_k_dist);
	return maxD;
}


