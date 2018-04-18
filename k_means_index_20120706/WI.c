/*2010.12.27*/
#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	<math.h>
#include	<limits.h>
#include	"struct.h"
#include	"prototype.h"
//#define		calcTime
//#define		Debug
//#define		IndexW

/****************************************************************************************
*	Calculate Minimum W's Index                                                         *
*****************************************************************************************/
void MinW (double WiV [],struct config conf[],char *filename)
{
	// Variable Declared
	int	i;
//	double	wi;
	double	MinW;
	int		MinW_k;
	//寫檔
	char	TMP[256]="";
    FILE    *f;
	sprintf(TMP,"%s_out/WIndex_Result.txt",filename);
    f=fopen(TMP,"a+");

	// Initialize variables
	MinW = (double)_I64_MAX;

	for(i=2;i<=conf[0].max_k;i++)
	{	
		if(WiV [i] < MinW)
		{
			MinW = WiV [i];
			MinW_k = i;
		}
	}

#ifdef Result
	printf("Min_WI[%d] = %lf\n",MinW_k,MinW);
	printf("分%d群最好!!!\n",MinW_k);
#endif

	fprintf(f,"Min_WI[%d] = %lf\n",MinW_k,MinW);
	fprintf(f,"分%d群最好!!!\n",MinW_k);
	fclose(f);
}
/****************************************************************************************
*	Calculate W's Index                                                                 *
*****************************************************************************************/
void	WI(double VarV [], double SepV [], double WiV [],struct config conf[],char *filename)
{
	// Variable Declared
	int	i;
	double	wi;
	double	MaxV;
	//int		MaxV_k;
	double	MaxS;
	//int		MaxS_k;
	double	VarN;
	double	SepN;

#ifdef calcTime
	float	c1, c2;//Time
#endif
/*========================寫檔=========================*/
	char	TMP[256]="";
    FILE    *f;
	//sprintf(TMP,"%s_out/WIndex_Result.txt",filename);
	sprintf(TMP,"%s_out/WIndex_Value.csv",filename);
    f=fopen(TMP,"a+");
/*=====================================================*/

	// Initialize variables
	wi = 0.0;
	MaxV = (double)_I64_MIN;
	MaxS = (double)_I64_MIN;
	VarN = 0.0;
	SepN = 0.0;

#ifdef calcTime
	c1=clock();
#endif
#ifdef Debug
	printf("----------------WI----------------\n");
#endif

	// Calculate MAX Var & MAX Sep
	for(i=2;i<=conf[0].max_k;i++)
	{
		MaxV = var_max(VarV[i],MaxV);
		/*if(var_max(VarV[i],MaxV))
		{
			MaxV_k = i;
		}*/
		MaxS = var_max(SepV[i],MaxS);

#ifdef IndexW
	printf("VarV[%d] = %lf\n",i,VarV[i]);
	//printf("MaxV_k = %d\n",MaxV_k);
	//printf("SepV[%d] = %lf\n",i,SepV[i]);
#endif
	}

#ifdef IndexW
	printf("MaxV = %lf\n",MaxV);
#endif

	// Calculate WI
	for(i=2;i<=conf[0].max_k;i++)
	{	
		VarN = VarV[i] / MaxV;
		SepN = SepV[i] / MaxS;
		WiV[i] = VarN / SepN;
	}

#ifdef Result
	for(i=2;i<=conf[0].max_k;i++)
	{	
		printf("WI[%d] = %lf\n",i,WiV[i]);
	}
#endif
	/*
	for(i=2;i<=conf[0].max_k;i++)
	{	
		fprintf(f,"WI[%d] = %lf\n",i,WiV[i]);
	}	
	
	 for(i=2;i<=conf[0].max_k;i++)
	{	
		fprintf(f,"%d,%lf\n",i,WiV[i]);
	}
	*/
	for(i=2;i<=conf[0].max_k;i++)
	{	
		fprintf(f,"%d,",i);
	}
	fprintf(f,"\n",i);
	for(i=2;i<=conf[0].max_k;i++)
	{	
		fprintf(f,"%lf,",WiV[i]);
	}

#ifdef calcTime
	c2=clock();
	printf("\nWI總共花費時間：%g秒\n",(c2-c1)/CLK_TCK);
#endif
	fclose(f);
}

