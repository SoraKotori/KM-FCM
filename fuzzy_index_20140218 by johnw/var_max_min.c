#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	<limits.h>
#include	<math.h>
#include	"struct.h"
#include	"prototype.h"

/**************************
求最大值和最小值的函式
**************************/

double var_max(double var,double var_max)
{
    if(var > var_max)
    {
        var_max=var;
    }
    return var_max;
}

double var_min(double var,double var_min)
{
    if(var < var_min)
    {
        var_min=var;
    }
    return var_min;
}
