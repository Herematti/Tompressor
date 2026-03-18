#include "map_bytes.hpp"

map<uint8_t, int> map_bytes(vector<uint8_t> bytes)
{
	map<uint8_t, int> mapped_bytes;
	for (uint8_t byte : bytes)
	{
		mapped_bytes[byte] += 1;
	}
	return mapped_bytes;
}

map<uint8_t, int> map_bytes(vector<vector<uint8_t>> bytes)
{
	map<uint8_t, int> mapped_bytes;
	for (auto file_bytes : bytes)
	{
		for (uint8_t byte : file_bytes)
		{
			mapped_bytes[byte] += 1;
		}
	}
	return mapped_bytes;
}

void add_map_bytes(vector<vector<uint8_t>> bytes, map<uint8_t, int> &mapped_bytes)
{
	for (auto file_bytes : bytes)
	{
		for (uint8_t byte : file_bytes)
		{
			mapped_bytes[byte] += 1;
		}
	}
}