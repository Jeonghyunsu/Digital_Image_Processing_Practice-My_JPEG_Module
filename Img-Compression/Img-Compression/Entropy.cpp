#include "Entropy.h"

void ZigZag(double** dct, double** Zigzag_array, int nHeight, int nWidth)
{
	int h = 0, w = 0;
	int h_limit = nHeight / TABLESIZE -1;
	int w_limit = nWidth / TABLESIZE -1;
	int num = 0;
	for (int i = 0; i < nHeight*TABLESIZE; i++)
	{
		Zigzag_array[i][0] = dct[h*TABLESIZE][w*TABLESIZE];
		//(0,0)
		Zigzag_array[i][1] = dct[h*TABLESIZE][w*TABLESIZE + 1]; Zigzag_array[i][2] = dct[h*TABLESIZE + 1][w*TABLESIZE];
		//(0,1)(1,0)
		Zigzag_array[i][3] = dct[h*TABLESIZE + 2][w*TABLESIZE]; Zigzag_array[i][4] = dct[h*TABLESIZE + 1][w*TABLESIZE + 1]; Zigzag_array[i][5] = dct[h*TABLESIZE][w*TABLESIZE + 2];
		//(2,0)(1,1)(0,2)
		Zigzag_array[i][6] = dct[h*TABLESIZE][w*TABLESIZE + 3]; Zigzag_array[i][7] = dct[h*TABLESIZE + 1][w*TABLESIZE + 2]; Zigzag_array[i][8] = dct[h*TABLESIZE + 2][w*TABLESIZE + 1]; Zigzag_array[i][9] = dct[h*TABLESIZE + 3][w*TABLESIZE];
		//(0,3)(1,2)(2,1)(3,0)
		Zigzag_array[i][10] = dct[h*TABLESIZE + 4][w*TABLESIZE]; Zigzag_array[i][11] = dct[h*TABLESIZE + 3][w*TABLESIZE + 1]; Zigzag_array[i][12] = dct[h*TABLESIZE + 2][w*TABLESIZE + 2]; Zigzag_array[i][13] = dct[h*TABLESIZE + 1][w*TABLESIZE + 3]; Zigzag_array[i][14] = dct[h*TABLESIZE][w*TABLESIZE + 4];
		//(4,0)(3,1)(2,2)(1,3)(0,4)
		Zigzag_array[i][15] = dct[h*TABLESIZE][w*TABLESIZE + 5]; Zigzag_array[i][16] = dct[h*TABLESIZE + 1][w*TABLESIZE + 4]; Zigzag_array[i][17] = dct[h*TABLESIZE + 2][w*TABLESIZE + 3]; Zigzag_array[i][18] = dct[h*TABLESIZE + 3][w*TABLESIZE + 2]; Zigzag_array[i][19] = dct[h*TABLESIZE + 4][w*TABLESIZE + 1]; Zigzag_array[i][20] = dct[h*TABLESIZE + 5][w*TABLESIZE];
		//(0,5)(1,4)(2,3)(3,2)(4,1)(5,0)
		Zigzag_array[i][21] = dct[h*TABLESIZE + 6][w*TABLESIZE]; Zigzag_array[i][22] = dct[h*TABLESIZE + 5][w*TABLESIZE + 1]; Zigzag_array[i][23] = dct[h*TABLESIZE + 4][w*TABLESIZE + 2]; Zigzag_array[i][24] = dct[h*TABLESIZE + 3][w*TABLESIZE + 3]; Zigzag_array[i][25] = dct[h*TABLESIZE + 2][w*TABLESIZE + 4]; Zigzag_array[i][26] = dct[h*TABLESIZE + 1][w*TABLESIZE + 5]; Zigzag_array[i][27] = dct[h*TABLESIZE][w*TABLESIZE + 6];
		//(6,0)(5,1)(4,2)(3,3)(2,4)(1,5)(0,6)
		Zigzag_array[i][28] = dct[h*TABLESIZE][w*TABLESIZE + 7]; Zigzag_array[i][29] = dct[h*TABLESIZE + 1][w*TABLESIZE + 6]; Zigzag_array[i][30] = dct[h*TABLESIZE + 2][w*TABLESIZE + 5]; Zigzag_array[i][31] = dct[h*TABLESIZE + 3][w*TABLESIZE + 4]; Zigzag_array[i][32] = dct[h*TABLESIZE + 4][w*TABLESIZE + 3]; Zigzag_array[i][33] = dct[h*TABLESIZE + 5][w*TABLESIZE + 2]; Zigzag_array[i][34] = dct[h*TABLESIZE + 6][w*TABLESIZE + 1]; Zigzag_array[i][35] = dct[h*TABLESIZE + 7][w*TABLESIZE + 0];
		//(0,7)(1,6)(2,5)(3,4)(4,3)(5,2)(6,1)(7,0)
		Zigzag_array[i][36] = dct[h*TABLESIZE + 7][w*TABLESIZE + 1]; Zigzag_array[i][37] = dct[h*TABLESIZE + 6][w*TABLESIZE + 2]; Zigzag_array[i][38] = dct[h*TABLESIZE + 5][w*TABLESIZE + 3]; Zigzag_array[i][39] = dct[h*TABLESIZE + 4][w*TABLESIZE + 4]; Zigzag_array[i][40] = dct[h*TABLESIZE + 3][w*TABLESIZE + 5]; Zigzag_array[i][41] = dct[h*TABLESIZE + 2][w*TABLESIZE + 6]; Zigzag_array[i][42] = dct[h*TABLESIZE + 1][w*TABLESIZE + 7];
		//(7,1)(6,2)(5,3)(4,4)(3,5)(2,6)(1,7)
		Zigzag_array[i][43] = dct[h*TABLESIZE + 2][w*TABLESIZE + 7]; Zigzag_array[i][44] = dct[h*TABLESIZE + 3][w*TABLESIZE + 6]; Zigzag_array[i][45] = dct[h*TABLESIZE + 4][w*TABLESIZE + 5]; Zigzag_array[i][46] = dct[h*TABLESIZE + 5][w*TABLESIZE + 4]; Zigzag_array[i][47] = dct[h*TABLESIZE + 6][w*TABLESIZE + 3]; Zigzag_array[i][48] = dct[h*TABLESIZE + 7][w*TABLESIZE + 2];
		//(2,7)(3,6)(4,5)(5,4)(6,3)(7,2)
		Zigzag_array[i][49] = dct[h*TABLESIZE + 7][w*TABLESIZE + 3]; Zigzag_array[i][50] = dct[h*TABLESIZE + 6][w*TABLESIZE + 4]; Zigzag_array[i][51] = dct[h*TABLESIZE + 5][w*TABLESIZE + 5]; Zigzag_array[i][52] = dct[h*TABLESIZE + 4][w*TABLESIZE + 6]; Zigzag_array[i][53] = dct[h*TABLESIZE + 3][w*TABLESIZE + 7];
		//(7,3)(6,4)(5,5)(4,6)(3,7)
		Zigzag_array[i][54] = dct[h*TABLESIZE + 4][w*TABLESIZE + 7]; Zigzag_array[i][55] = dct[h*TABLESIZE + 5][w*TABLESIZE + 6]; Zigzag_array[i][56] = dct[h*TABLESIZE + 6][w*TABLESIZE + 5]; Zigzag_array[i][57] = dct[h*TABLESIZE + 7][w*TABLESIZE + 4];
		//(4,7)(5,6)(6,5)(7,4)
		Zigzag_array[i][58] = dct[h*TABLESIZE + 7][w*TABLESIZE + 5]; Zigzag_array[i][59] = dct[h*TABLESIZE + 6][w*TABLESIZE + 6]; Zigzag_array[i][60] = dct[h*TABLESIZE + 5][w*TABLESIZE + 7];
		//(7,5)(6,6)(5,7)
		Zigzag_array[i][61] = dct[h*TABLESIZE + 6][w*TABLESIZE + 7]; Zigzag_array[i][62] = dct[h*TABLESIZE + 7][w*TABLESIZE + 6];
		//(6,7)(7,6)
		Zigzag_array[i][63] = dct[h*TABLESIZE + 7][w*TABLESIZE + 7];
		//(7,7)		

		for (int z = 0; z < TABLESIZE*TABLESIZE; z++)
			if (Zigzag_array[i][z] == -0)Zigzag_array[i][z] = 0;

		if (h == h_limit && w == w_limit)
		{
			break;
		}
		if (w == w_limit)
		{
			w = 0;
			h++;
		}
		else w++;
	}
}
void RunLevelEncoding(double** Zigzag_array, short** run_level_array, int nHeight, int nWidth)
{
	int zero_temp = 0, temp_loop = 0;

	for (int i = 0; i < nHeight; i++)
	{
		zero_temp = 0;
		temp_loop = 0;
		for (int j = 0; j < nWidth; j++)
		{
			if (Zigzag_array[i][j] == 0 && j != 63)
			{
				zero_temp++;
			}
			else if (Zigzag_array[i][j] != 0)
			{
				run_level_array[i][temp_loop++] = zero_temp;
				zero_temp = 0;
				run_level_array[i][temp_loop++] = Zigzag_array[i][j];
			}
			else if (Zigzag_array[i][j] == 0 && j == 63)
			{
				run_level_array[i][temp_loop++] = zero_temp;
				run_level_array[i][temp_loop++] = Zigzag_array[i][j];
			}

		}
		for (int k = temp_loop - 2; k < nWidth; k++)
			run_level_array[i][k] = EOF_NUM;
	}
}

