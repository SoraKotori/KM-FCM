#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	<math.h>
#include	"struct.h"
#include	"prototype.h"

void cal_vbar_CS(int k, struct data dataset[],double v_bar[], struct config conf[]);

double CS(int k,struct data dataset[],struct center k_center[],struct config conf[])
{
	int	i,j;
	double	sum	=0.0;
	double	CS	=0.0;
	double	*v_bar = NULL;

	v_bar = New_1D_doubleArr(v_bar,conf[0].dim);

	// Calculate vbar (Calculate the CS_vbar)
	cal_vbar_CS(k, dataset, v_bar, conf);
		
	for(j = 0;j < k; j++)
	{
		for(i = 0;i < conf[0].datasize;i++)
		{
			sum = sum + pow(dataset[i].u[j], conf[0].m) * pow(point_distance(k_center[j].point,dataset[i].point,conf),2);
		}
	}

	CS = sum;
	sum = 0.0;

	for(j = 0;j < k; j++)
	{
		for(i = 0;i < conf[0].datasize;i++)
		{
			sum = sum + pow(dataset[i].u[j], conf[0].m) * pow(point_distance(k_center[j].point, v_bar, conf), 2);
		}
	}

	CS = CS - sum;

	free(v_bar);

	return CS;	
}


/*CSvbar*/
void cal_vbar_CS(int k, struct data dataset[], double v_bar[], struct config conf[])
{
	int d,i,j;
	double Sum_u=0.0;
	
	for(d = 0; d < conf[0].dim; d++)
	{
		v_bar[d]=0.0;
	}
	
	for(j = 0;j < k; j++)
	{
		for(i = 0;i < conf[0].datasize; i++)
		{
			Sum_u =	Sum_u + pow(dataset[i].u[j],conf[0].m);
			//printf("pow(dataset[%d].u[%d],conf[0].m)=%lf\n",i,j,pow(dataset[i].u[j],conf[0].m));
		}

	}
	//printf("Sum_u=%lf\n",Sum_u);

	for(d = 0; d < conf[0].dim; d++)
	{
		for(j = 0;j < k; j++)
		{
			for(i = 0; i < conf[0].datasize; i++)
			{
				v_bar[d] = v_bar[d] + pow(dataset[i].u[j],conf[0].m) * dataset[i].point[d];
			}
		}
		v_bar[d] = v_bar[d] / Sum_u;
		//printf("v_bar[%d]=%lf\n",d,v_bar[d]);
	}

}