#include 	<stdio.h>
#include 	<stdlib.h>
#include	<time.h>
#include	<math.h>
#include	<limits.h>
#include	"struct.h"
#include	"prototype.h"

void	center_point_f1(int k,struct center k_center[],double max[],double min[],struct config conf[])
{
	int	j,d;
	srand(time(0));
	if(k > conf[0].datasize)
	{
		printf("錯誤！k的個數必需小於資料集個數");
	}
	else
	{
		for(j = 0;j < k; j++)
		{
			for(d = 0; d < conf[0].dim; d++)
			{
				//k_center[j].point[d]=fmod(rand(),(max[d] - min[d]))+min[d];
				//k_center[j].point[d]=fmod(rand()/1.0,(max[d] - min[d])/1.0)+min[d];
				k_center[j].point[d]=(double)fmod(rand(),(max[d] - min[d])) / 6.6 + (double)min[d];
			}
		}
	}
}

void center_point_f2(int k,struct center k_center[],struct data dataset[],struct config conf[])
{
		int i,d,tmp;
		srand(time(0));
		if( k <= conf[0].datasize )
		{
			for(i = 0; i < k; i++)
			{
				//tmp=rand()%conf[0].datasize+1;
				tmp=rand()%conf[0].datasize;
				//printf("tmp=%d",tmp);
				k_center[i].cid = i;
				for(d = 0; d <  conf[0].dim; d++)
				{
					k_center[i].point[d] = dataset[tmp].point[d];
				}
				/*
				printf("第%d中心：",i);
				for( d = 0; d <conf[0].dim; d++)
				{
						printf("%lf\t",k_center[i].point[d]);
				}
				*/
				//printf("\n");
			}
		}
		else
		{
			printf("錯誤！k的個數必需小於資料集的個數");
		}
}


void new_center(int k,struct center k_center[],struct config conf[])
{
	int j,d;
	for(j = 0;j < k; j++)
	{
		for(d = 0; d < conf[0].dim; d++)
		{
			k_center[j].point[d] = (k_center[j].max[d] + k_center[j].min[d])/2;
		}
	}

}

void new_center_data(int k,struct center k_center[],struct data dataset[],struct config conf[])
{
	int i,j,d;
	double *sum_data;

	sum_data	=	(double*)malloc(conf[0].dim*sizeof(double));

	for(j = 0;j < k; j++)
	{
		for(d = 0; d < conf[0].dim; d++)
		{
			sum_data[d] = 0.0;
		}
		for(i = 0;i < conf[0].datasize; i++)
		{
			if(dataset[i].cid == j)
			{
				for(d = 0; d < conf[0].dim; d++)
				{
					sum_data[d] = sum_data[d] + dataset[i].point[d];
				}	
			}
		}
		for(d = 0; d < conf[0].dim; d++)
		{
			k_center[j].point[d] = (double)sum_data[d] / k_center[j].count;
		}	
	}

	free(sum_data);

}
/*double gaussian_rand_gather(double sigma)
{
    const gsl_rng_type * T;
    gsl_rng * r;
    double G_rand;
    int n=1;

    gsl_rng_env_setup();

    T = gsl_rng_default;
    r = gsl_rng_alloc (T) ;
    gsl_rng_set(r, time(NULL));
    G_rand = gsl_ran_gaussian  (r , sigma );

    gsl_rng_free (r);
    return G_rand;
}

double	center_gussian(int k,struct data dataset[],struct center k_center[],struct config conf[],double d_max[],double d_min[])
{
	int i,j,d,tmp;
	double	*sigma;
	srand(time(0));
	sigma	=	(double*)malloc(conf[0].dim*sizeof(double));
	for(j = 0;j < k;j++)
	{
		for(d = 0;d < conf[0].dim; d++)
		{
			sigma[d]				=	(k_center[j].max[d] + k_center[j].min[d])/4;
			k_center[j].point[d]	=	k_center[j].point[d]+gaussian_rand_gather(sigma[d]);
			while(1)
			{
    			if(k_center[j].point[d] >= d_max[d])
    			{
                    	tmp=rand()%conf[0].datasize+1;
						k_center[i].point[d]=dataset[tmp].point[d];
						printf("now var=%lf\t max_var=%lf\n",k_center[i].point[d],d_max[d]);
                }else if(k_center[j].point[d] < d_min[d])
                {
                        tmp=rand()%conf[0].datasize+1;
						k_center[i].point[d]=dataset[tmp].point[d];
						printf("now var=%lf\t min_var=%lf\n",k_center[i].point[d],d_min[d]);

                }else
                {
                    break;
                }
            }
		}
	}

	free(sigma);
}
*/
