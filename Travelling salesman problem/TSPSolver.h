#pragma once
#include "ProblemInstance.h"

class TSPSolver
{
	ProblemInstance instance;

public:

	TSPSolver()
	{
	}

	~TSPSolver()
	{
	}

	virtual unsigned int solve();
};

