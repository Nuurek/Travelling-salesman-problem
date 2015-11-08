#include "Driver.h"

void Driver::loadProblemFromFile(std::string file)
{
	std::ifstream in(file);
	unsigned int distance, cityA = 0, cityB = 0, numberOfCities = 0;
	
	in >> numberOfCities;
	ProblemInstance newTSP(numberOfCities);

	while (in >> distance)
	{
		if (cityA == cityB)
		{
			++cityA;
			cityB = 0;
		}
		newTSP(cityA, cityB) = distance;
		++cityB;
	}
	TSP_ = std::make_unique<ProblemInstance>(newTSP);
}

void Driver::saveProblemToFile(std::string file)
{
	std::ofstream out(file);
	std::streambuf *coutbuf = std::cout.rdbuf();
	std::cout.rdbuf(out.rdbuf());

	std::cout << TSP_->getNumberOfCities() << "\n";
	TSP_->print();

	std::cout.rdbuf(coutbuf);
}

void Driver::loadCitiesFromFile(std::string file)
{
}

void Driver::printDistanceChart()
{
	TSP_->print();
}

void Driver::generateProblem(unsigned int numberOfCities, unsigned int minDistance, unsigned int maxDistance)
{
	TSP_ = std::make_unique<ProblemInstance>(generator_.generateProblem(numberOfCities, minDistance, maxDistance));
}

void Driver::solveProblem(Algorithms algorithm)
{
	Solution sol;// = std::move(algorithms_[static_cast<unsigned int>(algorithm)].solve());
	std::cout << "\nShortest path: " << sol.first << "\n";
	for (auto city : sol.second)
		std::cout << city << " -> ";
	std::cout << "\n";
}

Driver::Driver() : 
	TSP_(std::make_shared<ProblemInstance>(ProblemInstance(0))), 
	generator_() 
	//algorithms_(std::move(std::vector<TSPSolver>{BruteForce(*TSP_), NearestNeighbour(*TSP_), SimulatedAnnealing(*TSP_), GeneticAlgorithm(*TSP_)}))
{
}

Driver::~Driver()
{
}
