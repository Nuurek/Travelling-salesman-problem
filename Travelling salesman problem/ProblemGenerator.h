#pragma once
#include <random>
#include <chrono>
#include "ProblemInstantion.h"

class ProblemGenerator
{
	std::default_random_engine randomEngine_;
	std::uniform_int_distribution<unsigned int> distribiution_;

public:
	ProblemGenerator();

	ProblemInstantion generateProblem(unsigned int numberOfCities, unsigned int minDistance, unsigned int maxDistance);
};

