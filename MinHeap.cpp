#include "MinHeap.hpp"
#include <iostream>
#include <stdexcept>

using namespace std;

Node::Node(int x)
{
	data = x;
	left = nullptr;
	right = nullptr;
}

Node::Node(Node *x)
{
	data = x->data;
	left = x->left;
	right = x->right;
}

MinHeap::MinHeap()
{
	storage.push_back(Node(-1));
}

void MinHeap::addNode(int val)
{
	storage.push_back(Node(val));
	int id = storage.size() - 1;

	while (id >= 2)
	{
		if (storage[id / 2].data > storage[id].data)
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
		if (storage[id / 2].data > storage[id].data)
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
		cout << storage[i].data << " ";
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
		throw new runtime_error("tried to pop empty heap");

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
			storage[smallest + 1].data < storage[smallest].data)
		{
			smallest++;
		}

		if (storage[id].data <= storage[smallest].data)
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