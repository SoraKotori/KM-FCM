#include 	<stdio.h>
#include 	<stdlib.h>
#include	<time.h>
#include	<math.h>
#include	<limits.h>
#include	"struct.h"
#include	"prototype.h"

void	k_means(int k,struct data dataset[],struct config conf[],struct name Fname[])
{
	//�ܼƫŧi
	int		i,j,d;
	int		iteration=0;
	double	*d_max,*d_min;
	struct	center	*k_center;
	double	difference=0.0, sum_dist_past=0.0, sum_dist_present=0.0;	// �פ���󪺰Ѽ�
	//double	sum_distance,tmp_sum_dist;
	double	*index;
	char	*filename;
	int		calcflag;
	int		nodataflag;		//����������s����������I (k_center[i].count != 0)
	int		samecenterflag;	//�P�_�O�_���ۦP�������I
	double	center_dist;
	int		*nodataIndex;
	int		nodataCount = 0;
	filename = Fname[0].file_name;
//--------------------------------------------------------------------------
// ��l��
//--------------------------------------------------------------------------
	nodataIndex =	(int*)malloc(k*sizeof(int));

	index	=	(double*)malloc(conf[0].index*sizeof(double));
	for( i = 0; i < conf[0].index; i++ )
	{
		index[i] = 0.0;
	}
	k_center=	(struct center*)malloc(k*sizeof(struct center));
	
	for( i = 0; i < k; i++ )
	{
		k_center[i].point = ( double* ) malloc( conf[0].dim * sizeof(double) );
	}

	d_max	=	(double*)malloc(conf[0].dim*sizeof(double));
	d_min	=	(double*)malloc(conf[0].dim*sizeof(double));
	for(d = 0; d < conf[0].dim; d++)
	{
		d_max[d]=(double)_I64_MIN;
		d_min[d]=(double)_I64_MAX;
	}

	//�p���ƶ�������
	for(i = 0; i < conf[0].datasize ; i++)
	{
		for(d = 0;d < conf[0].dim ; d++)
		{
			d_max[d]	=	var_max(dataset[i].point[d],d_max[d]);
			d_min[d]	=	var_min(dataset[i].point[d],d_min[d]);
		}
	}

	//��l�Ƥ����I
	if( conf[0].center_f ==	0)
	{
		//�q�̤j�M�̤p���׽d�򤺡A�H��
		center_point_f1(k,k_center,d_max,d_min,conf);
	}
	else if(conf[0].center_f ==	1)
	{
		//�q����I����K�������I
		center_point_f2(k,k_center,dataset,conf);
	}


//�����I �L�X�ù�����
	for(i = 0;i < k; i++)
	{	
		printf("%d\t",i);
		for(j = 0;j < conf[0].dim; j++)
		{
			printf("%lf\t",k_center[i].point[j]);
		}
		printf("\n");
	}

/*
//Input Data �L�X�ù�����
	for(i = 0;i < conf[0].datasize; i++)
	{
		printf("%d\t",dataset[i].id);
		for(j = 0;j <conf[0].dim; j++)
		{
			printf("%lf\t",dataset[i].point[j]);
		}
		printf("\n");
	}
*/

	while(1)
	{
		//2012.04.16 ��g
		//�p��C�@���I��C�@�Ӥ����I���Z��
		data_center_dist(k,k_center,dataset,conf);


		//���t��ƨ�Y�@�s
		assign(k,dataset,conf);

/*
		for(i = 0;i < conf[0].datasize; i++)
		{
			printf("dataset %d\n",i);
			for(j = 0;j < k; j++)
			{	
				printf("k_center %d\t",j);
				printf("%lf\n",dataset[i].dist[j]);
			}
			printf("�ݩ�C %d �s\n",dataset[i].cid);
		}
*/
		//�p���k�ݨ�ơBk_center[j].dist_sum�Bk_center[j].count�Bk_center[j].avg_dist�B���s�p��C�@�s������
		Initialize(k,dataset,k_center,conf);

		
		
	
//--------------------------------------------------------------------------
// �ˬd
//	1.�O�_���ۦP�������I
//	2.�O�_���Y�@�s�S������I
//--------------------------------------------------------------------------
		//�ˬd�����I�O�_�ۦP �]�i�H�Ĩ��p���Ӥ����I���覡
		for(i = 0;i < k; i++)
		{
			for(j = i+1;j < k; j++)
			{
				center_dist	= point_distance(k_center[i].point,k_center[j].point,conf);
				//if(center_dist == 0.0)
				if(center_dist < pow(10,-6))
				{
					//printf("center_dist=%lf\n",center_dist);
					samecenterflag = 1; //samecenterflag=1��ܦ��Y��Ӥ����I�@��
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
		printf("samecenterflag=%d\n",samecenterflag);

		//�ˬd�O�_�����@�s�S��Data	
		//���FSym�ݭn�C�@�s����3��Data�H�W�A��LIndex���u�n��Data�N�i�H
		//End_check_center: 
		j=0;
		for(i = 0;i < k; i++)
		{
			if(k_center[i].count > 1)
			{
				nodataflag = 0;
			}
			else
			{
				nodataflag = 1;
				nodataIndex[j]=i;
				j++;
				nodataCount++;
				//break;
			}
		}

//--------------------------------------------------------------------------
		if(nodataflag == 1 || samecenterflag == 1)
		{
			calcflag++;
		}

		if(nodataflag == 0 || calcflag % 200 == 0)
		{
			//calcflag = 0;
			//�Ҧ��s�����Z���������`�X
			sum_dist_present = sum_dist(k,k_center,dataset,conf);
			//printf("sum_dist_present=%lf\tsum_dist_past=%lf\n",sum_dist_present,sum_dist_past);
			//printf("�Ҧ��s�����Z���������`�X\n");
			sum_dist_past	=	sum_dist_present;
			if(iteration >=	conf[0].iter && sum_dist_past == sum_dist_present)
			{
				break;
			}
		}
		printf("nodataflag=%d\n",nodataflag);
		if(iteration >=	3000)
		{
			break;
		}

		//���ͷs�������I
		//if(sum_dist_past == sum_dist_present && iteration % 100 == 0)
		if(calcflag % 100 == 0)
		{
			//intf("�üƤ���\n");
			//�q�̤j�M�̤p���׽d�򤺡A�H��
			center_point_f1(k,k_center,d_max,d_min,conf);
			//center_point_f2(k,k_center,dataset,conf);
			//center_gussian(k,dataset,k_center,conf,d_max,d_min);
		}

		if(calcflag % 100 != 0 && nodataflag == 0)
		{
			printf("�p�⭫��\n");
			//new_center(k,k_center,conf);
			//�p�⭫��
			new_center_data(k,k_center,dataset,conf);
		}

		if(calcflag % 100 != 0 && nodataflag == 1)
		{
			for(j = 0;j < nodataCount; j++)
			{
				for(d = 0; d < conf[0].dim; d++)
				{
					k_center[nodataIndex[j]].point[d]=fmod(rand()/1.0,(d_max[d] - d_min[d])/1.0)+d_min[d];
				}
			}
		}

		iteration++;

		for(j= 0;j < k; j++)
		{
			printf("C%d\t",j);
			for(d = 0;d < conf[0].dim; d++)
			{
				printf("%lf\t",k_center[j].point[d]);
			}
			printf("\n");
		}

	}
	//�p�⭫��
	new_center_data(k,k_center,dataset,conf);
	//�p��C�@���I��C�@�Ӥ����I���Z��
	data_center_dist(k,k_center,dataset,conf);
	//���t��ƨ�Y�@�s
	assign(k,dataset,conf);
	Initialize(k,dataset,k_center,conf);
//--------------------------------------------------------------------------
// ��X��T
//--------------------------------------------------------------------------
	output(k,dataset,filename,conf);
	out_cluster(k,dataset,filename,conf);
	output_center(k,k_center,filename,conf);

	//��X�|�N����
	outputIteration(k,filename,iteration);
	//��X�C�@�s����ƶq
	output_DataNumber(k,k_center,filename,conf);
//--------------------------------------------------------------------------
// �p��Index
//--------------------------------------------------------------------------
	index[0]	=	DSI(k,dataset,k_center,conf);//��
	printf("DSI=%lf\n",index[0]);
	index[1]	=	XBI(k,dataset,k_center,conf);//��
	printf("XBI=%lf\n",index[1]);
	index[2]	=	DBI(k,dataset,k_center,conf);//��
	printf("DBI=%lf\n",index[2]);
	//index[3]	=	PC(k,dataset,conf);//��
	//printf("PC=%lf\n",index[3]);
	//index[4]	=	MPC(k,dataset,conf);//��
	//printf("MPC=%lf\n",index[4]);
	//index[5]	=	PE(k,dataset,conf);//��
	//printf("PE=%lf\n",index[5]);
	index[6]	=	PBM(k,dataset,k_center,conf);//��
	printf("PBM=%lf\n",index[6]);
	index[7]	=	PBMF(k,dataset,k_center,conf);//��
	printf("PBMF=%lf\n",index[7]);
	index[8]	=	Kwon(k,dataset,k_center,conf);//��
	printf("Kwon=%lf\n",index[8]);
	index[9]	=	FSI(k,dataset,k_center,conf);//��
	printf("FSI=%lf\n",index[9]);
 	index[10]	=	PCAESI(k,dataset,k_center,conf);//��
	printf("PCAESI=%lf\n",index[10]);
	//index[11]	=	SC(k,dataset,k_center,conf);//��
	//printf("SC=%lf\n",index[11]);
	index[12]	=	CHI(k,dataset,k_center,conf);//��
	printf("CHI=%lf\n",index[12]);
	index[13]	=	CS(k,dataset,k_center,conf);//��
	printf("CS_ck=%lf\n",index[13]);
	index[14]	=	WL(k,dataset,k_center,conf);//��
	printf("WLI=%lf\n",index[14]);
	index[15]	=	CSI(k,dataset,k_center,conf);	//�t�׫ܺC  //��
	printf("CS=%lf\n",index[15]);

	for(i = 0;i < k; i++)
	{
		if(k_center[i].count > 3)
		{
			calcflag = 1;
		}
		else
		{
			calcflag = 0;
			break;
		}
	}
	if(calcflag == 1)
	{
		index[16]	=	Sym_Index(k,dataset,k_center,conf);//��
		printf("Sym=%lf\n",index[16]);
		//printf("Sym_Index����\n");
	}
	else
	{
		index[16]	=	0;
		printf("����Sym_Index\n");
	}

	index[17]	=	DunnI(k,dataset,conf);			//�t�׫ܺC	//��
	printf("Dunn=%lf\n",index[17]);
	index[18]	=	WL1(k,dataset,k_center,conf);	//��
	printf("WL1=%lf\n",index[18]);
	//printf("DunnI����\n");
/**/
//--------------------------------------------------------------------------
// Index Value��X�ܿù�
//--------------------------------------------------------------------------
	//printf("Sym=%lf\n",index[15]);
	//printf("Dunn=%lf\n",index[16]);
	
	//printf("FDI2=%lf\n",index[13]);
	//printf("CSI=%lf\n",index[13]);
	//printf("DunnI=%lf\n",index[14]);
	output_index(k,index,Fname[0].file_name,conf);
//--------------------------------------------------------------------------
// ��ƿ�X
//--------------------------------------------------------------------------
	//��X������
	//out_info(k,time,filename,indexname,conf,index_var[0]);	
	if(conf[0].dim <= 3)
	{
		if(	conf[0].dim <= 2 )
		{
			Gnuplot2D_Data(k,dataset,conf,filename);
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
// ����O����
//--------------------------------------------------------------------------
	for( i = 0; i < k; i++ )
	{
		free(k_center[i].point);
	}
	for( i = 0; i < conf[0].datasize; i++ )
	{
		free(dataset[i].u);
		free(dataset[i].dist);
	}
	//free(k_center);
	free(d_max);
	free(d_min);
	free(index);
	free(nodataIndex);

}

