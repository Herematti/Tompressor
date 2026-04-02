#include "write_file.hpp"

void write_file(const vector<bool>& bits, string path)
{
	path += ".tom";
	ofstream file(path, ios::binary);

	uint8_t byte = 0;
	uint8_t mask;
	int bitCount = 0;
	for (bool bit : bits)
	{
		mask = 1 << (7 - bitCount);

		if (bit)
		{
			byte += mask;
		}
		// buffer = (buffer << 1);
		// if (bit)
		// {
		// 	buffer++;
		// }
		if (bitCount == 7)
		{
			file.put(byte);
			byte = 0;
			bitCount = 0;
		}
		else
		{
			bitCount++;
		}
	}

	if (bitCount > 0)
	{
		file.put(byte);
	}
}

void write_file(const vector<uint8_t> &bytes, const string &path)
{
	ofstream file(path, ios::binary);
	file.write(reinterpret_cast<const char *>(bytes.data()), bytes.size()); // evil fucking reinterpretation magic spell cast
}

void write_files(const pair<vector<vector<uint8_t>>, vector<vector<uint8_t>>> &names_and_contents, const string &directory)
{

	for (int i = 0; i < names_and_contents.first.size(); i++)
	{
		string file_name = "";
		for (auto c : names_and_contents.first[i])
		{
			file_name += char(c);
		}

		write_file(names_and_contents.second[i], directory + "/" + file_name);
	}
}