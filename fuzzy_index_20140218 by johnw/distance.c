#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	<limits.h>
#include	<math.h>
#include	"struct.h"
#include	"prototype.h"


double	point_distance( double	var1[] , double	var2[] ,struct config conf[])
{
	//變數宣告
	int d;
	double	distance=0;
	double	*tmp;
	//初始化
	tmp=(double*)malloc(conf[0].dim*sizeof(double));
	for ( d=0; d < conf[0].dim; d++)
	{
		tmp[d]	=	pow(var1[d]-var2[d],2);
	}
	for( d = 0; d < conf[0].dim; d++)
	{
		distance	=	distance+tmp[d];
	}
	distance	=	sqrt(distance);
	free(tmp);
	return distance;
}
