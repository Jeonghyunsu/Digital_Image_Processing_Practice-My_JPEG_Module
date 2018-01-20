#include "Decoding.h"

void Decoding(string filename, string decoding_filename)
{	
	unsigned short read_height;  unsigned short *read_height_ptr = &read_height;
	unsigned short read_width;  unsigned short *read_width_ptr = &read_width;
	FILE* input;
	fopen_s(&input, decoding_filename.c_str(), "rb");

	fread(read_height_ptr, sizeof(unsigned short), 1, input);
	fread(read_width_ptr, sizeof(unsigned short), 1, input);
	int nHeight = *read_height_ptr;
	int nWidth = *read_width_ptr;

	short** run_level_array_Y = MemAlloc2D<short>(nHeight*TABLESIZE, TABLESIZE*TABLESIZE, EOF_NUM);
	short** run_level_array_U = MemAlloc2D<short>(nHeight*TABLESIZE / 4, TABLESIZE*TABLESIZE, EOF_NUM);
	short** run_level_array_V = MemAlloc2D<short>(nHeight*TABLESIZE / 4, TABLESIZE*TABLESIZE, EOF_NUM);

	double** Zigzag_array_Y = MemAlloc2D<double>(nHeight*TABLESIZE, TABLESIZE*TABLESIZE, 0);
	double** Zigzag_array_U = MemAlloc2D<double>(nHeight*TABLESIZE / 4, TABLESIZE*TABLESIZE, 0);
	double** Zigzag_array_V = MemAlloc2D<double>(nHeight*TABLESIZE / 4, TABLESIZE*TABLESIZE, 0);
	
	double** dct_Y = MemAlloc2D<double>(nHeight, nWidth, 0);
	double** dct_U = MemAlloc2D<double>(nHeight / 2, nWidth / 2, 0);
	double** dct_V = MemAlloc2D<double>(nHeight / 2, nWidth / 2, 0);
	
	unsigned char** Y = MemAlloc2D<unsigned char>(nHeight, nWidth, 0);
	unsigned char** U420 = MemAlloc2D<unsigned char>(nHeight / 2, nWidth / 2, 0);
	unsigned char** V420 = MemAlloc2D<unsigned char>(nHeight / 2, nWidth / 2, 0);

	cout << "----------Decoding----------" << endl;

	Decoding_Huffman(run_level_array_Y, TABLESIZE*nHeight, input);
	Decoding_Huffman(run_level_array_U, TABLESIZE*nHeight /4, input);
	Decoding_Huffman(run_level_array_V, TABLESIZE*nHeight /4, input);
	fclose(input);

	RunLevelDecoding(Zigzag_array_Y, run_level_array_Y, nHeight * TABLESIZE, TABLESIZE*TABLESIZE);
	ZigZag_Dec(dct_Y, Zigzag_array_Y, nHeight, nWidth);
	Dec_quantizationY(dct_Y, nHeight, nWidth);
	IDCT(Y, dct_Y, nHeight, nWidth);

	RunLevelDecoding(Zigzag_array_U, run_level_array_U, nHeight * TABLESIZE / 4, TABLESIZE*TABLESIZE);
	ZigZag_Dec(dct_U, Zigzag_array_U, nHeight / 2, nWidth / 2);
	Dec_quantizationUV(dct_U, nHeight/2, nWidth/2);
	IDCT(U420, dct_U, nHeight/2, nWidth/2);

	RunLevelDecoding(Zigzag_array_V, run_level_array_V, nHeight * TABLESIZE / 4, TABLESIZE*TABLESIZE);
	ZigZag_Dec(dct_V, Zigzag_array_V, nHeight / 2, nWidth / 2);
	Dec_quantizationUV(dct_V, nHeight/2, nWidth/2);
	IDCT(V420, dct_V, nHeight/2, nWidth/2);

	WriteYUV420Format(Y, U420, V420, nHeight, nWidth, filename.c_str());

	MemFree2D<double>(Zigzag_array_Y, nHeight*TABLESIZE);
	MemFree2D<double>(Zigzag_array_U, nHeight*TABLESIZE / 4);
	MemFree2D<double>(Zigzag_array_V, nHeight*TABLESIZE / 4);

	MemFree2D<short>(run_level_array_Y, nHeight*TABLESIZE);
	MemFree2D<short>(run_level_array_U, nHeight*TABLESIZE / 4);
	MemFree2D<short>(run_level_array_V, nHeight*TABLESIZE / 4);

	MemFree2D<double>(dct_Y, nHeight);
	MemFree2D<double>(dct_U, nHeight / 2);
	MemFree2D<double>(dct_V, nHeight / 2);

	MemFree2D<unsigned char>(Y, nHeight);
	MemFree2D<unsigned char>(U420, nHeight / 2);
	MemFree2D<unsigned char>(V420, nHeight / 2);
}

