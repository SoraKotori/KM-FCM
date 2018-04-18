#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	<math.h>
#include	"struct.h"
#include	"prototype.h"

/* 點對稱index */
double Sym_Index(int k, struct data dataset[], struct center k_center[], struct config conf[] )
{
	int		m, j, i, d;
	int		q, r;

	int		*choose;	// 符合條件者
	double	*reflected;	// 鏡射出來的對稱點

	double	distance_e;		// data與中心點距離
	double	distance_re;	// 附近data與對稱點距離
	double	tem;
	double	threshold;	// 門檻：資料點與對稱點的距離
	double	threshold_II;	// 門檻：最小的距

	double	sigma;
	double	distance_sym;	// 較接近對稱點的data，其距離平均
	double	distance_ps;	// 一個data的對稱指標

	double	Ei;		// cluster內的指標累加
	double	Epsilon;	// 所有cluster內的指標累加
	double	Maxdistance_center;	// 中心點之間的最大距離
	double	Sym;	// Sym-Index

	reflected = (double*) malloc ( conf[0].dim * sizeof (double) );
	choose = (int*) malloc ( conf[0].nearer_number * sizeof (int) );

	Epsilon = 0;
	for( j = 0; j < k; j++ ) // 計算每個cluster
	{
		Ei = 0;
		for( m = 0; m < conf[0].datasize ; m++ ) // cluster內的每個點都計算
		{
			if( dataset[m].cid == j ) // 確認分群
			{
				distance_e = point_distance( dataset[m].point, k_center[j].point, conf ); 
				// 資料點對中心點的歐幾里得距離 (Euclidean distance)，即是 de(x,c)

				for( d = 0; d < conf[0].dim; d++ )
				{
					reflected[d] = 2 * k_center[j].point[d] - dataset[m].point[d];
				}
				// 鏡射出來的對稱點，x*
				/*************************************************/
				
				threshold = 1000000;
				r = 0;	// 較接近的對稱點計數初始化
				for( i = 0; i < conf[0].datasize; i++ )
				{
					if( dataset[i].cid == j )
					{
						distance_re = point_distance( dataset[i].point, reflected, conf );
						if( distance_re < threshold )
						{ 
							threshold = distance_re;
							choose[r] = i;
						}
						// 求出距離對稱點最接近距離及data位置
					}
				}

				r = 1;	// 較接近對稱點的data計數初始化
				while( r < conf[0].nearer_number )	// 達到預計的較接近對稱點的data數
				{
					threshold_II = 1000000;
					for( i = 0; i < conf[0].datasize; i++ )
					{
						if( dataset[i].cid == j )
						{
							distance_re = point_distance( dataset[i].point, reflected, conf );
							// 資料點與對稱點的歐幾里得距離 (Euclidean distance)，即是 dis
			
							if( distance_re > threshold && distance_re - threshold < threshold_II )	// 範圍門檻限制
							{
								tem = distance_re; // 符合條件的距離先暫存
								threshold_II = distance_re - threshold; // 距離差門檻縮小
								choose[r] = i; // data位置記錄
							}
							// 找出較接近的一點
						}
					}
					threshold = tem; // 距離門檻放寬
					r++;	// 較接近對稱點的data計數累加
				}

				sigma = 0;
				for( q = 0; q < conf[0].nearer_number ; q++ )
				{ 
					i = choose[q]; //  呼叫出所有較接近對稱點的data位置
					sigma = sigma + point_distance( dataset[i].point, reflected, conf ); // 距離加總 
				}
				distance_sym = sigma / conf[0].nearer_number; // 平均

				/*************************************************/

				distance_ps = distance_sym * distance_e; //一個data的點對稱衡量指標
				Ei = Ei + distance_ps; // 累加cluster內所有點
			}	
		}
		Epsilon = Epsilon + Ei; // 累加所有cluster
	}

	Maxdistance_center = 0;
	for( i = 0; i < k; i++ )
	{
		for( j = 0; j < k; j++ )
		{
			if( i != j )
			{
				tem = point_distance( k_center[i].point, k_center[j].point, conf );
				if( tem > Maxdistance_center )
				{
					Maxdistance_center = tem; // 計算中心點之間的最大歐幾里得距離
				}
			}
		}
	}

	tem = k;
	Sym = (1/tem) * (1/Epsilon) * Maxdistance_center; // Sym

	free( reflected );
	free( choose );

	return Sym;
}