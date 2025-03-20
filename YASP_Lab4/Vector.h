#pragma once
#include <vector>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

class VECTOR
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