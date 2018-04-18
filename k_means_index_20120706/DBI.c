#include	<stdio.h>
#include	<stdlib.h>
#include	<math.h>
#include	<limits.h>
#include	"struct.h"
#include	"prototype.h"

//#define		Debug
/*------------------------------------------------------------------------------------
 DBI return Daviers-Bouldin Index
//input 
 k - the number of clusters
 data - the number of data
 center - the number of center
 config - Initialize
------------------------------------------------------------------------------------*/
double DBI(int k,struct data dataset[],struct center k_center[],struct config conf[])
{
	int		i,j,z,x;	
	double	DBI		= 0.0;
	double	DBI_sum	= 0.0;
	double	DBI_Max	= 0.0;
	double	S_sum	= 0.0;
	double	DBI_Sk_Molecular= 0.0;
	double	DBI_Sj_Molecular= 0.0;
	double	DBI_Denominator	= 0.0;
	double	clusters_DBI_max= (double)_I64_MIN;
	double	DBI_Sk_Molecular_sum	= 0.0;
	double	DBI_Sj_Molecular_sum	= 0.0;

	//-----------------------------------------------------------------
	//calculate Daviers-Bouldin Index
	//***************
	//*		DBI		*
	//***************

	for(i = 0;i < k; i++)
	{
		for(j = 0; j < k; j++)
		{
			if(i != j)
			{
				DBI_Denominator	= point_distance(k_center[j].point
												,k_center[i].point,conf); // || Vj - Vk ||
				#ifdef	Debug
					printf("i=%d\tj=%d\n",i,j);
					printf("DBI_Denominator = %lf\n", DBI_Denominator);
				#endif

				for(z = 0; z < conf[0].datasize; z++) // Sk
				{	
					if (dataset[z].cid == i)
					{
						DBI_Sk_Molecular = sqrt(point_distance(dataset[z].point
												,k_center[i].point,conf));
						DBI_Sk_Molecular_sum = DBI_Sk_Molecular_sum
										   + (DBI_Sk_Molecular / k_center[i].count);
					#ifdef	Debug
						printf("DBI_Sk_Molecular = %lf\n", DBI_Sk_Molecular);
					#endif
					}					
				}// End Sk

				#ifdef	Debug
					printf("k_center[%d].count = %d\n", i,k_center[i].count);
					printf("DBI_Sk_Molecular_sum = %lf\n", DBI_Sk_Molecular_sum);
				#endif

				for(x = 0; x < conf[0].datasize; x++) // Sj
				{	
					if (dataset[x].cid == j)
					{
						DBI_Sj_Molecular = sqrt(point_distance(dataset[x].point
												,k_center[j].point,conf));
						DBI_Sj_Molecular_sum = DBI_Sj_Molecular_sum 
										   + (DBI_Sj_Molecular / k_center[j].count);
					#ifdef	Debug
						printf("DBI_Sj_Molecular = %lf\n", DBI_Sj_Molecular);
					#endif

					}					
				}// End Sj

				#ifdef	Debug
					printf("k_center[%d].count = %d\n", j,k_center[i].count);
					printf("DBI_Sj_Molecular_sum = %lf\n", DBI_Sj_Molecular_sum);
				#endif

				DBI_sum = (DBI_Sk_Molecular_sum + DBI_Sj_Molecular_sum) / DBI_Denominator;
				DBI_Sk_Molecular_sum = 0.0;
				DBI_Sj_Molecular_sum = 0.0;
			}// End (i!=j) Loop	
			if(DBI_sum >= clusters_DBI_max)
			{
				clusters_DBI_max = DBI_sum;
			}
		}// End j Loop
		#ifdef	Debug
			printf("clusters_DBI_max = %lf\n", clusters_DBI_max);
			printf("----------------------------------------\n");
		#endif
		DBI_Max = DBI_Max + clusters_DBI_max;
		clusters_DBI_max= (double)_I64_MIN;
	}// End i Loop

	#ifdef	Debug
		printf("DBI_Max = %lf\n", DBI_Max);
	#endif
	DBI = DBI_Max/k;

	return DBI;
}