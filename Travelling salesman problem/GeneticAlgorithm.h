#pragma once
#include "TSPSolver.h"
#include "Chromosome.h"
#include <random>
#include <algorithm>
#include <chrono>
#include <list>
#include <memory>
#include <cmath>

class GeneticAlgorithm :
	protected TSPSolver
{
	std::default_random_engine randomEngine_;
	std::uniform_int_distribution<unsigned int> distribiution_;

	unsigned int populationCap_;
	unsigned int populationSize_;
	double crossoverPercentage_;
	double mutationPercentage_;
	unsigned int maxEpochs_;
	std::vector<Chromosome> population;

	unsigned long long updateFitness(Chromosome& chromosome);

	unsigned long long optSwap(Chromosome& chromosome, unsigned int cityA, unsigned int cityB);
	unsigned long long optMethod(Chromosome& chromosomse);

	Chromosome crossover(Chromosome& parentA, Chromosome& parentB);

	unsigned int eliminateDuplicates();

	unsigned int eliminateImpotents();

	void recombine();

	void mutate();

public:
	GeneticAlgorithm(ProblemInstance instance);
	~GeneticAlgorithm();

	void initialize();
	unsigned long long sort();
	void epoch();

	void setAttributes(unsigned int populationCap, double crossoverPercentage, double mutationPercentage);
	void setMaximums(unsigned int maxEpochs);
	void print();
	Solution solve();
	Solution solve(unsigned int eras);
};

