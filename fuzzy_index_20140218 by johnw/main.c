#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	<limits.h>
#include	<math.h>
#include	"struct.h"
#include	"prototype.h"

int main(int argc, char* argv[])
{
	struct	config	conf[1];	//宣告設定檔的struct
	struct	data	*dataset;	//宣告資料集的struct
	int		k_max,k_min;
	//double	c1,c2,time;		//時間相關變數
	int		tmp_k=0;
	//int		i;
	char	mkdirs[256];		//宣告新建資料夾名稱
	char	moveChr[256];		//宣告移動資料夾名稱
	char	*filename;			//宣告資料集檔名
	char	*confname;			//宣告設定檔檔名
	//char	*indexname;			//宣告指標檔名
//時間相關變數宣告
	clock_t start_time, end_time;		
	float	total_time = 0;
	clock_t start_alltime, end_alltime;
	char	action1[] = {'S', 'T', 'A', 'R', 'T', '\0'};	//開始的時間
	char	action2[] = {'E', 'N', 'D','\0'};				//結束的時間
//WI參數宣告
	double	*Var_value;
	double	*Sep_value;
	double	*WI_value;
//SVI參數宣告
	double	*Under_value;
	double	*Over_value;
	double	*SVI_value;
	
	filename=	argv[1];		//資料集檔名參數
	confname=	argv[2];		//設定檔檔名參數

	if (argc != 3)
	{
		printf("[ERROR] main(): Parameter error.\n");
		printf("Please input: data.csv config.inf\n");
		exit(0);
	}

//--------------------------------------------------------------------------
// 載入設定檔 & 資料大小 & 維度 & 最大群數
//--------------------------------------------------------------------------
//載入設定檔
	Input_Conf(conf, confname);	
    conf[0].nearer_number = 2; //SymIndex Need
//計算資料大小和維度
	Input_FileConf(conf, filename);  
	
	printf("Main檔案大小：%d\n",conf[0].datasize);
	printf("Main維度大小：%d\n",conf[0].dim);
	
//--------------------------------------------------------------------------
// 初始化
//--------------------------------------------------------------------------
	k_min	=	2;				//初始化最小群數
	//k_min	=	conf[0].min_k;	//初始化最小群數

//初始化最大群數
	if(conf[0].max_k == 0)
	{
		//人造資料
		if((int)sqrt(conf[0].datasize) > 16)
		{
			conf[0].max_k = 16;
		}
		else
		{
			//k的大值設定為資料筆開根號
			conf[0].max_k = (int)sqrt(conf[0].datasize);
		}
		k_max = conf[0].max_k;
	}
	else if(conf[0].max_k == 1)
	{
		if(conf[0].pic == 1)
		{
			//圖片
			conf[0].max_k = 8;
		}
		k_max	=	conf[0].max_k;
	}
	else
	{		
		k_max	=	conf[0].max_k;
	}

	printf("k_max=%d\n",k_max);

	dataset		=	(struct data*)malloc(conf[0].datasize*sizeof(struct data));
	//WI參數宣告
	Var_value	=	(double*)malloc(conf[0].max_k*sizeof(double));
	Sep_value	=	(double*)malloc(conf[0].max_k*sizeof(double));
	WI_value	=	(double*)malloc(conf[0].max_k*sizeof(double));
	//SVI參數宣告
	Under_value	=	(double*)malloc(conf[0].max_k*sizeof(double));
	Over_value	=	(double*)malloc(conf[0].max_k*sizeof(double));
	SVI_value	=	(double*)malloc(conf[0].max_k*sizeof(double));
//--------------------------------------------------------------------------
// 讀入資料
//--------------------------------------------------------------------------
	Input_Data(dataset,conf,filename);
//--------------------------------------------------------------------------
// 圖片
//--------------------------------------------------------------------------
	if(conf[0].pic == 1)
	{
		define_hw(dataset,conf);
	}
//--------------------------------------------------------------------------
// 產生結果資料夾
//--------------------------------------------------------------------------
	sprintf(mkdirs, "mkdir %s_out", filename);
	system(mkdirs);
//--------------------------------------------------------------------------
	//開始的時間
	//outputTimes(action1,Fname[0].file_name);
	outputTimes(action1,filename,0,0); //最後一個參數是控制輸出格式
	start_alltime = clock(); /* mircosecond */
//--------------------------------------------------------------------------
// 主程式
//--------------------------------------------------------------------------

	srand(time(NULL));
	// add by johnw at 20140217


	if(conf[0].debug == 0)
	{
		//c1=clock();
		while(1)
		{
			printf("The number of k= %d\n",k_min);
			//k_max	=	conf[0].max_k;
		//--------------------------------------------------------------------------
		// 產生&移動資料夾
			sprintf(mkdirs, "mkdir K%d", k_min);
			system(mkdirs);
			sprintf(moveChr, "move K%d %s_out", k_min,filename);
			system(moveChr);
		//--------------------------------------------------------------------------
		//開始的時間
			start_time = clock();
		//--------------------------------------------------------------------------
			//fuzzy(k_min,dataset,conf,filename);

			fuzzy(k_min,dataset,Var_value,Sep_value,Under_value,Over_value,conf,filename);

	
		//--------------------------------------------------------------------------
		//結束的時間
			end_time = clock();
			/* CLOCKS_PER_SEC is defined at time.h */
			total_time = (float)(end_time - start_time)/CLOCKS_PER_SEC;
			//time	=	(c2-c1)/CLK_TCK;
			outputTimes_Cluster(filename,k_min,total_time);
		//--------------------------------------------------------------------------
			/*2011.07.11新增*/
			//out_cluster(k_min,dataset,filename,conf);

			printf("=========================================\n");

			if(k_min ==	k_max)
			{
				break;
			}
			
			k_min++;

			//printf("k_max=%d\n",k_max);
			
		}
		//WI
		WI(Var_value,Sep_value,WI_value,conf,filename);
		MinW (WI_value,conf,filename);
		//SVI
		SVI(Under_value,Over_value,SVI_value,conf,filename);
		MinSV (SVI_value,conf,filename);

        //輸出WI和SVI
		output_WIndex(Var_value,Sep_value,WI_value,filename,conf);
		output_SVIndex(Under_value,Over_value,SVI_value,filename,conf);
		/*c2=clock();
		if(conf[0].debug == 1)
		printf("\n\nThe running time of the code is: %g sec\n\n",(c2-c1)/CLK_TCK);*/
	}

//--------------------------------------------------------------------------
	//結束的時間
	outputTimes(action2,filename,0,1);
	end_alltime = clock();
	total_time = (float)(end_alltime - start_alltime)/CLOCKS_PER_SEC;
	outputTimes(action2,filename,total_time,2);
	
	
	printf("%s Over!!\n",filename);
	//system("pause");


	free(dataset);

 	return 0;
}
