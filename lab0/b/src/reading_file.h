#ifndef READING_FILE_H
#define READING_FILE_H
#include <string>
#include <fstream>
class reading_file {
  std::string file_name;
  std::string reading_str; 
  std::string new_word = "";  
 public:
  void set_file_name(const std::string& name);

  std::string get_file_name();

  bool read_line(std::ifstream& file);

  std::string get_read();

  void add_to_new_word(char c);
  bool check_empty_new_word();
  std::string get_new_word();
  void new_word_drop();
};

#endif