#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	<limits.h>
#include	<math.h>
#include	"struct.h"
#include	"prototype.h"

/* �p�� membership function */
void	membership(int k,struct data dataset[],struct center k_center[],struct config conf[])
{
	int		i,j,d;
	double	**dist=	NULL;
	double	tmp=0,sum=0;
	int		flag;
	int		uindex;	//�����I�M�Y�Ӥ����I�Z����0�A�����O���Ӥ����I �]�аOd(x,c)�Z����0 �����s�^

	//��l��
	dist	=	(double **)malloc(conf[0].datasize*sizeof(double *));
	for(i = 0;i < conf[0].datasize; i++)
	{
		dist[i]	=	(double *)malloc(k*sizeof(double));
		if(dist[i]==NULL)
		{
			printf("malloc error [%d]\n",i);
		}
	}

	//�p��s�줤�߶Z��
	for(i = 0;i < conf[0].datasize; i++)
	{
		for(j = 0;j < k; j++)
		{
			dist[i][j]	=	point_distance(dataset[i].point,k_center[j].point,conf);

		}
	}

	for(i = 0;i < conf[0].datasize; i++)
	{
		flag = 0;
		for(d = 0;d < k; d++)
		{	//�P�_����I�M�����I�Z����0
			if(dist[i][d] == 0)
			{
				flag=1;
				uindex=d;
				break;
			}
		}
		if(flag != 1)
		{
			for(d = 0;d < k; d++)
			{
				for(j = 0;j < k; j++)
				{
					tmp	=	dist[i][d]/dist[i][j];
					tmp	=	pow(tmp,2/(conf[0].m-1));
					sum	=	sum+tmp;
				}
				dataset[i].u[d]	=	1/sum;
				sum	=	0.0;
			}
		}
		else
		{
			for(d = 0;d < k; d++)
			{
				dataset[i].u[d]	= 0;
			}
			dataset[i].u[uindex]=1;
		}
		/*//�C�LU�x�}�A�i�H�ˬd
		for(d = 0;d < k; d++)
		{
			printf("��%d�I��%d��U�x�}=%lf\n",i+1,d,dataset[i].u[d]);
		}
		*/
	}

	for(i=0;i<conf[0].datasize;i++)
	{
		free(dist[i]);
	}
	free(dist);
}



/* ��l��membership function */
void	membership_initialize(int k, struct data dataset[], struct config conf[])
{
	int		i, j;
	double	q;

	srand( time(0) );
	for( i = 0; i < conf[0].datasize; i++ )
	{
		q = 0; 
		for( j = 0; j < k; j++ )
		{
			dataset[i].u[j] = 1 + rand() % 10000;
			q = q + dataset[i].u[j];
		}
		for( j = 0; j < k; j++ )
		{
			dataset[i].u[j] = dataset[i].u[j] / q;
//			printf( "dataset[%d].u[%d] = %lf\n", i, j, dataset[i].u[j] );
		}
	}
}