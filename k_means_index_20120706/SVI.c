/*2011.04.08*/
#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	<math.h>
#include	<limits.h>
#include	"struct.h"
#include	"prototype.h"
//#define		calcTime
//#define		Debug
//#define IndexSV

/****************************************************************************************
*	Calculate Minimum SV's Index                                                        *
*****************************************************************************************/
void MinSV (double SViV[],struct config conf[],char *filename)
{
	// Variable Declared
	int	i;
	double	MinSV;
	int		MinSV_k;

/*========================寫檔=========================*/
	char	TMP[256]="";
    FILE    *f;
	sprintf(TMP,"%s_out/SVIndex_Result.txt",filename);
    f=fopen(TMP,"a+");
/*=====================================================*/

	// Initialize variables
	MinSV = (double)_I64_MAX;

	for(i=2;i<=conf[0].max_k;i++)
	{	
		if(SViV[i] < MinSV)
		{
			MinSV = SViV[i];
			MinSV_k = i;
		}
	}
#ifdef Result
	printf("Min_SVI[%d] = %lf\n",MinSV_k,MinSV);
	printf("分%d群最好!!!\n",MinSV_k);
#endif
	fprintf(f,"Min_SVI[%d] = %lf\n",MinSV_k,MinSV);
	fprintf(f,"分%d群最好!!!\n",MinSV_k);
	fclose(f);
}

/****************************************************************************************
*	Calculate SV's Index                                                                *
*****************************************************************************************/
//double	SVI(int k,struct data dataset[],struct center k_center[],struct config conf[])
void SVI(double UnderV[], double OverV[], double SViV[],struct config conf[],char *filename)
{
	// Variable Declared
	int		i;
	double	svi;
	double	MaxU;
	int		MaxU_k;
	double	MaxO;
	int		MaxO_k;
	double	MinU;
	int		MinU_k;
	double	MinO;
	int		MinO_k;
	double	UnderN;
	double	OverN;
/*========================寫檔=========================*/
	char	TMP[256]="";
    FILE    *f;
	sprintf(TMP,"%s_out/SVIndex_Value.csv",filename);
    f=fopen(TMP,"a+");
/*=====================================================*/

#ifdef calcTime
	clock_t start_time, end_time;
#endif

	// Initialize variables
	svi = 0.0;
	MaxU = (double)_I64_MIN;
	MaxO = (double)_I64_MIN;
	MinU = (double)_I64_MAX;
	MinO = (double)_I64_MAX;
	UnderN = 0.0;
	OverN = 0.0;

#ifdef calcTime
	start_time = clock();  /* mircosecond */
#endif

#ifdef Debug
	printf("-------------SVI-------------\n");
	//printf("Vu = %lf\n",Under(k,dataset,k_center,conf));
	//printf("Vo = %lf\n",Over(k,k_center,conf));
#endif


	// Calculate MAX Under & MAX Over
	for(i=2;i<=conf[0].max_k;i++)
	{
		if(UnderV[i] > MaxU)
		{
			MaxU = UnderV[i];
			MaxU_k = i;
		}
		
		if(UnderV[i] < MinU) 
		{
			MinU = UnderV[i];
			MinU_k = i;
		}
		
		if(OverV[i] > MaxO)
		{
			MaxO = OverV[i];
			MaxO_k = i;
		}
		
		if(OverV[i] < MinO) 
		{
			MinO = OverV[i];
			MinO_k = i;
		}
/*
		MaxU = var_max(UnderV[i],MaxU);
		MaxO = var_max(OverV[i],MaxO);
		MinU = var_min(UnderV[i],MinU);
		MinO = var_min(OverV[i],MinO);
*/
#ifdef IndexSV
	printf("UnderV[%d] = %lf\n",i,UnderV[i]);
	printf("OverV[%d] = %lf\n",i,OverV[i]);
#endif
	}

#ifdef IndexSV
	printf("MaxU[%d] = %lf\n",MaxU_k,MaxU);
	printf("MinU[%d] = %lf\n",MinU_k,MinU);
	printf("MaxO[%d] = %lf\n",MaxO_k,MaxO);
	printf("MinO[%d] = %lf\n",MinO_k,MinO);
#endif

	// Calculate SVI
	for(i=2;i<=conf[0].max_k;i++)
	{	
		UnderN = (double)(UnderV[i] -  MinU) / (MaxU - MinU);
		OverN = (double)(OverV[i] -  MinO) / (MaxO - MinO);
		SViV[i] = UnderN + OverN;
	}

#ifdef IndexSV
	printf("UnderN = %lf\n",UnderN);
	printf("OverN = %lf\n",OverN);
#endif

#ifdef Result
	for(i=2;i<=conf[0].max_k;i++)
	{	
		printf("SVI[%d] = %lf\n",i,SViV[i]);
	}
#endif
	/*
	for(i=2;i<=conf[0].max_k;i++)
	{	
		fprintf(f,"SVI[%d] = %lf\n",i,SViV[i]);
	}
	*/

	for(i=2;i<=conf[0].max_k;i++)
	{	
		fprintf(f,"%d,",i);
	}
	fprintf(f,"\n",i);
	for(i=2;i<=conf[0].max_k;i++)
	{	
		fprintf(f,"%lf,",SViV[i]);
	}

#ifdef calcTime
	end_time = clock();
	printf("\nSVI總共花費時間：%g秒\n",(float)(end_time - start_time)/CLOCKS_PER_SEC);
#endif

	fclose(f);
	//return svi;
}

