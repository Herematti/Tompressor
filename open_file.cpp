#include "open_file.hpp"
#include <fstream>
#include <vector>
#include <cstdint>
#include <stdexcept>

vector<uint8_t> open_file(string path)
{
	ifstream file(path, ios::binary | ios::ate); //ios::ate daje nas na sam koniec

	if (!file.is_open())
	{
		throw runtime_error("failed to open file " + path);
	}

	streamsize size = file.tellg(); //tellg mowi gdzie jestem - a jestem na samym koncu
	file.seekg(0, ios::beg); //idziemy z powrotem na poczatek

	vector<uint8_t> bytes(size);

	if(file.read(reinterpret_cast<char*>(bytes.data()), size)) //bezposrednio na pamieci vectora castujemy plik
	{
		return bytes;
	}

	throw runtime_error("failed to read file " + path);
}