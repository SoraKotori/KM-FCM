#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	<math.h>
#include	<limits.h>
#include	"struct.h"
#include	"prototype.h"

double	XBI(int k,struct data dataset[],struct center k_center[],struct config conf[])
{
	int	i,j;
	double	dist;
	double	sum;
	double	min_dist;
	double	XBI;
	
	sum		=	0.0;
	dist	=	0.0;
	XBI		=	0.0;
	min_dist=	(double)_I64_MAX;
	
	
	for(j = 0;j < k; j++)
	{
		for(i = 0;i < conf[0].datasize;i++)
		{
			dist	=	point_distance(k_center[j].point,dataset[i].point,conf);
			dist	=	pow(dist,2);
			dist	=	pow(dataset[i].u[j],2) * dist;
			sum		=	sum	+ dist;
		}
	}
	
	dist	=	0.0;
	for(i = 0;i < k; i++)
	{
		for(j = 0; j < k; j++)
		{
			if(i != j)
			{
				dist	=	point_distance(k_center[i].point,k_center[j].point,conf);
				dist	=	pow(dist,2);
				if(dist <= min_dist)
				{
					min_dist	=	dist;
				}
			}
		}
	}
	
	XBI		=	sum/(min_dist*conf[0].datasize);
	
	return XBI;	
}

