#ifndef READING_FILE_H
#define READING_FILE_H
#include "fstream"
#include "iostream"
#include "map"
#include "string"
class reading_file {
  std::string new_word = "";
  std::string file_name;
  std::map<std::string, unsigned> words;
  double number_words = 0.0;
  std::string read;

 public:
  void set_file_name();

  std::string get_file_name();

  std::string get_read();

  void add_to_new_word(char c);
  bool check_empty_new_word();
  std::string get_new_word();
  void new_word_drop();
  void plus_word();

  void improve_number_map(std::string new_word);

  std::map<std::string, unsigned>::iterator get_words_begin();

  std::map<std::string, unsigned>::iterator get_words_end();

  double get_number_words();

  void adding_map(reading_file &map_words);

  bool read_line(std::ifstream &file);
};

#endif