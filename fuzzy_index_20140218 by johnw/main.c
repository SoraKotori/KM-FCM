#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	<limits.h>
#include	<math.h>
#include	"struct.h"
#include	"prototype.h"

int main(int argc, char* argv[])
{
	struct	config	conf[1];	//�ŧi�]�w�ɪ�struct
	struct	data	*dataset;	//�ŧi��ƶ���struct
	int		k_max,k_min;
	//double	c1,c2,time;		//�ɶ������ܼ�
	int		tmp_k=0;
	//int		i;
	char	mkdirs[256];		//�ŧi�s�ظ�Ƨ��W��
	char	moveChr[256];		//�ŧi���ʸ�Ƨ��W��
	char	*filename;			//�ŧi��ƶ��ɦW
	char	*confname;			//�ŧi�]�w���ɦW
	//char	*indexname;			//�ŧi�����ɦW
//�ɶ������ܼƫŧi
	clock_t start_time, end_time;		
	float	total_time = 0;
	clock_t start_alltime, end_alltime;
	char	action1[] = {'S', 'T', 'A', 'R', 'T', '\0'};	//�}�l���ɶ�
	char	action2[] = {'E', 'N', 'D','\0'};				//�������ɶ�
//WI�Ѽƫŧi
	double	*Var_value;
	double	*Sep_value;
	double	*WI_value;
//SVI�Ѽƫŧi
	double	*Under_value;
	double	*Over_value;
	double	*SVI_value;
	
	filename=	argv[1];		//��ƶ��ɦW�Ѽ�
	confname=	argv[2];		//�]�w���ɦW�Ѽ�

	if (argc != 3)
	{
		printf("[ERROR] main(): Parameter error.\n");
		printf("Please input: data.csv config.inf\n");
		exit(0);
	}

//--------------------------------------------------------------------------
// ���J�]�w�� & ��Ƥj�p & ���� & �̤j�s��
//--------------------------------------------------------------------------
//���J�]�w��
	Input_Conf(conf, confname);	
    conf[0].nearer_number = 2; //SymIndex Need
//�p���Ƥj�p�M����
	Input_FileConf(conf, filename);  
	
	printf("Main�ɮפj�p�G%d\n",conf[0].datasize);
	printf("Main���פj�p�G%d\n",conf[0].dim);
	
//--------------------------------------------------------------------------
// ��l��
//--------------------------------------------------------------------------
	k_min	=	2;				//��l�Ƴ̤p�s��
	//k_min	=	conf[0].min_k;	//��l�Ƴ̤p�s��

//��l�Ƴ̤j�s��
	if(conf[0].max_k == 0)
	{
		//�H�y���
		if((int)sqrt(conf[0].datasize) > 16)
		{
			conf[0].max_k = 16;
		}
		else
		{
			//k���j�ȳ]�w����Ƶ��}�ڸ�
			conf[0].max_k = (int)sqrt(conf[0].datasize);
		}
		k_max = conf[0].max_k;
	}
	else if(conf[0].max_k == 1)
	{
		if(conf[0].pic == 1)
		{
			//�Ϥ�
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
	//WI�Ѽƫŧi
	Var_value	=	(double*)malloc(conf[0].max_k*sizeof(double));
	Sep_value	=	(double*)malloc(conf[0].max_k*sizeof(double));
	WI_value	=	(double*)malloc(conf[0].max_k*sizeof(double));
	//SVI�Ѽƫŧi
	Under_value	=	(double*)malloc(conf[0].max_k*sizeof(double));
	Over_value	=	(double*)malloc(conf[0].max_k*sizeof(double));
	SVI_value	=	(double*)malloc(conf[0].max_k*sizeof(double));
//--------------------------------------------------------------------------
// Ū�J���
//--------------------------------------------------------------------------
	Input_Data(dataset,conf,filename);
//--------------------------------------------------------------------------
// �Ϥ�
//--------------------------------------------------------------------------
	if(conf[0].pic == 1)
	{
		define_hw(dataset,conf);
	}
//--------------------------------------------------------------------------
// ���͵��G��Ƨ�
//--------------------------------------------------------------------------
	sprintf(mkdirs, "mkdir %s_out", filename);
	system(mkdirs);
//--------------------------------------------------------------------------
	//�}�l���ɶ�
	//outputTimes(action1,Fname[0].file_name);
	outputTimes(action1,filename,0,0); //�̫�@�ӰѼƬO�����X�榡
	start_alltime = clock(); /* mircosecond */
//--------------------------------------------------------------------------
// �D�{��
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
		// ����&���ʸ�Ƨ�
			sprintf(mkdirs, "mkdir K%d", k_min);
			system(mkdirs);
			sprintf(moveChr, "move K%d %s_out", k_min,filename);
			system(moveChr);
		//--------------------------------------------------------------------------
		//�}�l���ɶ�
			start_time = clock();
		//--------------------------------------------------------------------------
			//fuzzy(k_min,dataset,conf,filename);

			fuzzy(k_min,dataset,Var_value,Sep_value,Under_value,Over_value,conf,filename);

	
		//--------------------------------------------------------------------------
		//�������ɶ�
			end_time = clock();
			/* CLOCKS_PER_SEC is defined at time.h */
			total_time = (float)(end_time - start_time)/CLOCKS_PER_SEC;
			//time	=	(c2-c1)/CLK_TCK;
			outputTimes_Cluster(filename,k_min,total_time);
		//--------------------------------------------------------------------------
			/*2011.07.11�s�W*/
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

        //��XWI�MSVI
		output_WIndex(Var_value,Sep_value,WI_value,filename,conf);
		output_SVIndex(Under_value,Over_value,SVI_value,filename,conf);
		/*c2=clock();
		if(conf[0].debug == 1)
		printf("\n\nThe running time of the code is: %g sec\n\n",(c2-c1)/CLK_TCK);*/
	}

//--------------------------------------------------------------------------
	//�������ɶ�
	outputTimes(action2,filename,0,1);
	end_alltime = clock();
	total_time = (float)(end_alltime - start_alltime)/CLOCKS_PER_SEC;
	outputTimes(action2,filename,total_time,2);
	
	
	printf("%s Over!!\n",filename);
	//system("pause");


	free(dataset);

 	return 0;
}
