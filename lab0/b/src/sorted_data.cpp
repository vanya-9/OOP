
#include "sorted_data.h"
bool sorted_data::compare(std::pair<std::string, unsigned> &element_one,
                          std::pair<std::string, unsigned> &element_two) {
  return element_one.second > element_two.second;
}

void sorted_data::copy_from_map(
    std::map<std::string, unsigned>::iterator map_begin,
    std::map<std::string, unsigned>::iterator map_end) {
  vector.assign(map_begin, map_end);
}

std::vector<std::pair<std::string, unsigned>>::iterator
sorted_data::get_vector_begin() {
  return vector.begin();
}

std::vector<std::pair<std::string, unsigned>>::iterator
sorted_data::get_vector_end() {
  return vector.end();
}
void sorted_data::vector_sort(
    std::vector<std::pair<std::string, unsigned>>::iterator vector_begin,
    std::vector<std::pair<std::string, unsigned>>::iterator vector_end) {
  std::sort(vector.begin(), vector.end(), compare);
}
std::vector<std::pair<std::string, unsigned>> sorted_data::get_vectop() {
  return vector;
}
