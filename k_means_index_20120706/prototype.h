#ifndef prototype
#define prototype

#define MAX_STRING 255 
#define FALSE 0
#define TRUE 1


/*New Function = DataType.c*/
int *New_1D_intArr(int *Arr,long Size);
int **New_2D_intArr(int **Arr,long width,long Size);
double *New_1D_doubleArr(double *Arr,long Size);
double **New_2D_doubleArr(double **Arr,long width,long Size);

/*Free Function = DataType.c*/
void Free_2D_doubleArr(double **Arr,long width);
void Free_2D_intArr(int **Arr,long width);

/*index_lib*/
void	cal_vbar_barycentre(int k,struct center k_center[],double v_bar[], struct config conf[]);
void	cal_vbar_gocenter(int k,struct center k_center[],double v_bar[], struct config conf[]);
void	cal_vbar_allPointsCentre(struct data dataset[],double v_bar[], struct config conf[]);
double	Min_VV(int k,struct center k_center[],struct config conf[],int PowerD);


double	Median_VV(int k,struct center k_center[],struct config conf[],int PowerD);
void    quicksort_InputBuffer(int size, double InputBuffer[]);


/****Input****/
void	Input_Conf(struct config conf[],struct name Fname[]);
void	Input_FileConf(struct config conf[], struct name Fname[]);
void	Input_Data(struct data dataset[], struct config conf[], struct name Fname[]);
void	input(struct data dataset[],struct config conf[],char *filename);
void 	define_hw(struct data dataset[],struct config conf[]);

/***k-menas***/
void	center_point_f1(int k,struct center k_center[],double max[],double min[],struct config conf[]);
void 	center_point_f2(int k,struct center k_center[],struct data dataset[],struct config conf[]);
double	point_distance(double	var1[] , double	var2[], struct config conf[]);
void	assign(int k,struct data dataset[],struct config conf[]);
//double	assign(int i,int j,struct data dataset[],double distance,double min_distance);
void 	new_center(int k,struct center k_center[],struct config conf[]);
//2012.0707
void	new_center_data(int k,struct center k_center[],struct data dataset[],struct config conf[]);
void	avg_dist(int k,struct center k_center[],struct data dataset[],struct config conf[]);
double	sum_dist(int k,struct center k_center[],struct data dataset[],struct config conf[]);
void	data_center_dist(int k,struct center k_center[],struct data dataset[],struct config conf[]);
void	k_means(int k,struct data dataset[],struct config conf[],struct name Fname[]);
void	Initialize(int k,struct data dataset[],struct center k_center[],struct config conf[]);

/*index*/
double	DSI(int k,struct data dataset[],struct center k_center[],struct config conf[]);
double	XBI(int k,struct data dataset[],struct center k_center[],struct config conf[]);
double	DBI(int k,struct data dataset[],struct center k_center[],struct config conf[]);
double	PC(int k,struct data dataset[],struct config conf[]);
double	MPC(int k,struct data dataset[],struct config conf[]);
double	PE(int k, struct data dataset[], struct config conf[]);
double	PBM(int k,struct data dataset[],struct center k_center[],struct config conf[]);
double	PBMF(int k, struct data dataset[],struct center k_center[],struct config conf[]);
double	Kwon(int k,struct data dataset[],struct center k_center[],struct config conf[]);
double	FSI(int k,struct data dataset[],struct center k_center[],struct config conf[]);
double	PCAESI(int k,struct data dataset[],struct center k_center[],struct config conf[]);
double	SC(int k,struct data dataset[],struct center k_center[],struct config conf[]);
double	CHI(int k,struct data dataset[],struct center k_center[],struct config conf[]);
double	CSI(int k,struct data dataset[],struct center k_center[],struct config conf[]);
double	CS(int k,struct data dataset[],struct center k_center[],struct config conf[]);
double	Sym_Index(int k, struct data dataset[], struct center k_center[], struct config conf[] );
double	DunnI(int k,struct data dataset[],struct config conf[]);
//³t«×«ÜºC CSI¡BDunn

//2012.07.01 WL Index
double	WL(int k,struct data dataset[],struct center k_center[],struct config conf[]);
double	WL1(int k,struct data dataset[],struct center k_center[],struct config conf[]);


/*Output Gunplot*/
/*
void	cluster(int k,struct data dataset[],struct config conf[],char *filename,char *indexname);
void	output_center(int k,struct center k_center[],char *filename,struct config conf[]);
void	graphic(int k,char *filename,char *indexname);
void	pic_hw(int k,struct data dataset[],struct config conf[],char *filename,char *indexname);
void	graphic_hw(int k,char *filename,char *indexname);
void	out_bat(char *filename,char *indexname);
*/
void	Gnuplot3D_Data(int k,struct data dataset[],struct config conf[],char *filename);
void	Gnuplot3D_Graphic(int k,char *filename);
void	Image_Gnuplot2D_Data(int k,struct data dataset[],struct config conf[],char *filename);
void	Image_Gnuplot2D_Graphic(int k,char *filename);
void	Image_Gnuplot_bat(int k,char *filename);
void	Gnuplot2D_Data(int k,struct data dataset[],struct config conf[],char *filename);
void	Gnuplot2D_Center(int k,struct center k_center[],struct config conf[],char *filename);
void	Gnuplot2D_Graphic(int k,char *filename);
void	Gnuplot_bat(int k,char *filename);

/*Output*/

void	out_info(int k,double time,char *filename,char *indexname,struct config conf[],struct k_number num_k[]);
void 	output(int k,struct data dataset[],char *filename,struct config conf[]);
void	out_cluster(int k,struct data dataset[],char *filename, struct config conf[]);
void	output_center(int k,struct center k_center[],char *filename,struct config conf[]);
void   	output_index(int k,double index[],char *filename,struct config conf[]);
//void	outputTimes(char  *action,char *filename);
void	output_DataNumber(int k,struct center k_center[],char *filename,struct config conf[]);
void	outputTimes(char  *action, char *filename, float total_time, int flag);
void	outputTimes_Cluster(char *filename,int k,float time);
void	outputIteration(int k,char *filename,int iteration);

/*Others*/
double 	var_max(double var,double var_max);
double 	var_min(double var,double var_min);

#endif