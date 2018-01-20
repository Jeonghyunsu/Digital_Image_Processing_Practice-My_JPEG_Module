#pragma once

#include <iostream>
#include <crtdbg.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iomanip>
#include "opencv2\opencv.hpp"

#define PI 3.141592
#define TABLESIZE 8
#define EOF_NUM 256

#define CLIP(x) (((x) < 0) ? 0 : (((x) > 255) ? 255 : (x)))

using namespace std;
using namespace cv;

void DCT(unsigned char** Y, double** dct, int nHeight, int nWidth);
void IDCT(unsigned char** Ori_Value, double** idct, int nHeight, int nWidth);