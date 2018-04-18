#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	<math.h>
#include	"struct.h"
#include	"prototype.h"

/* �I���index */
double Sym_Index(int k, struct data dataset[], struct center k_center[], struct config conf[] )
{
	int		m, j, i, d;
	int		q, r;

	int		*choose;	// �ŦX�����
	double	*reflected;	// ��g�X�Ӫ�����I

	double	distance_e;		// data�P�����I�Z��
	double	distance_re;	// ����data�P����I�Z��
	double	tem;
	double	threshold;	// ���e�G����I�P����I���Z��
	double	threshold_II;	// ���e�G�̤p���Z

	double	sigma;
	double	distance_sym;	// ���������I��data�A��Z������
	double	distance_ps;	// �@��data����٫���

	double	Ei;		// cluster�������в֥[
	double	Epsilon;	// �Ҧ�cluster�������в֥[
	double	Maxdistance_center;	// �����I�������̤j�Z��
	double	Sym;	// Sym-Index

	reflected = (double*) malloc ( conf[0].dim * sizeof (double) );
	choose = (int*) malloc ( conf[0].nearer_number * sizeof (int) );

	Epsilon = 0;
	for( j = 0; j < k; j++ ) // �p��C��cluster
	{
		Ei = 0;
		for( m = 0; m < conf[0].datasize ; m++ ) // cluster�����C���I���p��
		{
			if( dataset[m].cid == j ) // �T�{���s
			{
				distance_e = point_distance( dataset[m].point, k_center[j].point, conf ); 
				// ����I�襤���I���ڴX���o�Z�� (Euclidean distance)�A�Y�O de(x,c)

				for( d = 0; d < conf[0].dim; d++ )
				{
					reflected[d] = 2 * k_center[j].point[d] - dataset[m].point[d];
				}
				// ��g�X�Ӫ�����I�Ax*
				/*************************************************/
				
				threshold = 1000000;
				r = 0;	// �����񪺹���I�p�ƪ�l��
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
						// �D�X�Z������I�̱���Z����data��m
					}
				}

				r = 1;	// ���������I��data�p�ƪ�l��
				while( r < conf[0].nearer_number )	// �F��w�p�����������I��data��
				{
					threshold_II = 1000000;
					for( i = 0; i < conf[0].datasize; i++ )
					{
						if( dataset[i].cid == j )
						{
							distance_re = point_distance( dataset[i].point, reflected, conf );
							// ����I�P����I���ڴX���o�Z�� (Euclidean distance)�A�Y�O dis
			
							if( distance_re > threshold && distance_re - threshold < threshold_II )	// �d����e����
							{
								tem = distance_re; // �ŦX���󪺶Z�����Ȧs
								threshold_II = distance_re - threshold; // �Z���t���e�Y�p
								choose[r] = i; // data��m�O��
							}
							// ��X�����񪺤@�I
						}
					}
					threshold = tem; // �Z�����e��e
					r++;	// ���������I��data�p�Ʋ֥[
				}

				sigma = 0;
				for( q = 0; q < conf[0].nearer_number ; q++ )
				{ 
					i = choose[q]; //  �I�s�X�Ҧ����������I��data��m
					sigma = sigma + point_distance( dataset[i].point, reflected, conf ); // �Z���[�` 
				}
				distance_sym = sigma / conf[0].nearer_number; // ����

				/*************************************************/

				distance_ps = distance_sym * distance_e; //�@��data���I��ٿŶq����
				Ei = Ei + distance_ps; // �֥[cluster���Ҧ��I
			}	
		}
		Epsilon = Epsilon + Ei; // �֥[�Ҧ�cluster
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
					Maxdistance_center = tem; // �p�⤤���I�������̤j�ڴX���o�Z��
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