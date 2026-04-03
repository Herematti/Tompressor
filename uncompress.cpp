#include "uncompress.hpp"
#include "HuffmanTree.hpp"
#include "secret.hpp"
#include <queue>
#include <cstdint>
#include "progressbar.hpp"

const int OVERFLOW_LENGTH = 3;
const int TREESIZE_LENGTH = 16;

pair<vector<vector<uint8_t>>, vector<vector<uint8_t>>> uncompress(vector<bool> compressed)
{
	// cout << "FULL STARTING: \n";
	// for (auto b : compressed)
	// {
	// 	cout << b;
	// }
	// cout << "\n";

	vector<vector<uint8_t>> uncompressedFileNames;
	vector<vector<uint8_t>> uncompressedContents;

	generate_progressbar("UNCOMPRESSING");

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
	const int CONTENT_SIZE_LENGTH = 32;

	int i = OVERFLOW_LENGTH + TREESIZE_LENGTH + treeLength;
	while (i < compressed.size())
	{
		update_progressbar(i, compressed.size());
		// cout << "START: ";
		// for (int j = i; j < compressed.size(); j++)
		// {
		// 	cout << compressed[j];
		// }
		// cout << "\t" << compressed.size() - i;
		// cout << "\n";

		int fileNameLength = 0;
		for (int j = 0; j < NAME_SIZE_LENGTH; j++)
		{
			update_progressbar(i + j, compressed.size());
			if (compressed[i + j])
			{
				fileNameLength += 1 << (NAME_SIZE_LENGTH - 1 - j);
			}
		}

		i += NAME_SIZE_LENGTH;

		// cout << "NameL: ";
		// for (int j = i; j < compressed.size(); j++)
		// {
		// 	cout << compressed[j];
		// }
		// cout << "\t" << compressed.size() - i;
		// cout << "\n";

		vector<uint8_t> uncompressed;

		for (int j = 0; j < fileNameLength; j++)
		{
			update_progressbar(i + j, compressed.size());
			path.push_back(compressed[i + j]);
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

		// cout << "Name : ";
		// for (int j = i; j < compressed.size(); j++)
		// {
		// 	cout << compressed[j];
		// }
		// cout << "\t" << compressed.size() - i;
		// cout << "\n";

		int contentLength = 0;
		for (int j = 0; j < CONTENT_SIZE_LENGTH; j++)
		{
			update_progressbar(i + j, compressed.size());
			if (compressed[i + j])
			{
				contentLength += 1 << (CONTENT_SIZE_LENGTH - 1 - j);
			}
		}
		i += CONTENT_SIZE_LENGTH;

		// cout << "ContL: ";
		// for (int j = i; j < compressed.size(); j++)
		// {
		// 	cout << compressed[j];
		// }
		// cout << "\t" << compressed.size() - i;
		// cout << "\n";

		for (int j = 0; j < contentLength; j++)
		{
			update_progressbar(i + j, compressed.size());
			path.push_back(compressed[i + j]);
			auto check = tree.find_by_path(path);
			if (!check.second)
			{
				continue;
			}
			uncompressed.push_back(check.first);
			path = {};
		}
		i += contentLength;

		// cout << "ContZ: ";
		// for (int j = i; j < compressed.size(); j++)
		// {
		// 	cout << compressed[j];
		// }
		// cout << "\t" << compressed.size() - i;
		// cout << "\n";

		uncompressedContents.push_back(uncompressed);
		uncompressed = {};
	}

	force_finish_progressbar();
	cout << "\nuncompression succesful\n\n";
	//super_secret_func();

	// cout << "filenames: ";
	// for (auto uncompressedFilename : uncompressedFileNames)
	// {
	// 	for (auto c : uncompressedFilename)
	// 	{
	// 		cout << (char)c;
	// 	}
	// 	cout << "\n";
	// }
	// cout << "\n";

	// cout << "contents: ";
	// for (auto uncompressedcontent : uncompressedContents)
	// {
	// 	for (auto c : uncompressedcontent)
	// 	{
	// 		cout << (char)c;
	// 	}
	// 	cout << "\n";
	// }

	return {uncompressedFileNames, uncompressedContents};
}
