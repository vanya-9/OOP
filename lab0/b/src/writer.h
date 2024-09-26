#pragma once
#include "fstream"
#include "vector"
const int kPercent = 100;

class writer {
  std::string file_writing_name_;

 public:
  void SetFileName(const std::string& name);

  void Write(std::vector<std::pair<std::string, unsigned>> vector_map,
             double number_words,
             std::string output_file_name);
};
