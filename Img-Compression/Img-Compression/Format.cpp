#define PI 3.141592
#define TABLESIZE 8
#define EOF_NUM 255.0

//512 X 512 X 24bit lena.jpg
#include "Format.h"
#include <iostream>
#include "opencv2\opencv.hpp"
#include <math.h>
#include <iomanip>

using namespace std;
using namespace cv;

void ReadBMPFormat(unsigned char** Y, unsigned char** U, unsigned char** V, int nHeight, int nWidth, const char* filename)
{
	unsigned char* RGB = (unsigned char*)malloc(sizeof(unsigned char)*(nHeight*nWidth * 3));
	unsigned char* ch_in_1 = (unsigned char*)malloc(sizeof(unsigned char)*(nHeight*nWidth));
	unsigned char* ch_in_2 = (unsigned char*)malloc(sizeof(unsigned char)*(nHeight*nWidth));
	unsigned char* ch_in_3 = (unsigned char*)malloc(sizeof(unsigned char)*(nHeight*nWidth));

	unsigned char* header = (unsigned char*)malloc(sizeof(unsigned char) * 54);
	FILE* input;
	fopen_s(&input, filename, "rb");
	fread(header, 54, sizeof(unsigned char), input);
	fread(RGB, 512 * 512 * 3, sizeof(unsigned char), input);
	fclose(input);

	for (int i = 0; i < nHeight*nWidth * 3; i++)
	{
		if (i % 3 == 0)ch_in_1[i / 3] = RGB[i];//b
		else if (i % 3 == 1)ch_in_2[i / 3] = RGB[i];//g
		else if (i % 3 == 2)ch_in_3[i / 3] = RGB[i];//r/////////////////////////////////
	}
	RGB_input(RGB, ch_in_1, ch_in_2, ch_in_3, nHeight, nWidth);
	int channel_num = 0;
	for (int h = 0; h < nHeight; h++)
		for (int w = 0; w < nWidth; w++)
		{
			Y[h][w] = saturate_cast<unsigned char>((0.299*ch_in_1[channel_num] + 0.587*ch_in_2[channel_num] + 0.114*ch_in_3[channel_num]));
			U[h][w] = saturate_cast<unsigned char>(-0.169*ch_in_1[channel_num] - 0.332*ch_in_2[channel_num] + 0.500*ch_in_3[channel_num] + 128.0);
			V[h][w] = saturate_cast<unsigned char>(0.5*ch_in_1[channel_num] - 0.419*ch_in_2[channel_num] - 0.0813*ch_in_3[channel_num] + 128.0);
			channel_num++;
		}
	delete[] RGB, ch_in_1, ch_in_2, ch_in_3, header;
}

void RGB_input(unsigned char* RGB, unsigned char* R, unsigned char* G, unsigned char* B, int nHeight, int nWidth)
{
	int rgb_index = 0;
	int h = 0, w = 0;

	for (rgb_index = 0; rgb_index < nHeight*nWidth * 3; rgb_index++)
		if (rgb_index % 3 == 0)
		{
			*B++= RGB[rgb_index];		
		}

	h = 0, w = 0;
	for (rgb_index = 0; rgb_index < nHeight*nWidth * 3; rgb_index++)
		if (rgb_index % 3 == 1)
		{
			*G++ = RGB[rgb_index];	
		}

	h = 0, w = 0;
	for (rgb_index = 0; rgb_index < nHeight*nWidth * 3; rgb_index++)
		if (rgb_index % 3 == 2)
		{
			*R++ = RGB[rgb_index];
		}
}

void ReadRGBFormat(unsigned char** Y, unsigned char** U, unsigned char** V, int nHeight, int nWidth, const char* filename)
{
	unsigned char* RGB = (unsigned char*)malloc(sizeof(unsigned char)*(nHeight*nWidth * 3));
	unsigned char* ch_in_1 = (unsigned char*)malloc(sizeof(unsigned char)*(nHeight*nWidth));
	unsigned char* ch_in_2 = (unsigned char*)malloc(sizeof(unsigned char)*(nHeight*nWidth));
	unsigned char* ch_in_3 = (unsigned char*)malloc(sizeof(unsigned char)*(nHeight*nWidth));

	FILE* input;
	fopen_s(&input, filename, "rb");
	fread(RGB, 512 * 512 * 3, sizeof(unsigned char), input);
	fclose(input);

	for (int i = 0; i < nHeight*nWidth * 3; i++)
	{
		if (i % 3 == 0)ch_in_1[i / 3] = RGB[i];//b
		else if (i % 3 == 1)ch_in_2[i / 3] = RGB[i];//g
		else if (i % 3 == 2)ch_in_3[i / 3] = RGB[i];//r
	}

	int channel_num = 0;
	for (int h = 0; h < nHeight; h++)
		for (int w = 0; w < nWidth; w++)
		{
			Y[h][w] = saturate_cast<unsigned char>((0.299*ch_in_1[channel_num] + 0.587*ch_in_2[channel_num] + 0.114*ch_in_3[channel_num]));
			U[h][w] = saturate_cast<unsigned char>(-0.169*ch_in_1[channel_num] - 0.332*ch_in_2[channel_num] + 0.500*ch_in_3[channel_num] + 128.0);
			V[h][w] = saturate_cast<unsigned char>(0.5*ch_in_1[channel_num] - 0.419*ch_in_2[channel_num] - 0.0813*ch_in_3[channel_num] + 128.0);
			channel_num++;
		}
	delete[] RGB, ch_in_1, ch_in_2, ch_in_3;
}
void ReadYUV420Format(unsigned char* Y420, unsigned char* U420, unsigned char* V420, int nHeight, int nWidth, const char* filename)
{
	FILE* input;
	fopen_s(&input, filename, "rb");
	fread(Y420, 512 * 512 * 3 >> 1, sizeof(unsigned char), input);
	fread(U420, 512 * 512 >>2, sizeof(unsigned char), input);
	fread(V420, 512 * 512 >>2, sizeof(unsigned char), input);

	cout << "파일 입력" << endl;
	fclose(input);
}

