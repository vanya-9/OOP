#ifndef WRITING_CSV_H
#define WRITING_CSV_H
#include "fstream"
#include "vector"
#define percent 100

class writing_csv {
  std::string file_writing_name;

 public:
  void set_file_name(const std::string& name);
  void writing(std::vector<std::pair<std::string, unsigned>> vector_map,
               double number_words, const char* output_file_name);
};
#endif