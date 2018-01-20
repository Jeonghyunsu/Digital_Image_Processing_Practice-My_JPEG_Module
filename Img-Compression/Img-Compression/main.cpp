#define HEIGHT 512
#define WIDTH 512
#define TABLESIZE 8

//512 X 512 X 24bit lena.jpg
#include "Encoding.h"
#include "Decoding.h"

#include "opencv2\opencv.hpp"

#define EOF_NUM 255.0

using namespace std;
using namespace cv;

int main()
{
	
	// Encoding
	int nHeight = 512, nWidth = 512;
	string filename = "test2.bmp"; string encoding_filename = "test2.zip";
	Encoding(filename, encoding_filename, nHeight, nWidth);
	
	// Decoding
	//string filename_ = "test2.raw"; string decoding_filename = "test2.zip";
	//Decoding(filename_, decoding_filename);
	
	return 0;
}











