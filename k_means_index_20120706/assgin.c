#include 	<stdio.h>
#include 	<stdlib.h>
#include	<time.h>
#include	<math.h>
#include	<limits.h>
#include	"struct.h"
#include	"prototype.h"


void	assign(int k,struct data dataset[],struct config conf[])
{
	int		i,j ;
	double	min_distance;

	
	
	for(i = 0;i < conf[0].datasize; i++)
	{
		min_distance=(double)_I64_MAX;
		for(j = 0;j < k; j++)
		{
			if(dataset[i].dist[j] <= min_distance)
			{
				min_distance	=	dataset[i].dist[j];
				dataset[i].cid	=	j;
			}
		}
	}

}

/*
double	assign(int i,int j,struct data dataset[],double distance,double min_distance)
{
	if(distance	<	min_distance)
	{
		min_distance=distance;
        dataset[i].cid=j;
	}
	//printf("dataset[%d].cid=%d\n",i,j);
	
	return min_distance;
}
*/