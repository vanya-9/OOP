
#include "data_process.h"

void DataProcess::IncreseWordCount(std::string word) {
  words_[word]++;
  number_words_++;
}

double DataProcess::GetNumberWords() {
  return number_words_;
}

void DataProcess::SortData(
    std::list<std::pair<std::string, unsigned>>& list_map) {

   list_map.assign(words_.begin(), words_.end());
  list_map.sort(
            [](const std::pair<std::string, unsigned>& element_one,
               const std::pair<std::string, unsigned>& element_two) {
              if (element_one.second == element_two.second) {
                return element_one.first < element_two.first;
              }
              return element_one.second > element_two.second;
            });
}

 void DataProcess::AddToMap(std::string& new_word){
    if (!new_word.empty()) {
    IncreseWordCount(new_word);
  }
}
