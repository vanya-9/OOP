#include "writing_csv.h"
void WriteCsv::SetFileName(const std::string& name) {
  file_writing_name_ = name;
}

void WriteCsv::Write(std::vector<std::pair<std::string, unsigned>> vector_map,
                     double number_words,
                     std::string output_file_name) {
  SetFileName(output_file_name);
  std::ofstream out(file_writing_name_, std::ios::app);
  if (out.is_open()) {
    for (int i = 0; i < vector_map.size(); i++) {
      out << vector_map[i].first << " " << vector_map[i].second << " "
          << (vector_map[i].second / number_words) * kPercent << std::endl;
    }
    out.close();
  }
}