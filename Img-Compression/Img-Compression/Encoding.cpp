#include "Encoding.h"

void Encoding(string filename, string encoding_filename, int nHeight, int nWidth)
{
	unsigned char** Y = MemAlloc2D<unsigned char>(nHeight, nWidth, 0);
	unsigned char** U = MemAlloc2D<unsigned char>(nHeight, nWidth, 0);
	unsigned char** V = MemAlloc2D<unsigned char>(nHeight, nWidth, 0);
	unsigned char** U420 = MemAlloc2D<unsigned char>(nHeight/2, nWidth/2, 0);
	unsigned char** V420 = MemAlloc2D<unsigned char>(nHeight/2, nWidth/2, 0);

	double** dct_Y = MemAlloc2D<double>(nHeight, nWidth, 0);
	double** dct_U = MemAlloc2D<double>(nHeight/2, nWidth/2, 0);
	double** dct_V = MemAlloc2D<double>(nHeight/2, nWidth/2, 0);

	double** Zigzag_array_Y = MemAlloc2D<double>(nHeight*TABLESIZE, TABLESIZE*TABLESIZE, 0);
	double** Zigzag_array_U = MemAlloc2D<double>(nHeight*TABLESIZE/4, TABLESIZE*TABLESIZE, 0);
	double** Zigzag_array_V = MemAlloc2D<double>(nHeight*TABLESIZE/4, TABLESIZE*TABLESIZE, 0);
	
	short** run_level_array_Y = MemAlloc2D<short>(nHeight*TABLESIZE, TABLESIZE*TABLESIZE, 0.0);
	short** run_level_array_U = MemAlloc2D<short>(nHeight*TABLESIZE/4, TABLESIZE*TABLESIZE, 0.0);
	short** run_level_array_V = MemAlloc2D<short>(nHeight*TABLESIZE/4, TABLESIZE*TABLESIZE, 0.0);

	cout << "----------Encoding----------" << endl;
	ReadBMPFormat(Y, U, V, nHeight, nWidth, filename.c_str()); 
	ReadRGBFormat(Y, U, V, nHeight, nWidth, filename.c_str());
	
	Convert_YUV420_2ptr(U, V,  U420, V420, nHeight, nWidth);
	
	DCT(Y, dct_Y, nHeight, nWidth);
	quantizationY(dct_Y, nHeight, nWidth);
	ZigZag(dct_Y, Zigzag_array_Y, nHeight, nWidth);
	RunLevelEncoding(Zigzag_array_Y, run_level_array_Y, nHeight * TABLESIZE, TABLESIZE*TABLESIZE);
	
	DCT(U420, dct_U, nHeight/2, nWidth/2);
	quantizationUV(dct_U, nHeight/2, nWidth/2);
	ZigZag(dct_U, Zigzag_array_U, nHeight/2, nWidth/2);
	RunLevelEncoding(Zigzag_array_U, run_level_array_U, nHeight * TABLESIZE/4, TABLESIZE*TABLESIZE);
	
	DCT(V420, dct_V, nHeight / 2, nWidth / 2);
	quantizationUV(dct_V, nHeight / 2, nWidth / 2);
	ZigZag(dct_V, Zigzag_array_V, nHeight / 2, nWidth / 2);
	RunLevelEncoding(Zigzag_array_V, run_level_array_V, nHeight * TABLESIZE / 4, TABLESIZE*TABLESIZE);

	unsigned short write_height = nHeight; unsigned short write_width = nWidth;
	unsigned short *write_height_ptr = &write_height; unsigned short* write_width_ptr = &write_width;
	FILE* output;
	fopen_s(&output, encoding_filename.c_str(), "wb");
	fwrite(write_height_ptr, sizeof(unsigned short), 1, output);
	fwrite(write_width_ptr, sizeof(unsigned short), 1, output);

	Encoding_Huffman(run_level_array_Y, TABLESIZE*nHeight, output);
	Encoding_Huffman(run_level_array_U, TABLESIZE*nHeight/4, output);
	Encoding_Huffman(run_level_array_V, TABLESIZE*nHeight/4, output);

	fclose(output);
	
	MemFree2D<unsigned char>(Y, nHeight);
	MemFree2D<unsigned char>(U, nHeight);
	MemFree2D<unsigned char>(V, nHeight);

	MemFree2D<unsigned char>(U420, nHeight/2);
	MemFree2D<unsigned char>(V420, nHeight/2);

	MemFree2D<double>(dct_Y, nHeight);
	MemFree2D<double>(dct_U, nHeight/2);
	MemFree2D<double>(dct_V, nHeight/2);

	MemFree2D<double>(Zigzag_array_Y, nHeight*TABLESIZE);
	MemFree2D<double>(Zigzag_array_U, nHeight*TABLESIZE/4);
	MemFree2D<double>(Zigzag_array_V, nHeight*TABLESIZE/4);

	MemFree2D<short>(run_level_array_Y, nHeight*TABLESIZE);
	MemFree2D<short>(run_level_array_U, nHeight*TABLESIZE/4);
	MemFree2D<short>(run_level_array_V, nHeight*TABLESIZE/4);
}

bool compare_(const Node& first, const Node& second)
{
	return first.frequency > second.frequency;
}

