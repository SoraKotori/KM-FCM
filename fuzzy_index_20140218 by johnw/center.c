#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	<limits.h>
#include	<math.h>
#include	"struct.h"
#include	"prototype.h"


void	center_f1(int k,struct center k_center[],double max[],double min[],struct config conf[])
{
	int i,d;
	//srand(time(0));
	if(k >= conf[0].datasize)
	{
		printf("錯誤！k的個數必需小於資料集的個數");
	}else
	{
		//printf("使用方法1初始化中心點\n");
		for(i=0;i<k;i++)
		{
			for(d = 0;d <conf[0].dim; d++)
			{
				k_center[i].point[d]=fmod(rand()*1.0,(max[d] - min[d])*1.0)+min[d];
			}
			//printf("第%d中心：",i);
			for(d = 0;d <conf[0].dim; d++)
			{
				printf("%lf\t",k_center[i].point[d]);
			}
			printf("\n");
		}
	}
}
void	center_f2(int k,struct center k_center[],struct data dataset[],struct config conf[])
{
		int i,d,tmp;
	//	srand(time(0));
		if( k >= conf[0].datasize )
		{
				printf("錯誤！k的個數必需小於資料集的個數");
		}else
		{
				//printf("使用方法2初始化中心點\n");
				for(i = 0; i < k; i++)
				{
						tmp=rand()%conf[0].datasize+0;
						for(d = 0; d < conf[0].dim; d++)
						{
								k_center[i].point[d]=dataset[tmp].point[d];
						}
						
						//printf("第%d中心：",i);
						for( d = 0; d <	conf[0].dim; d++)
						{
								printf("%lf\t",k_center[i].point[d]);
						}
						printf("\n");
						
				}
		}
}

void	f_center(int k,struct data dataset[],struct center k_center[],struct config conf[])
{
	int i,j,d;
	double	tmp=0,sum_of_num=0;
	double	*sum_of_deno;
	//初始化
	sum_of_deno	=	(double*)malloc(k*sizeof(double));
	for(j = 0;j < k;j++)
	{
		sum_of_deno[j]=0;
	}
	//計算分母
	for(j = 0;j < k; j++)
	{
		for(i = 0;i < conf[0].datasize; i++)
		{
			sum_of_deno[j]	=	sum_of_deno[j]	+	dataset[i].u[j];
		}
	}

	//計算分子

	for(j = 0;j < k; j++)
	{
		for(d = 0;d < conf[0].dim; d++)
		{
			for(i = 0;i < conf[0].datasize; i++)
			{
				tmp	=	dataset[i].point[d]*dataset[i].u[j];
				sum_of_num	= sum_of_num+ tmp;
				//printf("%d\t%d\t%d\n",i,d,j);
			}
			k_center[j].point[d]=sum_of_num/sum_of_deno[j];
			// add by johnw on 20140218
			// output new centroids
			printf("%lf\t",k_center[j].point[d]);
			sum_of_num	=	0.0;
		}
		printf("\n");
	}
	free(sum_of_deno);
	printf("\n=================\n");
}

