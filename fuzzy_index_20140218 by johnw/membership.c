#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	<limits.h>
#include	<math.h>
#include	"struct.h"
#include	"prototype.h"

/* 計算 membership function */
void	membership(int k,struct data dataset[],struct center k_center[],struct config conf[])
{
	int		i,j,d;
	double	**dist=	NULL;
	double	tmp=0,sum=0;
	int		flag;
	int		uindex;	//當資料點和某個中心點距離為0，紀錄是哪個中心點 （標記d(x,c)距離為0 的分群）

	//初始化
	dist	=	(double **)malloc(conf[0].datasize*sizeof(double *));
	for(i = 0;i < conf[0].datasize; i++)
	{
		dist[i]	=	(double *)malloc(k*sizeof(double));
		if(dist[i]==NULL)
		{
			printf("malloc error [%d]\n",i);
		}
	}

	//計算群到中心距離
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
		{	//判斷資料點和中心點距離為0
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
		/*//列印U矩陣，可以檢查
		for(d = 0;d < k; d++)
		{
			printf("第%d點第%d個U矩陣=%lf\n",i+1,d,dataset[i].u[d]);
		}
		*/
	}

	for(i=0;i<conf[0].datasize;i++)
	{
		free(dist[i]);
	}
	free(dist);
}



/* 初始化membership function */
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