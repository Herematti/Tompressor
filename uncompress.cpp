#include "uncompress.hpp"
#include "HuffmanTree.hpp"
#include "secret.hpp"
#include <queue>
#include <cstdint>

vector<uint8_t> uncompress(vector<bool> compressed)
{
	vector<uint8_t> uncompressed;

	int overflowing_bits = 0;
	uint8_t mask = 1 << 2;
	for(int i = 0; i < 3; i++)
	{
		if(compressed[i])
		{
			overflowing_bits += mask;
		}
		mask = mask >> 1;
	}

	for(int i = 0; i < overflowing_bits; i++)
	{
		compressed.pop_back();
	}

	int treeLength = 0;
	for (int i = 3; i < 19; i++)
	{
		if (compressed[i])
		{
			treeLength += 1 << (18 - i);
		}
	}

	queue<bool> binary_tree;

	for (int i = 19; i < 19 + treeLength; i++)
	{
		binary_tree.push(compressed[i]);
	}

	// cout << "\nbinary tree:\n";
	// for(bool bit : binary_tree)
	// {
	// 	cout << bit;
	// }
	// cout << "\n";

	HuffmanTree tree(binary_tree);

	// tree.print();

	vector<bool> path = {};
	for (int i = 19 + treeLength; i < compressed.size(); i++)
	{
		path.push_back(compressed[i]);
		auto check = tree.find_by_path(path);
		if(!check.second)
		{
			continue;
		}

		// cout << "\npath:";
		// for (auto dir : path)
		// {
		// 	cout << dir;
		// }
		// cout << " " << (char)check.first << "\n";

		uncompressed.push_back(check.first);
		path = {};
	}

	cout << "uncompression succesful bro\n";
	super_secret_func();

	return uncompressed;
}
