#pragma once
#include "TSPSolver.h"

class NearestNeighbour :
	public TSPSolver
{
	std::vector<bool> isVisited;

public:
	NearestNeighbour(ProblemInstance instance);

	Solution solve();
};

