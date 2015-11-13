#include "Driver.h"

int main() {

//	ProblemGenerator generator;
//	ProblemInstance TSP = generator.generateProblem(150, 1, 100);
//	SimulatedAnnealing SA = SimulatedAnnealing(TSP);
//	std::ofstream times, results;
//	times.open("SAczasy50c20e.txt");
//	results.open("SAwyniki50c20e.txt");
//	unsigned long long path = 0;

//	for (double T = 1; T <= 100000; T *= 10)
//	{
//		for (double mutate = 0.1; mutate <= 0.9; mutate += 0.1)
//		{
//			auto start = std::chrono::high_resolution_clock::now();
//			GA.setAttributes(100, cross, mutate);
//			path = GA.solve().first;
//			auto end = std::chrono::high_resolution_clock::now();
//			double duration = static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()) / 1000.0;
//			times << duration << "\t";
//			results << path << "\t";
//			std::cout << cross << " x " << mutate << " -> " << path << " in " << duration << "\n";
//		}
//		times << "\n";
//		results << "\n";
//	}

	
	Driver driver;
	driver.run();
	
	
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
}