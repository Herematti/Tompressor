#include "MinHeap.hpp"
#include <iostream>
#include <queue>
#include <map>

using namespace std;

class HuffmanTree
{
private:
	Node root;

	void print_helper(Node *node);
	void binary_tree_helper(Node *node, bool direction, vector<bool> &bits);
	void map_tree_helper(Node *node, map<uint8_t, vector<bool>> &map_final, vector<bool> path);

public:
	HuffmanTree(MinHeap heap);
	HuffmanTree(queue<bool> binary_tree);

	void print();
	vector<bool> binary_tree();
	map<uint8_t, vector<bool>> map_tree();
	pair<uint8_t, bool> find_by_path(vector<bool> path);
};