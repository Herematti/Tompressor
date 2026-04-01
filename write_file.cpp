#include "write_file.hpp"

void write_file(vector<bool> bits, string path)
{
	path += ".tom";
	ofstream file(path, ios::binary);

	uint8_t byte = 0;
	uint8_t mask;
	int bitCount = 0;
	for (bool bit : bits)
	{
		mask = 1 << (7 - bitCount);
		
		if(bit)
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

void write_file(vector<uint8_t> bytes, string path)
{
	ofstream file(path, ios::binary);

	for (uint8_t byte : bytes)
	{
		file.put(byte);
	}
}

void write_files(pair<vector<vector<uint8_t>>, vector<vector<uint8_t>>> para, string directory)
{

	for (int i = 0; i < para.first.size(); i++)
	{
		string file_name = "";
		for (auto c : para.first[i])
		{
			file_name += char(c);
		}

		write_file(para.second[i], directory + "/" + file_name);
	}
}