#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	<limits.h>
#include	<math.h>
#include	"struct.h"
#include	"prototype.h"

//void	fuzzy(int k,struct data dataset[],struct config conf[],char *filename)
void	fuzzy(int k,struct data dataset[],double Var_value [],double Sep_value [],double Under_value [],double Over_value [],struct config conf[],char *filename)
{
	//變數宣告
	int		i,j,d;
	int		nodataflag;		//控制全部的群集都有資料點 (k_center[i].count != 0)
	int		lowdataflag;	//控制計算Sym (k_center[i].count >3)
	int		samecenterflag;	//判斷是否有相同的中心點
	int		samecenterflag_k;
	int		calcflag;		//重複的次數
	int		iteration = 0;	//代數
	int		data_K;		//紀錄有資料點的中心，剩下幾個
	struct	center	*k_center;
	double	*d_max,*d_min;
	double	difference=0.0, index_past=0.0, index_present=0.0;	// 終止條件的參數
	double	center_dist;
	double	*index;

	//2012.02.14新增
	struct	center	*Old_k_center;
	struct	data	*Old_dataset; 
	conf[0].original_k = k;


	calcflag = 0;
	samecenterflag = 0;//都沒有相同的中心點
	nodataflag = 0;		//都有Data
//--------------------------------------------------------------------------
	//初始化
	k_center	=	(struct center*)malloc(k*sizeof(struct center));
	d_max		=	(double*)malloc(conf[0].dim*sizeof(double));
	d_min		=	(double*)malloc(conf[0].dim*sizeof(double));
	index		=	(double*)malloc(conf[0].index*sizeof(double));
	//index_value	=	(double*)calloc(conf[0].index,sizeof(double));
	for(d = 0;d < conf[0].dim; d++)
	{
		d_max[d]=(double)_I64_MIN;
		d_min[d]=(double)_I64_MAX;
	}

//--------------------------------------------------------------------------	
	//printf("Fuzzy：K%d開始\n",k);
    //printf("FUZZY檔案大小：%d\n",conf[0].datasize);
//--------------------------------------------------------------------------

//初始化 U矩陣 或 中心點
	if(conf[0].initial_fuzzy == 0)
	{
		//初始化U矩陣
		membership_initialize(k,dataset,conf);
	}
	else 
	{	//初始化中心點
		if(conf[0].initial_fuzzy == 1)
		{
			//計算中心點的極值
			for(i = 0; i < conf[0].datasize; i++)
			{
				for(d = 0;d < conf[0].dim; d++)
				{
					d_max[d]=var_max(dataset[i].point[d],d_max[d]);
					d_min[d]=var_min(dataset[i].point[d],d_min[d]);
				}
			}
			center_f1(k,k_center,d_max,d_min,conf);
		}
		else
		{
			center_f2(k,k_center,dataset,conf);
		}
		//透過亂數中心點計算初始化U矩陣
		membership(k,dataset,k_center,conf);
	}
	
	iteration = 0;
	//printf("Fuzzy：K%d_初始化中心點&初始化U矩陣結束\n",k);
	while(1)
	{
		//計算新中心點
		f_center(k,dataset,k_center,conf);

		//if(iteration == 0 || iteration % 100 == 0)
		// check by johnw on 20140218
		// iteration % 100 == 0 <-- this is restart 
		// Johnw turns it off
		//
		if(iteration == 0 )
		{
			if(conf[0].initial_fuzzy == 0)
			{
				printf("使用初始化membership\n");
			}
			else
			{
				printf("使用初始化中心點\n");
			}
			for(i=0;i<k;i++)
			{
				printf("第%d中心：",i);
				for(d = 0;d <conf[0].dim; d++)
				{
					printf("%lf\t",k_center[i].point[d]);
				}
				printf("\n");
			}
		}

		//新算新的U矩陣
		membership(k,dataset,k_center,conf);
		
		//分配資料點屬於哪個中心點
		assgin(k,dataset,conf);
		Initialize(k,dataset,k_center,conf);
		
//--------------------------------------------------------------------------
// 檢查
//	1.是否有相同的中心點
//	2.是否有某一群沒有資料點
//--------------------------------------------------------------------------
		
		//檢查中心點是否相同 也可以採取計算兩個中心點的方式
		for(i = 0;i < k; i++)
		{
			for(j = i+1;j < k; j++)
			{
				center_dist	= point_distance(k_center[i].point,k_center[j].point,conf);
				//if(center_dist == 0.0)
				if(center_dist < pow(10,-5))
					// remark by johnw: two identical centroids=center_dist < pow(10,-6)
					// Li's setting: 10^-6 (approaching to 0
					// Johnw's setting: 10^-5
				{
					//printf("center_dist=%lf\n",center_dist);
					samecenterflag = 1; //samecenterflag=1表示有某兩個中心點一樣
					break;
				}
				else
				{
					samecenterflag = 0;
				}
			}
			if(samecenterflag == 1)
			{
				break;
			}
		}

		//檢查是否有哪一群沒有Data	
		//除了Sym需要每一群都有3筆Data以上，其他Index都只要有Data就可以
		//End_check_center: 
		if(conf[0].index != 16)
		{
			for(i = 0;i < k; i++)
			{
				if(k_center[i].count != 0)
				{
					nodataflag = 0;
				}
				else
				{
					nodataflag = 1;
					break;
				}
			}
		}
		else
		{
			for(i = 0;i < k; i++)
			{
				if(k_center[i].count > 3)
				{
					nodataflag = 0;
				}
				else
				{
					nodataflag = 1;
					break;
				}
			}
		}
//--------------------------------------------------------------------------
	
		//假如某一群裡面沒有資料點，iteration會增加
		if( nodataflag == 1 || samecenterflag == 1)
		{
			calcflag++;
		}
		//printf("samecenterflag=%d\n",samecenterflag);
		//printf("nodataflag=%d\n",nodataflag);
		//printf("calcflag=%d\n",calcflag);
		
		//假如每一群都有資料點或者某一群沒有資料點的狀況超過1000次，就計算目標函式
		if( (nodataflag == 0 && samecenterflag == 0)|| calcflag>1501 )
		{
			calcflag = 0;
			//目標函式
			index_present	=	object(k,dataset,k_center,conf);
			difference	=	fabs(index_past - index_present);

			//if( difference < ( fabs(index_present) * conf[0].end_var ) && iteration > 201) //請勿使用，會導致中心點很近的狀況，除非再加上代數限制
			if(difference < conf[0].end_var)
			{
				break;
			}
			index_past	 =	index_present;
		}
		if( iteration > 2501 )
		{
				break;
		}
		iteration++;
	}

//輸出FCM疊代次數
	outputIteration(k,filename,iteration);

//分配資料點屬於哪個中心點
	membership(k,dataset,k_center,conf);
	assgin(k,dataset,conf);
	Initialize(k,dataset,k_center,conf);


	printf("<<<< Fuzzy 分群結束 >>>\n");

//--------------------------------------------------------------------------
// 檢查
//	1.是否有某一群沒有資料點
//	2.是否有相同的中心點
// 刪除以上兩種狀況的中心點
//--------------------------------------------------------------------------
	printf("conf[0].original_k=%d\n",conf[0].original_k);
	//檢查是否有哪一群沒有Data
	nodataflag = 0;
	for(i = 0;i < conf[0].original_k; i++)
	{
		if(k_center[i].count == 0)
		{
			k--;
			nodataflag = 1; //nodataflag=1表示有某一群沒有資料點
		}
	}
	printf("nodataflag=%d\n",nodataflag);

	data_K = k;
	conf[0].real_k = k;
	printf("data_K=%d\n",data_K);
	printf("conf[0].real_k=%d\n",conf[0].real_k);

	if(nodataflag == 1)
	{
		//動態配置
		Old_k_center	=	(struct center*)malloc(conf[0].original_k*sizeof(struct center));
		Old_dataset		=	(struct data*)malloc(conf[0].datasize*sizeof(struct data));
	}

	if(nodataflag == 1)
	{
		memcpy(Old_k_center, k_center,conf[0].original_k*sizeof(struct center));
		//Old_k_center=k_center; //記憶體位址相同
		for(i=0; i<conf[0].original_k; i++)
		{
			for(d = 0; d<conf[0].dim; d++)
			{
				printf("Old_k_center[%d].point[%d]=%lf\n",i,d,Old_k_center[i].point[d]);
				printf("k_center[%d].point[%d]=%lf\n",i,d,k_center[i].point[d]);
			}
		}
		k_center=(struct center*)malloc(data_K*sizeof(struct center));
		printf("某一群集沒有資料點\n");
		delete_noData_center(k_center,Old_k_center,conf);
	}
	
	//檢查中心點是否相同-採取計算兩個中心點的方式
	samecenterflag = 0;//都沒有相同的中心點
	samecenterflag_k = 0;
	for(i = 0;i < data_K; i++)
	{
		for(j = i+1;j < data_K; j++)
		{
			center_dist	= point_distance(k_center[i].point,k_center[j].point,conf);
			//if(center_dist == 0.0)
			if(center_dist < CENTER_DIFF)
			{
				samecenterflag_k = 1; //samecenterflag=1表示有某兩個中心點一樣
				break;
			}
			else
			{
				samecenterflag_k = 0;
			}
			
		}
		if(samecenterflag_k == 1)
		{
			k--;
			samecenterflag = 1; //表示有兩個中心點一樣，需到下面判斷
		}
	}
	printf("samecenterflag=%d\n",samecenterflag);

	conf[0].real_k = k;
	printf("conf[0].original_k=%d\n",conf[0].original_k);
	printf("conf[0].real_k=%d\n",conf[0].real_k);

	if(nodataflag == 0 && samecenterflag == 1)
	{
		//動態配置
		Old_k_center	=	(struct center*)malloc(conf[0].original_k*sizeof(struct center));
		Old_dataset		=	(struct data*)malloc(conf[0].datasize*sizeof(struct data));
	}

	if(samecenterflag == 1)
	{
		printf("k_center.point\n");
		for(i=0; i<data_K; i++)
		{
			printf("%d\t",i);
			for(d = 0; d<conf[0].dim; d++)
			{
				printf("%lf\t",k_center[i].point[d]);
			}
		}
		printf("有相同的中心點\n");
		delete_same_center(k_center,conf,data_K);
	}

	if(nodataflag == 1 || samecenterflag == 1)
	{
		//Old_dataset	= dataset;
		/*
		for(i=0; i<conf[0].datasize; i++)
		{
			Old_dataset[i].id	= dataset[i].id;
			Old_dataset[i].cid	= dataset[i].cid;
			if(conf[0].pic == 1)
			{
				Old_dataset[i].h = dataset[i].h;
				Old_dataset[i].w = dataset[i].w;
			}
			for(d = 0; d<conf[0].dim; d++)
			{
				Old_dataset[i].point[d] = dataset[i].point[d];
			}
			for(j = 0; j<conf[0].original_k; j++)
			{
				Old_dataset[i].u[j] = dataset[i].u[j];
			}
		}
		*/
		memcpy(Old_dataset, dataset,conf[0].datasize*sizeof(struct data));

		printf("檢查完兩項結果的k_center\n");
		for(i=0; i<conf[0].real_k; i++)
		{
			printf("%d\t",i);
			for(d = 0; d<conf[0].dim; d++)
			{
				printf("%lf\t",k_center[i].point[d]);
			}
			printf("\n");
		}
	
		printf("k=%d\n",k);

		k=conf[0].real_k;
		printf("k=%d\n",k);
		membership(k,dataset,k_center,conf);
		assgin(k,dataset,conf);
		Initialize(k,dataset,k_center,conf);
		//輸出資訊
		/*
		output(k,filename,dataset,conf);
		output_center(k,k_center,filename,conf);
		out_cluster(k,dataset,filename,conf);
		*/
		//輸出每一群的資料量
		output_DataNumber(k,k_center,filename,conf);
		output_New_clusterANDcenter(dataset,k_center,filename,conf);
		output_Old_clusterANDcenter(Old_dataset,Old_k_center,filename,conf);
	}
	else
	{
		//輸出資訊
		output(k,filename,dataset,conf);
		output_center(k,k_center,filename,conf);
		out_cluster(k,dataset,filename,conf);
		//輸出每一群的資料量
		output_DataNumber(k,k_center,filename,conf);
	}

//--------------------------------------------------------------------------
// 計算Index - WI&SVI
//--------------------------------------------------------------------------
	/*WI - 計算 Var 和 Sep*/
	Var_value[conf[0].original_k] = Var(k,dataset,k_center,conf,filename);
	Sep_value[conf[0].original_k] = Sep(k,dataset,k_center,conf);
	/* SVI - 計算 Under 和 Over */
	Under_value[conf[0].original_k] = Under(k,dataset,k_center,conf,filename);
	Over_value[conf[0].original_k] = Over(k,k_center,conf);
	printf("WI&SVI結束\n");

//--------------------------------------------------------------------------
// 計算Index
//--------------------------------------------------------------------------
	index[0]	=	FDI(k,dataset,k_center,conf);//↓
	printf("FDI結束\n");
	index[1]	=	XBI(k,dataset,k_center,conf);//↓
	printf("XBI結束\n");
	index[2]	=	DBI(k,dataset,k_center,conf);//↓
	printf("DBI結束\n");
	index[3]	=	PC(k,dataset,conf);//↑
	printf("PC結束\n");
	index[4]	=	MPC(k,dataset,conf);//↑
	printf("MPC結束\n");
	index[5]	=	PE(k,dataset,conf);//↓
	printf("PE結束\n");
	index[6]	=	PBM(k,dataset,k_center,conf);//↑
	printf("PBM結束\n");
	index[7]	=	PBMF(k,dataset,k_center,conf);//↑
	printf("PBMF結束\n");
	index[8]	=	Kwon(k,dataset,k_center,conf);//↓
	printf("Kwon結束\n");
	index[9]	=	FSI(k,dataset,k_center,conf);//↓
	printf("FSI結束\n");
	index[10]	=	PCAESI(k,dataset,k_center,conf);//↑
	printf("PCAESI結束\n");
	index[11]	=	SC(k,dataset,k_center,conf);//↑
	printf("SC結束\n");
	index[12]	=	CHI(k,dataset,k_center,conf);//↑
	printf("CHI結束\n");
	index[13]	=	CS(k,dataset,k_center,conf);//↓
	printf("CS_ck結束\n");
	index[14]	=	WL1(k,dataset,k_center,conf,filename);//↓
	printf("WL1結束\n");
	index[15]	=	CSI(k,dataset,k_center,conf);	//速度很慢  //↓
	printf("CSI結束\n");
/*	*/

	//檢查是否有哪一群Data<3個 (給Sym使用)
	lowdataflag = 0;
	for(i = 0;i < conf[0].original_k; i++)
	{
		if(k_center[i].count < 2)
		{
			lowdataflag = 1; //lowdataflag=1表示有某一群太少資料點
			break;
		}
	}
	printf("lowdataflag=%d\n",lowdataflag);
	if(lowdataflag == 0)
	{
		index[16]	=	Sym_Index(k,dataset,k_center,conf);//↑
		printf("Sym_Index結束\n");
	}
	else
	{
		index[16]	=	-1;
		printf("不算Sym_Index\n");
	}

	index[17]	=	DunnI(k,dataset,conf);			//速度很慢	//↑
	printf("DunnI結束\n");
	
	index[18]	=	WL2(k,dataset,k_center,conf,filename);//↓
	printf("WL2結束\n");
	

	/**/
	//index[16]	=	FDI2(k,dataset,k_center,conf);
	//printf("FDI2結束\n");

//--------------------------------------------------------------------------
// Index Value輸出至螢幕
//--------------------------------------------------------------------------
	printf("FDI=%lf\n",index[0]);
	printf("XBI=%lf\n",index[1]);
	printf("DBI=%lf\n",index[2]);
	printf("PC=%lf\n",index[3]);
	printf("MPC=%lf\n",index[4]);
	printf("PE=%lf\n",index[5]);
	printf("PBM=%lf\n",index[6]);
	printf("PBMF=%lf\n",index[7]);
	printf("Kwon=%lf\n",index[8]);
	printf("FSI=%lf\n",index[9]);
	printf("PCAESI=%lf\n",index[10]);
	printf("SC=%lf\n",index[11]);
	printf("CHI=%lf\n",index[12]);
	printf("CS_ck=%lf\n",index[13]);
	printf("WL1=%lf\n",index[14]);
	printf("CS=%lf\n",index[15]);
	printf("Sym=%lf\n",index[16]);
	printf("Dunn=%lf\n",index[17]);
	printf("WL2=%lf\n",index[18]);
	
	
	//printf("FDI2=%lf\n",index[13]);
	//printf("CSI=%lf\n",index[13]);
	//printf("DunnI=%lf\n",index[14]);
//--------------------------------------------------------------------------
	//printf("第 %d 群，Index計算完畢！\n",k);
/*
	printf("==================================================\n");
	for(i=0;i<15;i++)
	{
		printf("index[%d]=%lf\n",i,index[i]);
	}
*/
	output_index(k,index,filename,conf);
	printf("output_index OVER\n");

	k=conf[0].original_k;

//輸出網頁檔
	//out_info(k,time,filename,indexname,conf,index_var[0]);						
/**/
	if(conf[0].dim <= 3)
	{
		if(	conf[0].dim <= 2 )
		{
			Gnuplot2D_Data(k,dataset,conf,filename);
			Gnuplot2D_Center(k,k_center,conf,filename);
			Gnuplot2D_Graphic(k,filename);
		}
		Gnuplot3D_Data(k,dataset,conf,filename);
		Gnuplot3D_Graphic(k,filename);
		Gnuplot_bat(k,filename);
	}

	if(conf[0].pic == 1)
	{
		Image_Gnuplot2D_Data(k,dataset,conf,filename);
		Image_Gnuplot2D_Graphic(k,filename);
		Image_Gnuplot_bat(k,filename);
	}

//--------------------------------------------------------------------------
	//輸出元素
	outputElement(k,dataset,k_center,filename,conf);

	free(k_center);
	free(d_max);
	free(d_min);
	free(index);
	if(nodataflag == 1 || samecenterflag == 1)
	{
		free(Old_k_center);
	}
	//printf("<<<< Fuzzy.c結束 >>>\n");

}
