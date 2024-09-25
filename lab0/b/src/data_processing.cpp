
#include "data_processing.h"

void data_processing::IncreseWordCount(std::string word) {
  words[word]++;
  number_words_++;
}

double data_processing::GetNumberWords() {
  return number_words_;
}

void data_processing::SortData(
    std::vector<std::pair<std::string, unsigned>>& vector_map) {
  vector_map.assign(words.begin(), words.end());
  std::sort(vector_map.begin(), vector_map.end(),
            [](const std::pair<std::string, unsigned>& element_one,
               const std::pair<std::string, unsigned>& element_two) {
              return element_one.second > element_two.second;
            });
}
