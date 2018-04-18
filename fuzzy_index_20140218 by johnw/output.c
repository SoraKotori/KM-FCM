#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	<limits.h>
#include	<math.h>
#include	"struct.h"
#include	"prototype.h"


/*****輸出網頁檔*****/
void	out_info(int k,double time,char *filename,char *indexname,struct config conf[],struct k_number num_k[])
{
	char	TMP[MAX_STRING];
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
	fprintf(f,"index=%s<br />群數=%d<br />時間=%lf<br />維度=%d<br />終止條件=%lf<br />index=%lf<br />\n",indexname,k,time,conf[0].dim,conf[0].end_var,num_k[0].index_var);
	fprintf(f,"</center>\n");
	fprintf(f,"</html>\n");
	fclose(f);
}

/*****輸出cluster.csv*****/
void 	output(int k,char *filename,struct data dataset[],struct config conf[])
{
	char	TMP[MAX_STRING]="";
	FILE	*f;
	int		i,j,d;
	//sprintf(TMP,"%s_out/cluster.csv",filename);
	sprintf(TMP,"%s_out/K%d/cluster_%d.csv",filename,k,k);
	f=fopen(TMP,"w+");

//類別
	fprintf(f,"id,cid");
	for(d = 0;d < conf[0].dim; d++)
	{
		fprintf(f,",dim_%d",d);
	}
	for(j = 0;j < k; j++)
	{
		fprintf(f,",u%d",j);
	}
	fprintf(f,"\n");

//Value
	for(i = 0;i < conf[0].datasize; i++)
	{
		fprintf(f,"%d",dataset[i].id);
		fprintf(f,",%d",dataset[i].cid);
		for(d = 0;d < conf[0].dim; d++)
		{
			fprintf(f,",%lf",dataset[i].point[d]);
		}
		for(j = 0;j < k; j++)
		{
			fprintf(f,",%lf",dataset[i].u[j]);
		}
		fprintf(f,"\n");
	}
	fclose(f);

}

