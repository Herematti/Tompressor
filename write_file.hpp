#include <fstream>
#include <cstdint>
#include <vector>

using namespace std;

void write_file(const vector<bool>& bits, string path);
void write_file(const vector<uint8_t>& bytes, const string& path);
void write_files(const pair<vector<vector<uint8_t>>, vector<vector<uint8_t>>> &names_and_contents, const string &directory);