#include "MinHeap.hpp"
#include <iostream>
#include <queue>

using namespace std;

Node huffmanize(MinHeap heap)
{
	while (heap.size() > 1)
	{
		Node *first = new Node(heap.pop());
		Node *second = new Node(heap.pop());

		// cout << "heap";
		// heap.print();

		Node product(first->frequency + second->frequency, false);
		product.left = first;
		product.right = second;

		heap.addNode(product);

		// cout << "heap";
		// heap.print();
	}
	return heap.top();
}

void printHuffmanHelper(Node *huffman)
{
	if (huffman == nullptr)
	{
		return;
	}
	cout << huffman->frequency;
	if(huffman->isLeaf)
	{
		cout << "/" << (int)huffman->key;
	}
	cout << " ";

	printHuffmanHelper(huffman->left);
	printHuffmanHelper(huffman->right);
}

void printHuffman(Node huffman)
{
	cout << huffman.frequency;
	if(huffman.isLeaf)
	{
		cout << "/" << (int)huffman.key;
	}
	cout << " ";

	printHuffmanHelper(huffman.left);
	printHuffmanHelper(huffman.right);
}

int main()
{
	MinHeap heapson;

	heapson.addNode(5, 0b0);
	heapson.addNode(6, 0b1);
	heapson.addNode(5, 0b10);
	heapson.addNode(6, 0b11);

	Node huffmanerson = huffmanize(heapson);
	printHuffman(huffmanerson);
}