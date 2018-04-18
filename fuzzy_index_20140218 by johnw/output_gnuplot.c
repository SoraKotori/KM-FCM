#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	<limits.h>
#include	<math.h>
#include	"struct.h"
#include	"prototype.h"

/****gnuplot3D畫圖資料****/
void	Gnuplot3D_Data(int k,struct data dataset[],struct config conf[],char *filename)
{
	int 	i,j,d;
	char	*STR	=	"cluster";
	char	TMP[MAX_STRING]	=	"";

	for(j = 0;j < k; j++)
	{
		FILE *f;
		//sprintf(TMP,"%s_out/%s_%s%d.3D",filename,indexname,STR,j);
		//sprintf(TMP,"%s_out/K%d_%s%d.3D",filename,k,STR,j);
		sprintf(TMP,"%s_out/K%d/%s%d.3D",filename,k,STR,j);
		f=fopen(TMP,"w+");
		for(i = 0;i < conf[0].datasize; i++)
		{
			if(dataset[i].cid == j)
			{
				for(d = 0;d < conf[0].dim; d++)
				{
					fprintf(f,"%lf\t",dataset[i].point[d]);
				}
				fprintf(f,"%d\n",dataset[i].cid);
			}
		}
		fclose(f);
	}

}

/****gunplot3D指令****/
void	Gnuplot3D_Graphic(int k,char *filename)
{
	int		j=0;
	char	*STR 	= 	"cluster";
	char	TMP[MAX_STRING] =	"";
    FILE	*Splot;
	//sprintf(TMP,"%s_out/%s_plot.txt",filename,indexname);
	//sprintf(TMP,"%s_out/K%d_Plot3D.txt",filename,k);
	sprintf(TMP,"%s_out/K%d/Plot3D.txt",filename,k);
	Splot = fopen (TMP,"w+");
	fprintf(Splot,"set terminal png enhanced size 640,480\n");
	//fprintf(Splot,"set output \"%s_3D.png\"\n",indexname);
	fprintf(Splot,"set output \"K%d_3D.png\"\n",k);
	fprintf(Splot,"set key outside center bottom horizontal\n");
	fprintf(Splot,"splot ");
	while(j<k)
	{
        //sprintf(TMP,"%s_%s%d.ja",indexname,STR,j);
		//sprintf(TMP,"K%d_%s%d.3D",k,STR,j);
		sprintf(TMP,"%s%d.3D",STR,j);
        fprintf(Splot,"\"%s\"",TMP);
        j++;
        if(j<k)
        {
            fprintf(Splot,",");
        }
    }

    fclose(Splot);
}

/*****Image gnuplot 2D繪圖資料****/
void	Image_Gnuplot2D_Data(int k,struct data dataset[],struct config conf[],char *filename)
{
	int		i,j;
	char	*GPIC	=	"Image_pic";
	char	TMP[MAX_STRING]	=	"";
	for(j = 0;j < k; j++)
	{
		FILE *f;
		//sprintf(TMP,"%s_out/%s_%s%d.2D",filename,indexname,GPIC,j);
		//sprintf(TMP,"%s_out/K%d_%s%d.2D",filename,k,GPIC,j);
		sprintf(TMP,"%s_out/K%d/%s%d.2D",filename,k,GPIC,j);
        f=fopen(TMP,"w+");
		for(i = 0;i < conf[0].datasize; i++)
		{
			if(dataset[i].cid == j)
			{
				fprintf(f,"%d\t%d\n",dataset[i].h,dataset[i].w);
			}
		}
		 fclose(f);
	}

}


