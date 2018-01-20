#pragma once

#include <crtdbg.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iomanip>
#include <iostream>
#include "opencv2\opencv.hpp"

#define PI 3.141592
#define TABLESIZE 8
#define EOF_NUM 256

using namespace std;
using namespace cv;

void quantizationY(double** result_dct_Y, int nHeight, int nWidth);
void quantizationUV(double** result_dct_UV, int nHeight, int nWidth);
void Dec_quantizationY(double** result_dct_Y, int nHeight, int nWidth);
void Dec_quantizationUV(double** result_dct_UV, int nHeight, int nWidth);