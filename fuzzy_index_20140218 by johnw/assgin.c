#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	<limits.h>
#include	<math.h>
#include	"struct.h"
#include	"prototype.h"


void	assgin(int k,struct data dataset[],struct config conf[])
{
	//�ܼƫŧi
	int		i,j;
	double	max_u;


	for(i = 0;i < conf[0].datasize; i++)
	{
		max_u=0.0;
		for(j = 0;j < k; j++)
		{
			if(dataset[i].u[j] >= max_u)
			{
				max_u	=	dataset[i].u[j];
				dataset[i].cid	=	j;
			}

		}

	}
}
