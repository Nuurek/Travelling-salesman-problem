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
	std::shared_ptr<ProblemInstance> TSP_;
	ProblemGenerator generator_;
	//std::vector<TSPSolver> algorithms_;
	
public:
	Driver();
	~Driver();
	
	void loadProblemFromFile(std::string file);
	void saveProblemToFile(std::string file);
	void loadCitiesFromFile(std::string file);
	void printDistanceChart();
	void generateProblem(unsigned int numberOfCities, unsigned int minDistance, unsigned int maxDistance);
	void solveProblem(Algorithms algorithm);
};