/*****Image gnuplot2D繪圖指令*****/
void	Image_Gnuplot2D_Graphic(int k,char *filename)
{
    int j=0;
    char *STR = "Image_pic";
	char TMP[MAX_STRING] ="";
    FILE *plot;
    //sprintf(TMP,"%s_out/%s_pic.txt",filename,indexname);
	//sprintf(TMP,"%s_out/K%d_Plot2D.txt",filename,k);
	sprintf(TMP,"%s_out/K%d/Image_Plot2D.txt",filename,k);
    plot = fopen (TMP,"w+");
    fprintf(plot,"set terminal png enhanced size 480,480\n");
	//fprintf(plot,"set output \"%s.png\"\n",indexname);
	fprintf(plot,"set output \"Image_K%d_2D.png\"\n",k);
	fprintf(plot,"set key outside center bottom horizontal\n");
	fprintf(plot,"plot ");
	while(j<k)
	{
        //sprintf(TMP,"%s_%s%d.hw",indexname,STR,j);
		//sprintf(TMP,"K%d_%s%d.2D",k,STR,j);
		//sprintf(TMP,"%s%d.2D",STR,j);
		//fprintf(plot,"\"%s\"",TMP);
		sprintf(TMP," \"%s%d.2D\" title \"Cluster%d\" with points pointtype 7 pointsize 1",STR,j,j);
        fprintf(plot,"%s",TMP);
        j++;
        if(j<k)
        {
            fprintf(plot,",");
        }
    }
    fclose(plot);

	//Image
	j=0;
	sprintf(TMP,"%s_out/K%d/Image_Plot.txt",filename,k);
    plot = fopen (TMP,"w+");
    fprintf(plot,"set terminal png transparent nocrop enhanced size 360,360\n");
	fprintf(plot,"set output \"Image_K%d.png\"\n",k);
	fprintf(plot,"unset border\nunset xtics\nunset ytics\nunset key\n");
	fprintf(plot,"plot ");
	while(j<k)
	{
		sprintf(TMP," \"%s%d.2D\" with points pointtype 7 pointsize 1",STR,j,j);
        fprintf(plot,"%s",TMP);
        j++;
        if(j<k)
        {
            fprintf(plot,",");
        }
    }
    fclose(plot);
}

/*****輸出Gnuplot批次檔*****/
void	Image_Gnuplot_bat(int k,char *filename)
{
	char 	TMP[MAX_STRING]="";
	FILE	*f;
	sprintf(TMP,"%s_out/K%d/Go_gnuplot.bat",filename,k);
	f=fopen(TMP,"w+");
	fprintf(f,"C:\\gnuplot\\binary\\wgnuplot.exe Image_Plot2D.txt\n");
	fprintf(f,"C:\\gnuplot\\binary\\wgnuplot.exe Image_Plot.txt\n");
	fprintf(f,"C:\\gnuplot\\binary\\wgnuplot.exe Plot3D.txt\n");
	fclose(f);
	sprintf(TMP,"%s_out/K%d/del.bat",filename,k);
	f=fopen(TMP,"w+");
	fprintf(f,"del \"*.hw\",\"*.txt\",\"*.ja\",\"*.bat\"");
	fclose(f);
}

//2011.10.26新增
/*****gnuplot 2D繪圖資料****/
void	Gnuplot2D_Data(int k,struct data dataset[],struct config conf[],char *filename)
{
	int		i,j,d;
	char	*GPIC	=	"Data";
	char	TMP[MAX_STRING]	=	"";
	for(j = 0;j < k; j++)
	{
		FILE *f;
		sprintf(TMP,"%s_out/K%d/%s%d.2D",filename,k,GPIC,j);
        f=fopen(TMP,"w+");
		for(i = 0;i < conf[0].datasize; i++)
		{
			if(dataset[i].cid == j)
			{
				for(d = 0;d < conf[0].dim; d++)
				{
					fprintf(f,"%lf\t",dataset[i].point[d]);
				}
				fprintf(f,"\n");
			}
		}
		 fclose(f);
	}
}