/*****輸出dataset.csv*****/
void	out_cluster(int k,struct data dataset[],char *filename, struct config conf[])
{
	char	TMP[MAX_STRING]	=	"";
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
	char 	TMP[MAX_STRING]	=	"";
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

/*****輸出舊的dataset.csv 和 center.csv*****/
void	output_Old_clusterANDcenter(struct data Old_dataset[],struct center Old_k_center[],char *filename,struct config conf[])
{
	char 	TMP[MAX_STRING]	=	"";
	int		i,j,d;
	FILE	*f;
	
	sprintf(TMP,"%s_out/ClusterNumber.txt",filename);
	f=fopen(TMP,"w+");
	fprintf(f,"第%d群→第%d群\n",conf[0].original_k,conf[0].real_k);
	fclose(f);
//--------------------------------------------------------------------------
//cluster.csv
	sprintf(TMP,"%s_out/K%d/Old_cluster_%d_New%d.csv",filename,conf[0].original_k,conf[0].original_k,conf[0].real_k);
	f=fopen(TMP,"w+");
	fprintf(f,"id,cid");
	for(d = 0;d < conf[0].original_k; d++)
	{
		fprintf(f,",dim_%d",d);
	}
	for(j = 0;j < conf[0].original_k; j++)
	{
		fprintf(f,",u%d",j);
	}
	fprintf(f,"\n");

//Value
	for(i = 0;i < conf[0].datasize; i++)
	{
		fprintf(f,"%d,",Old_dataset[i].id);
		fprintf(f,"%d,",Old_dataset[i].cid);
		for(d = 0;d < conf[0].dim; d++)
		{
			fprintf(f,"%lf,",Old_dataset[i].point[d]);
		}
		for(j = 0;j < conf[0].original_k; j++)
		{
			fprintf(f,"%lf,",Old_dataset[i].u[j]);
		}
		fprintf(f,"\n");
	}
	fclose(f);
//--------------------------------------------------------------------------
//dataset.csv
	sprintf(TMP,"%s_out/K%d/Old_dataset_%d_New%d.csv",filename,conf[0].original_k,conf[0].original_k,conf[0].real_k);
	f=fopen(TMP,"w+");
	fprintf(f,"id,cid");
	for(d = 0;d < conf[0].dim; d++)
	{
		fprintf(f,",dim_%d",d);
	}
	fprintf(f,"\n");
	for(i = 0;i < conf[0].datasize; i++)
	{
		fprintf(f,"%d,",Old_dataset[i].id);
		fprintf(f,"%d",Old_dataset[i].cid);
		for(d = 0;d < conf[0].dim; d++)
		{
			fprintf(f,",%lf",Old_dataset[i].point[d]);
		}
		fprintf(f,"\n");
	}
	fclose(f);
//--------------------------------------------------------------------------
//center.csv
	sprintf(TMP,"%s_out/K%d/Old_center_%d_New%d.csv",filename,conf[0].original_k,conf[0].original_k,conf[0].real_k);
	f=fopen(TMP,"w+");

	fprintf(f,"cid");
	for(d = 0;d < conf[0].dim; d++)
	{
		fprintf(f,",dim_%d",d);
	}
	fprintf(f,"\n");
	for(i= 0;i < conf[0].original_k; i++)
	{
		fprintf(f,"%d",i);
		for(d = 0;d < conf[0].dim; d++)
		{
			fprintf(f,",%lf",Old_k_center[i].point[d]);
		}
		fprintf(f,"\n");
	}
	fclose(f);
}


/*****輸出新的dataset.csv 和 center.csv*****/
void	output_New_clusterANDcenter(struct data dataset[],struct center k_center[],char *filename,struct config conf[])
{
	char 	TMP[MAX_STRING]	=	"";
	int		i,j,d;
	FILE	*f;
//--------------------------------------------------------------------------
//cluster.csv
	//sprintf(TMP,"%s_out/K%d/New_cluster_Or%d_%d.csv",filename,conf[0].original_k,conf[0].original_k,conf[0].real_k);
	sprintf(TMP,"%s_out/K%d/cluster_%d.csv",filename,conf[0].original_k,conf[0].original_k);
	f=fopen(TMP,"w+");
	fprintf(f,"id,cid");
	for(d = 0;d < conf[0].original_k; d++)
	{
		fprintf(f,",dim_%d",d);
	}
	for(j = 0;j < conf[0].original_k; j++)
	{
		fprintf(f,",u%d",j);
	}
	fprintf(f,"\n");
//Value
	for(i = 0;i < conf[0].datasize; i++)
	{
		fprintf(f,"%d,",dataset[i].id);
		fprintf(f,"%d,",dataset[i].cid);
		for(d = 0;d < conf[0].dim; d++)
		{
			fprintf(f,"%lf,",dataset[i].point[d]);
		}
		for(j = 0;j < conf[0].original_k; j++)
		{
			fprintf(f,"%lf,",dataset[i].u[j]);
		}
		fprintf(f,"\n");
	}
	fclose(f);
//--------------------------------------------------------------------------
//dataset.csv
	//sprintf(TMP,"%s_out/K%d/New_dataset_Or%d_%d.csv",filename,conf[0].original_k,conf[0].original_k,conf[0].real_k);
	sprintf(TMP,"%s_out/K%d/dataset_%d.csv",filename,conf[0].original_k,conf[0].original_k);
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
//--------------------------------------------------------------------------
//center.csv
	//sprintf(TMP,"%s_out/K%d/New_center_Or%d_%d.csv",filename,conf[0].original_k,conf[0].original_k,conf[0].real_k);
	sprintf(TMP,"%s_out/K%d/center_%d.csv",filename,conf[0].original_k,conf[0].original_k);
	f=fopen(TMP,"w+");

	fprintf(f,"cid");
	for(d = 0;d < conf[0].dim; d++)
	{
		fprintf(f,",dim_%d",d);
	}
	fprintf(f,"\n");
	for(i= 0;i < conf[0].real_k; i++)
	{
		fprintf(f,"%d",i);
		for(d = 0;d < conf[0].dim; d++)
		{
			fprintf(f,",%lf",k_center[i].point[d]);
		}
		fprintf(f,"\n");
	}
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

//void    output_index(int k,double index[],char *filename,char *indexname,struct config conf[])
void   	output_index(int k,double index[],char *filename,struct config conf[])
{
    int     i;
    char	TMP[MAX_STRING]="";
    FILE    *f;
    sprintf(TMP,"%s_out/index.csv",filename);
    f=fopen(TMP,"a+");
	//fprintf(f,"FDI,XBI,DBI,PC,MPC,PE,PBM,PBMF\n");
	//fprintf(f,"%d",k);
	//fprintf(f,"Original_k,Real_k\n");
	fprintf(f," , ,FDI,XBI,DBI,PC,MPC,PE,PBM,PBMF,Kwon,FSI,PCAES,SC,CHI,Cs_ck,WLI,CSI,Sym,Dunn,WL2\n");
	// this should be updated if more DVIs are added 

	fprintf(f,"%d,%d",conf[0].original_k,conf[0].real_k);

    for(i = 0;i < conf[0].index; i++)
    {
        fprintf(f,",%lf",index[i]);
    }
    fprintf(f,"\n");
    fclose(f);
}

/*****輸出WI*****/
void    output_WIndex(double VarV [], double SepV [], double WiV [],char *filename,struct config conf[])
{
    int     i;
    char	TMP[MAX_STRING]="";
    FILE    *f;
    sprintf(TMP,"%s_out/Windex_OtherValue.csv",filename);
    f=fopen(TMP,"a+");
	fprintf(f,"C,Var,Sep,WI\n");
	for(i = 2;i <= conf[0].max_k; i++)
	{	
		fprintf(f,"%d,%lf,%lf,%lf\n",i,VarV[i],SepV[i],WiV[i]);
		
	}
    
    fprintf(f,"\n");
    fclose(f);
}

/*****輸出SVI*****/
void    output_SVIndex(double UnderV [], double OverV [], double SViV [],char *filename,struct config conf[])
{
    int     i;
    char	TMP[MAX_STRING]="";
    FILE    *f;
    sprintf(TMP,"%s_out/SVindex_OtherValue.csv",filename);
    f=fopen(TMP,"a+");
	fprintf(f,"C,Under,Over,SVI\n");
	for(i = 2;i <= conf[0].max_k; i++)
	{	
		fprintf(f,"%d,%lf,%lf,%lf\n",i,UnderV[i],OverV[i],SViV[i]);
		
	}
    
    fprintf(f,"\n");
    fclose(f);
}

/*****輸出FCM疊代次數*****/
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

/*****輸出CVI的元素*****/
void	outputElement(int k,struct data dataset[],struct center k_center[],char *filename,struct config conf[])
{
	double	minVV,medianVV;
	char	tmp_Char[MAX_STRING];
	FILE    *File;


	sprintf(tmp_Char,"%s_out/Min&Median.csv",filename);
	File=fopen(tmp_Char,"a+");
    

	fprintf(File,"Cluster,Min,Median\n");
	fprintf(File,"%d",k);
   

	minVV	= Min_VV(k,k_center,conf,2);
	medianVV= Median_VV(k,k_center,conf,2);

	fprintf(File,",%lf,%lf\n",minVV,medianVV);


	fclose(File);
}
