#include "uncompress.hpp"

vector<int> power_of_2()
{
	vector<int> powers(16);
	powers[0] = 1;
	for (int i = 1; i < 16; i++)
	{
		powers[i] = powers[i - 1] * 2;
	}
	return powers;
}

HuffmanTree reTree(vector<bool> binary_tree)
{
	HuffmanTree Tree();
}

vector<bool> uncompress(vector<bool> compressed)
{
	vector<bool> uncompressed;
	vector<int> powers = power_of_2();

	int treeLength = 0;
	for(int i = 0; i < 16; i++)
	{
		if (compressed[i])
		{
			treeLength += powers[15 - i];
		}
	}
	//cout << treeLength << "\n";

	vector<bool> binary_tree;

	for(int i = 16; i < 16 + treeLength; i++)
	{
		binary_tree.push_back(compressed[i]);
	}

	// cout << "\nbinary tree:\n";
	// for(bool bit : binary_tree)
	// {
	// 	cout << bit;
	// }
	// cout << "\n";



	return uncompressed;
}
