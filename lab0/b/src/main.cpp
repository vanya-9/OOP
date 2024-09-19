#include <algorithm>  // для std::sort
#include <map>        // для map
#include <vector>

#include "cctype"  // Для std::isalpha и std::isdigit
#include "fstream"
#include "iostream"
#include "string"


#include "reading_file.h"
#include "sorted_data.h"
#include "writing_csv.h"




bool is_delimiter(char symbol) {
  return !std::isalpha(symbol) && !std::isdigit(symbol);
}

void create_map(reading_file &myfile, reading_file &map_words) {
  std::ifstream shows_file(myfile.get_file_name());
  while (myfile.read_line(shows_file)) {
    for (char c : myfile.get_read()) {
      if (!is_delimiter(c)) {
        myfile.add_to_new_word(c);
      } else {
        myfile.adding_map(map_words);
      }
    }
    myfile.adding_map(map_words);
  }
}

int main() {
  std::string file_name;
  reading_file myfile;
  reading_file map_words;
  myfile.set_file_name();
  create_map(myfile, map_words);
  //  Сортируем вектор по значению (второй элемент)
  sorted_data vector_map;
  vector_map.copy_from_map(map_words.get_words_begin(),
                           (map_words.get_words_end()));
  vector_map.vector_sort(vector_map.get_vector_begin(),
                         vector_map.get_vector_end());
  writing_csv writing_file;
  writing_file.writing(vector_map.get_vectop(), map_words.get_number_words());
  return 0;
}