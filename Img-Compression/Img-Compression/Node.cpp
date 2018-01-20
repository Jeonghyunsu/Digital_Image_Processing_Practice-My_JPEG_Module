#include "Node.h"

#define NONVALUE -256

using namespace std;

bool compare(const Node& first, const Node& second)
{
	return first.frequency > second.frequency;
}

void BinarySearch(Node* root_ptr, KeyValue** table, int depth, string code)
{
	string  temp_code = code;
	if (root_ptr->left_node == NULL && root_ptr->right_node == NULL)
	{
		if (code == "") { code = "0"; }
		int huffman_value_10 = stoi(code);
		huffman_value_10 = KeyValue::twoConvertTen(huffman_value_10);
		table[IMAGESCALE + root_ptr->value] = new KeyValue(root_ptr->value, huffman_value_10, code, depth);
		return;
	}

	depth++;
	if (root_ptr->left_node != NULL)
	{
		code += "0";
		BinarySearch(root_ptr->left_node, table, depth, code);
	}
	if (root_ptr->right_node != NULL)
	{
		code = temp_code;
		code += "1";
		BinarySearch(root_ptr->right_node, table, depth, code);
	}
}
Node* MakeTree(list<Node>* Nodelist, list<Node>::iterator it, Node* NodeTree)
{
	int size = 0;
	int node_num = 0;

	for (it = Nodelist->begin(); it != Nodelist->end(); ++it)
	{
		NodeTree[size].value = it->value;
		NodeTree[size].frequency = it->frequency;
		NodeTree[size].left_node = NULL;
		NodeTree[size].right_node = NULL;
		size++;
	}

	Node* head_ptr = NULL;
	Node* temp_ptr = NULL;
	Node* previous_ptr = NULL;
	int valuenode_size = size;
	node_num = size;

	size--;
	if (size == 0)
		return NodeTree;
	else
	{
		if (NodeTree[size - 1].frequency >= NodeTree[size].frequency)
		{
			previous_ptr = new Node(NONVALUE, NodeTree[size - 1].frequency + NodeTree[size].frequency);
			previous_ptr->left_node = &NodeTree[size - 1];
			previous_ptr->right_node = &NodeTree[size];
		}
		else
		{
			previous_ptr = new Node(NONVALUE, NodeTree[size - 1].frequency + NodeTree[size].frequency);
			previous_ptr->right_node = &NodeTree[size - 1];
			previous_ptr->left_node = &NodeTree[size];
		}
		node_num++;
		size -= 2;


		for (int i = size; i >= 0; i--)
		{
			if (NodeTree[i].frequency >= previous_ptr->frequency)
			{
				temp_ptr = new Node(NONVALUE, NodeTree[i].frequency + previous_ptr->frequency);
				temp_ptr->left_node = &NodeTree[i];
				temp_ptr->right_node = previous_ptr;
				previous_ptr = temp_ptr;
			}
			else
			{
				temp_ptr = new Node(NONVALUE, NodeTree[i].frequency + previous_ptr->frequency);
				temp_ptr->right_node = &NodeTree[i];
				temp_ptr->left_node = previous_ptr;
				previous_ptr = temp_ptr;
			}
			node_num++;
		}
		return previous_ptr;
	}
}

unsigned short CheckFrequency(short* pixel_data, list<Node>* Nodelist, list<Node>::iterator it, int nHeight, int nWidth)
{
	bool Nonredundancy = true; unsigned short listsize;

	Nodelist->push_back(Node(pixel_data[0], 1));

	for (int i = 1; i < nHeight*nWidth; i++)
	{
		if (pixel_data[i] == EOF_NUM)
		{
			listsize = i;
			break;
		}

		Nonredundancy = true;
		for (it = Nodelist->begin(); it != Nodelist->end(); ++it)
		{
			if (it->value == pixel_data[i])
			{
				it->frequency++;
				Nonredundancy = false;
				break;
			}
		}
		if (Nonredundancy) Nodelist->push_back(Node(pixel_data[i], 1));
	}

	return listsize;
}