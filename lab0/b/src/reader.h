#pragma once
#include <fstream>
#include <string>
class Reader {
  std::string file_name_;
  std::ifstream shows_file_;

 public:
  Reader(std::string file_name) : file_name_(file_name) {
    shows_file_.open(file_name_);
  }

  ~Reader() {
    if (shows_file_.is_open()) {
      shows_file_.close();
    }
  }

  std::string GetFileName();

  bool ReadLine(std::string& read_str);
};
