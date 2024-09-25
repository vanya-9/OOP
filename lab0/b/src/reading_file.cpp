#include "reading_file.h"

void ReadingFile::SetFileName(const std::string& name) {
  file_name_ = name;
}

std::string ReadingFile::GetFileName() {
  return file_name_;
}
