#pragma once
#include "TSPSolver.h"
#include "Chromosome.h"
#include <random>
#include <chrono>

class GeneticAlgorithm :
	protected TSPSolver
{
	std::default_random_engine randomEngine_;

	unsigned int populationSize_;
	std::vector<Chromosome> population;

	unsigned long long updateFitnesses();

public:
	GeneticAlgorithm(ProblemInstance instance);
	~GeneticAlgorithm();

	void initialize();

	void setAttributes(unsigned int populationSize);
	void print();
	Solution solve();
};

