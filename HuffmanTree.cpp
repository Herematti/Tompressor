#include <iostream>
#include "HuffmanTree.hpp"

using namespace std;

void HuffmanTree::printHelper(Node *node)
{
	if (node == nullptr)
		return;

	cout << node->frequency;
	if (node->isLeaf)
	{
		cout << "/" << (int)node->key;
	}
	cout << " ";

	printHelper(node->left);
	printHelper(node->right);
}

HuffmanTree::HuffmanTree(MinHeap heap)
{
	while (heap.size() > 1)
	{
		Node *first = new Node(heap.pop());
		Node *second = new Node(heap.pop());

		Node *product = new Node(first->frequency + second->frequency);
		product->left = first;
		product->right = second;

		heap.addNode(*product);
	}
	root = heap.top();
}

void HuffmanTree::print()
{
	cout << root.frequency;
	if (root.isLeaf)
	{
		cout << "/" << (int)root.key;
	}
	cout << " ";
	printHelper(root.left);
	printHelper(root.right);
}
