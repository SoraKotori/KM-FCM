#include 	<stdio.h>
#include 	<stdlib.h>
#include	<string.h>
#include	<math.h>
#include	<limits.h>
#include	"struct.h"
#include	"prototype.h"

void	Input_Conf(struct config conf[],struct name Fname[])
{
	FILE *InputF;

	InputF=fopen(Fname[0].conf_name,"r");
	if(!InputF)
	{
		printf("[ERROR] Input_Conf()：No Input Config Data\n");
		exit(1);
	}

	fscanf(InputF,"center_f=%d;\n",&conf[0].center_f);
	fscanf(InputF,"membership=%lf;\n",&conf[0].m);
	fscanf(InputF,"iteration=%d;\n",&conf[0].iter);
	fscanf(InputF,"index=%d;\n",&conf[0].index);
	fscanf(InputF,"vbar=%d;\n",&conf[0].vbar);
	fscanf(InputF,"picture=%d;\n",&conf[0].pic);
	fscanf(InputF,"high=%d;\n",&conf[0].pic_h);
	fscanf(InputF,"width=%d;\n",&conf[0].pic_w);
//	fscanf(InputF,"debug=%d;\n",&conf[0].debug);

	fclose(InputF);

	//印出結果
	printf("初始化中心點的方法=%d\n",conf[0].center_f);
	printf("Membership=%lf\n",conf[0].m);
	printf("迭代次數=%d\n",conf[0].iter);
	printf("使用 %d 個Index\n",conf[0].index);
	printf("vbar=%d\n",conf[0].vbar);
	printf("是否為圖片=%d\n",conf[0].pic);
	printf("圖片高度=%d\n",conf[0].pic_h);
	printf("圖片寬度=%d\n",conf[0].pic_w);
//	printf("除錯模式=%d\n",conf[0].debug);
	printf("設定檔載入完畢...\n");
}

void	Input_FileConf(struct config conf[],struct name Fname[])
{
	char	*ch;
	char	tmp_str[MAX_STRING];
	int		SizeCount=0;
	int		DimCount=0;

	FILE *InputF;

	InputF=fopen(Fname[0].file_name, "r");
	
	if (InputF == NULL)
	{
		printf("[ERROR] Input_FileConf()：No Input Data\n");
		exit(1);
	}

//計算維度
	fgets(tmp_str, MAX_STRING, InputF); //讀取第一行字串
	
	ch = strtok(tmp_str, ",");
	ch = strtok (NULL, ",");  //排除掉ID的部分
	while (ch != NULL)
	{
		ch = strtok (NULL, ",");
		DimCount++;
	}

	conf[0].dim = DimCount;

	fseek(InputF,0,SEEK_SET);

//計算資料筆數
	if(fgets(tmp_str, MAX_STRING, InputF)!=NULL)
	{
		SizeCount=0;
		while(!feof(InputF))
		{
			if(fgets(tmp_str, MAX_STRING, InputF)!=NULL)
			{
				SizeCount++;
			}
		}
	}

	conf[0].datasize = SizeCount;

	fclose(InputF);

	printf("資料筆數=%d\n",conf[0].datasize);
	printf("資料維度=%d\n",conf[0].dim);
}

void	Input_Data(struct data dataset[],struct config conf[],struct name Fname[])
{
	int		i=0,d;
	char	tmp_str[MAX_STRING];

	FILE *InputF;

	InputF=fopen(Fname[0].file_name, "r");

	if(!InputF)
	{
		printf("[ERROR] Input_Data()：No Input Data\n");
		exit(1);
	}

//載入資料
	if(fgets(tmp_str, MAX_STRING, InputF)!=NULL)
	{	
		//printf("%s",tmp_str);
		//while(!feof(InputF))
		for(i=0; i<conf[0].datasize; i++)
		{
			fscanf(InputF,"%d",&dataset[i].id);
			//printf("%d",dataset[i].id);
			for(d = 0;d < conf[0].dim; d++)
			{
				fscanf(InputF,",%lf",&dataset[i].point[d]);
				//printf(",%lf",dataset[i].point[d]);
			}
			//i++;
			//printf("\n");
		}
	}
	
	fclose(InputF);
	printf("資料讀取完畢...\n");
}


void 	define_hw(struct data dataset[],struct config conf[])
{
    int h=0,w=0,i=0;
    for(h=0;h<conf[0].pic_h;h++)
    {
        for(w=0;w<conf[0].pic_w;w++)
        {
            dataset[i].h=h;
            dataset[i].w=w;
            i++;
        }
    }
}
