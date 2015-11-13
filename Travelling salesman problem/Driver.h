#pragma once
#include "ProblemGenerator.h"
#include "BruteForce.h"
#include "NearestNeighbour.h"
#include "GeneticAlgorithm.h"
#include "SimulatedAnnealing.h"
#include <fstream>
#include <memory>
#include <iostream>
#include <string>

enum class Algorithms
{
	BRUTE_FORCE, NEAREST_NEIGHBOUR, SIMULATED_ANNEALING, GENETIC_ALGORITHM
};

class Driver
{
	
	
public:
	Driver();
	~Driver();

	std::unique_ptr<ProblemInstance> TSP_;
	ProblemGenerator generator_;
	BruteForce BF;
	NearestNeighbour NN;
	SimulatedAnnealing SA;
	GeneticAlgorithm GA;

	bool loadCitiesFromFile(const std::string file);
	bool loadProblemFromFile(const std::string file);
	void saveProblemToFile(const std::string file);
	void printDistanceChart();
	void generateProblem(unsigned int numberOfCities, unsigned int minDistance, unsigned int maxDistance);
	void solveProblem(Algorithms algorithm);
	void run();
};

