
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
	int		datasize;	//由計算得來
	int		dim;		//由計算得來
	int		max_k;		//0:人造 1:Image Other:手動輸入
	//int	min_k;		
	//int 	center_f;	
	int		initial_fuzzy; //0:初始化MF 1:初始化中心點(找最大最小去rand) 2:初始化中心點(找原本的Data當中心點)
	int		eva;
	double	end_var;
	double	m;
	int		index;
	int		vbar;		//計算平均中心
	int		pic;
	int		pic_h;
	int		pic_w;
	int		debug;
	int		nearer_number; //Sym_Index需要
	int		original_k;	   //原始的K值
	int		real_k;		   //真實的K值
};
