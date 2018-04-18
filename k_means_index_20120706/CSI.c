#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	<math.h>
#include	<limits.h>
#include	"struct.h"
#include	"prototype.h"

//#define		Debug

double	CSI(int k,struct data dataset[],struct center k_center[],struct config conf[])
{
	int		i,j,a;
	double	dist;
	double	*dist_max	=	NULL;
	double	*dist_min	=	NULL;
	double	*mole		=	NULL;
	//double	sum_dist_max	=	0.0;
	double	sum_max	=	0.0;
	double	*sum_dist_max	=	NULL;
	double	sum_dist_min	=	0.0;
	double	sum_mole		=	0.0;
	double	CSI;
	

	dist_max	=	New_1D_doubleArr(dist_max,conf[0].datasize);
	dist_min	=	New_1D_doubleArr(dist_min,conf[0].datasize);
	sum_dist_max	=	New_1D_doubleArr(sum_dist_max,k);
	mole		=	New_1D_doubleArr(mole,k);
	for(i = 0;i < conf[0].datasize; i++)
	{
		dist_max[i]		=	(double)_I64_MIN;
		dist_min[i]		=	(double)_I64_MAX;
	}
	for(j = 0;j < k; j++)
	{
		sum_dist_max[j] =	0.0;
		mole	[j]		=	0.0;
	}
	
	for(a = 0;a < k; a++)
	{
		#ifdef Debug
			printf("k=%d\n",a);
		#endif
		for(i = 0;i < conf[0].datasize; i++)
		{
			if(dataset[i].cid == a)
			{
				for(j = 0;j < conf[0].datasize; j++)
				{
					if(dataset[j].cid == a)
					{
						dist = point_distance(dataset[i].point,dataset[j].point,conf);
						dist_max[i]	= var_max(dist,dist_max[i]);
					#ifdef Debug
						printf("%d\t%d\t%lf\n",i,j,dist);
						printf("dist_max[%d]=%lf\n",i,dist_max[i]);
					#endif	
					}
				}
				sum_dist_max[a] = sum_dist_max[a] + dist_max[i];
			#ifdef Debug
				printf("sum_dist_max[%d]=%lf\n",a,sum_dist_max[a]);
			#endif
			}
		}
		if(k_center[a].count != 0)
		{
			mole[a]	 =	(1.0/k_center[a].count)	* sum_dist_max[a];
		}
		else
		{
			mole[a]	 =	0;
		}
		sum_mole	=	sum_mole	+	mole[a];
	#ifdef Debug
		printf("mole[%d]=%lf\n",a,mole[a]);
		printf("sum_mole=%lf\n",sum_mole);
	#endif	
	}

	for(j = 0;j < k; j++)
	{
		for(i = 0;i < k; i++)
		{
			if(i != j)
			{
				dist		=	point_distance(k_center[j].point,k_center[i].point,conf);
			#ifdef Debug
				printf("%d\t%d\t%lf\n",j,i,dist);
			#endif
				dist_min[j]	= var_min(dist,dist_min[j]);
			}
		}
		sum_dist_min	=	sum_dist_min	+	dist_min[j];
	#ifdef Debug
		printf("sum_dist_min = %lf\n",sum_dist_min);
	#endif
	}
	CSI		=	sum_mole/sum_dist_min;
	//printf("CSI=%lf\n",CSI);
	free(dist_max);
	free(dist_min);
	free(mole);
	return CSI;
}