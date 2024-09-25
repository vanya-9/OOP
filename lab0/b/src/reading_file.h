#pragma once
#include <fstream>
#include <string>
class ReadingFile {
  std::string file_name_;

 public:
  void SetFileName(const std::string& name);

  std::string GetFileName();
};
