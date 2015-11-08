#pragma once
#include "TSPSolver.h"
#include <climits>

class BruteForce :
	public TSPSolver
{
protected:
	Solution bestSolution_;
	std::vector<unsigned int> firstPathPermutation();

public:
	BruteForce(ProblemInstance instance);
	Solution solve();

	void special()
	{
		auto path = std::vector<unsigned int>{ 1, 76, 59, 15, 30, 29, 120, 32, 92, 28, 45, 78, 86, 94, 81, 22, 66, 31, 117, 85, 18, 19, 25, 108, 43, 79, 52, 33, 100, 58, 91, 68, 65, 69, 113, 107, 20, 46, 50, 44, 75, 14, 87, 74, 105, 40, 72, 38, 7, 56, 41, 42, 98, 17, 118, 49, 13, 51, 11, 23, 9, 103, 119, 3, 82, 2, 115, 21, 93, 53, 64, 109, 88, 97, 12, 95, 77, 39, 63, 5, 27, 80, 101, 102, 48, 110, 112, 106, 114, 73, 57, 83, 67, 37, 62, 99, 10, 35, 104, 36, 84, 6, 89, 55, 47, 71, 26, 4, 34, 116, 70, 8, 54, 90, 96, 111, 24, 60, 16, 61, 1 };
		for (auto &city : path)
			--city;
		std::cout << "OPT: " << calculateDistance(std::make_shared<std::vector<unsigned int>>(path)) << "\n";
	}
};

