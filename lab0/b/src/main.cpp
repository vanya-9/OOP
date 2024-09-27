#include <algorithm>
#include <map>
#include <vector>
#include <list>

#include "cctype"
#include "data_process.h"
#include "fstream"
#include "iostream"
#include "reader.h"
#include "string"
#include "writer.h"

bool CountFrequency(char symbol) {
  return !std::isalpha(symbol) && !std::isdigit(symbol);
}

void CreateMap(Reader& input_file, DataProcess& map) {
  std::string read_str;
  std::string new_word = "";

  while (input_file.ReadLine(read_str)) {
    for (char symbol : read_str) {
      if (!CountFrequency(symbol)) {
        new_word += symbol;
      } else {
        map.AddToMap(new_word);
        new_word.clear();
      }
    }
    map.AddToMap(new_word);
    new_word.clear();
  }
}

int main(int argc, char* argv[]) {
  if (argc < 3) {
    std::cerr << "Error: Not enough arguments" << std::endl;
    return 1;
  }


  Reader input_file(argv[1]);

  DataProcess map;
  CreateMap(input_file, map);
  std::list<std::pair<std::string, unsigned>> list_map;
  map.SortData(list_map);

  std::string output_file = argv[2];
  Writer writing_file(output_file);
  writing_file.Write(list_map, map.GetNumberWords(), output_file);

  return 0;
}
