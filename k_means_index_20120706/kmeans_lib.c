#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	<math.h>
#include    <limits.h>
#include	"struct.h"
#include	"prototype.h"


/*Initialize Uij functon*/
void	membership(int k,struct data dataset[],struct center k_center[],struct config conf[])
{
	int		i,j;


	for(i = 0;i < conf[0].datasize; i++)
	{
		for(j = 0;j < k; j++)
		{
			if(dataset[i].cid == j)
			{
				dataset[i].u[j] = 1;
			}
			else
			{
				dataset[i].u[j] = 0; 
			}
		}
	}
/*
	//列印U矩陣，可以檢查
	for(i = 0;i < conf[0].datasize; i++)
	{
		printf("dataset[%d].cid=%d\n",i,dataset[i].cid);
		for(d = 0;d < k; d++)
		{
			printf("第%d點第%d個U矩陣=%lf\n",i,d,dataset[i].u[d]);
		}	
	}
*/	

}
/*distance information of data to center include sum of distance, avg of distance, count of data point in the cluster*/
void	sum_cluster_dist(int k,struct data dataset[],struct center k_center[],struct config conf[])
{
	int	i,j;
	double	dist=0.0;
	for(j = 0;j < k; j++)
	{
		for(i = 0; i < conf[0].datasize; i++)
		{
			if(dataset[i].cid == j)
			{
				dist					=	point_distance(dataset[i].point,k_center[j].point,conf);
				k_center[j].dist_sum	=	k_center[j].dist_sum + dist;
				k_center[j].count		=	k_center[j].count+1;
			}
		}
		k_center[j].avg_dist	=	k_center[j].dist_sum / k_center[j].count;
	}
}


/*Maximum and minimum in the cluster*/
void	cluster_max_min(int k,struct data dataset[],struct center k_center[],struct config conf[])
{
	int	i,j,d;
	for(j = 0;j < k; j++)
	{
		//Initialization
		for(d = 0;d < conf[0].dim; d++)
		{
			k_center[j].max[d]=(double)_I64_MIN;
			k_center[j].min[d]=(double)_I64_MAX;
		}
		for(i = 0; i < conf[0].datasize; i++)
		{
			if(dataset[i].cid == j)
			{
				for(d = 0;d < conf[0].dim; d++)
				{
					k_center[j].max[d]=var_max(dataset[i].point[d],k_center[j].max[d]);
					k_center[j].min[d]=var_min(dataset[i].point[d],k_center[j].min[d]);
				}
			}
		}
	}
}

/*Initialize*/
void Initialize(int k,struct data dataset[],struct center k_center[],struct config conf[])
{
	int j;
	for(j = 0;j < k; j++)
    {
		k_center[j].dist_sum	=	0.0;
		k_center[j].count		=	0;
		k_center[j].avg_dist	=	0.0;
	}
	//計算歸屬函數
    membership(k,dataset,k_center,conf);
	//k_center[j].dist_sum,k_center[j].count,k_center[j].avg_dist
    sum_cluster_dist(k,dataset,k_center,conf);
	//重新計算每一群的極值
	cluster_max_min(k,dataset,k_center,conf);
}