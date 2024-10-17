#include "writer.h"

void Writer::Write(std::list<std::pair<std::string, unsigned>> list_map,
                   double number_words, std::string output_file_name) {

  if (output_file_.is_open()) {
    for (auto& pair : list_map) {  
      output_file_ << pair.first << " " << pair.second << " " << ((pair.second) / number_words) * kPercent << std::endl;
    }
  }
}