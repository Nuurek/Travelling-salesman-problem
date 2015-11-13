#pragma once
#include <iostream>
#include <cmath>
#include "CityDistanceMatrix.h"

class ProblemInstance
{
	unsigned int numberOfCities_;
	CityDistanceMatrix distances_;
	std::vector<std::pair<double, double>> citiesPositions;

public:
	unsigned int startingCity = 0;

	ProblemInstance();
	ProblemInstance(unsigned int numberOfCities);
	ProblemInstance(std::vector<std::pair<double, double>> vectorOfCities);

	unsigned int& operator()(unsigned int start, unsigned int destination);
	unsigned int operator()(unsigned int start, unsigned int destination) const;
	
	using iterator = unsigned int*;
	iterator begin() { return &distances_(1, 0); }
	iterator end() { return &distances_(numberOfCities_ - 1, numberOfCities_ - 2) + 1; }

	unsigned int getNumberOfCities()
	{
		return numberOfCities_;
	}
	void print();
};

