#pragma once
#include "TSPSolver.h"
#include <climits>

class BruteForce :
	protected TSPSolver
{
	Solution bestSolution_;

public:
	BruteForce(ProblemInstance instance);

	std::vector<unsigned int> firstPathPermutation();
	Solution solve();
};

