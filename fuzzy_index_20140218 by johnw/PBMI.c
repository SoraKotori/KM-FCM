#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	<math.h>
#include	<limits.h>
#include	"struct.h"
#include	"prototype.h"
/*******************************************************************************
 *   argument variable  
 *   dataset         = dataset variable array 
 *   conf            = config variable array   
 *
 *   PE_index variable
 *   i,j are counter 
 *   dataset[].u[]   = dataset's u matrix 
 *   conf[].k        = number of cluster
 *   conf[].datasize = number of datasize 
 *   sum             = final PBM value 
 ******************************************************************************/    

double PBM(int k,struct data dataset[],struct center k_center[],struct config conf[])
{
	int	i,j;
	double	dist;
	double	sum;
	double	Ent;
	double  Dk;
	double  Ek;
	double  E1;
	dist = 0.0;
	sum = 0.0;
	Ent = 0.0;
	Dk = (double)_I64_MIN;
	Ek = 0.0;
	E1 = 0.0;

	//calculate E1
	for(i = 0;i < 1; i++)
	{
		for(j = 0; j < conf[0].datasize; j++)
		{
			E1 = E1 + dataset[j].u[i] * point_distance(k_center[i].point,dataset[j].point,conf);

		}
	}

	//calculate Ek
	for(i = 0;i < k; i++)
	{
		for(j = 0; j < conf[0].datasize; j++)
		{
			Ek = Ek + dataset[j].u[i] * point_distance(k_center[i].point,dataset[j].point,conf);
		}
		
	}

	//calculate Dk
	for(i = 0;i < k; i++)
	{
		for(j = i+1; j < k; j++)
		{
				dist = point_distance(k_center[i].point,k_center[j].point,conf);
				Dk = var_max(dist,Dk);
		}
	
	}

	sum = (1.0/k)*(E1/Ek)*Dk;

	sum = sum * sum;
	
	return sum;
}
