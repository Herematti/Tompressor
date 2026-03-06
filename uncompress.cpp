#include "uncompress.hpp"
#include "HuffmanTree.hpp"
#include <queue>
#include <cstdint>

vector<uint8_t> uncompress(vector<bool> compressed)
{
	vector<uint8_t> uncompressed;

	int treeLength = 0;
	for (int i = 0; i < 16; i++)
	{
		if (compressed[i])
		{
			treeLength += 1 << (15 - i);
		}
	}
	// cout << treeLength << "\n";

	queue<bool> binary_tree;

	for (int i = 16; i < 16 + treeLength; i++)
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
	for (int i = 16 + treeLength; i < compressed.size(); i++)
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

	return uncompressed;
}
