#pragma once
#include <vector>
#include <memory>
#include <functional>
#include "ProblemInstance.h"

class Chromosome : public std::vector<unsigned int>
{
private:

public:
	unsigned long long fitness;

	Chromosome();
	Chromosome(unsigned int size);

	Chromosome complementChromosome(unsigned int numberOfCities) const;
	static Chromosome emptyChromosome();

	bool operator==(const Chromosome& rhs);
	bool operator<(const Chromosome& rhs) const;

	void print() const;
};