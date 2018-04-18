#include 	<stdio.h>
#include 	<stdlib.h>
#include	<time.h>
#include	<math.h>
#include	<limits.h>
#include	"struct.h"
#include	"prototype.h"

/*****輸出網頁檔*****/
void	out_info(int k,double time,char *filename,char *indexname,struct config conf[],struct k_number num_k[])
{
	char	TMP[256];
	FILE	*f;
	sprintf(TMP,"%s_out/%s.html",filename,indexname);
	f=fopen(TMP,"w+");
	fprintf(f,"<html>\n");
	fprintf(f,"<title>%s</title>\n",filename);
	fprintf(f,"<center>\n");
	fprintf(f,"<img src=\"%s.png\" width=\"640\" high=\"480\"/><br/>\n",indexname);
	if(conf[0].dim <= 3)
	{
		fprintf(f,"<img src=\"%s_3D.png\" width=\"640\" high=\"480\"/><br/>\n",indexname);
	}
	fprintf(f,"index=%s<br />群數=%d<br />時間=%lf<br />維度=%d<br />index=%lf<br />\n",indexname,k,time,conf[0].dim,num_k[0].index_var);
	fprintf(f,"</center>\n");
	fprintf(f,"</html>\n");
	fclose(f);
}

/*****輸出cluster.csv*****/
void 	output(int k,struct data dataset[],char *filename,struct config conf[])
{
	char	TMP[256]="";
	FILE	*f;
	int		i,j,d;
	sprintf(TMP,"%s_out/K%d/cluster_%d.csv",filename,k,k);
	f=fopen(TMP,"w+");
	for(i = 0;i < conf[0].datasize; i++)
	{
		fprintf(f,"%d,",dataset[i].id);
		fprintf(f,"%d,",dataset[i].cid);
		for(d = 0;d < conf[0].dim; d++)
		{
			fprintf(f,"%lf,",dataset[i].point[d]);
		}
		for(j = 0;j < k; j++)
		{
			fprintf(f,"%lf,",dataset[i].u[j]);
		}
		fprintf(f,"\n");
	}
	fclose(f);

}
/*****輸出dataset.csv*****/
void	out_cluster(int k,struct data dataset[],char *filename, struct config conf[])
{
	char	TMP[256]	=	"";
	int		i,d;
	FILE	*f;
	sprintf(TMP,"%s_out/K%d/dataset_%d.csv",filename,k,k);
	f=fopen(TMP,"w+");
	fprintf(f,"id,cid");
	for(d = 0;d < conf[0].dim; d++)
	{
		fprintf(f,",dim_%d",d);
	}
	fprintf(f,"\n");
	for(i = 0;i < conf[0].datasize; i++)
	{
		fprintf(f,"%d,",dataset[i].id);
		fprintf(f,"%d",dataset[i].cid);
		for(d = 0;d < conf[0].dim; d++)
		{
			fprintf(f,",%lf",dataset[i].point[d]);
		}
		fprintf(f,"\n");
	}
	fclose(f);


}

/*****輸出center.csv*****/
void	output_center(int k,struct center k_center[],char *filename,struct config conf[])
{
	char 	TMP[256]	=	"";
	int		j,d;
	FILE	*f;
	sprintf(TMP,"%s_out/K%d/center_%d.csv",filename,k,k);
	f=fopen(TMP,"w+");

	fprintf(f,"cid");
	for(d = 0;d < conf[0].dim; d++)
	{
		fprintf(f,",dim_%d",d);
	}
	fprintf(f,"\n");
	for(j= 0;j < k; j++)
	{
		fprintf(f,"%d",j);
		for(d = 0;d < conf[0].dim; d++)
		{
			//printf("%lf\t",k_center[j].point[d]);
			fprintf(f,",%lf",k_center[j].point[d]);
		}
		//printf("\n");
		fprintf(f,"\n");
	}

	fclose(f);


}

void    output_index(int k,double index[],char *filename,struct config conf[])
{
    int     i;
    char	TMP[MAX_STRING]="";
    FILE    *f;
    sprintf(TMP,"%s_out/index.csv",filename);
    f=fopen(TMP,"a+");
    fprintf(f,"%d",k);
    for(i = 0;i < conf[0].index; i++)
    {
        fprintf(f,",%lf",index[i]);
    }
    fprintf(f,"\n");
    fclose(f);
}


/*****輸出每一群有幾個Data*****/
void	output_DataNumber(int k,struct center k_center[],char *filename,struct config conf[])
{
	char 	TMP[MAX_STRING]	=	"";
	int		i;
	FILE	*f;
	sprintf(TMP,"%s_out/Cluster_Data_Num.csv",filename);
	f=fopen(TMP,"a+");

	fprintf(f,"k,%d\n",k);
	fprintf(f,"Cluster,Number\n");
	for(i= 0; i<k; i++)
	{
		fprintf(f,"%d,%d\n",i,k_center[i].count);
	}
	fprintf(f,"\n");

	fclose(f);
}


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


/*****輸出疊代次數*****/
void	outputIteration(int k,char *filename,int iteration)
{
	char 	TMP[MAX_STRING]	=	"";
    FILE    *f;
	
	sprintf(TMP,"%s_out/Iteration.txt",filename);
	f=fopen(TMP,"a+");
    //f = fopen("OutputTimes.txt","a+");
	fprintf(f,"---------------------------------\n");
	fprintf(f,"The number of k = %d\n", k);
	fprintf(f,"Iteration = %d\n", iteration);
    fclose(f);
}