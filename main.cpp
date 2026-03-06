#include "HuffmanTree.hpp"
#include <iostream>
#include <queue>
#include "open_file.hpp"
#include "map_bytes.hpp"
#include <map>
#include <vector>
#include <cstdint>
#include <stdexcept>

using namespace std;

int main(int argc, char *argv[])
{
	MinHeap heapson;

	// heapson.addNode(5, 0b0);
	// heapson.addNode(6, 0b1);
	// heapson.addNode(5, 0b10);
	// heapson.addNode(6, 0b11);
	if (argc == 1)
	{
		throw runtime_error("no arguments given");
	}

	auto file_path = argv[1];
	vector<uint8_t> bytes = open_file(file_path);

	{ // holy scopes
		"ok";
	}

	map<uint8_t, int> mapped_bytes = map_bytes(bytes);

	for (auto byte : mapped_bytes)
	{
		heapson.addNode(byte.second, byte.first);
	}

	HuffmanTree huffman(heapson);
	vector<bool> binary_tree = huffman.binary_tree(); // ts just worked first try wtf?

	for (auto bit : binary_tree)
	{
		cout << bit;
	}
	cout << "\n";

	huffman.print();
}