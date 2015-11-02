#pragma once
#include "ProblemInstance.h"
#include "ProblemGenerator.h"
#include "BruteForce.h"
#include "NearestNeighbour.h"
#include "GeneticAlgorithm.h"

int main()
{
	ProblemGenerator generator;
	ProblemInstance TSP = generator.generateProblem(10, 1, 20);
	TSP.startingCity = 0;
	TSP.print();
	Solution sol;

	for (int i = -10; i <= 10; i++)
		std::cout << "Modulo: " << i % 10 << "\n";

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
	ga.setAttributes(10);
	ga.initialize();
	ga.print();
	system("PAUSE");
}