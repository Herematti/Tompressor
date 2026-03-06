#include "uncompress.hpp"
#include "HuffmanTree.hpp"
#include <queue>

vector<bool> uncompress(vector<bool> compressed)
{
	vector<bool> uncompressed;

	int treeLength = 0;
	for(int i = 0; i < 16; i++)
	{
		if (compressed[i])
		{
			treeLength += 1 << (15 - i);
		}
	}
	//cout << treeLength << "\n";

	queue<bool> binary_tree;

	for(int i = 16; i < 16 + treeLength; i++)
	{
		binary_tree.push(compressed[i]);
	}

	// cout << "\nbinary tree:\n";
	// for(bool bit : binary_tree)
	// {
	// 	cout << bit;
	// }
	// cout << "\n";

	cout << "\n\n NOW TRYING TO UNCOMPRESS TREE \n\n";
	HuffmanTree tree(binary_tree);
	cout << "\n\n NOW TRYING TO PRINT TREE \n\n";

	tree.print();



	return uncompressed;
}
