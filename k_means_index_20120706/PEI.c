#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	<math.h>
#include	"struct.h"
#include	"prototype.h"

//Entropy_index
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