void Encoding_Huffman(short** run_level_array, int nHeight, FILE* output)
{
	list<Node>* Nodelist = new list<Node>(); list<Node>::iterator it;
	Node* NodeTree = (Node*)malloc(sizeof(Node)*(TABLESIZE*TABLESIZE)); Node* root_ptr;
	
	for (int loop = 0; loop < nHeight; loop++)
	{
		KeyValue** table = (KeyValue**)malloc(sizeof(KeyValue*)*(IMAGESCALE<<1)); string code = "";//store KeyValue table
		memset(table, NULL, IMAGESCALE << 3);
		unsigned short listsize = CheckFrequency(run_level_array[loop], Nodelist, it, TABLESIZE, TABLESIZE);
		
		Nodelist->sort(compare_);
	
		root_ptr = MakeTree(Nodelist, it, NodeTree);
		BinarySearch(root_ptr, table, 0, code);
		Nodelist->clear();
		
		int table_num = 0;
		for (int i = -IMAGESCALE; i < IMAGESCALE; i++)if (table[i + IMAGESCALE] != NULL) table_num++;
		
		KeyValue** final_table = (KeyValue**)malloc(sizeof(KeyValue*)*table_num);
		int j = 0;
		for (int i = -IMAGESCALE; i < IMAGESCALE; i++)
			if (table[i + IMAGESCALE] != NULL)
			{
				final_table[j] = table[i + IMAGESCALE];
				j++;
			}
		
		queue<unsigned char> enc_Queue = EncodingQueue(run_level_array[loop], final_table, table_num, listsize);
		int enc_size = enc_Queue.size();
		int filewrite_ptr_size = enc_size / 8 + 1;
		unsigned char* filewrite_ptr = (unsigned char*)malloc(sizeof(unsigned char)*filewrite_ptr_size);
		memset(filewrite_ptr, 0, filewrite_ptr_size);
		Encoding_Write(enc_Queue,  final_table, filewrite_ptr, filewrite_ptr_size, table_num, listsize, output);

		delete final_table, filewrite_ptr, table;
	}

	delete Nodelist, NodeTree;
}

queue<unsigned char> EncodingQueue(short* pixel_data, KeyValue** final_table, int table_num, unsigned short listsize)
{
	queue<unsigned char> Queue;
	for (int i = 0; i < listsize; i++)
		for (int j = 0; j < table_num; j++)
		{
			if (pixel_data[i] == final_table[j]->value)
			{
				for (int k = 0; k < final_table[j]->huffman_bit.size(); k++)
				{
					Queue.push(unsigned char(final_table[j]->huffman_bit.c_str()[k]));
				}
				break;
			}
		}
			
	return Queue;
}

void Encoding_Write(queue<unsigned char> Queue, KeyValue** final_table, unsigned char* filewrite_ptr, int filewrite_ptr_size, int table_num, unsigned short pixelsize, FILE* output)
{
	int size = Queue.size();
	unsigned char* store_ptr = filewrite_ptr;

	for (int i = 1; i <= size; i++)
	{
		unsigned char c = KeyValue::getAbit(Queue.front(), 0);
		Queue.pop();
		
		if ((i - 1) % 8 == 0)
		{		
			*filewrite_ptr = c;
		}
		else if (i % 8 == 0)
		{
			*filewrite_ptr = *filewrite_ptr << 1;
			*filewrite_ptr = (*filewrite_ptr | c);
			filewrite_ptr++;
		}
		else
		{
			*filewrite_ptr = *filewrite_ptr << 1;
			*filewrite_ptr = (*filewrite_ptr | c);
		}


		if (i == size)
			for (int j = size; j < filewrite_ptr_size * 8; j++)
			{
				c = 0;
				*filewrite_ptr = *filewrite_ptr << 1;
				*filewrite_ptr = (*filewrite_ptr | c);
			}
	}

	filewrite_ptr = store_ptr;

	unsigned short tablesize = (unsigned short)table_num; unsigned short* tablesize_ptr = &tablesize;
	unsigned short bitsize = (unsigned short)size; unsigned short* bitsize_ptr = &bitsize;
	unsigned short * pixelsize_ptr = &pixelsize;

	unsigned short bytesize;
	if (bitsize % 8 == 0)bytesize = bitsize / 8;
	else bytesize = bitsize / 8 + 1;
	
	short* value_ptr = (short*)malloc(sizeof(short)*(tablesize));
	for (int i = 0; i < tablesize; i++)
		value_ptr[i] = (short)final_table[i]->value;

	short* huffman_value_ptr = (short*)malloc(sizeof(short)*(tablesize));
	unsigned char* depth_ptr = (unsigned char*)malloc(sizeof(unsigned char)*(tablesize));

	for (int i = 0; i < tablesize; i++)
	{
		huffman_value_ptr[i] = final_table[i]->huffman_value;
		depth_ptr[i] = final_table[i]->depth;
	}

	fwrite(tablesize_ptr, sizeof(unsigned short), 1, output);
	fwrite(bitsize_ptr, sizeof(unsigned short), 1, output);
	fwrite(pixelsize_ptr, sizeof(unsigned short), 1, output);
	fwrite(value_ptr, sizeof(short), tablesize, output);
	fwrite(huffman_value_ptr, sizeof(short), tablesize, output);
	fwrite(depth_ptr, sizeof(unsigned char), tablesize, output);
	fwrite(filewrite_ptr, sizeof(unsigned char), bytesize, output);
	
	filewrite_ptr = store_ptr;

	delete value_ptr, huffman_value_ptr, depth_ptr;
}

