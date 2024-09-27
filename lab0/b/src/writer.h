#pragma once
#include <list>
#include "fstream"
#include "vector"
const int kPercent = 100;

class Writer {
  std::string file_writing_name_;
  std::ofstream output_file_;

 public:
  Writer(std::string file_writing_name_) : file_writing_name_(file_writing_name_) {
    output_file_.open(file_writing_name_);
  }

  ~Writer() {
    if (output_file_.is_open()) {
      output_file_.close();
    }
  }

  void Write(std::list<std::pair<std::string, unsigned>> list_map,
             double number_words, std::string output_file_name);
};
