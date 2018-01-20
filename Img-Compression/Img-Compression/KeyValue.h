#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include <list>
#include <math.h>
#include <bitset>

#define NONVALUE -256
#define LASTINDEX 31
#define BITNONVALUE 2

using namespace std;

class KeyValue
{
public:

	int value;
	int huffman_value = NONVALUE;
	string huffman_bit;
	int depth;

	KeyValue(int value, int huffman_value, string huffman_bit, int depth) :value(value), huffman_value(huffman_value), huffman_bit(huffman_bit), depth(depth) {}

	void PrintMyBit()
	{
		cout << "value, depth, bit : " << value << "  " << depth << "  " << huffman_bit;
		cout << endl;
	}

	static int tenConvertTwo(int num)
	{
		int result = 0;
		for (int i = 1; num > 0; i *= 10)
		{
			int binary = num % 2;
			result += binary*i;
			num /= 2;
		}
		return result;
	}
	static int twoConvertTen(int num)
	{
		int result = 0, mul = 1;
		while (num > 0)
		{
			if (num % 2)
				result += mul;
			mul *= 2;
			num /= 10;
		}
		return result;
	}

	static int getAbit(unsigned char x, int n)
	{
		return (x & (1 << n)) >> n;
	}
	static char *ucharToBinary(unsigned char i)
	{
		static char s[8 + 1] = { '0', };
		int count = 8;

		do {
			s[--count] = '0' + (char)(i & 1);
			i = i >> 1;
		} while (count);

		return s;
	}
	static char *ucharToBinary(unsigned char *i)
	{
		static char s[8 + 1] = { '0', };
		int count = 8;

		do {
			s[--count] = '0' + (char)(*i & 1);
			*i = *i >> 1;
		} while (count);

		return s;
	}

};