#include 	<stdio.h>
#include 	<stdlib.h>
#include	<time.h>
#include	<math.h>
#include	<limits.h>
#include	"struct.h"
#include	"prototype.h"

double	point_distance(double	var1[] , double	var2[], struct config conf[])
{
	int d;
	double	dist=0.0;
	double	*tmp;
	tmp	=	(double*)malloc(conf[0].dim*sizeof(double));
	for ( d=0; d < conf[0].dim; d++)
	{
		tmp[d]	=	pow(var1[d]-var2[d],2);
	}

	for( d = 0; d < conf[0].dim; d++)
	{
		dist	=	dist+tmp[d];
	}

	dist	=	sqrt(dist);
	free(tmp);
	
	return dist;
}

//計算資料點到中心點的距離
void	data_center_dist(int k,struct center k_center[],struct data dataset[],struct config conf[])
{
	int i,j;

	for(i = 0;i < conf[0].datasize; i++)
	{
		for(j = 0;j < k; j++)
		{
			dataset[i].dist[j]	=	point_distance(dataset[i].point,k_center[j].point,conf);
		}
	}
}

//各群的距離平均
void	avg_dist(int k,struct center k_center[],struct data dataset[],struct config conf[])
{
	int i,j,count=0;
    double dist=0,sum=0;
    for(j = 0;j < k; j++)
    {
		sum=0;
        count=0;
        for(i = 0;i < conf[0].datasize; i++)
        {
            if(dataset[i].cid == j)
            {
                dist=point_distance(dataset[i].point,k_center[j].point,conf);
                sum=sum+dist;
                count++;
                //printf("%d\t%lf\t%lf\t%d\n",dataset[i].cid,dist,sum,count);
            }
        }
        k_center[j].avg_dist = sum/count;
		//if(conf[0].debug == 1)
        //printf("k %d 距離平均：%lf\n",j,k_center[j].avg_dist);
    }

}

//所有群集的距離平均的總合
double	sum_dist(int k,struct center k_center[],struct data dataset[],struct config conf[])
{
	int j;
    double sum;
    sum=0;

	//各群的距離平均
	avg_dist(k,k_center,dataset,conf);
			
    for(j = 0;j < k;j++)
    {
        //printf("%lf\n",k_center[j].avg_dist);
        sum=sum+k_center[j].avg_dist;
    }
    //printf("%lf",sum);
    return sum;
}
