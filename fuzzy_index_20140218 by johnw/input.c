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
	//printf("��Ƶ���=%d\n",conf[0].datasize);
	//printf("��ƺ���=%d\n",conf[0].dim);
	printf("k���j��=%d\n",conf[0].max_k);
	//printf("�̤p�s��=%d;\n",&conf[0].min_k);
	printf("��l�Ƥ�k�M�w=%d\n",conf[0].initial_fuzzy);
	printf("membership=%lf\n",conf[0].m);
	printf("�פ��=%lf\n",conf[0].end_var);
	printf("Index=%d��\n",conf[0].index);
	printf("vbar=%d\n",conf[0].vbar);
	printf("�O�_���Ϥ�=%d\n",conf[0].pic);
	printf("�Ϥ�����=%d\n",conf[0].pic_h);
	printf("�Ϥ��e��=%d\n",conf[0].pic_w);
	printf("�����Ҧ�=%d\n",conf[0].debug);
	printf("�]�w�ɸ��J����...\n");
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

//�p�����
//fgets()�q�ɮפ@��@�檺Ū����ơA�@�ݤT�ӰѼ�
// �Ĥ@�ӰѼƬ��x�s��J��ƪ��}�C�A�ĤG�ӰѼƬ��Ӧ�̦h�X�Ӧr���A�ĤT�ӰѼƬ����V���c FILE ������

	fgets(tmp_str, MAX_STRING, InputF); //Ū���Ĥ@��r��
	//printf("%s",tmp_str);
	
	ch = strtok(tmp_str, ",");
	ch = strtok (NULL, ",");  //�ư���ID������
	while (ch != NULL)
	{
		//printf ("%s\n",ch);
		ch = strtok (NULL, ",");
		DimCount++;
	}

	conf[0].dim = DimCount;
	//printf("Dim�G%d\n",conf[0].dim);

//fseek()�i�]�w�b�ɮפ��s������m�A�@�ݤT�ӰѼơA�Ĥ@�ӰѼƬ����V���c FILE �����СA�ĤG�ӰѼƬ��첾�r���q�A�ĤT�ӰѼƬ��첾���_���}�A
//�i�H�O�ɮ׶}�Y SEEK_SET �B�{�b��m SEEK_CUR ���ɮ׵��� SEEK_END 
	fseek(InputF,0,SEEK_SET);

//�p���Ƶ���
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
	//printf("��ƶq:%d\n",conf[0].datasize);

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

//���J���
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
 	
/*//�غa
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
