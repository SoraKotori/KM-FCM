#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	<math.h>
#include	"struct.h"
#include	"prototype.h"

double FSI(int k,struct data dataset[],struct center k_center[],struct config conf[])
{
	int	i,j;
	double	sum;
	double	FSI;
	double	*v_bar = NULL;
	sum = 0.0;
	FSI = 0.0;

	v_bar = New_1D_doubleArr(v_bar,conf[0].dim);

	// Calculate vbar (Calculate the center of all centers of clusters)
	if(conf[0].vbar == 0)
	{
		cal_vbar_barycentre(k,k_center,v_bar,conf);
	}
	else if(conf[0].vbar == 0)
	{ 
		cal_vbar_gocenter(k,k_center,v_bar,conf);
	}
	else
	{
		cal_vbar_allPointsCentre(dataset,v_bar,conf);
	}
	
	for(j = 0;j < k; j++)
	{
		for(i = 0;i < conf[0].datasize;i++)
		{
			sum = sum + pow(dataset[i].u[j], conf[0].m) * pow(point_distance(k_center[j].point,dataset[i].point,conf),2);
		}
	}

	FSI = sum;

	sum = 0.0;

	for(j = 0;j < k; j++)
	{
		for(i = 0;i < conf[0].datasize;i++)
		{
			sum = sum + pow(dataset[i].u[j], conf[0].m) * pow(point_distance(k_center[j].point, v_bar, conf), 2);
		}
	}

	FSI = FSI - sum;

	free(v_bar);
	return FSI;	
}