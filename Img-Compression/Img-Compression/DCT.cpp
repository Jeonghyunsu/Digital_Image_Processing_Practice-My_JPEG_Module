#include "DCT.h"


void DCT(unsigned char** Y, double** dct, int nHeight, int nWidth) {
	double Cu, Cv;
	int h, w, u, v, i, j, x, y;

	for (h = 0; h < nHeight / TABLESIZE; h++)
		for (w = 0; w < nWidth / TABLESIZE; w++)
			for (u = 0; u < TABLESIZE; u++)
				for (v = 0; v < TABLESIZE; v++)
				{
					if (u == 0)Cu = 1.0 / sqrt(2.0);
					else Cu = 1.0;

					if (v == 0) Cv = 1.0 / sqrt(2.0);
					else Cu = (1.0);

					double sum = 0.0;
					for (i = 0; i < TABLESIZE; i++)
						for (j = 0; j < TABLESIZE; j++)
							sum += (Y[h * TABLESIZE + i][w * TABLESIZE + j] - 128)* cos((2 * i + 1) * u * acos(-1) / 16.0) * cos((2 * j + 1) * v * acos(-1) / 16.0);

					sum *= 0.25 * Cu * Cv;//cos행렬과 행렬변환된 cosine들의 곱이 결과적으로 3가지의 형태로 나올 수 있다. 
					dct[h * TABLESIZE + u][w * TABLESIZE + v] = sum;
				}
}

void IDCT(unsigned char** Ori_Value, double** idct, int nHeight, int nWidth)
{

	double Ci, Cj;
	int h, w, u, v, i, j, x, y;
	for (h = 0; h < nHeight / TABLESIZE; h++)
		for (w = 0; w < nWidth / TABLESIZE; w++)
			for (u = 0; u < TABLESIZE; u++)
				for (v = 0; v < TABLESIZE; v++)
				{
					double sum = 0.0;
					for (i = 0; i < TABLESIZE; i++)
						for (j = 0; j < TABLESIZE; j++)
						{
							if (i == 0)Ci = 1.0 / sqrt(2.0);
							else Ci = 1.0;

							if (j == 0) Cj = 1.0 / sqrt(2.0);
							else Cj = (1.0);


							sum += Ci * Cj*(idct[h * TABLESIZE + i][w * TABLESIZE + j])* cos((2 * u + 1) * i * acos(-1) / 16.0) * cos((2 * v + 1) * j * acos(-1) / 16.0);
						}
					sum *= 0.25;
					sum += 128;
					Ori_Value[h * TABLESIZE + u][w * TABLESIZE + v] = CLIP(sum);
				}
}