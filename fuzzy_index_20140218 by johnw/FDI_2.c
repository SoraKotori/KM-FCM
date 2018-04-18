#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	<math.h>
#include	"struct.h"
#include	"prototype.h"


double	FDI2(int k,struct data dataset[],struct center k_center[],struct config conf[])
{
	int		i,j;
	double	FDI		=	0.0;
	double	dist	=	0.0;
	double	var		=	0.0;

	for(j = 0;j < k; j++)
	{
		for(i = 0;i < conf[0].datasize; i++)
		{
			dist	=	point_distance(k_center[j].point,dataset[i].point,conf);
			var		=	pow(dataset[i].u[j],conf[0].m) * pow(dist,2);
			FDI		=	FDI + var;
		}
	}
	
	return FDI;
}