void ReadRGBFormat_JPEG(unsigned char** Y, unsigned char** U, unsigned char** V, const char* filename)
{
	Mat Ori_Img = imread(filename);
	int nHeight = Ori_Img.rows;
	int nWidth = Ori_Img.cols;

	unsigned char** ch_in_1 = MemAlloc2D<unsigned char>(nHeight, nWidth, 0);
	unsigned char** ch_in_2 = MemAlloc2D<unsigned char>(nHeight, nWidth, 0);
	unsigned char** ch_in_3 = MemAlloc2D<unsigned char>(nHeight, nWidth, 0);

	for (int h = 0; h < nHeight; h++)
		for (int w = 0; w < nWidth; w++)
		{
			Vec3b RGB = Ori_Img.at<Vec3b>(h, w);
			ch_in_1[h][w] = RGB[2];//R
			ch_in_2[h][w] = RGB[1];//G
			ch_in_3[h][w] = RGB[0];//B
		}

	for (int h = 0; h < nHeight; h++)
		for (int w = 0; w < nWidth; w++)
		{
			Y[h][w] = saturate_cast<unsigned char>((0.299*ch_in_1[h][w] + 0.587*ch_in_2[h][w] + 0.114*ch_in_3[h][w]));
			U[h][w] = saturate_cast<unsigned char>(-0.169*ch_in_1[h][w] - 0.332*ch_in_2[h][w] + 0.500*ch_in_3[h][w] + 128.0);
			V[h][w] = saturate_cast<unsigned char>(0.5*ch_in_1[h][w] - 0.419*ch_in_2[h][w] - 0.0813*ch_in_3[h][w] + 128.0);
		}

	MemFree2D<unsigned char>(ch_in_1, nHeight);
	MemFree2D<unsigned char>(ch_in_2, nHeight);
	MemFree2D<unsigned char>(ch_in_3, nHeight);
}
void Convert_YUV420(unsigned char** Y, unsigned char** U, unsigned char** V, unsigned char* Y420, unsigned char* U420, unsigned char* V420, int nHeight, int nWidth)
{
	int i = 0, j = 0;
	for (int h = 0; h < nHeight; h += 2)
		for (int w = 0; w < nWidth; w += 2)
		{
			*U420++ = (U[h][w] + U[h][w + 1] + U[h + 1][w] + U[h + 1][w + 1]) / 4;
			*V420++ = (V[h][w] + V[h][w + 1] + V[h + 1][w] + V[h + 1][w + 1]) / 4;
		}
	for (int h = 0; h < nHeight; h++)for (int w = 0; w < nWidth; w++)*Y420++ = Y[h][w];
}
void Convert_YUV420_2ptr(unsigned char** U, unsigned char** V, unsigned char** U420, unsigned char** V420, int nHeight, int nWidth)
{
	int i = 0, j = 0;
	for (int h = 0; h < nHeight; h += 2)
	{
		for (int w = 0; w < nWidth; w += 2)
		{
			U420[h/2][w/2] = (U[h][w] + U[h][w + 1] + U[h + 1][w] + U[h + 1][w + 1]) / 4;
			V420[h/2][w/2] = (V[h][w] + V[h][w + 1] + V[h + 1][w] + V[h + 1][w + 1]) / 4;
		}
	}
}

void FileRead(const char* strFilename, unsigned char** arr2D, int nHeight, int nWidth)
{
	FILE* fp_in;
	fopen_s(&fp_in, strFilename, "rb");
	for (int h = 0; h < nHeight; h++)
	{
		fread(arr2D[h], sizeof(unsigned char), nWidth, fp_in);
	}
	cout << "파일 입력" << endl;
	fclose(fp_in);
}
void FileWrite(const char* strFilename, unsigned char** arr2D, int nHeight, int nWidth)
{
	FILE* fp_out;
	fopen_s(&fp_out, strFilename, "wb");
	for (int h = 0; h < nHeight; h++)
	{
		fwrite(arr2D[h], sizeof(unsigned char), nWidth, fp_out);
	}

	cout << "파일 출력" << endl;
	fclose(fp_out);
}

void WriteYUV420Format(unsigned char** Y, unsigned char** U420, unsigned char** V420, int nHeight, int nWidth, const char* filename)
{
	FILE* output;
	fopen_s(&output, filename, "wb");
	for (int h = 0; h < nHeight; h++)
	{
		fwrite(Y[h], sizeof(unsigned char), nWidth, output);
	}
	for (int h = 0; h < nHeight/2; h++)
	{
		fwrite(U420[h], sizeof(unsigned char), nWidth/2, output);
	}
	for (int h = 0; h < nHeight/2; h++)
	{
		fwrite(V420[h], sizeof(unsigned char), nWidth/2, output);
	}
	cout << "출력완료" << endl;
	fclose(output);
}
