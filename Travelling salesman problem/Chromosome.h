#pragma once
#include <vector>
#include <memory>
#include "ProblemInstance.h"

class Chromosome : public std::vector<unsigned int>
{
public:
	unsigned long long fitness;

	Chromosome(unsigned int size);
};

