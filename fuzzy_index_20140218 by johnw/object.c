#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	<limits.h>
#include	<math.h>
#include	"struct.h"
#include	"prototype.h"



double	object(int k,struct data dataset[],struct center k_center[],struct config conf[])
{
	//�ܼƫŧi
	int	i,j;
	double	dist;
	double	var,sum=0;
	//�p��U�I��U���ߪ��Z��
	for(i = 0;i < conf[0].datasize; i++)
	{
		for(j = 0;j < k; j++)
		{
			dist	=	point_distance(dataset[i].point,k_center[j].point,conf);
			var		=	pow(dataset[i].u[j],conf[0].m)*pow(dist,2);
			sum		=	sum+var;
		}
	}
	return sum;
}
