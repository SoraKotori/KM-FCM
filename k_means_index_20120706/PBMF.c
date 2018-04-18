#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	<math.h>
#include	<limits.h>
#include	"struct.h"
#include	"prototype.h"
//#define		Debug
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

double PBMF(int k,struct data dataset[],struct center k_center[],struct config conf[])
{
	// Variable Declared
	int	i,j;
	double	dist;
	double	pbmf;
	double  Dk;
	double  E1;
	double  Jm;

	// Initialize variables
	dist = 0.0;
	pbmf = 0.0;
	Dk = (double)_I64_MIN;
	E1 = 0.0;
	Jm = 0.0;

	//calculate E1
	for(i = 0;i < 1; i++)
	{
		for(j = 0; j < conf[0].datasize; j++)
		{
			E1 = E1 + dataset[j].u[i] * point_distance(k_center[i].point,dataset[j].point,conf);

		}
	}

	//calculate Jm
	for(i = 0;i < k; i++)
	{
		for(j = 0; j < conf[0].datasize; j++)
		{
			Jm = Jm + pow(dataset[j].u[i],conf[0].m) * point_distance(dataset[j].point,k_center[i].point,conf);
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

	pbmf = (1.0/k)*(E1/Jm)*Dk;
	
	//pbmf = pow(pbmf,2);

	return pbmf;
}