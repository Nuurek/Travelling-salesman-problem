#pragma once
#include <random>
#include <chrono>
#include "ProblemInstance.h"

class ProblemGenerator
{
	std::default_random_engine randomEngine_;
	std::uniform_int_distribution<unsigned int> distribiution_;

public:
	ProblemGenerator();

	ProblemInstance generateProblem(unsigned int numberOfCities, unsigned int minDistance, unsigned int maxDistance);
};

