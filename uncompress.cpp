#include "uncompress.hpp"
#include "HuffmanTree.hpp"
#include "secret.hpp"
#include <queue>
#include <cstdint>

const int OVERFLOW_LENGTH = 3;
const int TREESIZE_LENGTH = 16;

pair<vector<vector<uint8_t>>, vector<vector<uint8_t>>> uncompress(vector<bool> compressed)
{
	vector<vector<uint8_t>> uncompressedFileNames;
	vector<vector<uint8_t>> uncompressedContents;

	int overflowing_bits = 0;
	uint8_t mask = 1 << 2;
	for (int i = 0; i < OVERFLOW_LENGTH; i++)
	{
		if (compressed[i])
		{
			overflowing_bits += mask;
		}
		mask = mask >> 1;
	}

	for (int i = 0; i < overflowing_bits; i++)
	{
		compressed.pop_back();
	}

	int treeLength = 0;
	for (int i = OVERFLOW_LENGTH; i < OVERFLOW_LENGTH + TREESIZE_LENGTH; i++)
	{
		if (compressed[i])
		{
			treeLength += 1 << (18 - i);
		}
	}

	queue<bool> binary_tree;

	for (int i = OVERFLOW_LENGTH + TREESIZE_LENGTH; i < OVERFLOW_LENGTH + TREESIZE_LENGTH + treeLength; i++)
	{
		binary_tree.push(compressed[i]);
	}

	// cout << "\nbinary tree:\n";
	// for(bool bit : binary_tree)
	// {
	// 	cout << bit;
	// }
	// cout << "\n";

	HuffmanTree tree(binary_tree);

	// tree.print();

	vector<bool> path = {};

	const int NAME_SIZE_LENGTH = 8;
	const int CONTENT_SIZE_LENGTH = 16;

	int i = OVERFLOW_LENGTH + TREESIZE_LENGTH + treeLength;
	while (i < compressed.size())
	{

		int fileNameLength = 0;
		for (int j = 0; j < NAME_SIZE_LENGTH; j++)
		{
			if (compressed[i + j])
			{
				fileNameLength += 1 << (i - 1 - j);
			}
		}
		i += NAME_SIZE_LENGTH;

		vector<uint8_t> uncompressed;
		for (int j = i; j < fileNameLength; j++)
		{
			path.push_back(compressed[j]);
			auto check = tree.find_by_path(path);
			if (!check.second)
			{
				continue;
			}
			uncompressed.push_back(check.first);
			path = {};
		}
		uncompressedFileNames.push_back(uncompressed);
		uncompressed = {};

		i += fileNameLength;
		

		int contentLength = 0;
		for (int j = 0; j < CONTENT_SIZE_LENGTH; j++)
		{
			if (compressed[i + j])
			{
				contentLength += 1 << (i - 1 - j);
			}
		}
		i += CONTENT_SIZE_LENGTH;

		for (int j = i; j < contentLength; j++)
		{
			path.push_back(compressed[j]);
			auto check = tree.find_by_path(path);
			if (!check.second)
			{
				continue;
			}
			uncompressed.push_back(check.first);
			path = {};
		}
		uncompressedContents.push_back(uncompressed);
		uncompressed = {};

		i += fileNameLength;
	}

	cout << "uncompression succesful bro\n";
	super_secret_func();

	return {uncompressedFileNames, uncompressedContents};
}
