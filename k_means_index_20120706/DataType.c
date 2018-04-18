#include <stdio.h>
#include <stdlib.h>


/************************************************************************/
int *New_1D_intArr(int *Arr,long Size)
{
	Arr = (int*)malloc(Size*sizeof(int));
	if(Arr==NULL)
	{
		printf("error");
		return NULL;
	}
	return Arr;
}
/*************************************************************************/
int **New_2D_intArr(int **Arr,long width,long Size)
{
	long i;
	Arr = (int**)malloc(width*sizeof(int*));
	if(Arr==NULL)
	{
		printf("Malloc faile\n");
		exit(1);
	}
	for(i=0;i<width;i++)
	{
		Arr[i]=(int*)malloc(Size*sizeof(int));
		if(Arr[i]==NULL)
		{
			printf("Malloc %d faile\n",i);
			exit(1);
		}
	}
	return Arr;
}
/*************************************************************************/
double *New_1D_doubleArr(double *Arr,long Size)
{
	Arr = (double*)malloc(Size*sizeof(double));
	if(Arr==NULL)
	{
		printf("error");
		return NULL;
	}
	return Arr;
}
/*************************************************************************/
double **New_2D_doubleArr(double **Arr,long width,long Size)
{
	long i;
	Arr = (double**)malloc(width*sizeof(double*));
	if(Arr==NULL)
	{
		printf("Malloc faile\n");
		exit(1);
	}
	for(i=0;i<width;i++)
	{
		Arr[i]=(double*)malloc(Size*sizeof(double));
		if(Arr==NULL)
		{
			printf("Malloc faile\n");
			exit(1);
		}
	}
	return Arr;
}
/*************************************************************************/
void Free_2D_intArr(int **Arr,long wight)
{
	long i;
	for(i=0;i<wight;i++)
	{
		free(Arr[i]);
	}
	free(Arr);
}
/*************************************************************************/
void Free_2D_doubleArr(double **Arr,long wight)
{
	long i;
	for(i=0;i<wight;i++)
	{
		free(Arr[i]);
	}
	free(Arr);
}
/*************************************************************************/
