#include "reading_file.h"

  void reading_file::set_file_name(const std::string& name) { file_name = name; }

  std::string reading_file::get_file_name() { return file_name; }

  bool reading_file::read_line(std::ifstream& file) {
    return bool(getline(file, reading_str));
  }

  std::string reading_file::get_read() { return reading_str; }

  void reading_file::add_to_new_word(char c) { new_word += c; }
  bool reading_file::check_empty_new_word() { return new_word.empty(); }
  std::string reading_file::get_new_word() { return new_word; }
  void reading_file::new_word_drop() { new_word.clear(); }
;