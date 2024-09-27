#pragma once
#include <algorithm>
#include <map>
#include <string>
#include <vector> //
#include <list>
class DataProcess {
  std::map<std::string, unsigned> words_;
  double number_words_ = 0.0;

 public:

  void IncreseWordCount(std::string word);

  double GetNumberWords();

  void SortData(std::list<std::pair<std::string, unsigned>>& list_map);

  void AddToMap(std::string& new_word);
};
