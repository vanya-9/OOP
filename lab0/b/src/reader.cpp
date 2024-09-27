#include "reader.h"

std::string Reader::GetFileName() {
  return file_name_;
}

bool Reader::ReadLine(std::string& read_str) {
  if (std::getline(shows_file_, read_str)) {
    return true;
  }
  return false;
}
