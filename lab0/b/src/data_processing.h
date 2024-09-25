#pragma once
#include <algorithm>
#include <map>
#include <string>
#include <vector>
class data_processing {
  std::map<std::string, unsigned> words;
  double number_words_ = 0.0;

 public:
  void AddWord();

  void IncreseWordCount(std::string word);

  double GetNumberWords();

  void SortData(std::vector<std::pair<std::string, unsigned>>& vector_map);
};
