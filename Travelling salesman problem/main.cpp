#pragma once
#include "ProblemInstance.h"
#include "ProblemGenerator.h"
#include "BruteForce.h"

int main()
{
	ProblemGenerator generator;
	ProblemInstance TSP = generator.generateProblem(4, 1, 10);
	TSP.startingCity = 0;
	TSP.print();
	BruteForce bruteForce(TSP);
	Solution sol = bruteForce.solve();
	std::cout << "Shortest path: " << sol.first << "\n";
	for (auto city : sol.second)
		std::cout << city << " -> ";
	system("PAUSE");
}