#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	<limits.h>
#include	<math.h>
#include	"struct.h"
#include	"prototype.h"


double	FDI(int k,struct data dataset[],struct center k_center[],struct config conf[])
{
	int		i,j;
	double	FDI		=	0.0;
	double	dist	=	0.0;
	for(j = 0;j < k; j++)
	{
		for(i = 0;i < conf[0].datasize; i++)
		{
			dist	=	point_distance(k_center[j].point,dataset[i].point,conf);
			dist	=	dataset[i].u[j] * dist;
			FDI		=	FDI + dist;
		}
	}
	
	return FDI;
}

double	XBI(int k,struct data dataset[],struct center k_center[],struct config conf[])
{
	int	i,j;
	double	dist;
	double	sum;
	double	min_dist;
	double	XBI;
	
	sum		=	0.0;
	dist	=	0.0;
	XBI		=	0.0;
	min_dist=	(double)_I64_MAX;
	
	
	for(j = 0;j < k; j++)
	{
		for(i = 0;i < conf[0].datasize;i++)
		{
			dist	=	point_distance(k_center[j].point,dataset[i].point,conf);
			dist	=	pow(dist,2);
			dist	=	pow(dataset[i].u[j],2) * dist;
			sum		=	sum	+ dist;
		}
	}
	
	dist	=	0.0;
	for(i = 0;i < k; i++)
	{
		for(j = 0; j < k; j++)
		{
			if(i != j)
			{
				dist	=	point_distance(k_center[i].point,k_center[j].point,conf);
				dist	=	pow(dist,2);
				if(dist <= min_dist)
				{
					min_dist	=	dist;
				}
			}
		}
	}
	
	XBI		=	sum/(min_dist*conf[0].datasize);
	
	return XBI;	
}


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

				for(z = 0; z < conf[0].datasize; z++) // Sk
				{	
					if (dataset[z].cid == i)
					{
						DBI_Sk_Molecular = sqrt(point_distance(dataset[z].point
												,k_center[i].point,conf));
						DBI_Sk_Molecular_sum = DBI_Sk_Molecular_sum;
					}					
				}// End Sk

				for(x = 0; x < conf[0].datasize; x++) // Sj
				{	
					if (dataset[x].cid == j)
					{
						DBI_Sj_Molecular = sqrt(point_distance(dataset[x].point
												,k_center[j].point,conf));
						DBI_Sj_Molecular_sum = DBI_Sj_Molecular_sum 
										   + (DBI_Sj_Molecular / k_center[j].count);
					}					
				}// End Sj

				DBI_sum = (DBI_Sk_Molecular_sum + DBI_Sj_Molecular_sum) / DBI_Denominator;
				DBI_Sk_Molecular_sum = 0.0;
				DBI_Sj_Molecular_sum = 0.0;
			}// End (i!=j) Loop	
			if(DBI_sum >= clusters_DBI_max)
			{
				clusters_DBI_max = DBI_sum;
			}
		}// End j Loop
		DBI_Max = DBI_Max + clusters_DBI_max;
	}// End i Loop

	DBI = DBI_Max/k;

	return DBI;
}

double PC(int k,struct data dataset[],struct config conf[])
{
	int	i,j;
	double	PCI;
	PCI = 0.0;
	for(i = 0;i < k; i++)
	{
		for(j = 0;j < conf[0].datasize;j++)
		{
			PCI = PCI + (dataset[j].u[i] * dataset[j].u[i]);
		}
	}

	PCI = PCI / conf[0].datasize;

	return PCI;
}

double MPC(int k,struct data dataset[],struct config conf[])
{
	int	i,j;
	double	PCI,MPC;
	PCI = 0.0;
	for(i = 0;i < k; i++)
	{
		for(j = 0;j < conf[0].datasize;j++)
		{
			PCI = PCI + (dataset[j].u[i] * dataset[j].u[i]);
		}
	}
	PCI = PCI / conf[0].datasize;
	MPC = 1 - (double)(k / (k-1.0)) * (1 - PCI);
	MPC=1.0/MPC;

	return MPC;
}

double PE(int k, struct data dataset[], struct config conf[])
{
	int	i,j;
	double	sum;
	double	Ent;
	double Entlog2;
	sum = 0.0;
	Ent = 0.0;
	Entlog2 = 0.0;
	for(i = 0;i < k; i++)
	{
		for(j = 0;j < conf[0].datasize;j++)
		{
			Ent = dataset[j].u[i] * log(dataset[j].u[i]) /log(2.0);
			sum = sum + Ent;
		}
	}
	
	sum = sum / (-conf[0].datasize);
	
	return sum;
}

double PBM(int k,struct data dataset[],struct center k_center[],struct config conf[])
{
	int	i,j;
	double	dist;
	double	sum;
	double	Ent;
	double  Dk;
	double  Ek;
	double  E1;
	dist = 0.0;
	sum = 0.0;
	Ent = 0.0;
	Dk = (double)_I64_MIN;
	Ek = 0.0;
	E1 = 0.0;

	//calculate E1
	for(i = 0;i < 1; i++)
	{
		for(j = 0; j < conf[0].datasize; j++)
		{
			E1 = E1 + dataset[j].u[i] * point_distance(k_center[i].point,dataset[j].point,conf);

		}
	}

	//calculate Ek
	for(i = 0;i < k; i++)
	{
		for(j = 0; j < conf[0].datasize; j++)
		{
			Ek = Ek + dataset[j].u[i] * point_distance(k_center[i].point,dataset[j].point,conf);
		}
		
	}

	//calculate Dk
	for(i = 0;i < k; i++)
	{
		for(j = i+1; j < k; j++)
		{
				dist = point_distance(k_center[i].point,k_center[j].point,conf);
				Dk = var_max(dist,Dk);
		}
	
	}

	sum = (1.0/k)*(E1/Ek)*Dk;

	sum = sum * sum;
	
	return sum;
}

double PBMF(int k,struct data dataset[],struct center k_center[],struct config conf[])
{
	// Variable Declared
	int	i,j;
	double	dist;
	double	pbmf;
	double  Dk;
	double  E1;
	double  Jm;

	// Initialize variables
	dist = 0.0;
	pbmf = 0.0;
	Dk = (double)_I64_MIN;
	E1 = 0.0;
	Jm = 0.0;

	//calculate E1
	for(i = 0;i < 1; i++)
	{
		for(j = 0; j < conf[0].datasize; j++)
		{
			E1 = E1 + dataset[j].u[i] * point_distance(k_center[i].point,dataset[j].point,conf);

		}
	}

	//calculate Jm
	for(i = 0;i < k; i++)
	{
		for(j = 0; j < conf[0].datasize; j++)
		{
			Jm = Jm + pow(dataset[j].u[i],conf[0].m) * point_distance(dataset[j].point,k_center[i].point,conf);
		}
		
	}

	//calculate Dk
	for(i = 0;i < k; i++)
	{
		for(j = i+1; j < k; j++)
		{
				dist = point_distance(k_center[i].point,k_center[j].point,conf);
				Dk = var_max(dist,Dk);
		}
	
	}

	pbmf = (1.0/k)*(E1/Jm)*Dk;
	
	//pbmf = pow(pbmf,2);

	return pbmf;
}