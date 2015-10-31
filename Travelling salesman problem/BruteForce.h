#pragma once
#include "TSPSolver.h"
#include <climits>

class BruteForce :
	protected TSPSolver
{
protected:
	Solution bestSolution_;
	std::vector<unsigned int> firstPathPermutation();

public:
	BruteForce(ProblemInstance instance);
	Solution solve();
};

