#include "HuffmanTree.hpp"
#include <iostream>
#include <queue>
#include "open_file.hpp"
#include "map_bytes.hpp"
#include "generate_binary.hpp"
#include "uncompress.hpp"
#include <map>
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <cmath>
#include "write_file.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	MinHeap heapson;

	if (argc == 1)
	{
		throw runtime_error("no arguments given");
	}

	auto file_path = argv[1];

	if (argc == 1)
	{
		throw runtime_error("no arguments given");
	}

	vector<uint8_t> bytes = open_file(file_path);

	cout << "original file length: ";
	cout << 8 * bytes.size() << " bits\n";
	// for (uint8_t byte : bytes)
	// {
	// 	uint8_t mask = 1 << 7;
	// 	for (int i = 0; i < 8; i++)
	// 	{
	// 		cout << (bool)(byte & mask);
	// 		mask = mask >> 1;
	// 	}
	// }

	{ // holy scopes
		map<uint8_t, int> mapped_bytes = map_bytes(bytes);

		for (auto byte : mapped_bytes)
		{
			heapson.addNode(byte.second, byte.first);
		}
	}

	HuffmanTree huffman(heapson);

	vector<bool> binary_tree = huffman.binary_tree(); // ts just worked first try wtf?
	// cout << "\ntreeLength: " << binary_tree.size() << "\n";
	// for (auto bit : binary_tree)
	// {
	// 	cout << bit;
	// }
	// cout << "\nthis was the binary tree\n";

	auto final_map = huffman.map_tree();

	// for (auto map : mapa)
	// {
	// 	cout << map.first << "/";
	// 	for (auto bit : map.second)
	// 	{
	// 		cout << bit;
	// 	}
	// 	cout << " ";
	// }
	// cout << "\n";

	// huffman.print();

	auto final_bin = final_binary(bytes, binary_tree, final_map);

	cout << "compressed file length: ";
	cout << final_bin.size() << " bits\n";
	// for (bool bit : final_bin)
	// {
	// 	cout << bit;
	// }

	double compression = 100.0 * final_bin.size() / (bytes.size() * 8);
	compression = floor(compression);

	cout << "\nfile compressed to ~" << compression << "% of original size\n";

	// for (auto bit : binary_tree)
	// {
	// 	cout << bit;
	// }
	// cout << "\n";

	write_file(final_bin, "compression/compressed.tom");

	// cout << "\nprint\n";
	// huffman.print();
	// cout << "\n";
	vector<uint8_t> bytes_to_unc = open_file("compression/compressed.tom");
	vector<bool> bits_to_unc;

	for (auto byte : bytes_to_unc)
	{
		uint8_t mask = 1 << 7;

		for (int i = 0; i < 8; i++)
		{
			bits_to_unc.push_back(byte & mask);
			mask = mask >> 1;
		}
	}

	auto unc = uncompress(bits_to_unc);

	// cout << "\n--uncompressed--\n";
	// for (auto u : unc)
	// {
	// 	cout << (char)u;
	// }
	// cout << "\n--uncompressed--\n";

	write_file(unc, "compression/uncompressed.wav");
}