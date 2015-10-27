#pragma once
#include "ProblemInstance.h"
#include "ProblemGenerator.h"
#include "BruteForce.h"
#include "NearestNeighbour.h"

int main()
{
	ProblemGenerator generator;
	ProblemInstance TSP = generator.generateProblem(9, 1, 100);
	TSP.startingCity = 0;
	TSP.print();

	BruteForce bf(TSP);
	Solution sol = bf.solve();
	std::cout << "\nShortest path: " << sol.first << "\n";
	for (auto city : sol.second)
		std::cout << city << " -> ";

	NearestNeighbour nn(TSP);
	sol = nn.solve();
	std::cout << "\nShortest path: " << sol.first << "\n";
	for (auto city : sol.second)
		std::cout << city << " -> ";

	system("PAUSE");
}