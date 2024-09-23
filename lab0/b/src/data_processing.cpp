
#include "data_processing.h"

void data_processing::plus_word() { number_words++; }
void data_processing::increse_word_count(std::string word) { words[word]++; }
std::map<std::string, unsigned>::iterator data_processing::get_words_begin() {
  return words.begin();
}

std::map<std::string, unsigned>::iterator data_processing::get_words_end() {
  return words.end();
}
double data_processing::get_number_words() { return number_words; }
