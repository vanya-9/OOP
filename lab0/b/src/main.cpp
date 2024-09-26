#include <algorithm>
#include <map>
#include <vector>

#include "cctype"
#include "data_processing.h"
#include "fstream"
#include "iostream"
#include "reading_file.h"
#include "string"
#include "writer.h"

bool IsDelimiter(char symbol) {
  return !std::isalpha(symbol) && !std::isdigit(symbol);
}

void AddToMap(std::string& new_word, dataProcessing& map) {
  if (!new_word.empty()) {
    map.IncreseWordCount(new_word);
  }
}

void CreateMap(ReadingFile& input_file, dataProcessing& map) {
  std::ifstream shows_file(input_file.GetFileName());
  std::string reading_str;
  std::string new_word = "";
  
  while (getline(shows_file, reading_str)) {
    for (char c : reading_str) {
      if (!IsDelimiter(c)) {
        new_word += c;
      } else {
        AddToMap(new_word, map);
        new_word.clear();
      }
    }
    AddToMap(new_word, map);
    new_word.clear();
  }
}

int main(int argc, char* argv[]) {
  if (argc < 3) {
    std::cerr << "Error: Not enough arguments" << std::endl;
    return 1;
  }

  ReadingFile input_file;
  input_file.SetFileName(argv[1]);

  dataProcessing map;
  CreateMap(input_file, map);
  std::vector<std::pair<std::string, unsigned>> vector_map;
  map.SortData(vector_map);

  writer writing_file;
  std::string output_file = argv[2];
  writing_file.Write(vector_map, map.GetNumberWords(), output_file);

  return 0;
}
