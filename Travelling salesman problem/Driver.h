#pragma once
#include "ProblemGenerator.h"
#include "BruteForce.h"
#include "NearestNeighbour.h"
#include "GeneticAlgorithm.h"
#include "SimulatedAnnealing.h"
#include <fstream>
#include <memory>

enum class Algorithms
{
	BRUTE_FORCE, NEAREST_NEIGHBOUR, SIMULATED_ANNEALING, GENETIC_ALGORITHM
};

class Driver
{
	
	
public:
	std::unique_ptr<ProblemInstance> TSP_;
	ProblemGenerator generator_;
	BruteForce BF;
	NearestNeighbour NN;
	SimulatedAnnealing SA;
	GeneticAlgorithm GA;

	Driver();
	~Driver();
	
	void loadCitiesFromFile(std::string file);
	void loadProblemFromFile(std::string file);
	void saveProblemToFile(std::string file);
	void printDistanceChart();
	void generateProblem(unsigned int numberOfCities, unsigned int minDistance, unsigned int maxDistance);
	void solveProblem(Algorithms algorithm);
};

