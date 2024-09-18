#include "writing.h"
void write(std::vector<std::pair<std::string, unsigned>> vector_map, double k)
{
    std::ofstream out("csv.txt", std::ios::app);
    if (out.is_open())
    {
        for(int i = 0; i < vector_map.size(); i++)
        {
            out << vector_map[i].first << " " << vector_map[i].second << " " << (vector_map[i].second / k) * 100 << endl;
        }
        out.close();
    }

}