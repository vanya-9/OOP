#ifndef WRITING_CSV_H
#define WRITING_CSV_H
#include "fstream"
#include "vector"
#define percent 100

class writing_csv {
 public:
  void writing(std::vector<std::pair<std::string, unsigned>> vector_map,
               double number_words);
};
#endif