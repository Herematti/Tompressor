#include "HuffmanTree.hpp"
#include <iostream>
#include <queue>
#include "open_file.hpp"
#include "map_bytes.hpp"
#include <map>
#include <vector>
#include <cstdint>

using namespace std;

int main(int argc, char *argv[])
{
	MinHeap heapson;

	// heapson.addNode(5, 0b0);
	// heapson.addNode(6, 0b1);
	// heapson.addNode(5, 0b10);
	// heapson.addNode(6, 0b11);

	
	auto file_path = argv[1];
	map<uint8_t, int> mapped_bytes;

	{ //holy scopes
		vector<uint8_t> bytes = open_file(file_path);
		mapped_bytes = map_bytes(bytes);
	}

	for (auto byte : mapped_bytes)
	{
		heapson.addNode(byte.second, byte.first);
	}

	HuffmanTree huffman(heapson);
	huffman.print();
}