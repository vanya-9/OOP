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

bool is_delimiter(char symbol) {
  return !std::isalpha(symbol) && !std::isdigit(symbol);
}

void adding_map(reading_file& myfile, data_processing& map) {
  if (!myfile.check_empty_new_word()) {
    map.plus_word();
    map.increse_word_count(myfile.get_new_word());
    myfile.new_word_drop();
  }
}

bool compare(std::pair<std::string, unsigned>& element_one,
             std::pair<std::string, unsigned>& element_two) {
  return element_one.second > element_two.second;
}

void create_map(reading_file& myfile, data_processing& map) {
  std::ifstream shows_file(myfile.get_file_name());
  while (myfile.read_line(shows_file)) {
    for (char c : myfile.get_read()) {
      if (!is_delimiter(c)) {
        myfile.add_to_new_word(c);
      } else {
        adding_map(myfile, map);
      }
    }
    adding_map(myfile, map);
  }
}

int main(int argc, char* argv[]) {
  if (argc < 3) {
    std::cerr << "Mistake" << std::endl;
    return 1;
  }
  reading_file myfile;
  myfile.set_file_name(argv[1]);
  data_processing map;
  create_map(myfile, map);

  std::vector<std::pair<std::string, unsigned>> vector_map(
      map.get_words_begin(), map.get_words_end());
  std::sort(vector_map.begin(), vector_map.end(), compare);
  writing_csv writing_file;
  writing_file.writing(vector_map, map.get_number_words(), argv[2]);
  return 0;
}
