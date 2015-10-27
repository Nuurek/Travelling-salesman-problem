#include "ProblemGenerator.h"


ProblemGenerator::ProblemGenerator()
{
	randomEngine_.seed(static_cast<unsigned long>(std::chrono::system_clock::now().time_since_epoch().count()));
}

ProblemInstantion ProblemGenerator::generateProblem(unsigned int numberOfCities, unsigned int minDistance, unsigned int maxDistance)
{
	ProblemInstantion instantion(numberOfCities);
	distribiution_ = std::move(std::uniform_int_distribution<unsigned int>(minDistance, maxDistance));
	
	for (auto& distance : instantion)
		distance = distribiution_(randomEngine_);

	return instantion;
}

