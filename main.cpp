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

		Node product(first->data + second->data);
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
	cout << huffman->data << " ";

	printHuffmanHelper(huffman->left);
	printHuffmanHelper(huffman->right);
}

void printHuffman(Node huffman)
{
	cout << huffman.data << " ";
	printHuffmanHelper(huffman.left);
	printHuffmanHelper(huffman.right);
}

int main()
{
	MinHeap heapson;

	heapson.addNode(5);
	heapson.addNode(6);
	heapson.addNode(5);
	heapson.addNode(6);

	Node huffmanerson = huffmanize(heapson);
	printHuffman(huffmanerson);
}