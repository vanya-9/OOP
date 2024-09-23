#include "writing_csv.h"
  void writing_csv::set_file_name(const std::string& name) { file_writing_name = name; }
  void writing_csv::writing(std::vector<std::pair<std::string, unsigned>> vector_map,
               double number_words, const char  *output_file_name) {
    set_file_name(output_file_name);
    std::ofstream out(file_writing_name, std::ios::app);
    if (out.is_open()) {
      for (int i = 0; i < vector_map.size(); i++) {
        out << vector_map[i].first << " " << vector_map[i].second << " "
            << (vector_map[i].second / number_words) * percent << std::endl;
      }
      out.close();
    }
  }