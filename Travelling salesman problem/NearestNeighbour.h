#pragma once
#include "TSPSolver.h"

class NearestNeighbour :
	protected TSPSolver
{
	std::vector<bool> isVisited;

public:
	NearestNeighbour(ProblemInstance instance);

	Solution solve();
};

