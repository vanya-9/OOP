#ifndef SORTED_DATA_H
#define SORTED_DATA_H
#include "map"
#include "string"
#include "vector"
#include "algorithm"
class sorted_data {
  std::vector<std::pair<std::string, unsigned>> vector;

 public:
  static bool compare(std::pair<std::string, unsigned> &element_one,
                      std::pair<std::string, unsigned> &element_two);

  void copy_from_map(std::map<std::string, unsigned>::iterator map_begin,
                     std::map<std::string, unsigned>::iterator map_end);

  std::vector<std::pair<std::string, unsigned>>::iterator get_vector_begin();

  // Возвращаем итератор на конец
  std::vector<std::pair<std::string, unsigned>>::iterator get_vector_end();

  void vector_sort(
      std::vector<std::pair<std::string, unsigned>>::iterator vector_begin,
      std::vector<std::pair<std::string, unsigned>>::iterator vector_end);
  std::vector<std::pair<std::string, unsigned>> get_vectop();
};

#endif