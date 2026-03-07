#include "write_file.hpp"

void write_file(vector<bool> bits, string path)
{
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