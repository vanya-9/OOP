
#include "data_processing.h"

void dataProcessing::IncreseWordCount(std::string word) {
  words[word]++;
  number_words_++;
}

double dataProcessing::GetNumberWords() {
  return number_words_;
}

void dataProcessing::SortData(
    std::vector<std::pair<std::string, unsigned>>& vector_map) {

  vector_map.assign(words.begin(), words.end());
  std::sort(vector_map.begin(), vector_map.end(),
            [](const std::pair<std::string, unsigned>& element_one,
               const std::pair<std::string, unsigned>& element_two) {
              if (element_one.second == element_two.second) {
                return element_one.first < element_two.first;
              }
              return element_one.second > element_two.second;
            });
}
