#include "Quantization.h"

void quantizationY(double** result_dct_Y, int nHeight, int nWidth) {
	int Y_table[TABLESIZE][TABLESIZE] = {
		16, 11, 10, 16, 24, 40, 51, 61,
		12, 12, 14, 19, 26, 58, 60, 55,
		14, 13, 16, 24, 40, 57, 69, 56,
		14, 17, 22, 29, 51, 87, 80, 82,
		18, 22, 37, 56, 68, 109, 103, 77,
		24, 35, 55, 64, 81, 104, 113, 92,
		49, 64, 78, 87, 103, 121, 120, 101,
		72, 92, 95, 98, 112, 100, 103, 99
	};
	int h, w, i, j;
	for (h = 0; h < nHeight / TABLESIZE; h++)
		for (w = 0; w < nWidth / TABLESIZE; w++)
			for (i = 0; i < TABLESIZE; i++)
				for (j = 0; j < TABLESIZE; j++) {
					result_dct_Y[(h * TABLESIZE) + i][(w * TABLESIZE) + j] = round(result_dct_Y[(h * TABLESIZE) + i][(w * TABLESIZE) + j] / Y_table[i][j]);
				}
}


void quantizationUV(double** result_dct_UV, int nHeight, int nWidth) {
	int UV_table[TABLESIZE][TABLESIZE] = {
		17, 18, 24, 47, 99, 99, 99, 99,
		18, 21, 26, 66, 99 ,99, 99, 99,
		24, 26, 56, 99, 99, 99, 99, 99,
		47, 66, 99, 99, 99, 99, 99, 99,
		99, 99, 99, 99, 99, 99, 99, 99,
		99, 99, 99, 99, 99, 99, 99, 99,
		99, 99, 99, 99, 99, 99, 99, 99,
		99, 99, 99, 99, 99, 99, 99, 99
	};
	int h, w, i, j;
	for (h = 0; h < nHeight / TABLESIZE; h++)
		for (w = 0; w < nWidth / TABLESIZE; w++)
			for (i = 0; i < TABLESIZE; i++)
				for (j = 0; j < TABLESIZE; j++) {
					result_dct_UV[(h * TABLESIZE) + i][(w * TABLESIZE) + j] = round(result_dct_UV[(h * TABLESIZE) + i][(w * TABLESIZE) + j] / UV_table[i][j]);
				}
}

void Dec_quantizationY(double** result_dct_Y, int nHeight, int nWidth) {
	int Y_table[TABLESIZE][TABLESIZE] = {
		16, 11, 10, 16, 24, 40, 51, 61,
		12, 12, 14, 19, 26, 58, 60, 55,
		14, 13, 16, 24, 40, 57, 69, 56,
		14, 17, 22, 29, 51, 87, 80, 82,
		18, 22, 37, 56, 68, 109, 103, 77,
		24, 35, 55, 64, 81, 104, 113, 92,
		49, 64, 78, 87, 103, 121, 120, 101,
		72, 92, 95, 98, 112, 100, 103, 99
	};
	int h, w, i, j;
	for (h = 0; h < nHeight / TABLESIZE; h++)
		for (w = 0; w < nWidth / TABLESIZE; w++)
			for (i = 0; i < TABLESIZE; i++)
				for (j = 0; j < TABLESIZE; j++) {
					result_dct_Y[(h * TABLESIZE) + i][(w * TABLESIZE) + j] = round(result_dct_Y[(h * TABLESIZE) + i][(w * TABLESIZE) + j] * Y_table[i][j]);
				}
}

void Dec_quantizationUV(double** result_dct_UV, int nHeight, int nWidth) {
	int UV_table[TABLESIZE][TABLESIZE] = {
		17, 18, 24, 47, 99, 99, 99, 99,
		18, 21, 26, 66, 99 ,99, 99, 99,
		24, 26, 56, 99, 99, 99, 99, 99,
		47, 66, 99, 99, 99, 99, 99, 99,
		99, 99, 99, 99, 99, 99, 99, 99,
		99, 99, 99, 99, 99, 99, 99, 99,
		99, 99, 99, 99, 99, 99, 99, 99,
		99, 99, 99, 99, 99, 99, 99, 99
	};
	int h, w, i, j;
	for (h = 0; h < nHeight / TABLESIZE; h++)
		for (w = 0; w < nWidth / TABLESIZE; w++)
			for (i = 0; i < TABLESIZE; i++)
				for (j = 0; j < TABLESIZE; j++) {
					result_dct_UV[(h * TABLESIZE) + i][(w * TABLESIZE) + j] = round(result_dct_UV[(h * TABLESIZE) + i][(w * TABLESIZE) + j] * UV_table[i][j]);
				}
}