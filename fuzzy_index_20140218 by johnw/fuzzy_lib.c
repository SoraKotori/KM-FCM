#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	<limits.h>
#include	<math.h>
#include	"struct.h"
#include	"prototype.h"

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
			k_center[j].max[d]= (double)_I64_MIN;
			k_center[j].min[d]= (double)_I64_MAX;
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
    //membership(k,dataset,k_center,conf);
    sum_cluster_dist(k,dataset,k_center,conf);
	cluster_max_min(k,dataset,k_center,conf);
}


/*刪除掉沒有資料的中心點*/
void delete_noData_center(struct center k_center[],struct center Old_k_center[],struct config conf[])
{
	int i,j,d;

	j=0;

//	if(conf[0].index != 16)
//	{
		for(i=0; i<conf[0].original_k; i++)
		{
			//printf("i=%d\tj=%d\n",i,j);
			//printf("Old_k_center[%d].count=%d\n",i,Old_k_center[i].count);
			//printf("---------------------------------------------------------\n");
			if(Old_k_center[i].count != 0)
			{
				for(d = 0; d<conf[0].dim; d++)
				{
					//printf("Old_k_center[%d].point[%d]=%lf\n",i,d,Old_k_center[i].point[d]);
					k_center[j].point[d] = Old_k_center[i].point[d];
					printf("k_center[%d].point[%d]=%lf\n",j,d,k_center[j].point[d]);
				}
				j++;
			}
			//printf("---------------------------------------------------------\n");
		}
	//}
	/*
	else
	{
		for(i=0; i<conf[0].original_k; i++)
		{
			//printf("i=%d\tj=%d\n",i,j);
			//printf("Old_k_center[%d].count=%d\n",i,Old_k_center[i].count);
			//printf("---------------------------------------------------------\n");
			if(Old_k_center[i].count > 3)
			{
				for(d = 0; d<conf[0].dim; d++)
				{
					//printf("Old_k_center[%d].point[%d]=%lf\n",i,d,Old_k_center[i].point[d]);
					k_center[j].point[d] = Old_k_center[i].point[d];
					printf("k_center[%d].point[%d]=%lf\n",j,d,k_center[j].point[d]);
				}
				j++;
			}
			//printf("---------------------------------------------------------\n");
		}
	}
	*/
}


/*刪除掉中心點一樣的*/
void delete_same_center(struct center k_center[],struct config conf[],int data_K)
{
	int		i,j,d,t;
	double	center_dist;
	int		samecenterflag;
	struct	center	*Old_same_k_center;
	

   //動態配置
	Old_same_k_center	=	(struct center*)malloc(data_K*sizeof(struct center));

	memcpy(Old_same_k_center, k_center,data_K*sizeof(struct center));
	//Old_same_k_center = k_center; //記憶體位址相同

	printf("Old_same_k_center\n");
	for(i = 0;i < data_K; i++)
	{
		printf("%d\t",i);
		for(d = 0; d<conf[0].dim; d++)
		{	
			printf("%lf\t",Old_same_k_center[i].point[d]);
		}
		printf("\n");
	}

	printf("k_center\n");
	for(i = 0;i < data_K; i++)
	{
		printf("%d\t",i);
		for(d = 0; d<conf[0].dim; d++)
		{	
			printf("%lf\t",k_center[i].point[d]);
		}
		printf("\n");
	}

	k_center=(struct center*)malloc(conf[0].real_k*sizeof(struct center));

	samecenterflag = 0;
	t=0;
	for(i = 0;i < data_K; i++)
	{
		for(j = i+1;j < data_K; j++)
		{
			center_dist	= point_distance(Old_same_k_center[i].point,Old_same_k_center[j].point,conf);
			//if(center_dist == 0.0)
			if(center_dist < CENTER_DIFF)
			{
				samecenterflag = 1;
				break;
			}
			else
			{
				samecenterflag = 0;
			}
			
		}
		if(samecenterflag == 0)
		{
			k_center[t].cid = t;
			for(d = 0; d<conf[0].dim; d++)
			{
				k_center[t].point[d] = Old_same_k_center[i].point[d];
				printf("k_center[%d].point[%d]=%lf\n",t,d,k_center[t].point[d]);
			}
			t++;
		}
	}
	

	printf("相同中心點刪除k_center\n");
	for(i = 0;i < conf[0].real_k; i++)
	{
		printf("%d\t",i);
		for(d = 0; d<conf[0].dim; d++)
		{	
			printf("%lf\t",k_center[i].point[d]);
		}
		printf("\n");
	}

	free(Old_same_k_center);

}