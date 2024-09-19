#include "writing_csv.h"
void writing_csv::writing(
    std::vector<std::pair<std::string, unsigned>> vector_map,
    double number_words) {
  std::ofstream out("csv.txt", std::ios::app);
  if (out.is_open()) {
    for (int i = 0; i < vector_map.size(); i++) {
      out << vector_map[i].first << " " << vector_map[i].second << " "
          << (vector_map[i].second / number_words) * percent << std::endl;
    }
    out.close();
  }
}