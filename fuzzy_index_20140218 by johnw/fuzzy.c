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
	//�ܼƫŧi
	int		i,j,d;
	int		nodataflag;		//����������s����������I (k_center[i].count != 0)
	int		lowdataflag;	//����p��Sym (k_center[i].count >3)
	int		samecenterflag;	//�P�_�O�_���ۦP�������I
	int		samecenterflag_k;
	int		calcflag;		//���ƪ�����
	int		iteration = 0;	//�N��
	int		data_K;		//����������I�����ߡA�ѤU�X��
	struct	center	*k_center;
	double	*d_max,*d_min;
	double	difference=0.0, index_past=0.0, index_present=0.0;	// �פ���󪺰Ѽ�
	double	center_dist;
	double	*index;

	//2012.02.14�s�W
	struct	center	*Old_k_center;
	struct	data	*Old_dataset; 
	conf[0].original_k = k;


	calcflag = 0;
	samecenterflag = 0;//���S���ۦP�������I
	nodataflag = 0;		//����Data
//--------------------------------------------------------------------------
	//��l��
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
	//printf("Fuzzy�GK%d�}�l\n",k);
    //printf("FUZZY�ɮפj�p�G%d\n",conf[0].datasize);
//--------------------------------------------------------------------------

//��l�� U�x�} �� �����I
	if(conf[0].initial_fuzzy == 0)
	{
		//��l��U�x�}
		membership_initialize(k,dataset,conf);
	}
	else 
	{	//��l�Ƥ����I
		if(conf[0].initial_fuzzy == 1)
		{
			//�p�⤤���I������
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
		//�z�L�üƤ����I�p���l��U�x�}
		membership(k,dataset,k_center,conf);
	}
	
	iteration = 0;
	//printf("Fuzzy�GK%d_��l�Ƥ����I&��l��U�x�}����\n",k);
	while(1)
	{
		//�p��s�����I
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
				printf("�ϥΪ�l��membership\n");
			}
			else
			{
				printf("�ϥΪ�l�Ƥ����I\n");
			}
			for(i=0;i<k;i++)
			{
				printf("��%d���ߡG",i);
				for(d = 0;d <conf[0].dim; d++)
				{
					printf("%lf\t",k_center[i].point[d]);
				}
				printf("\n");
			}
		}

		//�s��s��U�x�}
		membership(k,dataset,k_center,conf);
		
		//���t����I�ݩ���Ӥ����I
		assgin(k,dataset,conf);
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
				if(center_dist < pow(10,-5))
					// remark by johnw: two identical centroids=center_dist < pow(10,-6)
					// Li's setting: 10^-6 (approaching to 0
					// Johnw's setting: 10^-5
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

		//�ˬd�O�_�����@�s�S��Data	
		//���FSym�ݭn�C�@�s����3��Data�H�W�A��LIndex���u�n��Data�N�i�H
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
	
		//���p�Y�@�s�̭��S������I�Aiteration�|�W�[
		if( nodataflag == 1 || samecenterflag == 1)
		{
			calcflag++;
		}
		//printf("samecenterflag=%d\n",samecenterflag);
		//printf("nodataflag=%d\n",nodataflag);
		//printf("calcflag=%d\n",calcflag);
		
		//���p�C�@�s��������I�Ϊ̬Y�@�s�S������I�����p�W�L1000���A�N�p��ؼШ禡
		if( (nodataflag == 0 && samecenterflag == 0)|| calcflag>1501 )
		{
			calcflag = 0;
			//�ؼШ禡
			index_present	=	object(k,dataset,k_center,conf);
			difference	=	fabs(index_past - index_present);

			//if( difference < ( fabs(index_present) * conf[0].end_var ) && iteration > 201) //�ФŨϥΡA�|�ɭP�����I�ܪ񪺪��p�A���D�A�[�W�N�ƭ���
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

//��XFCM�|�N����
	outputIteration(k,filename,iteration);

//���t����I�ݩ���Ӥ����I
	membership(k,dataset,k_center,conf);
	assgin(k,dataset,conf);
	Initialize(k,dataset,k_center,conf);


	printf("<<<< Fuzzy ���s���� >>>\n");

//--------------------------------------------------------------------------
// �ˬd
//	1.�O�_���Y�@�s�S������I
//	2.�O�_���ۦP�������I
// �R���H�W��ت��p�������I
//--------------------------------------------------------------------------
	printf("conf[0].original_k=%d\n",conf[0].original_k);
	//�ˬd�O�_�����@�s�S��Data
	nodataflag = 0;
	for(i = 0;i < conf[0].original_k; i++)
	{
		if(k_center[i].count == 0)
		{
			k--;
			nodataflag = 1; //nodataflag=1��ܦ��Y�@�s�S������I
		}
	}
	printf("nodataflag=%d\n",nodataflag);

	data_K = k;
	conf[0].real_k = k;
	printf("data_K=%d\n",data_K);
	printf("conf[0].real_k=%d\n",conf[0].real_k);

	if(nodataflag == 1)
	{
		//�ʺA�t�m
		Old_k_center	=	(struct center*)malloc(conf[0].original_k*sizeof(struct center));
		Old_dataset		=	(struct data*)malloc(conf[0].datasize*sizeof(struct data));
	}

	if(nodataflag == 1)
	{
		memcpy(Old_k_center, k_center,conf[0].original_k*sizeof(struct center));
		//Old_k_center=k_center; //�O�����}�ۦP
		for(i=0; i<conf[0].original_k; i++)
		{
			for(d = 0; d<conf[0].dim; d++)
			{
				printf("Old_k_center[%d].point[%d]=%lf\n",i,d,Old_k_center[i].point[d]);
				printf("k_center[%d].point[%d]=%lf\n",i,d,k_center[i].point[d]);
			}
		}
		k_center=(struct center*)malloc(data_K*sizeof(struct center));
		printf("�Y�@�s���S������I\n");
		delete_noData_center(k_center,Old_k_center,conf);
	}
	
	//�ˬd�����I�O�_�ۦP-�Ĩ��p���Ӥ����I���覡
	samecenterflag = 0;//���S���ۦP�������I
	samecenterflag_k = 0;
	for(i = 0;i < data_K; i++)
	{
		for(j = i+1;j < data_K; j++)
		{
			center_dist	= point_distance(k_center[i].point,k_center[j].point,conf);
			//if(center_dist == 0.0)
			if(center_dist < CENTER_DIFF)
			{
				samecenterflag_k = 1; //samecenterflag=1��ܦ��Y��Ӥ����I�@��
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
			samecenterflag = 1; //��ܦ���Ӥ����I�@�ˡA�ݨ�U���P�_
		}
	}
	printf("samecenterflag=%d\n",samecenterflag);

	conf[0].real_k = k;
	printf("conf[0].original_k=%d\n",conf[0].original_k);
	printf("conf[0].real_k=%d\n",conf[0].real_k);

	if(nodataflag == 0 && samecenterflag == 1)
	{
		//�ʺA�t�m
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
		printf("���ۦP�������I\n");
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

		printf("�ˬd���ⶵ���G��k_center\n");
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
		//��X��T
		/*
		output(k,filename,dataset,conf);
		output_center(k,k_center,filename,conf);
		out_cluster(k,dataset,filename,conf);
		*/
		//��X�C�@�s����ƶq
		output_DataNumber(k,k_center,filename,conf);
		output_New_clusterANDcenter(dataset,k_center,filename,conf);
		output_Old_clusterANDcenter(Old_dataset,Old_k_center,filename,conf);
	}
	else
	{
		//��X��T
		output(k,filename,dataset,conf);
		output_center(k,k_center,filename,conf);
		out_cluster(k,dataset,filename,conf);
		//��X�C�@�s����ƶq
		output_DataNumber(k,k_center,filename,conf);
	}

//--------------------------------------------------------------------------
// �p��Index - WI&SVI
//--------------------------------------------------------------------------
	/*WI - �p�� Var �M Sep*/
	Var_value[conf[0].original_k] = Var(k,dataset,k_center,conf,filename);
	Sep_value[conf[0].original_k] = Sep(k,dataset,k_center,conf);
	/* SVI - �p�� Under �M Over */
	Under_value[conf[0].original_k] = Under(k,dataset,k_center,conf,filename);
	Over_value[conf[0].original_k] = Over(k,k_center,conf);
	printf("WI&SVI����\n");

//--------------------------------------------------------------------------
// �p��Index
//--------------------------------------------------------------------------
	index[0]	=	FDI(k,dataset,k_center,conf);//��
	printf("FDI����\n");
	index[1]	=	XBI(k,dataset,k_center,conf);//��
	printf("XBI����\n");
	index[2]	=	DBI(k,dataset,k_center,conf);//��
	printf("DBI����\n");
	index[3]	=	PC(k,dataset,conf);//��
	printf("PC����\n");
	index[4]	=	MPC(k,dataset,conf);//��
	printf("MPC����\n");
	index[5]	=	PE(k,dataset,conf);//��
	printf("PE����\n");
	index[6]	=	PBM(k,dataset,k_center,conf);//��
	printf("PBM����\n");
	index[7]	=	PBMF(k,dataset,k_center,conf);//��
	printf("PBMF����\n");
	index[8]	=	Kwon(k,dataset,k_center,conf);//��
	printf("Kwon����\n");
	index[9]	=	FSI(k,dataset,k_center,conf);//��
	printf("FSI����\n");
	index[10]	=	PCAESI(k,dataset,k_center,conf);//��
	printf("PCAESI����\n");
	index[11]	=	SC(k,dataset,k_center,conf);//��
	printf("SC����\n");
	index[12]	=	CHI(k,dataset,k_center,conf);//��
	printf("CHI����\n");
	index[13]	=	CS(k,dataset,k_center,conf);//��
	printf("CS_ck����\n");
	index[14]	=	WL1(k,dataset,k_center,conf,filename);//��
	printf("WL1����\n");
	index[15]	=	CSI(k,dataset,k_center,conf);	//�t�׫ܺC  //��
	printf("CSI����\n");
/*	*/

	//�ˬd�O�_�����@�sData<3�� (��Sym�ϥ�)
	lowdataflag = 0;
	for(i = 0;i < conf[0].original_k; i++)
	{
		if(k_center[i].count < 2)
		{
			lowdataflag = 1; //lowdataflag=1��ܦ��Y�@�s�Ӥָ���I
			break;
		}
	}
	printf("lowdataflag=%d\n",lowdataflag);
	if(lowdataflag == 0)
	{
		index[16]	=	Sym_Index(k,dataset,k_center,conf);//��
		printf("Sym_Index����\n");
	}
	else
	{
		index[16]	=	-1;
		printf("����Sym_Index\n");
	}

	index[17]	=	DunnI(k,dataset,conf);			//�t�׫ܺC	//��
	printf("DunnI����\n");
	
	index[18]	=	WL2(k,dataset,k_center,conf,filename);//��
	printf("WL2����\n");
	

	/**/
	//index[16]	=	FDI2(k,dataset,k_center,conf);
	//printf("FDI2����\n");

//--------------------------------------------------------------------------
// Index Value��X�ܿù�
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
	//printf("�� %d �s�AIndex�p�⧹���I\n",k);
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

//��X������
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
	//��X����
	outputElement(k,dataset,k_center,filename,conf);

	free(k_center);
	free(d_max);
	free(d_min);
	free(index);
	if(nodataflag == 1 || samecenterflag == 1)
	{
		free(Old_k_center);
	}
	//printf("<<<< Fuzzy.c���� >>>\n");

}