void RunLevelDecoding(double** Zigzag_array, short** run_level_array, int nHeight, int nWidth)
{
	int zero_temp = 0, temp_loop = 0;

	for (int i = 0; i < nHeight; i++)
	{
		for (int j = 0; j < nWidth; j++)
		{
			if (run_level_array[i][j] != EOF_NUM)
			{
				Zigzag_array[i][j] = run_level_array[i][j];
			}
			else
				Zigzag_array[i][j] = 0;
		}
	}
}

void ZigZag_Dec(double** dct, double** Zigzag_array_Previous, int nHeight, int nWidth)
{
	
	int i = 0;
	double* Zigzag_array = (double*)malloc(sizeof(double)*TABLESIZE*TABLESIZE);

	for (int h = 0; h < nHeight/TABLESIZE; h++)
	{	
		for (int w = 0; w < nWidth/TABLESIZE; w++)
		{
			int index = 0;
			int result_index = 0;
			while (index < TABLESIZE*TABLESIZE)
			{
				if (index % 2 == 0)//zero count 
				{
					if (Zigzag_array_Previous[i][index] == 0)
					{
						index++;
					}
					else
					{
						int zero_size = Zigzag_array_Previous[i][index];
						for (int next = 0; next < zero_size; next++)
						{
							Zigzag_array[result_index] = 0;
							result_index++;
						}
						index++;
					}
				}
				else
				{
					if (Zigzag_array_Previous[i][index] == 0)
					{
						for (int i = result_index; i < TABLESIZE*TABLESIZE; i++)
						{
							Zigzag_array[result_index] = 0;
							result_index++;
						}
						break;
					}
					else
					{
						Zigzag_array[result_index] = Zigzag_array_Previous[i][index];
						result_index++;
						index++;
					}
				}
			}

			dct[h*TABLESIZE][w*TABLESIZE] = Zigzag_array[0];
			//(0,0)
			dct[h*TABLESIZE][w*TABLESIZE + 1] = Zigzag_array[1]; dct[h*TABLESIZE + 1][w*TABLESIZE] = Zigzag_array[2];
			//(0,1)(1,0)
			dct[h*TABLESIZE + 2][w*TABLESIZE] = Zigzag_array[3]; dct[h*TABLESIZE + 1][w*TABLESIZE + 1] = Zigzag_array[4]; dct[h*TABLESIZE][w*TABLESIZE + 2] = Zigzag_array[5];
			//(2,0)(1,1)(0,2)
			dct[h*TABLESIZE][w*TABLESIZE + 3] = Zigzag_array[6]; dct[h*TABLESIZE + 1][w*TABLESIZE + 2] = Zigzag_array[7]; dct[h*TABLESIZE + 2][w*TABLESIZE + 1] = Zigzag_array[8]; dct[h*TABLESIZE + 3][w*TABLESIZE] = Zigzag_array[9];
			//(0,3)(1,2)(2,1)(3,0)
			dct[h*TABLESIZE + 4][w*TABLESIZE] = Zigzag_array[10]; dct[h*TABLESIZE + 3][w*TABLESIZE + 1] = Zigzag_array[11]; dct[h*TABLESIZE + 2][w*TABLESIZE + 2] = Zigzag_array[12]; dct[h*TABLESIZE + 1][w*TABLESIZE + 3] = Zigzag_array[13]; dct[h*TABLESIZE][w*TABLESIZE + 4] = Zigzag_array[14];
			//(4,0)(3,1)(2,2)(1,3)(0,4)
			dct[h*TABLESIZE][w*TABLESIZE + 5] = Zigzag_array[15]; dct[h*TABLESIZE + 1][w*TABLESIZE + 4] = Zigzag_array[16]; dct[h*TABLESIZE + 2][w*TABLESIZE + 3] = Zigzag_array[17]; dct[h*TABLESIZE + 3][w*TABLESIZE + 2] = Zigzag_array[18]; dct[h*TABLESIZE + 4][w*TABLESIZE + 1] = Zigzag_array[19]; dct[h*TABLESIZE + 5][w*TABLESIZE] = Zigzag_array[20];
			//(0,5)(1,4)(2,3)(3,2)(4,1)(5,0)
			dct[h*TABLESIZE + 6][w*TABLESIZE] = Zigzag_array[21]; dct[h*TABLESIZE + 5][w*TABLESIZE + 1] = Zigzag_array[22]; dct[h*TABLESIZE + 4][w*TABLESIZE + 2] = Zigzag_array[23]; dct[h*TABLESIZE + 3][w*TABLESIZE + 3] = Zigzag_array[24]; dct[h*TABLESIZE + 2][w*TABLESIZE + 4] = Zigzag_array[25]; dct[h*TABLESIZE + 1][w*TABLESIZE + 5] = Zigzag_array[26]; dct[h*TABLESIZE][w*TABLESIZE + 6] = Zigzag_array[27];
			//(6,0)(5,1)(4,2)(3,3)(2,4)(1,5)(0,6)
			dct[h*TABLESIZE][w*TABLESIZE + 7] = Zigzag_array[28]; dct[h*TABLESIZE + 1][w*TABLESIZE + 6] = Zigzag_array[29]; dct[h*TABLESIZE + 2][w*TABLESIZE + 5] = Zigzag_array[30]; dct[h*TABLESIZE + 3][w*TABLESIZE + 4] = Zigzag_array[31]; dct[h*TABLESIZE + 4][w*TABLESIZE + 3] = Zigzag_array[32]; dct[h*TABLESIZE + 5][w*TABLESIZE + 2] = Zigzag_array[33]; dct[h*TABLESIZE + 6][w*TABLESIZE + 1] = Zigzag_array[34]; dct[h*TABLESIZE + 7][w*TABLESIZE + 0] = Zigzag_array[35];
			//(0,7)(1,6)(2,5)(3,4)(4,3)(5,2)(6,1)(7,0)
			dct[h*TABLESIZE + 7][w*TABLESIZE + 1] = Zigzag_array[36]; dct[h*TABLESIZE + 6][w*TABLESIZE + 2] = Zigzag_array[37]; dct[h*TABLESIZE + 5][w*TABLESIZE + 3] = Zigzag_array[38]; dct[h*TABLESIZE + 4][w*TABLESIZE + 4] = Zigzag_array[39]; dct[h*TABLESIZE + 3][w*TABLESIZE + 5] = Zigzag_array[40]; dct[h*TABLESIZE + 2][w*TABLESIZE + 6] = Zigzag_array[41]; dct[h*TABLESIZE + 1][w*TABLESIZE + 7] = Zigzag_array[42];
			//(7,1)(6,2)(5,3)(4,4)(3,5)(2,6)(1,7)
			dct[h*TABLESIZE + 2][w*TABLESIZE + 7] = Zigzag_array[43]; dct[h*TABLESIZE + 3][w*TABLESIZE + 6] = Zigzag_array[44]; dct[h*TABLESIZE + 4][w*TABLESIZE + 5] = Zigzag_array[45]; dct[h*TABLESIZE + 5][w*TABLESIZE + 4] = Zigzag_array[46]; dct[h*TABLESIZE + 6][w*TABLESIZE + 3] = Zigzag_array[47]; dct[h*TABLESIZE + 7][w*TABLESIZE + 2] = Zigzag_array[48];
			//(2,7)(3,6)(4,5)(5,4)(6,3)(7,2)
			dct[h*TABLESIZE + 7][w*TABLESIZE + 3] = Zigzag_array[49]; dct[h*TABLESIZE + 6][w*TABLESIZE + 4] = Zigzag_array[50]; dct[h*TABLESIZE + 5][w*TABLESIZE + 5] = Zigzag_array[51]; dct[h*TABLESIZE + 4][w*TABLESIZE + 6] = Zigzag_array[52]; dct[h*TABLESIZE + 3][w*TABLESIZE + 7] = Zigzag_array[53];
			//(7,3)(6,4)(5,5)(4,6)(3,7)
			dct[h*TABLESIZE + 4][w*TABLESIZE + 7] = Zigzag_array[54]; dct[h*TABLESIZE + 5][w*TABLESIZE + 6] = Zigzag_array[55]; dct[h*TABLESIZE + 6][w*TABLESIZE + 5] = Zigzag_array[56]; dct[h*TABLESIZE + 7][w*TABLESIZE + 4] = Zigzag_array[57];
			//(4,7)(5,6)(6,5)(7,4)
			dct[h*TABLESIZE + 7][w*TABLESIZE + 5] = Zigzag_array[58]; dct[h*TABLESIZE + 6][w*TABLESIZE + 6] = Zigzag_array[59]; dct[h*TABLESIZE + 5][w*TABLESIZE + 7] = Zigzag_array[60];
			//(7,5)(6,6)(5,7)
			dct[h*TABLESIZE + 6][w*TABLESIZE + 7] = Zigzag_array[61]; dct[h*TABLESIZE + 7][w*TABLESIZE + 6] = Zigzag_array[62];
			//(6,7)(7,6)
			dct[h*TABLESIZE + 7][w*TABLESIZE + 7] = Zigzag_array[63];
			//(7,7)		
			i++;
		}
	}

	delete Zigzag_array;
}