void Decoding_Huffman(short**  run_level_array, int nHeight, FILE* input)
{
	short* value_ptr = NULL;  unsigned char* fileread_ptr = NULL;
	short* huffman_value = NULL; unsigned char* depth_ptr = NULL;
	unsigned short tablesize = NONVALUE; unsigned short* tablesize_ptr = &tablesize;
	unsigned short bytesize = NONVALUE; unsigned short* bytesize_ptr = &bytesize;
	unsigned short bitsize = NONVALUE; unsigned short* bitsize_ptr = &bitsize;

	unsigned short pixelsize = NONVALUE; unsigned short* pixelsize_ptr = &pixelsize;

	for (int loop = 0; loop < nHeight ; loop++)
	{
		KeyValue** table = (KeyValue**)malloc(sizeof(KeyValue*)*(IMAGESCALE << 1)); string code = "";//store KeyValue table
		memset(table, NULL, IMAGESCALE << 3);

		fileread_ptr = Decoding_Read(value_ptr, fileread_ptr, tablesize_ptr, bitsize_ptr, bytesize_ptr, huffman_value, depth_ptr, table, pixelsize_ptr, input);

		KeyValue** final_table = (KeyValue**)malloc(sizeof(KeyValue*)*(*tablesize_ptr));
		MakeTable(final_table, table);
	
		queue<unsigned char> dec_Queue = DecodingQueue(bitsize_ptr, fileread_ptr);
		PixelStore(run_level_array[loop], dec_Queue, final_table, tablesize_ptr);

		delete final_table, table;
	}
	delete fileread_ptr, value_ptr, huffman_value, depth_ptr;
}

void PixelStore(short* pixel_data, queue<unsigned char> Queue, KeyValue** final_table, unsigned short* tablesize_ptr)
{
	string code = "";
	int data_num = 0;

	while (Queue.size())
	{
		unsigned char c = Queue.front();
		
		if (c == 0) code += "0";
		else if (c == 1) code += "1";
	
		for (int i = 0; i < *tablesize_ptr; i++)
		{
			if (code == final_table[i]->huffman_bit)
			{
				pixel_data[data_num++] = final_table[i]->value;
				code = "";
				break;
			}
		}
		Queue.pop();
	}
}

queue<unsigned char> DecodingQueue(unsigned short *bitsize_ptr, unsigned char* fileread_ptr)
{
	queue<unsigned char> Queue;
	unsigned char c;

	for (int i = 1; i <= *bitsize_ptr; i++)
	{	
		if ((i - 1) % 8 == 0)
		{
			c = KeyValue::getAbit(*fileread_ptr >> (8 - (i % 8)), 0);

		}
		else if (i % 8 == 0)
		{
			c = KeyValue::getAbit(*fileread_ptr, 0);
			fileread_ptr++;
		}
		else  c = KeyValue::getAbit(*fileread_ptr >> (8 - (i % 8)), 0);

		Queue.push(c);
	}
	return Queue;
}

void MakeTable(KeyValue** final_table, KeyValue** table)
{
	int j = 0;
	for (int i = -IMAGESCALE; i < IMAGESCALE; i++)
	{
		if (table[i + IMAGESCALE] != NULL)
		{
			final_table[j] = table[i + IMAGESCALE];		
			j++;
		}
	}

}

unsigned char* Decoding_Read(short* value_ptr, unsigned char* fileread_ptr,
	unsigned short* tablesize_ptr, unsigned short* bitsize_ptr, unsigned short* bytesize_ptr, 
	short* huffman_value_ptr, unsigned char* depth_ptr, KeyValue** table, unsigned short* pixelsize_ptr, FILE* input)
{
	fread(tablesize_ptr, sizeof(unsigned short), 1, input);
	fread(bitsize_ptr, sizeof(unsigned short), 1, input);
	unsigned short bytesize;
	if (*bitsize_ptr % 8 == 0)*bytesize_ptr = *bitsize_ptr / 8;
	else *bytesize_ptr = *bitsize_ptr / 8 + 1;

	fread(pixelsize_ptr, sizeof(unsigned short), 1, input);

	value_ptr = (short*)malloc(sizeof(short)*(*tablesize_ptr));
	fread(value_ptr, sizeof(short), *tablesize_ptr, input);

	huffman_value_ptr = (short*)malloc(sizeof(short) * (*tablesize_ptr));
	fread(huffman_value_ptr, sizeof(short), *tablesize_ptr, input);

	depth_ptr = (unsigned char*)malloc(sizeof(unsigned char) * (*tablesize_ptr));
	fread(depth_ptr, sizeof(unsigned char), *tablesize_ptr, input);

	fileread_ptr = (unsigned char*)malloc(sizeof(unsigned char)*(*bytesize_ptr));
	memset(fileread_ptr, 0, *bytesize_ptr);
	unsigned char* read_ptr = fileread_ptr;
	fread(fileread_ptr, sizeof(unsigned char), *bytesize_ptr, input);

	fileread_ptr = read_ptr;

	for (int i = 0; i < *tablesize_ptr; i++)
	{
		string temp_huffman_bit = to_string(KeyValue::tenConvertTwo(huffman_value_ptr[i]));//  depth_ptr[i]
		string final_huffman_bit = "";

		for (int j = depth_ptr[i]; j > temp_huffman_bit.length(); j--)final_huffman_bit += "0";
		final_huffman_bit += temp_huffman_bit;

		table[value_ptr[i] + IMAGESCALE] = new KeyValue(value_ptr[i], huffman_value_ptr[i], final_huffman_bit, depth_ptr[i]);
	}
	return fileread_ptr;
}