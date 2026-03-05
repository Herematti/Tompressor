#include "HuffmanTree.hpp"
#include <iostream>
#include <queue>

using namespace std;

int main()
{
	MinHeap heapson;

	heapson.addNode(5, 0b0);
	heapson.addNode(6, 0b1);
	heapson.addNode(5, 0b10);
	heapson.addNode(6, 0b11);

	HuffmanTree huffman(heapson);
	huffman.print();
}