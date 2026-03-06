#include "MinHeap.hpp"
#include <iostream>

using namespace std;

class HuffmanTree
{
private:
	Node root;

	void print_helper(Node *node);
	void binary_tree_helper(Node *node, bool direction, vector<bool> &bits);

public:
	HuffmanTree(MinHeap heap);

	void print();
	vector<bool> binary_tree();
};