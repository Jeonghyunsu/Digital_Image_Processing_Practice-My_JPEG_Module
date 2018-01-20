#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <list>
#include <math.h>
#include "KeyValue.h"
#include "Encoding.h"

#define NONVALUE -256
#define EOF_NUM 256

using namespace std;

class Node
{
public:
	int value;
	int frequency;
	Node *left_node, *right_node;

	Node(int value, int frequency) :value(value), frequency(frequency) {
		left_node = NULL;
		right_node = NULL;
	}
	~Node()
	{
		delete left_node;
		delete right_node;
	}
};
bool compare(const Node& first, const Node& second);
unsigned short CheckFrequency(short* pixel_data, list<Node>* Nodelist, list<Node>::iterator it, int nHeight, int nWidth);
Node* MakeTree(list<Node>* Nodelist, list<Node>::iterator it, Node* NodeTree);
void BinarySearch(Node* root_ptr, KeyValue** table, int depth, string code);

