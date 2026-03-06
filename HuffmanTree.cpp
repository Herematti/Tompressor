#include <iostream>
#include <queue>
#include <stack>
#include "HuffmanTree.hpp"

using namespace std;

void HuffmanTree::print_helper(Node *node)
{
	if (node == nullptr)
		return;

	cout << "/";
	if (node->isLeaf)
	{
		cout << (char)node->key;
	}
	cout << " ";

	print_helper(node->left);
	print_helper(node->right);
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

	if (root.isLeaf) // single node tree edge case -- root cannot be a leaf
	{
		root.left = new Node(root);
		root.key = 0;
		root.isLeaf = false;
	}
}

HuffmanTree::HuffmanTree(queue<bool> binary_tree)
{
	root = Node();
	stack<Node *> s;
	s.push(&root);

	while (!binary_tree.empty())
	{
		// cout << "queue size: " << binary_tree.size() << "\n";

		Node *node = new Node();

		node->isLeaf = binary_tree.front();
		binary_tree.pop();

		bool direction = binary_tree.front();
		binary_tree.pop();

		if (!direction)
		{
			while (s.top()->left != nullptr)
			{
				s.pop();
			}
			s.top()->left = node;
		}
		else
		{
			while (s.top()->right != nullptr)
			{
				s.pop();
			}
			s.top()->right = node;
		}

		if (!node->isLeaf)
		{
			s.push(node);
		}
		else
		{
			uint8_t key = 0;
			for (int i = 0; i < 8; i++)
			{
				if (binary_tree.front())
				{
					key += 1 << (7 - i);
				}
				binary_tree.pop();
			}
			node->key = key;
		}
	}
}

void HuffmanTree::print()
{
	cout << '/';
	cout << " ";
	print_helper(root.left);
	print_helper(root.right);
}

void HuffmanTree::binary_tree_helper(Node *node, bool direction, vector<bool> &bits)
{
	if (node == nullptr)
	{
		return;
	}

	/* binary format:

	isLeaf:
		0 means not leaf, 1 means leaf

	Direction:
		determines wheter the current node is the left(0) or right(1) child

	Key:
		one byte long key (only if the current node is a leaf)


		--basically dfs that will have to be reconstructed back into a tree
	*/

	bits.push_back(node->isLeaf);
	bits.push_back(direction);

	if (node->isLeaf)
	{
		uint8_t mask = 1 << 7;

		for (int i = 0; i < 8; i++)
		{
			bits.push_back(node->key & mask);
			// cout << "mask: " << (int)mask << " ";
			mask = mask >> 1;
		}
	}

	binary_tree_helper(node->left, 0, bits);
	binary_tree_helper(node->right, 1, bits);
}

vector<bool> HuffmanTree::binary_tree() // fun fact -- a <bool> vector uses only 1 BIT of memory per element, not 1 byte
{
	vector<bool> bits;

	binary_tree_helper(root.left, 0, bits);
	binary_tree_helper(root.right, 1, bits);

	return bits;
}

void HuffmanTree::map_tree_helper(Node *node, map<uint8_t, vector<bool>> &map_final, vector<bool> path)
{
	if (node == nullptr)
	{
		return;
	}

	if (node->isLeaf)
	{
		map_final[node->key] = path;
		return;
	}

	auto left_path = path;
	left_path.push_back(0);
	map_tree_helper(node->left, map_final, left_path);

	auto right_path = path;
	right_path.push_back(1);
	map_tree_helper(node->right, map_final, right_path);
}

map<uint8_t, vector<bool>> HuffmanTree::map_tree()
{
	map<uint8_t, vector<bool>> map_final;

	map_tree_helper(root.left, map_final, {0});
	map_tree_helper(root.right, map_final, {1});

	return map_final;
}

pair<uint8_t, bool> HuffmanTree::find_by_path(vector<bool> path)
{
	Node current = root;

	for (bool direction : path)
	{
		if (!direction)
		{
			current = *current.left;
		}
		else
		{
			current = *current.right;
		}
	}

	return {current.key, current.isLeaf};
}
