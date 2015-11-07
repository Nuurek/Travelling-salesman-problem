#pragma once
#include "ProblemGenerator.h"
#include "BruteForce.h"
#include "NearestNeighbour.h"
#include "GeneticAlgorithm.h"
#include "SimulatedAnnealing.h"
#include <fstream>

class Driver
{
	ProblemInstance* TSP_;
	ProblemGenerator generator_;
	
public:
	Driver();
	~Driver();
	
	void loadProblemFromFile(std::string file);
	void saveProblemToFile(std::string file);
};

