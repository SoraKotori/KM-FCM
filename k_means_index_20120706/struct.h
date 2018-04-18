#pragma once

struct data{
	int		id;
	double	*point;
	double	*u;
	double	*dist; //點和中心的距離
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
	int		datasize;	//由計算得來
	int		dim;		//由計算得來
	int		max_k;		//由計算得來
	int		center_f;
	double	m;
	int		iter;
	int		index;
	int		vbar;		//計算平均中心
	int		pic;
	int		pic_h;
	int		pic_w;
	int		nearer_number; //Sym_Index需要
};


struct name
{
	char	*file_name;				// 宣告資料集檔名
	char	*conf_name;				// 宣告設定檔檔名
	char	*index_name;			// 宣告指標名稱
};