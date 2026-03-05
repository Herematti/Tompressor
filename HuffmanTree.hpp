#include "MinHeap.hpp"
#include <iostream>

using namespace std;

class HuffmanTree
{
private:
	Node root;

	void printHelper(Node *node);

public:
	HuffmanTree(MinHeap heap);

	void print();
};