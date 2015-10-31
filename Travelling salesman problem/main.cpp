#include "ProblemInstance.h"
#include "ProblemGenerator.h"
#include "BruteForce.h"
#include "NearestNeighbour.h"
#include "GeneticAlgorithm.h"
#include "SimulatedAnnealing.h"

int main()
{
	ProblemGenerator generator;
	ProblemInstance TSP = generator.generateProblem(100, 1, 10);
	TSP.startingCity = 0;
	TSP.print();
	Solution sol;

    /*
	BruteForce bf(TSP);
	sol = bf.solve();
	std::cout << "\nShortest path: " << sol.first << "\n";
	for (auto city : sol.second)
		std::cout << city << " -> ";
    /*

	/*
	NearestNeighbour nn(TSP);
	sol = nn.solve();
	std::cout << "\nShortest path: " << sol.first << "\n";
	for (auto city : sol.second)
		std::cout << city << " -> ";
	*/

    /*
	GeneticAlgorithm ga(TSP);
	ga.setAttributes(20);
	ga.initialize();
	ga.print();
	system("PAUSE");
    */

	SimulatedAnnealing sa(TSP);
	sol = sa.solve();
	std::cout << "\nShortest path: " << sol.first << "\n";
	for (auto city : sol.second)
		std::cout << city << " -> ";
}