#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	<limits.h>
#include	<math.h>
#include	<string.h>
#include	"struct.h"
#include	"prototype.h"


void	Input_Conf(struct config conf[], char *confname)
{
	FILE *f;
	f=fopen(confname,"r");
	//fscanf(f,"data_size=%d;\n",&conf[0].datasize);
	//fscanf(f,"dim_size=%d;\n",&conf[0].dim);
	fscanf(f,"max_k=%d;\n",&conf[0].max_k);
	//fscanf(f,"min_k=%d;\n",&conf[0].min_k);
	fscanf(f,"initial_fuzzy=%d;\n",&conf[0].initial_fuzzy);
	fscanf(f,"membership=%lf;\n",&conf[0].m);
	fscanf(f,"evaluate=%d;\n",&conf[0].eva);
	fscanf(f,"end_var=%lf;\n",&conf[0].end_var);
	fscanf(f,"index=%d;\n",&conf[0].index);
	fscanf(f,"vbar=%d;\n",&conf[0].vbar);
	fscanf(f,"picture=%d;\n",&conf[0].pic);
	fscanf(f,"high=%d;\n",&conf[0].pic_h);
	fscanf(f,"width=%d;\n",&conf[0].pic_w);
	fscanf(f,"debug=%d;\n",&conf[0].debug);
	fclose(f);
	//printf("資料筆數=%d\n",conf[0].datasize);
	//printf("資料維度=%d\n",conf[0].dim);
	printf("k的大值=%d\n",conf[0].max_k);
	//printf("最小群數=%d;\n",&conf[0].min_k);
	printf("初始化方法決定=%d\n",conf[0].initial_fuzzy);
	printf("membership=%lf\n",conf[0].m);
	printf("終止值=%lf\n",conf[0].end_var);
	printf("Index=%d個\n",conf[0].index);
	printf("vbar=%d\n",conf[0].vbar);
	printf("是否為圖片=%d\n",conf[0].pic);
	printf("圖片高度=%d\n",conf[0].pic_h);
	printf("圖片寬度=%d\n",conf[0].pic_w);
	printf("除錯模式=%d\n",conf[0].debug);
	printf("設定檔載入完畢...\n");
}

void	Input_FileConf(struct config conf[],char *filename)
{
	char	*ch;
	char	tmp_str[MAX_STRING];
	int		SizeCount=0;
	int		DimCount=0;

	FILE *InputF;

	InputF=fopen(filename,"r");

	if(!InputF)
	{
		printf("NO INPUT DATA!");
		exit(0);
	}

//計算維度
//fgets()從檔案一行一行的讀取資料，共需三個參數
// 第一個參數為儲存輸入資料的陣列，第二個參數為該行最多幾個字元，第三個參數為指向結構 FILE 的指標

	fgets(tmp_str, MAX_STRING, InputF); //讀取第一行字串
	//printf("%s",tmp_str);
	
	ch = strtok(tmp_str, ",");
	ch = strtok (NULL, ",");  //排除掉ID的部分
	while (ch != NULL)
	{
		//printf ("%s\n",ch);
		ch = strtok (NULL, ",");
		DimCount++;
	}

	conf[0].dim = DimCount;
	//printf("Dim：%d\n",conf[0].dim);

//fseek()可設定在檔案中存取的位置，共需三個參數，第一個參數為指向結構 FILE 的指標，第二個參數為位移字元量，第三個參數為位移的起算位址，
//可以是檔案開頭 SEEK_SET 、現在位置 SEEK_CUR 或檔案結尾 SEEK_END 
	fseek(InputF,0,SEEK_SET);

//計算資料筆數
	if(fgets(tmp_str, MAX_STRING, InputF)!=NULL)
	{
		SizeCount=0;
		while(!feof(InputF))
		{
			if(fgets(tmp_str, MAX_STRING, InputF)!=NULL)
			{
				//printf("%s",tmp_str);
				SizeCount++;
			}
		}
	}

	conf[0].datasize = SizeCount;
	//printf("資料量:%d\n",conf[0].datasize);

	fclose(InputF);
}



void	Input_Data(struct data dataset[],struct config conf[],char *filename)
{
	int		i=0,d;
	char	tmp_str[MAX_STRING];

	FILE *InputF;

	InputF=fopen(filename,"r");

	if(!InputF)
	{
		printf("NO INPUT DATA!");
		exit(0);
	}

//載入資料
	if(fgets(tmp_str, MAX_STRING, InputF)!=NULL)
	{	
		//printf("%s",tmp_str);
		while(!feof(InputF))		
		{
			fscanf(InputF,"%d",&dataset[i].id);
			//printf("%d",dataset[i].id);
			for(d = 0;d < conf[0].dim; d++)
			{
				fscanf(InputF,",%lf",&dataset[i].point[d]);
				//printf(",%lf",dataset[i].point[d]);
			}
			i++;
			//printf("\n");
		}
	}
	

	fclose(InputF);

}



void define_hw(struct data dataset[],struct config conf[])
{
    //int h=0,w=0,i=0;
	int h,w;
	int i=0;


	for(h=0; h<conf[0].pic_h; h++)
    {
        for(w=0; w<conf[0].pic_w; w++)
        {
            dataset[i].h=h;
            dataset[i].w=w;
			//printf("%d.(%d,%d)\n",i,dataset[i].h,dataset[i].w);
            i++;
        }
    }
 	
/*//建榮
	for(w=conf[0].pic_w-1; w>=0; w--)
    {
        for(h=0; h<conf[0].pic_h; h++)
		{
			dataset[i].h=h;
			dataset[i].w=w;
			//printf("%d.(%d,%d)\n",i,dataset[i].h,dataset[i].w);
            i++;
        }
    }
*/
	

}
