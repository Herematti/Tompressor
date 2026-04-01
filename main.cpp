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
#include <cstring>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

int main(int argc, char *argv[])
{
	MinHeap heapson;

	if (argc < 2)
	{
		throw runtime_error("No arguments given");
	}

	// bool ifCompression = (argv[1] == "-c");
	bool ifCompression = (strcmp(argv[1], "-c") == 0);

	if (ifCompression && argc < 3)
	{
		throw runtime_error("Not enough arguments given");
	}

	// cout << "ifcompression: " << argv[1];

	if (ifCompression)
	{
		auto target_path = argv[2];
		vector<string> file_paths;

		vector<string> file_names;

		for (int i = 3; i < argc; i++)
		{
			file_paths.push_back(argv[i]);
			file_names.push_back(fs::path(argv[i]).filename().string());
		}

		vector<vector<uint8_t>> binary_file_names;

		for (string file_name : file_names)
		{
			vector<uint8_t> temp;
			for (auto charr : file_name)
			{
				temp.push_back((uint8_t)charr);
			}
			binary_file_names.push_back(temp);
		}

		vector<vector<uint8_t>> bytes;

		cout << "bytes";
		for (string file_path : file_paths)
		{
			vector<uint8_t> temp = open_file(file_path);

			for (auto byte : temp)
				cout << char(byte);
			cout << "\n";

			bytes.push_back(temp);
		}
		cout << "\n";

		unsigned long long og_file_len = 0;
		for (auto file_bytes : bytes)
		{
			og_file_len += 8 * file_bytes.size();
		}

		cout << "original file length:   ";
		cout << og_file_len << " bits\n";

		{ // holy scopes
			map<uint8_t, int> mapped_bytes = map_bytes(bytes);
			add_map_bytes(binary_file_names, mapped_bytes);

			for (auto byte : mapped_bytes)
			{
				heapson.addNode(byte.second, byte.first);
			}
		}

		HuffmanTree huffman(heapson);

		cout << "TREE: ";
		huffman.print();
		cout << "\n";

		vector<bool> binary_tree = huffman.binary_tree();

		auto final_map = huffman.map_tree();

		auto final_bin = final_binary(bytes, binary_tree, final_map, binary_file_names);

		cout << "compressed file length: ";
		cout << final_bin.size() << " bits\n";

		double compression = 100.0 * final_bin.size() / (bytes.size() * 8);
		compression = floor(compression);

		cout << "\nfile compressed to ~" << compression << "% of original size\n";

		write_file(final_bin, target_path);
	}
	else
	{
		auto file_path = argv[2];
		auto target_path = argv[3];
		// huffman.print();
		// cout << "\n";
		vector<uint8_t> bytes_to_unc = open_file(file_path);
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

		write_files(unc, target_path);
	}
}