void Gnuplot2D_Center(int k,struct center k_center[],struct config conf[],char *filename)
{
	int		j,d;
	char	TMP[MAX_STRING]	=	"";
	
	//輸出中心點
	FILE *f;
	sprintf(TMP,"%s_out/K%d/Center.2D",filename,k);
    f=fopen(TMP,"w+");
	for(j= 0;j < k; j++)
	{
		for(d = 0;d < conf[0].dim; d++)
		{
			fprintf(f,"%lf\t",k_center[j].point[d]);
		}
		fprintf(f,"\n");
	}
	fclose(f);
}

/*****gnuplot2D繪圖指令*****/
void	Gnuplot2D_Graphic(int k,char *filename)
{
    int j=0;
    char *STR = "Data";
	char TMP[MAX_STRING] ="";
    FILE *plot;
	sprintf(TMP,"%s_out/K%d/Plot2D.txt",filename,k);
    plot = fopen (TMP,"w+");
    fprintf(plot,"set terminal png enhanced size 640,480\n");
	fprintf(plot,"set output \"K%d_2D.png\"\n",k);
	fprintf(plot,"set key outside center bottom horizontal\n");
	fprintf(plot,"plot ");
	while(j<k)
	{
 		sprintf(TMP,"%s%d.2D",STR,j);
        fprintf(plot," \"%s\" title \"Cluster%d\" ",TMP,j);
        j++;
        if(j<k)
        {
            fprintf(plot,",");
        }
    }
	fclose(plot);

	//沒有Key
	j=0;
	sprintf(TMP,"%s_out/K%d/Plot2D_NoKey.txt",filename,k);
    plot = fopen (TMP,"w+");
    fprintf(plot,"set terminal png enhanced size 640,480\n");
	fprintf(plot,"set output \"K%d_Nokey_2D.png\"\n",k);
	fprintf(plot,"unset key\n");
	fprintf(plot,"plot ");
	while(j<k)
	{
 		sprintf(TMP,"%s%d.2D",STR,j);
        fprintf(plot," \"%s\" title \"Cluster%d\" ",TMP,j);
        j++;
        if(j<k)
        {
            fprintf(plot,",");
        }
    }
	fclose(plot);

//包含中心點
	j=0;
	sprintf(TMP,"%s_out/K%d/Plot2D_Center.txt",filename,k);
    plot = fopen (TMP,"w+");
    fprintf(plot,"set terminal png enhanced size 640,480\n");
	fprintf(plot,"set output \"K%d_Center_2D.png\"\n",k);
	fprintf(plot,"set key outside center bottom horizontal\n");
	fprintf(plot,"plot ");
	while(j<k)
	{
 		sprintf(TMP,"%s%d.2D",STR,j);
        fprintf(plot," \"%s\" title \"Cluster%d\" ",TMP,j);
        j++;
        if(j<k)
        {
            fprintf(plot,",");
        }
    }
	fprintf(plot,", \"Center.2D\" title \"Center\" with points pointtype 7 pointsize 1");
   	fclose(plot);
}


/*****輸出Gnuplot批次檔*****/
void Gnuplot_bat(int k,char *filename)
{
	char 	TMP[MAX_STRING]="";
	FILE	*f;
	sprintf(TMP,"%s_out/K%d/Go_gnuplot.bat",filename,k);
	f=fopen(TMP,"w+");
	fprintf(f,"C:\\gnuplot\\binary\\wgnuplot.exe Plot2D.txt\n");
	fprintf(f,"C:\\gnuplot\\binary\\wgnuplot.exe Plot2D_NoKey.txt\n");
	fprintf(f,"C:\\gnuplot\\binary\\wgnuplot.exe Plot2D_Center.txt\n");
	fprintf(f,"C:\\gnuplot\\binary\\wgnuplot.exe Plot3D.txt\n");
	fclose(f);
	sprintf(TMP,"%s_out/K%d/del.bat",filename,k);
	f=fopen(TMP,"w+");
	fprintf(f,"del \"*.hw\",\"*.txt\",\"*.ja\",\"*.bat\"");
	fclose(f);
}
