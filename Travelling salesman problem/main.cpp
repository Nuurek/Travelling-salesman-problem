#pragma once
#include "ProblemInstance.h"
#include "ProblemGenerator.h"
#include "BruteForce.h"
#include "NearestNeighbour.h"
#include "GeneticAlgorithm.h"
#include <fstream>

int main()
{
	/*
	std::ofstream out("out.txt");
	std::streambuf *coutbuf = std::cout.rdbuf();
	std::cout.rdbuf(out.rdbuf());
	*/

	ProblemGenerator generator;
	ProblemInstance TSP = generator.generateProblem(100, 1, 100);
	TSP.startingCity = 0;
	TSP.print();
	Solution sol;

	/*
	BruteForce bf(TSP);
	sol = bf.solve();
	std::cout << "\nShortest path: " << sol.first << "\n";
	for (auto city : sol.second)
		std::cout << city << " -> ";
	*/

	
	NearestNeighbour nn(TSP);
	sol = nn.solve();
	std::cout << "\nShortest path: " << sol.first << "\n";
	for (auto city : sol.second)
		std::cout << city << " -> ";
	std::cout << "\n";

	GeneticAlgorithm ga(TSP);
	ga.setAttributes(100, 0.1, 0.1);
	sol = ga.solve(10);
	std::cout << "\nShortest path: " << sol.first << "\n";
	for (auto city : sol.second)
		std::cout << city << " -> ";
	std::cout << "\n";
	system("PAUSE");
}