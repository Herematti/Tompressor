#include "MinHeap.hpp"
#include <iostream>
#include <stdexcept>

using namespace std;

Node::Node()
{
	frequency = 0;
	isLeaf = false;

	left = nullptr;
	right = nullptr;
}
Node::Node(int x)
{
	frequency = x;
	isLeaf = false;

	left = nullptr;
	right = nullptr;
}
Node::Node(int x, uint8_t key)
{
	frequency = x;
	isLeaf = false;
	this->key = key;

	left = nullptr;
	right = nullptr;
}
Node::Node(int x, bool leaf, uint8_t key)
{
	frequency = x;
	isLeaf = leaf;
	this->key = key;

	left = nullptr;
	right = nullptr;
}

Node::Node(Node *x)
{
	frequency = x->frequency;
	isLeaf = x->isLeaf;
	key = x->key;

	left = x->left;
	right = x->right;
}

MinHeap::MinHeap()
{
	storage.push_back(Node(-1));
}

void MinHeap::addNode(int val, uint8_t key)
{
	storage.push_back(Node(val, true, key));
	int id = storage.size() - 1;

	while (id >= 2)
	{
		if (storage[id / 2].frequency > storage[id].frequency)
		{
			swap(storage[id / 2], storage[id]);
		}
		id /= 2;
	}
}

void MinHeap::addNode(Node val)
{
	storage.push_back(val);
	int id = storage.size() - 1;

	while (id >= 2)
	{
		if (storage[id / 2].frequency > storage[id].frequency)
		{
			swap(storage[id / 2], storage[id]);
		}
		id /= 2;
	}
}

void MinHeap::print()
{
	for (int i = 1; i < storage.size(); i++)
	{
		cout << storage[i].frequency << " ";
	}
	cout << "\n";
}

size_t MinHeap::size()
{
	return storage.size() - 1;
}

Node MinHeap::pop()
{
	if (size() == 0)
		throw runtime_error("tried to pop empty heap");

	int last = storage.size() - 1;
	auto res = storage[1];

	swap(storage[1], storage[last]);
	storage.pop_back();
	last--;

	int id = 1;

	while (2 * id <= last)
	{
		int smallest = 2 * id;

		if (smallest + 1 <= last &&
			storage[smallest + 1].frequency < storage[smallest].frequency)
		{
			smallest++;
		}

		if (storage[id].frequency <= storage[smallest].frequency)
			break;

		swap(storage[id], storage[smallest]);
		id = smallest;
	}

	return res;
}

Node MinHeap::top()
{
	if (size() == 0)
		return -1;

	return storage[1];
}