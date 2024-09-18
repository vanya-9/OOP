#include "creating_map.h"
bool check_symbol(char symbol)
{
    if (std::isalpha(symbol) || std::isdigit(symbol))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void create_map(std::string file_name, std::map<std::string, unsigned> &words, double* k)
{
    
    std::string new_word = ""; // суда буду лепить слова
    std::ifstream shows_file(file_name);
    std::string read; // в эту переменную буду считывать строки из файла
    while (getline(shows_file, read))
    {
        for (char c : read)
        {
            if (check_symbol(c))
            {
                new_word += c;
            }
            else
            {
                if (!new_word.empty())
                {
                    (*k)++;
                    words[new_word]++;
                    new_word.clear();
                }
            }
        }
        if (!new_word.empty())
        {
            (*k)++;
            words[new_word]++;
            new_word.clear();
        }

    }
}