/****************************************************************************************
*	Calculate the variation measure                                                     *
*****************************************************************************************/
double Var(int k, struct data dataset[],struct center k_center[],struct config conf[],char *filename)
{
	// Variable Declared
	int		i,j;
	int		noC;
	double	*v_bar = NULL;
	double	dist;
	double	beta;
	double	sum;
	double	var;
	//寫檔
	char	TMP[256]="";
    FILE    *f;
	sprintf(TMP,"%s_out/WIndex_DataNumber.txt",filename);
    f=fopen(TMP,"a+");

	v_bar = New_1D_doubleArr(v_bar,conf[0].dim);

	// Initialize variables
	for(i = 0;i < conf[0].dim; i++)
	{
		v_bar[i] = 0.0;
	}
	dist	=	0.0;
	beta	=	0.0;
	sum	=	0.0;
	var	=	0.0;
	noC	=	0;

	// Calculate vbar (Calculate the center of all points)
	cal_vbar_allPointsCentre(dataset,v_bar,conf);

	// Calculate beta
	for(i = 0;i < conf[0].datasize; i++)
	{
		beta = beta + pow( point_distance(dataset[i].point, v_bar, conf), 2 );
	}
	beta = pow( (beta / conf[0].datasize), -1 );

#ifdef Debug
	printf("Beta = %lf\n",beta);
#endif

	fprintf(f,"The number of k = %d\n",k);
/*Calculate Var*/
	for(i = 0;i < k; i++)
	{
		for(j = 0; j < conf[0].datasize; j++)
		{
            //Calculate Distance(Use exponential function)
			dist=sqrt( 1 - exp( ( -1 * beta * pow(point_distance(dataset[j].point, k_center[i].point, conf),2) ) ) );
		#ifdef Debug
			printf("i=%d,j=%2d  Exponential Distance = %lf\n",i,j,dist);
			printf("dataset[%d].u[%d] = %lf\n",j,i,dataset[j].u[i]);
		#endif
			if(k_center[i].count == 0)
			{
			#ifdef Result
				printf("分%d群時，第%d群，無資料\n",k,i+1);
			#endif
				fprintf(f,"分%d群時，第%d群，無資料\n",k,i+1);
				sum = sum + 0;
				noC	= noC + 1;
				break;
			}
			else
			{
				sum = sum + ( dataset[j].u[i] * pow(dist,2) ) / k_center[i].count;
			}
		#ifdef Debug
			printf("dataset[j].u[i] * pow(dist,2) = %lf\n",dataset[j].u[i] * pow(dist,2));
			printf("k_center[%d].count = %d\n", i, k_center[i].count);
			//printf("( dataset[%d].u[%d] * pow(dist,2) ) / k_center[%d].count = %lf\n",j,i,i,(( dataset[j].u[i] * pow(dist,2) ) / k_center[i].count));
			printf("sum = %lf\n",sum);
		#endif
		}
	}

#ifdef Debug
	printf("$sum = %lf\n",sum);
#endif

	var = sum * sqrt( (double)k+1 / k-1 );

#ifdef Debug
	printf("var = %lf\n",var);
#endif

#ifdef Result
	printf("總共%d群，沒有資料\n",noC);
	printf("這應該屬於%d群\n",k-noC);
#endif
	fprintf(f,"總共%d群，沒有資料\n",noC);
	fprintf(f,"這應該屬於[ %d ]群\n",k-noC);
	fprintf(f,"-----------------------------------------\n");
	

	fclose(f);
	free(v_bar);
	return var;
}

/****************************************************************************************
*	Calculate the separation measure                                                    *
*****************************************************************************************/
double Sep(int k, struct data dataset[],struct center k_center[],struct config conf[])
{
	// Variable Declared
	int		i,j,a;
	double	dist;
	double	* min_u = NULL;
	double	max_u;
	double	sep;

	min_u	=	New_1D_doubleArr(min_u,conf[0].datasize);

	// Initialize variables
	for(i = 0;i < conf[0].datasize; i++)
	{
		min_u[i] =	(double)_I64_MAX;
	}
	max_u	=	(double)_I64_MIN;
	dist	=	0.0;
	sep		=	0.0;

	// Calculate Similarity 
	for(a = 0;a < conf[0].datasize; a++)
	{
		for(i = 0;i < k; i++)
		{
			for(j = i+1; j < k; j++)
			{
				min_u[a] = var_min(dataset[a].u[i],dataset[a].u[j]);
			#ifdef Debug
				printf("a=%d , i=%d, j=%d\t",a,i,j);
				printf("min_u[%d] = %lf\n",a,min_u[a]);
			#endif
			}
		}

		#ifdef Debug
				printf("#min_u[%d] = %lf\n",a,min_u[a]);
		#endif
		max_u = var_max(min_u[a],max_u);
	}	

#ifdef Debug
	printf("max_u = %lf\n",max_u);
#endif

	sep = 1 - max_u;

	free(min_u);
	return sep;
}


