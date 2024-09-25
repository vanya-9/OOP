#include <algorithm>
#include <map>
#include <vector>

#include "cctype"
#include "data_processing.h"
#include "fstream"
#include "iostream"
#include "reading_file.h"
#include "string"
#include "writing_csv.h"

bool IsDelimiter(char symbol) {
  return !std::isalpha(symbol) && !std::isdigit(symbol);
}

void AddToMap(std::string& new_word, data_processing& map) {
  if (!new_word.empty()) {
    map.IncreseWordCount(new_word);
    new_word.clear();
  }
}

void CreateMap(ReadingFile& input_file, data_processing& map) {
  std::ifstream shows_file(input_file.GetFileName());
  std::string reading_str;
  std::string new_word = "";
  while (getline(shows_file, reading_str)) {
    for (char c : reading_str) {
      if (!IsDelimiter(c)) {
        new_word += c;
      } else {
        AddToMap(new_word, map);
      }
    }
    AddToMap(new_word, map);
  }
}

int main(int argc, char* argv[]) {
  if (argc < 3) {
    std::cerr << "Error: Not enough arguments" << std::endl;
    return 1;
  }
  ReadingFile input_file;
  input_file.SetFileName(argv[1]);
  data_processing map;
  CreateMap(input_file, map);
  std::vector<std::pair<std::string, unsigned>> vector_map;
  map.SortData(vector_map);
  WriteCsv writing_file;
  std::string output_file = argv[2];
  writing_file.Write(vector_map, map.GetNumberWords(), output_file);
  return 0;
}
