#include <fstream>
#include <cstdint>
#include <vector>

using namespace std;

void write_file(vector<bool> bits, string path);
void write_file(vector<uint8_t> bits, string path);
void write_files(pair<vector<vector<uint8_t>>, vector<vector<uint8_t>>> para, string directory);