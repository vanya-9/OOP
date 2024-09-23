#ifndef DATA_PROCESSING_H
#define SORTED_DATA_H
#include <map>
#include <string>
class data_processing {
  std::map<std::string, unsigned> words;
  double number_words = 0.0;

 public:
  void plus_word();
  void increse_word_count(std::string word);
  std::map<std::string, unsigned>::iterator get_words_begin();

  std::map<std::string, unsigned>::iterator get_words_end();
  double get_number_words();
};

#endif