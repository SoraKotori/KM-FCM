#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	"struct.h"
#include	"prototype.h"

/*****輸出每群的Start和End時間*****/
void	outputTimes_Cluster(char *filename,int k,float time)
{
	char 	TMP[MAX_STRING]	=	"";
    FILE    *f;

	sprintf(TMP,"%s_out/OutputTimes.txt",filename);
	f=fopen(TMP,"a+");
    
	fprintf(f,"The number of k= %d\n", k);
	fprintf(f,"Time : %g sec \n", time);
	fprintf(f,"---------------------------------\n");

    fclose(f);
}

/*****輸出Start和End時間*****/
void	outputTimes(char  *action, char *filename, float total_time, int flag)
{
	char 	TMP[MAX_STRING]	=	"";
    FILE    *f;
	time_t t1 = time(NULL);
	char *now = ctime(&t1);
	
	sprintf(TMP,"%s_out/OutputTimes.txt",filename);
	f=fopen(TMP,"a+");

	if(flag == 0)
	{
		fprintf(f,"\n%s:\t%s\n", action, now);
		fprintf(f,"---------------------------------\n");
	}
	else if(flag == 1)
	{
		fprintf(f,"\n%s:\t%s\n", action, now);
	}
	else
	{
		fprintf(f,"\nThe All time of the code is: %g sec\n\n",total_time);
	}

    fclose(f);
}


