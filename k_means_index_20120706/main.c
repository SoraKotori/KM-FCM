#include 	<stdio.h>
#include 	<stdlib.h>
#include	<time.h>
#include	<math.h>
#include	<limits.h>
#include	"struct.h"
#include	"prototype.h"

int		main(int argc, char *argv[])
{
	int i;//,d;
	struct	config	conf[1];
	struct	name	Fname[1];			//宣告各名稱的struct
	struct	data	*dataset;
	
	//struct	k_number num_k[3];
	int		k_max,k_min,k_mid;
	double	temp1=0.0,temp2=0.0;
	//double	c1,c2,time=0.0;
	char 	mkdirs[MAX_STRING];
	char	moveChr[MAX_STRING];
//時間相關變數宣告
	clock_t start_time, end_time;		
	float	total_time = 0;
	clock_t start_alltime, end_alltime;
	char	action1[] = {'S', 'T', 'A', 'R', 'T', '\0'};	//開始的時間
	char	action2[] = {'E', 'N', 'D','\0'};				//結束的時間
	//char		*confname;
	//char		*filename;
	//char		*indexname;
	int		tmp_k=0;

//載入檔名參數
	Fname[0].file_name	=	argv[1];
	Fname[0].conf_name	=	argv[2];

	if (argc != 3)
	{
		printf("[ERROR] main(): Parameter error.\n");
		printf("Please input: data.csv config.inf\n");
		exit(0);
	}

//--------------------------------------------------------------------------
// 載入設定檔 & 計算資料大小和維度 & 最大群數 & 配置dataset空間
//--------------------------------------------------------------------------
//載入設定檔
	Input_Conf(conf, Fname);	
    conf[0].nearer_number = 2; //SymIndex Need

//計算資料大小和維度
	Input_FileConf(conf, Fname);  


//動態配置空間
	dataset	=	(struct data*)malloc(conf[0].datasize*sizeof(struct data));
	for( i = 0; i < conf[0].datasize; i++ )
	{
		dataset[i].point = ( double* ) malloc( conf[0].dim * sizeof(double) );
	}
//--------------------------------------------------------------------------
// 群數設定 & 讀入資料
//--------------------------------------------------------------------------

//一般
	if((int)sqrt(conf[0].datasize) > 16)
	{
		conf[0].max_k = 16;
	}
	else
	{
		conf[0].max_k = (int)sqrt(conf[0].datasize);
	}

//圖片
	if(conf[0].pic == 1)
	{
		conf[0].max_k = 8;
		//設定座標
		define_hw(dataset,conf);
	}

	k_min	=	2;
	k_max	=	conf[0].max_k;
	k_mid	=	(k_max+k_min)/2;

//讀入資料
	Input_Data(dataset,conf,Fname);
//--------------------------------------------------------------------------
// 產生結果資料夾
//--------------------------------------------------------------------------
	sprintf(mkdirs, "mkdir %s_out", Fname[0].file_name);
	system(mkdirs);

//--------------------------------------------------------------------------
	//開始的時間
	outputTimes(action1,Fname[0].file_name,0,0);
	start_alltime = clock(); /* mircosecond */
//--------------------------------------------------------------------------
// 主程式開始
//--------------------------------------------------------------------------
	while(1)
	{
		printf("the number of k= %d\n",k_min);
	//--------------------------------------------------------------------------
	// 產生&移動資料夾
			sprintf(mkdirs, "mkdir K%d", k_min);
			system(mkdirs);
			sprintf(moveChr, "move K%d %s_out", k_min,Fname[0].file_name);
			system(moveChr);
	//--------------------------------------------------------------------------
	//動態配置空間
		for( i = 0; i < conf[0].datasize; i++ )
		{
			dataset[i].u = ( double* ) malloc( k_min * sizeof(double) );
			dataset[i].dist = ( double* ) malloc( k_min * sizeof(double) );
		}
//--------------------------------------------------------------------------
		//開始的時間
			start_time = clock();
//--------------------------------------------------------------------------
		k_means(k_min,dataset,conf,Fname);
//--------------------------------------------------------------------------
		//結束的時間
			end_time = clock();
			/* CLOCKS_PER_SEC is defined at time.h */
			total_time = (float)(end_time - start_time)/CLOCKS_PER_SEC;
			//time	=	(c2-c1)/CLK_TCK;
			outputTimes_Cluster(Fname[0].file_name,k_min,total_time);
//--------------------------------------------------------------------------
		/*2011.07.11新增*/
		//out_cluster(k_min,dataset,filename,conf);
		printf("=========================================\n");

		if(k_min == k_max)
		{
			break;
		}

		k_min++;
	}

	/*
	c2=clock();
	if(conf[0].debug == 1)
	printf("\n\nThe running time of the code is: %g sec\n\n",(c2-c1)/CLK_TCK);
	time	=	(c2-c1)/CLK_TCK;

	*/
//--------------------------------------------------------------------------
	//結束的時間
	outputTimes(action2,Fname[0].file_name,0,1);
	end_alltime = clock();
	total_time = (float)(end_alltime - start_alltime)/CLOCKS_PER_SEC;
	outputTimes(action2,Fname[0].file_name,total_time,2);


	for( i = 0; i < conf[0].datasize; i++ )
	{
		free(dataset[i].point);
	}
	free(dataset);

  	return 0;
}
