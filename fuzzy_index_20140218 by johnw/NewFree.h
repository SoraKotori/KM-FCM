
//New Function = DataType.c
int *New_1D_intArr(int *Arr,long Size);
int **New_2D_intArr(int **Arr,long width,long Size);
double *New_1D_doubleArr(double *Arr,long Size);
double **New_2D_doubleArr(double **Arr,long width,long Size);

//Free Function = DataType.c
void Free_2D_doubleArr(double **Arr,long width);
void Free_2D_intArr(int **Arr,long width);

//Struct New
struct DOT *New_1D_DOTArr(struct DOT *Arr,long Size);	
struct DOT **New_2D_DOTArr(struct DOT **Arr,long width,long Size);
//Struct Free
void free_2D_DOT(struct DOT **Arr,long width);