/****************************************************************************************
*	Calculate Under-Partition Measure Function                                          *
*****************************************************************************************/
double Under(int k,struct data dataset[],struct center k_center[],struct config conf[],char *filename)
{
	// Variable Declared
	int		i,j;
	int		noC; //計算總共有幾群沒有資料
	double	dist;
	double	MD;
	double	Vu;

/*========================寫檔=========================*/
	char	TMP[256]="";
    FILE    *f;
	sprintf(TMP,"%s_out/SVIndex_DataNumber.txt",filename);
    f=fopen(TMP,"a+");
/*=====================================================*/

	// Initialize variables
	dist	=	0.0;
	MD	=	0.0;
	noC	=	0;

	fprintf(f,"這是分 %d 群\n",k);
	
	// Calculate
	for(i = 0; i < k; i++)
	{
	#ifdef Debug
		printf("第 %d 群\n",i+1);
	#endif
		dist = 0.0;
		for(j = 0; j < conf[0].datasize; j++)
		{
			if(dataset[j].cid == i)
			{
				dist = dist + point_distance(k_center[i].point,dataset[j].point,conf);
			#ifdef Debug
				printf("j = %d\n",j+1);
				printf("dist = %lf\n",dist);
			#endif
			}
		}
		if(k_center[i].count == 0)
		{
		#ifdef Result
			printf("分%d群時，第%d群，無資料\n",k,i+1);
		#endif
			fprintf(f,"分%d群時，第%d群，無資料\n",k,i+1);
			MD = MD + 0;
			noC	= noC + 1;
			break;
		}
		else
		{
			MD = MD + dist / k_center[i].count;
		}
	#ifdef Debug
		printf("MD = %lf\n",MD);
	#endif
	}
	
	Vu = MD / k;																	

#ifdef Debug
	printf("k = %d\n",k);
	printf("#MD = %lf\n",MD);
	printf("Vu = %lf\n",Vu);
#endif

#ifdef Result
	printf("總共%d群，沒有資料\n",noC);
#endif
	fprintf(f,"總共%d群，沒有資料\n",noC);
	fprintf(f,"這應該屬於[ %d ]群\n",k-noC);
	fprintf(f,"-----------------------------------------\n");

	fclose(f);
	return Vu;
}

/****************************************************************************************
*	Calculate Over-Partition Measure Function                                           *
*****************************************************************************************/
double Over(int k,struct center k_center[],struct config conf[])
{
	// Variable Declared
	int		i,j;
	double	dist;
	double	min_dist;
	double	Vo;
	
	// Initialize variables
	dist	=	0.0;
	min_dist=	(double)_I64_MAX;


	// Calculate
	for(i = 0; i < k; i++)
	{
		for(j = i+1; j < k; j++)
		{
			dist = point_distance(k_center[i].point,k_center[j].point,conf);
			min_dist=var_min(dist,min_dist);
		}
	}
	
	Vo = k / min_dist;

#ifdef Debug
	printf("k = %d\n",k);
	printf("min_dist = %lf\n",min_dist);
	printf("Vo = %lf\n",Vo);
#endif

	return Vo;
}