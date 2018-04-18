#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	<math.h>
#include	"struct.h"
#include	"prototype.h"
/*******************************************************************************
 *   argument variable  
 *   dataset         = dataset variable array 
 *   conf            = config variable array   
 *
 *   PC_indxe variable
 *   i,j are counter 
 *   dataset[].u[]   = dataset's u matrix 
 *   conf[].k        = number of cluster
 *   conf[].datasize = number of datasize 
 *   PCI             = PC index variable 
 *   MPC             = Modified PC { 1-(K/K-1)*(1-PCI) } 
 *
 ******************************************************************************/    


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

