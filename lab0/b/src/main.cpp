#include "cctype" // Для std::isalpha и std::isdigit
#include <algorithm> // для std::sort
#include "writing.h"
#include "creating_map.h"
using std::cin;
using std::cout;
bool compare(std::pair<std::string, unsigned> &a, std::pair<std::string, unsigned> &b) {
    return a.second > b.second; // Сортировка по убыванию
}


int main()
{
    double k = 0.0;                 // количество слов в файле
    std::map<std::string, unsigned> words;
    std::string file_name = "file_name.txt";
    //cout << "What is file name?\n";
    //getline(cin, file_name); // так можно вводить строку с пробелом!
    create_map(file_name, words, &k);
    std::vector<std::pair<std::string, unsigned>> vector_map(words.begin(), words.end());
    // Сортируем вектор по значению (второй элемент)
    std::sort(vector_map.begin(), vector_map.end(), compare);
    write(vector_map, k);
    return 0;
}