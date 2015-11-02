#pragma once
#include "TSPSolver.h"
#include "Chromosome.h"
#include <random>
#include <algorithm>
#include <chrono>
#include <list>

class GeneticAlgorithm :
	protected TSPSolver
{
	std::default_random_engine randomEngine_;
	std::uniform_int_distribution<unsigned int> distribiution_;

	unsigned int populationSize_;
	std::vector<Chromosome> population;

	unsigned long long updateFitness(Chromosome& chromosome);
	unsigned long long updateFitnesses();
	unsigned long long optSwap(Chromosome& chromosome, unsigned int cityA, unsigned int cityB);
	unsigned long long optMethod(Chromosome& chromosomse);
	Chromosome crossover(Chromosome& parentA, Chromosome& parentB);

public:
	GeneticAlgorithm(ProblemInstance instance);
	~GeneticAlgorithm();

	void initialize();
	unsigned long long sort();

	void setAttributes(unsigned int populationSize);
	void print();
	Solution solve();
};

