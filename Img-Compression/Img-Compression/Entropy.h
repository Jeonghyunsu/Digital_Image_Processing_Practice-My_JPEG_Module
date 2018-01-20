#pragma once

#include <iomanip>>
#include <crtdbg.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "Format.h"
#include "opencv2\opencv.hpp"

using namespace std;
using namespace cv;

#define PI 3.141592
#define TABLESIZE 8
#define EOF_NUM 256
#define NONVALUE -256

void ZigZag(double** dct, double** Zigzag_array, int nHeight, int nWidth);
void ZigZag_Dec(double** dct, double** Zigzag_array, int nHeight, int nWidth);
void RunLevelEncoding(double** Zigzag_array, short** run_level_array, int nHeight, int nWidth);
void RunLevelDecoding(double** Zigzag_array, short** run_level_array, int nHeight, int nWidth);

