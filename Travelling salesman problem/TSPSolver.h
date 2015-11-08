#pragma once
#include <memory>
#include "ProblemInstance.h"

using Solution = std::pair<unsigned long long, std::vector<unsigned int>>;

class TSPSolver
{
protected:
	ProblemInstance instance_;

	unsigned long long calculateDistance(std::shared_ptr<std::vector<unsigned int>> path)
	{
		unsigned long long distance = 0;
		for (auto city = path->begin(); city != path->end() - 1; city++)
			distance += instance_(*city, *(city + 1));
		return distance;
	}

public:
	TSPSolver(ProblemInstance instance) :
		instance_(instance)
	{
	}

	~TSPSolver()
	{
	}

	void changeInstance(ProblemInstance instance)
	{
		instance_ = instance;
	}
	
	virtual Solution solve() = 0;
};

