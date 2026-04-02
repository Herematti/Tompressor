#include <iostream>
#include <map>
#include <cstdint>
#include <vector>

using namespace std;

map<uint8_t, int> map_bytes(vector<uint8_t> bytes);
map<uint8_t, int> map_bytes(vector<vector<uint8_t>> bytes);
void add_map_bytes(vector<vector<uint8_t>> bytes, map<uint8_t, int> &mapped_bytes);