#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	<math.h>
#include	"struct.h"
#include	"prototype.h"


double	DSI(int k,struct data dataset[],struct center k_center[],struct config conf[])
{
	int		i,j;
	double	dist;
	double	DSI=0.0;
/*
	for(j = 0;j < k; j++)
	{
		for(i = 0;i < conf[0].datasize; i++)
		{
			dist	=	point_distance(k_center[j].point,dataset[i].point,conf);
			DSI		=	DSI + dist;
		}
	}
*/
	for(i = 0;i < conf[0].datasize; i++)
	{
		for(j = 0;j < k; j++)
		{
			DSI	 =	DSI + dataset[i].dist[j];
		}
	}

	return DSI;

}
