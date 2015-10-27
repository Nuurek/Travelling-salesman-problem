#include "ProblemGenerator.h"


ProblemGenerator::ProblemGenerator()
{
	randomEngine_.seed(static_cast<unsigned long>(std::chrono::system_clock::now().time_since_epoch().count()));
}

ProblemInstance ProblemGenerator::generateProblem(unsigned int numberOfCities, unsigned int minDistance, unsigned int maxDistance)
{
	ProblemInstance instance(numberOfCities);
	distribiution_ = std::move(std::uniform_int_distribution<unsigned int>(minDistance, maxDistance));
	
	for (auto& distance : instance)
		distance = distribiution_(randomEngine_);

	return instance;
}

