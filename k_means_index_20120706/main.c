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
	struct	name	Fname[1];			//�ŧi�U�W�٪�struct
	struct	data	*dataset;
	
	//struct	k_number num_k[3];
	int		k_max,k_min,k_mid;
	double	temp1=0.0,temp2=0.0;
	//double	c1,c2,time=0.0;
	char 	mkdirs[MAX_STRING];
	char	moveChr[MAX_STRING];
//�ɶ������ܼƫŧi
	clock_t start_time, end_time;		
	float	total_time = 0;
	clock_t start_alltime, end_alltime;
	char	action1[] = {'S', 'T', 'A', 'R', 'T', '\0'};	//�}�l���ɶ�
	char	action2[] = {'E', 'N', 'D','\0'};				//�������ɶ�
	//char		*confname;
	//char		*filename;
	//char		*indexname;
	int		tmp_k=0;

//���J�ɦW�Ѽ�
	Fname[0].file_name	=	argv[1];
	Fname[0].conf_name	=	argv[2];

	if (argc != 3)
	{
		printf("[ERROR] main(): Parameter error.\n");
		printf("Please input: data.csv config.inf\n");
		exit(0);
	}

//--------------------------------------------------------------------------
// ���J�]�w�� & �p���Ƥj�p�M���� & �̤j�s�� & �t�mdataset�Ŷ�
//--------------------------------------------------------------------------
//���J�]�w��
	Input_Conf(conf, Fname);	
    conf[0].nearer_number = 2; //SymIndex Need

//�p���Ƥj�p�M����
	Input_FileConf(conf, Fname);  


//�ʺA�t�m�Ŷ�
	dataset	=	(struct data*)malloc(conf[0].datasize*sizeof(struct data));
	for( i = 0; i < conf[0].datasize; i++ )
	{
		dataset[i].point = ( double* ) malloc( conf[0].dim * sizeof(double) );
	}
//--------------------------------------------------------------------------
// �s�Ƴ]�w & Ū�J���
//--------------------------------------------------------------------------

//�@��
	if((int)sqrt(conf[0].datasize) > 16)
	{
		conf[0].max_k = 16;
	}
	else
	{
		conf[0].max_k = (int)sqrt(conf[0].datasize);
	}

//�Ϥ�
	if(conf[0].pic == 1)
	{
		conf[0].max_k = 8;
		//�]�w�y��
		define_hw(dataset,conf);
	}

	k_min	=	2;
	k_max	=	conf[0].max_k;
	k_mid	=	(k_max+k_min)/2;

//Ū�J���
	Input_Data(dataset,conf,Fname);
//--------------------------------------------------------------------------
// ���͵��G��Ƨ�
//--------------------------------------------------------------------------
	sprintf(mkdirs, "mkdir %s_out", Fname[0].file_name);
	system(mkdirs);

//--------------------------------------------------------------------------
	//�}�l���ɶ�
	outputTimes(action1,Fname[0].file_name,0,0);
	start_alltime = clock(); /* mircosecond */
//--------------------------------------------------------------------------
// �D�{���}�l
//--------------------------------------------------------------------------
	while(1)
	{
		printf("the number of k= %d\n",k_min);
	//--------------------------------------------------------------------------
	// ����&���ʸ�Ƨ�
			sprintf(mkdirs, "mkdir K%d", k_min);
			system(mkdirs);
			sprintf(moveChr, "move K%d %s_out", k_min,Fname[0].file_name);
			system(moveChr);
	//--------------------------------------------------------------------------
	//�ʺA�t�m�Ŷ�
		for( i = 0; i < conf[0].datasize; i++ )
		{
			dataset[i].u = ( double* ) malloc( k_min * sizeof(double) );
			dataset[i].dist = ( double* ) malloc( k_min * sizeof(double) );
		}
//--------------------------------------------------------------------------
		//�}�l���ɶ�
			start_time = clock();
//--------------------------------------------------------------------------
		k_means(k_min,dataset,conf,Fname);
//--------------------------------------------------------------------------
		//�������ɶ�
			end_time = clock();
			/* CLOCKS_PER_SEC is defined at time.h */
			total_time = (float)(end_time - start_time)/CLOCKS_PER_SEC;
			//time	=	(c2-c1)/CLK_TCK;
			outputTimes_Cluster(Fname[0].file_name,k_min,total_time);
//--------------------------------------------------------------------------
		/*2011.07.11�s�W*/
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
	//�������ɶ�
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
