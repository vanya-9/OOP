#include "reading_file.h"

void readingFile::SetFileName(const std::string& name) {
  file_name_ = name;
}

std::string readingFile::GetFileName() {
  return file_name_;
}
