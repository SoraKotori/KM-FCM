#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	<limits.h>
#include	<math.h>
#include	"struct.h"
#include	"prototype.h"

/*vbar use barycenter*/
void cal_vbar_barycentre(int k,struct center k_center[],double v_bar[], struct config conf[])
{
	int d,j;

	for(d = 0; d < conf[0].dim; d++)
	{
		v_bar[d]=0.0;
	}

	for(d = 0; d < conf[0].dim; d++)
	{

		for(j = 0; j < k; j++)
		{
			v_bar[d] = v_bar[d] + k_center[j].point[d];
		}
		v_bar[d] = v_bar[d] / k;
	}
}

/*vbar use gocenter*/
void cal_vbar_gocenter(int k,struct center k_center[],double v_bar[], struct config conf[])
{
	int j,d;
	double	*c_max;
	double	*c_min;
	c_max	=	malloc(conf[0].dim*sizeof(double));
	c_min	=	malloc(conf[0].dim*sizeof(double));
	for(j = 0; j < conf[0].dim; j++)
	{
		v_bar[j]=0.0;
		c_max[j]= (double)_I64_MIN;
		c_min[j]= (double)_I64_MAX;
	}

	for(d = 0;d < conf[0].dim; d++)
	{

		for(j = 0; j < k; j++)
		{
			c_max[d]	=	var_max(k_center[j].point[d],c_max[d]);
			c_min[d]	=	var_min(k_center[j].point[d],c_min[d]);
		}
		v_bar[d] = (c_max[d] + c_min[d]) / 2;
	}
	free(c_max);
	free(c_min);
}

/*vbar - the center of all points*/
void cal_vbar_allPointsCentre(struct data dataset[],double v_bar[], struct config conf[])
{
	int d,i;
	
	for(d = 0; d < conf[0].dim; d++)
	{
		v_bar[d]=0.0;
	}
	
	for(d = 0; d < conf[0].dim; d++)
	{
		for(i = 0; i < conf[0].datasize; i++)
		{
			v_bar[d] = v_bar[d] + dataset[i].point[d];
		}
		v_bar[d] = v_bar[d] / conf[0].datasize;
	}
}


/*-------------------------------------CVI使用的Function------------------------------------*/

/*計算兩兩中心點距離之最小距離*/
double	Min_VV(int k,struct center k_center[],struct config conf[],int PowerD)
{
	int		i,j;
	double	dist	=	0.0;
	double	min_dist;

	min_dist	= (double)_I64_MAX;
	
	for(i = 0;i < k; i++)
	{
		for(j = 0; j < k; j++)
		{
			if(i != j)
			{
				dist	=	pow( point_distance(k_center[i].point,k_center[j].point,conf), PowerD);
				min_dist = var_min(dist,min_dist);
				//printf("dist = %lf\n",dist);
				//printf("min_dist = %lf\n",min_dist);
			}
		}
	}
	

	return min_dist;
}

/*計算兩兩中心點距離之中位數*/
double	Median_VV(int k,struct center k_center[],struct config conf[],int PowerD)
{
	// Variable Declared
	int		i,j,t;
	double	*	VV_dist =	NULL;
	int		number;
	int		median_index;
	double	median_dist;

	// Initialize variables
	number = ( (1+(k-1)) * (k-1) ) / 2; 

	//printf("number=%d\n",number);

	VV_dist = New_1D_doubleArr(VV_dist,number);

	for(i = 0;i < number; i++)
	{
		VV_dist[i] = 0.0;
	}

	t=0;
	for(i = 0;i < k; i++)
	{
		
		for(j = i+1; j < k; j++)
		{
			VV_dist[t]	=	pow( point_distance(k_center[i].point,k_center[j].point,conf), PowerD);
			//printf("VV_dist[%d] = %lf\n",t,VV_dist[t]);
			t++;
		}
	}
	
	//printf("t=%d\n",t);
	//泡泡排序法
	quicksort_InputBuffer(t, VV_dist);

	median_index = (int)number/2;
	//printf("median_index=%d\n",median_index);
	median_dist = VV_dist[median_index];
	//printf("median_dist=%lf\n",median_dist);
	
	free(VV_dist);


	return median_dist;
}



/*--------------------------- Quicksort Population (small to big)---------------------------*/
void    quicksort_InputBuffer(int size, double InputBuffer[])
{
       int pass; /* passes counter */
       int i;    /* comparisons counter */
       double hold; /* temporary location used to swap array elements */
       int order = FALSE;
       int size2;

       size2 = size - 1;

       for (pass = 1; pass < size && order !=TRUE; pass++)
       {
               order = TRUE;    //assume that the order is correct

               for (i = 0; i < size2; i++)
               {
                       if (InputBuffer[i] > InputBuffer[i + 1])
                       {
                               hold = InputBuffer[i];
                               InputBuffer[i] = InputBuffer[i + 1];
                               InputBuffer[i + 1] = hold;

                               order = FALSE; // order is incorrect
                       }
               }
       }
}
/*------------------------- End Quicksort Population (small to big)-------------------------*/
