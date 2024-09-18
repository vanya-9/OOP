#include "string"
#include "map"
#include "fstream"
#include "iostream"
using std::cout;
bool check_symbol(char symbol);
void create_map(std::string file_name, std::map<std::string, unsigned> &words, double* k);