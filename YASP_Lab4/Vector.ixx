export module Vector;

import <vector>;
import <Windows.h>;
import <iostream>;
import <fstream>;
import <string>;
import <algorithm>;

export class VECTOR
{
private:
    std::vector<int> vector;
public:
    VECTOR() {};
    ~VECTOR() {};

    void fill(std::fstream&);
    std::vector<int> modify_for(std::vector<int>::iterator start, std::vector<int>::iterator end);
    std::vector<int> modify_transform(std::vector<int>::iterator start, std::vector<int>::iterator end);
    std::vector<int> modify_foreach(std::vector<int>::iterator start, std::vector<int>::iterator end);
    std::vector<int>::iterator begin() { return vector.begin(); };
    std::vector<int>::iterator end() { return vector.end(); }
    std::vector<int>::iterator get_iterator(const size_t number)
    {
        if (number > 0 && number <= vector.size())
            return vector.begin() + (number - 1);
        return vector.end();
    }
    int sum();
    float average();
    void print(std::ostream & = std::cout);
};

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

std::vector<int> VECTOR::modify_for(std::vector<int>::iterator start, std::vector<int>::iterator end)
{
    std::vector<int> res;
    res.reserve(std::distance(start, end)); 
    int first = (*start) * (*start);
    for (std::vector<int>::iterator ptr = start; ptr != end; ++ptr)
    {
        res.push_back(sqrt((*ptr) * (*ptr) + first));
    }
    return res;
}

std::vector<int> VECTOR::modify_transform(std::vector<int>::iterator start, std::vector<int>::iterator end)
{
    std::vector<int> res(std::distance(start,end));
    int first = (*start) * (*start);
    std::transform(start, end, res.begin(), [&first](int x) { return sqrt((x) * (x)+first); });
    return res;
}


std::vector<int> VECTOR::modify_foreach(std::vector<int>::iterator start, std::vector<int>::iterator end)
{
    std::vector<int> res;
    res.reserve(std::distance(start, end));

    int first = (*start) * (*start);
    std::for_each(start, end, [&res, &first](int x) { res.push_back(sqrt((x) * (x)+first)); });
    return res;
}
