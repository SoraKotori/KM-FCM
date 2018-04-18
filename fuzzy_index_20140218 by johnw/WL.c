#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	<math.h>
#include	<limits.h>
#include	"struct.h"
#include	"prototype.h"


double	WL1(int k,struct data dataset[],struct center k_center[],struct config conf[],char *filename)
{
	int	i,j;
	double	tmpu,tmpdist,tmpsum;
	double	alldist;
	double	sumU,Sum_dist_u;
	double	minVV,medianVV;
	double	E1,E2; //元素
	double	wl;

	char	tmp_Char[MAX_STRING];
	FILE    *File;
	sprintf(tmp_Char,"%s_out/WL1.csv",filename);
	File=fopen(tmp_Char,"a+");
    fprintf(File,"Cluster,E1,E2\n");
	fprintf(File,"%d",k);

	wl	=	0.0;

	Sum_dist_u =	0.0;
	for(j = 0;j < k; j++)
	{
		alldist	=	0.0;
		sumU	=	0.0;
		for(i = 0;i < conf[0].datasize; i++)
		{
			tmpu	=	pow(dataset[i].u[j],conf[0].m);
			tmpdist	=	pow(point_distance(k_center[j].point,dataset[i].point,conf),2);
			tmpsum	=	tmpu * tmpdist;
			alldist	=	alldist + tmpsum;
			sumU	=	sumU + dataset[i].u[j];
		}
		Sum_dist_u	=	Sum_dist_u + (alldist / sumU);
	}
	E1 = Sum_dist_u;


	minVV	= Min_VV(k,k_center,conf,2);
	medianVV= Median_VV(k,k_center,conf,2);


	E2 = minVV + medianVV;
	

	wl	=	E1/E2;
	
	fprintf(File,",%lf,%lf\n",E1,E2);
	fclose(File);

	return wl;	
}


//第2版WL  公式太複雜 可以用
double	WL2(int k,struct data dataset[],struct center k_center[],struct config conf[],char *filename)
{
	int	i,j;
	double	tmpu,tmpdist,tmpsum;
	double	alldist,sumdist;
	double	sumU,Sum_dist_u;
	double	avg,u;
	double	minVV,medianVV;
	//double	min_dist=	(double)_I64_MAX;
	double	min_u 	=	(double)_I64_MAX;
	double	E1,E2,E3,E4; //元素
	double	wl;

	char	tmp_Char[MAX_STRING];
	FILE    *File;
	sprintf(tmp_Char,"%s_out/WL2.csv",filename);
	File=fopen(tmp_Char,"a+");
	fprintf(File,"Cluster,E1,E2,E3,E4\n");
	fprintf(File,"%d",k);

	wl	=	0.0;


	Sum_dist_u =	0.0;
	for(j = 0;j < k; j++)
	{
		alldist	=	0.0;
		sumU	=	0.0;
		for(i = 0;i < conf[0].datasize; i++)
		{
			tmpu	=	pow(dataset[i].u[j],conf[0].m);
			tmpdist	=	pow(point_distance(k_center[j].point,dataset[i].point,conf),2);
			tmpsum	=	tmpu * tmpdist;
			alldist	=	alldist + tmpsum;
			sumU	=	sumU + dataset[i].u[j];
		}
		Sum_dist_u	=	Sum_dist_u + (alldist / sumU);
	}
	E1 = Sum_dist_u;

	minVV	= Min_VV(k,k_center,conf,2);
	medianVV= Median_VV(k,k_center,conf,2);

	E2 = minVV + medianVV;

	
	sumdist = 0.0;
	for(j = 0;j < k; j++)
	{
		alldist	=	0.0;
		for(i = 0;i < conf[0].datasize;i++)
		{
			if(dataset[i].cid == j)
			{
				tmpu	=	pow(dataset[i].u[j],2);
				tmpdist	=	pow(point_distance(k_center[j].point,dataset[i].point,conf),2);
				tmpsum	=	tmpu * tmpdist;
				alldist	=	alldist	+ tmpsum;
			}

		}
		if(k_center[j].count != 0)
		{
			avg = alldist / k_center[j].count;
		}
		else
		{
			avg = 0;
		}
		sumdist = sumdist + avg;
	}
	E3 = sumdist/k;


	for(j = 0;j < k; j++)
	{
		u = 0.0;
		for(i = 0;i < conf[0].datasize;i++)
		{
			u =	u +	pow(dataset[i].u[j],2);
		}
		min_u =	var_min(u,min_u);
	}
	E4 = min_u;
	

	wl	=	(E1/E2) * (E3/E4);
	
	fprintf(File,",%lf,%lf,%lf,%lf\n",E1,E2,E3,E4);
	fclose(File);

	return wl;	
}

//原本的第一版WL  不好的 跟XBI太像
/*
double	WL(int k,struct data dataset[],struct center k_center[],struct config conf[])
{
	int	i,j;
	double	tmpu,tmpdist,tmpsum;
	double	alldist,sumdist;
	double	avg,u;
	double	min_dist=	(double)_I64_MAX;
	double	min_u 	=	(double)_I64_MAX;
	double	E1,E2,E3,E4; //元素
	double	wl;
	
	wl	=	0.0;

	alldist	=	0.0;
	for(j = 0;j < k; j++)
	{
		for(i = 0;i < conf[0].datasize; i++)
		{
			tmpu	=	pow(dataset[i].u[j],2);
			tmpdist	=	pow(point_distance(k_center[j].point,dataset[i].point,conf),2);
			tmpsum	=	tmpu * tmpdist;
			alldist	=	alldist + tmpsum;
		}
	}
	E1 = alldist/conf[0].datasize;


	for(i = 0;i < k; i++)
	{
		for(j = 0; j < k; j++)
		{
			if(i != j)
			{
				tmpdist	=	pow( point_distance(k_center[i].point,k_center[j].point,conf), 2);
				min_dist= var_min(tmpdist,min_dist);
			}
		}
	}
	E2 = min_dist;


	alldist	=	0.0;
	sumdist = 0.0;
	for(j = 0;j < k; j++)
	{
		for(i = 0;i < conf[0].datasize;i++)
		{
			if(dataset[i].cid == j)
			{
				tmpu	=	pow(dataset[i].u[j], 1);
				tmpdist	=	pow(point_distance(k_center[j].point,dataset[i].point,conf),2);
				tmpsum	=	tmpu * tmpdist;
				alldist	=	alldist	+ tmpsum;
			}

		}
		if(k_center[j].count != 0)
		{
			avg = alldist / k_center[j].count;
		}
		else
		{
			avg = 0;
		}
		sumdist = sumdist + avg;
	}
	E3 = sumdist/k;


	for(j = 0;j < k; j++)
	{
		u = 0.0;
		for(i = 0;i < conf[0].datasize;i++)
		{
			u =	u +	pow(dataset[i].u[j],2);
		}
		min_u =	var_min(u,min_u);
	}
	E4 = min_u;
	

	wl	=	(E1/E2) * (E3/E4);
	
	return wl;	
}
*/
