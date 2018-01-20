#pragma once

#include <iomanip>>
#include <crtdbg.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <bitset>
#include <queue>
#include <list>
#include <algorithm>
#include "opencv2\opencv.hpp"

#include "Format.h"
#include "DCT.h"
#include "Quantization.h"
#include "Entropy.h"
#include "Node.h"
#include "KeyValue.h"

#define PI 3.141592
#define TABLESIZE 8
#define EOF_NUM 256

#define NONVALUE -256
#define LASTINDEX 31
#define IMAGESCALE 256

#define CLIP(x) (((x) < 0) ? 0 : (((x) > 255) ? 255 : (x)))

using namespace std;
using namespace cv;

void Encoding(string filename, string encoding_filename, int nHeight, int nWidth);
void Encoding_Huffman(short**  run_level_array, int nHeight, FILE* output);
queue<unsigned char> EncodingQueue(short* pixel_data, KeyValue** final_table, int table_num, unsigned short listsizes);
void Encoding_Write(queue<unsigned char> Queue, KeyValue** final_table, unsigned char* filewrite_ptr,
	int filewrite_ptr_size, int table_num, unsigned short pixelsize, FILE* output);


