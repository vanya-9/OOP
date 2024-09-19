#include "reading_file.h"

void reading_file::set_file_name() {
  std::cout << "What is file name?\n";
  getline(std::cin, file_name);  // так можно вводить строку с пробелом!
}

std::string reading_file::get_file_name() { return file_name; }

std::string reading_file::get_read() { return read; }

void reading_file::add_to_new_word(char c) { new_word += c; }
bool reading_file::check_empty_new_word() { return new_word.empty(); }
std::string reading_file::get_new_word() { return new_word; }
void reading_file::new_word_drop() { new_word.clear(); }
void reading_file::plus_word() { number_words++; }

void reading_file::improve_number_map(std::string new_word) {
  words[new_word]++;
}

std::map<std::string, unsigned>::iterator reading_file::get_words_begin() {
  return words.begin();
}

// Возвращаем итератор на конец
std::map<std::string, unsigned>::iterator reading_file::get_words_end() {
  return words.end();
}

double reading_file::get_number_words() { return number_words; }

void reading_file::adding_map(reading_file &map_words) {
  if (!check_empty_new_word()) {
    map_words.plus_word();  // Увеличиваем количество слов
    map_words.improve_number_map(
        get_new_word());  // Обновляем частотную карту слов
    new_word_drop();
  }
}

bool reading_file::read_line(std::ifstream &file) {
  return bool(getline(file, read));
}