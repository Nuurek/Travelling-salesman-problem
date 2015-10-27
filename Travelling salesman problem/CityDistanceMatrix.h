#pragma once
#include <vector>
#include <algorithm>

class CityDistanceMatrix
{
	std::vector<unsigned int> vectorOfDistances_;

public:
	CityDistanceMatrix(unsigned int numberOfCities);

	unsigned int& operator()(unsigned int start, unsigned int destination);
	unsigned int operator()(unsigned int start, unsigned int destination) const;
};

