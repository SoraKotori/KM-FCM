#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	<math.h>
#include	"struct.h"
#include	"prototype.h"


double	FDI(int k,struct data dataset[],struct center k_center[],struct config conf[])
{
	int		i,j;
	double	FDI		=	0.0;
	double	dist	=	0.0;

	for(j = 0;j < k; j++)
	{
		for(i = 0;i < conf[0].datasize; i++)
		{
			dist	=	point_distance(k_center[j].point,dataset[i].point,conf);
			dist	=	dataset[i].u[j] * dist;
			FDI		=	FDI + dist;
		}
	}
	
	return FDI;
}