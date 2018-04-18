#pragma once

struct data{
	int		id;
	double	*point;
	double	*u;
	double	*dist; //�I�M���ߪ��Z��
	int		cid;
	int		h;
	int		w;
};

struct center{
	int		cid;
	double	*point;
	double	max[99];
	double	min[99];
	int		count;
	double	dist_sum;
	double  avg_dist;
};

struct k_number
{
    int k;
    double index_var;
};

struct config{
	int		datasize;	//�ѭp��o��
	int		dim;		//�ѭp��o��
	int		max_k;		//�ѭp��o��
	int		center_f;
	double	m;
	int		iter;
	int		index;
	int		vbar;		//�p�⥭������
	int		pic;
	int		pic_h;
	int		pic_w;
	int		nearer_number; //Sym_Index�ݭn
};


struct name
{
	char	*file_name;				// �ŧi��ƶ��ɦW
	char	*conf_name;				// �ŧi�]�w���ɦW
	char	*index_name;			// �ŧi���ЦW��
};