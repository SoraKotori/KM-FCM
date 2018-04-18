#ifndef prototype
#define prototype

#define FALSE 0
#define TRUE 1
#define MAX_STRING 255 
#define CENTER_DIFF pow(10,-5) 


/***Input***/
void	Input_Conf(struct config conf[], char *confname);
void	Input_FileConf(struct config conf[],char *filename);  //2011.08.11 Add
void	Input_Data(struct data dataset[],struct config conf[],char *filename);
void 	define_hw(struct data dataset[],struct config conf[]);

/*Fuzzy*/
void	center_f1(int k,struct center k_center[],double max[],double min[],struct config conf[]);
void	center_f2(int k,struct center k_center[],struct data dataset[],struct config conf[]);
void	membership(int k,struct data dataset[],struct center k_center[],struct config conf[]);
void	f_center(int k,struct data dataset[],struct center k_center[],struct config conf[]);
double	object(int k,struct data dataset[],struct center k_center[],struct config conf[]);
void	assgin(int k,struct data dataset[],struct config conf[]);
//void	fuzzy(int k,struct data dataset[],struct config conf[],char *filename);
void	fuzzy(int k,struct data dataset[],double Var_value [],double Sep_value [],double Under_value [],double Over_value [],struct config conf[],char *filename);
void	membership_initialize(int k, struct data dataset[], struct config conf[]);

/*fuzzy_lib*/
void	sum_cluster_dist(int k,struct data dataset[],struct center k_center[],struct config conf[]);
void	cluster_max_min(int k,struct data dataset[],struct center k_center[],struct config conf[]);
void	Initialize(int k,struct data dataset[],struct center k_center[],struct config conf[]);
void	delete_noData_center(struct center k_center[],struct center Old_k_center[],struct config conf[]);
void	delete_same_center(struct center k_center[],struct config conf[],int data_K);

/*index_lib*/
void	cal_vbar_barycentre(int k,struct center k_center[],double v_bar[], struct config conf[]);
void	cal_vbar_gocenter(int k,struct center k_center[],double v_bar[], struct config conf[]);
void	cal_vbar_allPointsCentre(struct data dataset[],double v_bar[], struct config conf[]);
double	Min_VV(int k,struct center k_center[],struct config conf[],int PowerD);
double	Median_VV(int k,struct center k_center[],struct config conf[],int PowerD);
void    quicksort_InputBuffer(int size, double InputBuffer[]);

/*index*/
double	FDI(int k,struct data dataset[],struct center k_center[],struct config conf[]);
double	FDI2(int k,struct data dataset[],struct center k_center[],struct config conf[]);

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
//速度很慢 CSI、Dunn
double	CSI(int k,struct data dataset[],struct center k_center[],struct config conf[]);
double	DunnI(int k,struct data dataset[],struct config conf[]);
//2011.12.26
double Sym_Index(int k, struct data dataset[], struct center k_center[], struct config conf[] );
double CS(int k,struct data dataset[],struct center k_center[],struct config conf[]);

//WI
void	MinW (double WiV [],struct config conf[],char *filename);
void	WI(double VarV [], double SepV [], double WiV [],struct config conf[],char *filename);
double	Var(int k, struct data dataset[],struct center k_center[],struct config conf[],char *filename);
double	Sep(int k, struct data dataset[],struct center k_center[],struct config conf[]);
//SVI
void	MinSV (double SViV [],struct config conf[],char *filename);
void	SVI(double UnderV [], double OverV [], double SViV [],struct config conf[],char *filename);
double	Under(int k, struct data dataset[],struct center k_center[],struct config conf[],char *filename);
double	Over(int k,struct center k_center[],struct config conf[]);
//2012.06.19 WL Index
double	WL1(int k,struct data dataset[],struct center k_center[],struct config conf[],char *filename);
double	WL2(int k,struct data dataset[],struct center k_center[],struct config conf[],char *filename);


/*Output*/
/*
void	graphic(int k,char *filename,char *indexname);
void	pic_hw(int k,struct data dataset[],struct config conf[],char *filename,char *indexname);
void	graphic_hw(int k,char *filename,char *indexname);
void	out_bat(char *filename,char *indexname);
*/

void	out_info(int k,double time,char *filename,char *indexname,struct config conf[],struct k_number num_k[]);
void 	output(int k,char *filename,struct data dataset[],struct config conf[]);
void	output_center(int k,struct center k_center[],char *filename,struct config conf[]);
void	out_cluster(int k,struct data dataset[],char *filename, struct config conf[]);
void	output_New_clusterANDcenter(struct data dataset[],struct center k_center[],char *filename,struct config conf[]);
void	output_Old_clusterANDcenter(struct data Old_dataset[],struct center Old_k_center[],char *filename,struct config conf[]);
void	output_DataNumber(int k,struct center k_center[],char *filename,struct config conf[]);
void   	output_index(int k,double index[],char *filename,struct config conf[]);
//void    output_index(int k,double index[],char *filename,char *indexname,struct config conf[]);
void    output_WIndex(double VarV [], double SepV [], double WiV [],char *filename,struct config conf[]);
void    output_SVIndex(double UnderV [], double OverV [], double SViV [],char *filename,struct config conf[]);
//12.06.24 輸出FCM疊代次數
void	outputIteration(int k,char *filename,int iteration);
void	outputElement(int k,struct data dataset[],struct center k_center[],char *filename,struct config conf[]);

/*Output Gnuplot*/
void	Gnuplot3D_Data(int k,struct data dataset[],struct config conf[],char *filename);
void	Gnuplot3D_Graphic(int k,char *filename);
void	Image_Gnuplot2D_Data(int k,struct data dataset[],struct config conf[],char *filename);
void	Image_Gnuplot2D_Graphic(int k,char *filename);
void	Image_Gnuplot_bat(int k,char *filename);
void	Gnuplot2D_Data(int k,struct data dataset[],struct config conf[],char *filename);
void	Gnuplot2D_Center(int k,struct center k_center[],struct config conf[],char *filename);
void	Gnuplot2D_Graphic(int k,char *filename);
void	Gnuplot_bat(int k,char *filename);

/*Output Time*/
void	outputTimes(char  *action, char *filename, float total_time, int flag);
void	outputTimes_Cluster(char *filename,int k,float time);


/*others*/
double	point_distance(double var1[],double var2[],struct config conf[]);
double	var_max(double var,double var_max);
double	var_min(double var,double var_min);



#endif