#pragma once
#include <crtdbg.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "opencv2\opencv.hpp"

using namespace std;
using namespace cv;
#define PI 3.1415926535

//Convert RGB ¡æ YUV
void ReadRGBFormat_JPEG(unsigned char** Y, unsigned char** U, unsigned char** V, const char* filename);
void Convert_YUV420(unsigned char** Y, unsigned char** U, unsigned char** V, unsigned char* Y420, unsigned char* U420, unsigned char* V420, int nHeight, int nWidth);
void ReadRGBFormat(unsigned char** Y, unsigned char** U, unsigned char** V, int nHeight, int nWidth, const char* filename);
void ReadYUV420Format(unsigned char* Y420, unsigned char* U420, unsigned char* V420, int nHeight, int nWidth, const char* filename);
void Convert_YUV420_2ptr(unsigned char** U, unsigned char** V, unsigned char** U420, unsigned char** V420, int nHeight, int nWidth);
void WriteYUV420Format(unsigned char** Y, unsigned char** U420, unsigned char** V420, int nHeight, int nWidth, const char* filename);
void ReadBMPFormat(unsigned char** Y, unsigned char** U, unsigned char** V, int nHeight, int nWidth, const char* filename);
void RGB_input(unsigned char* RGB, unsigned char* R, unsigned char* G, unsigned char* B, int nHeight, int nWidth);

// Memory Management
template<typename T> T** MemAlloc2D(int nHeight, int nWidth, int nInitVal)
{
	T** rtn = new T*[nHeight];
	for (int h = 0; h < nHeight; h++)
	{
		rtn[h] = new T[nWidth];
		memset(rtn[h], nInitVal, sizeof(T) * nWidth);
	}
	return rtn;
}
template<typename T> void MemFree2D(T** arr2D, int nHeight)
{
	for (int h = 0; h < nHeight; h++)
	{
		delete[] arr2D[h];
	}
	delete[] arr2D;
}

// File Read & Write
void FileRead(const char* strFilename, unsigned char** arr2D, int nHeight, int nWidth);
void FileWrite(const char* strFilename, unsigned char** arr2D, int nHeight, int nWidth);
