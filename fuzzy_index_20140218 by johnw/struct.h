
struct	data{
	int		id;
	double	point[99];
	double	u[99];
	int		cid;
	int		h;
	int		w;
};

struct	center{
	int		cid;
	double	point[99];
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

struct	config
{
	int		datasize;	//�ѭp��o��
	int		dim;		//�ѭp��o��
	int		max_k;		//0:�H�y 1:Image Other:��ʿ�J
	//int	min_k;		
	//int 	center_f;	
	int		initial_fuzzy; //0:��l��MF 1:��l�Ƥ����I(��̤j�̤p�hrand) 2:��l�Ƥ����I(��쥻��Data�����I)
	int		eva;
	double	end_var;
	double	m;
	int		index;
	int		vbar;		//�p�⥭������
	int		pic;
	int		pic_h;
	int		pic_w;
	int		debug;
	int		nearer_number; //Sym_Index�ݭn
	int		original_k;	   //��l��K��
	int		real_k;		   //�u�ꪺK��
};
