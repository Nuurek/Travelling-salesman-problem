#pragma once
#include <iostream>
#include "CityDistanceMatrix.h"

class ProblemInstance
{
	unsigned int numberOfCities_;
	unsigned int startingCity_;
	CityDistanceMatrix distances_;

public:
	ProblemInstance();
	ProblemInstance(unsigned int numberOfCities);

	unsigned int& operator()(unsigned int start, unsigned int destination);
	unsigned int operator()(unsigned int start, unsigned int destination) const;
	
	using iterator = unsigned int*;
	iterator begin() { return &distances_(1, 0); }
	iterator end() { return &distances_(numberOfCities_ - 1, numberOfCities_ - 2) + 1; }

	void setStartingCity(unsigned int start);
	void print();
};

