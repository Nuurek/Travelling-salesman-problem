#include "Driver.h"

void Driver::loadCitiesFromFile(std::string file)
{
	std::ifstream in(file);
	std::vector<std::pair<double, double>> positions;
	double x, y;

	while (in >> x >> y)
	{
		positions.emplace_back(std::make_pair(x, y));
	}
	TSP_ = std::make_unique<ProblemInstance>(std::move(ProblemInstance(positions)));
}

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
	Solution solution;
	switch (algorithm)
	{
		case(Algorithms::BRUTE_FORCE) :
			BF = BruteForce(*TSP_);
			solution = BF.solve();
			break;

		case(Algorithms::NEAREST_NEIGHBOUR) :
			NN = NearestNeighbour(*TSP_);
			solution = NN.solve();
			break;

		case(Algorithms::SIMULATED_ANNEALING) :
			SA = SimulatedAnnealing(*TSP_);

			double T, Tmin, tempo;
			std::cout << "Enter the initial temperature: ";
			std::cin >> T;
			std::cout << "Enter the minimum temperature: ";
			std::cin >> Tmin;
			std::cout << "Enter the cooling tempo: ";
			std::cin >> tempo;
			SA.setAttributes(tempo, T, Tmin);

			solution = SA.solve();
			break;

		case(Algorithms::GENETIC_ALGORITHM) :
			GA = GeneticAlgorithm(*TSP_);

			unsigned int populationSize, maxEpochs, time;
			double crossoverPercentage, mutationPercentage;
			std::cout << "Enter the population size: ";
			std::cin >> populationSize;
			std::cout << "Enter the chance of crossover: ";
			std::cin >> crossoverPercentage;
			std::cout << "Enter the chance of mutation: ";
			std::cin >> mutationPercentage;
			std::cout << "\nAlgorithm's execution's restricions:\n";
			std::cout << "Enter the maximum number of epochs: ";
			std::cin >> maxEpochs;
			std::cout << "Enter the maximum time(in seconds): ";
			std::cin >> time;
			std::chrono::seconds maxTime = std::chrono::seconds(time);
			GA.setAttributes(populationSize, crossoverPercentage, mutationPercentage);
			GA.setRestrictions(maxEpochs, maxTime);

			solution = GA.solve();
			break;
	}

	std::cout << "\nShortest path: " << solution.first << "\n";
	for (auto city : solution.second)
		std::cout << city << " -> ";
	std::cout << "\n";
}

Driver::Driver() : 
	TSP_(std::make_unique<ProblemInstance>(ProblemInstance(0))), 
	generator_(), BF(*TSP_), NN(*TSP_), SA(*TSP_), GA(*TSP_)
{
	
}

Driver::~Driver()
{
}
