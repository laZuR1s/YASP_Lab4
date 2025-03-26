#include "Vector.h"


int VECTOR::sum()
{
    int res{};
    std::for_each(vector.begin(), vector.end(), [&res](int n) { res += n; });
    return res;
}

float VECTOR::average()
{
    float res{};
    int count{};
    std::for_each(vector.begin(), vector.end(), [&res, &count](int n) { res += n; count++; });
    if (!count) return 0;
    return res / count;
}

void VECTOR::print(std::ostream& stream)
{
    for (int a : vector)
        stream << a << " ";
    stream << std::endl;
}


void VECTOR::fill(std::fstream& file)
{
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return;
    }

    int x{};
    while (file >> x)
    {
        vector.push_back(x);
    }
}


std::vector<int> VECTOR::modify_for(std::vector<int>::iterator start, std::vector<int>::iterator end)
{
    std::vector<int> res; // выделить память (distance(start, end))
    int first = (*start) * (*start);
    for (std::vector<int>::iterator ptr = start; ptr != end; ++ptr)
    {
        res.push_back(sqrt((*ptr) * (*ptr) + first));
    }
    return res;
}


std::vector<int> VECTOR::modify_transform(std::vector<int>::iterator start, std::vector<int>::iterator end)
{
    std::vector<int> res(start, end); // создаем такого размера пустой (distance(start, end))
    int first = (*start) * (*start);
    std::transform(start, end, res.begin(), [&first](int x) { return sqrt((x) * (x)+first); });
    return res;
}

std::vector<int> VECTOR::modify_foreach(std::vector<int>::iterator start, std::vector<int>::iterator end)
{
	std::vector<int> res; // выделить память (distance(start, end))
    int first = (*start) * (*start);
    std::for_each(start, end, [&res, &first](int x) { res.push_back(sqrt((x) * (x)+first)); });
    return res;
}
