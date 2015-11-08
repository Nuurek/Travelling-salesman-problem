#pragma once
#include "Driver.h"

int main()
{
	
	Driver driver;
	driver.generateProblem(10, 1, 10);
	//driver.saveProblemToFile("distances.txt");
	driver.loadProblemFromFile("distances.txt");
	driver.printDistanceChart();
	driver.solveProblem(Algorithms::NEAREST_NEIGHBOUR);

	

	/*
	ProblemGenerator generator;
	ProblemInstance TSP;
	TSP = std::move(generator.generateProblem(100, 1, 100));
	//TSP = ProblemInstance(std::vector<std::pair<double, double>>{ {1, 1}, { -1, -1 }, { 2, 2 }, { 0,0 }, { 10, -8 }, { 9, 1 }});
	TSP.startingCity = 1;
	TSP.print();
	Solution sol;
	*/

	/*
	BruteForce bf(TSP);
	sol = bf.solve();
	std::cout << "\nShortest path: " << sol.first << "\n";
	for (auto city : sol.second)
		std::cout << city << " -> ";
	*/
	
	/*
	NearestNeighbour nn(TSP);
	sol = nn.solve();
	std::cout << "\nShortest path: " << sol.first << "\n";
	for (auto city : sol.second)
		std::cout << city << " -> ";
	std::cout << "\n";
	*/

	/*
	SimulatedAnnealing sa(TSP);
	sa.setAttributes(0.5);
	sol = sa.solve();
	std::cout << "\nShortest path: " << sol.first << "\n";
	for (auto city : sol.second)
		std::cout << city << " -> ";
	std::cout << "\n";
	*/

	/*
	GeneticAlgorithm ga(TSP);
	ga.setAttributes(100, 0.3, 0.3);
	sol = ga.solve(10);
	std::cout << "\nShortest path: " << sol.first << "\n";
	for (auto city : sol.second)
		std::cout << city << " -> ";
	std::cout << "\n";
	*/

	system("PAUSE");
}