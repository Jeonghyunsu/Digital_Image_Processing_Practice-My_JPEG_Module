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

void Decoding(string filename, string decoding_filename);
void Decoding_Huffman(short**  run_level_array, int nHeight, FILE* output);
unsigned char* Decoding_Read(short* value_ptr, unsigned char* fileread_ptr,
	unsigned short* tablesize_ptr, unsigned short* bitsize_ptr, unsigned short* bytesize_ptr,
	short* huffman_value_ptr, unsigned char* depth_ptr, KeyValue** table, unsigned short* pixelsize_ptr, FILE* input);

void MakeTable(KeyValue** final_table, KeyValue** table);
queue<unsigned char> DecodingQueue(unsigned short *bitsize_ptr, unsigned char* fileread_ptr);
void PixelStore(short* pixel_data, queue<unsigned char> dec_Queue, KeyValue** final_table, unsigned short* tablesize_ptr);


