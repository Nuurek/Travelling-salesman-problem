#include "Driver.h"

bool Driver::loadProblemFromFile(const std::string file)
{
	std::ifstream in;
	in.open(file);
	if (in.good())
	{
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
		in.close();
		return true;
	}
	else
		return false;
}

bool Driver::loadCitiesFromFile(const std::string file)
{
	std::ifstream in;
	in.open(file);
	if (in.good())
	{
		std::vector<std::pair<double, double>> positions;
		double x, y;

		while (in >> x >> y)
		{
			positions.emplace_back(std::make_pair(x, y));
		}
		TSP_ = std::make_unique<ProblemInstance>(std::move(ProblemInstance(positions)));
		in.close();
		return true;
	}
	else
		return false;
}

void Driver::saveProblemToFile(std::string file)
{
	std::ofstream out(file);
	std::streambuf *coutbuf = std::cout.rdbuf();
	std::cout.rdbuf(out.rdbuf());

	std::cout << TSP_->getNumberOfCities() << "\n";
	TSP_->print();

	std::cout.rdbuf(coutbuf);
	out.close();
}

void Driver::printDistanceChart()
{
	std::cout << "DISTANCE CHART\n";
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

void Driver::run()
{
	int selection = 0;
	while (selection != -1)
	{
		std::cout << "MENU:\n";
		std::cout << "1. Generate the problem.\n";
		std::cout << "2. Create problem from cities.\n";
		std::cout << "3. Load problem from file.\n";
		std::cout << "4. Load list of cities and create a problem from them.\n";
		std::cout << "5. Save problem to file.\n";
		std::cout << "6. Print a distance chart.\n";
		std::cout << "7. Solve the problem using one of the methods.\n";
		std::cout << "8. Exit the program.\n";
		std::cout << "> ";
		std::cin >> selection;
		std::cout << "\n";
		switch (selection)
		{
			case(1) :
			{
				unsigned int numberOfCities = 0, minDistance = 0, maxDistance = 0;
				std::cout << "Enter the number of cities: ";
				std::cin >> numberOfCities;
				std::cout << "Enter a minimal distance: ";
				std::cin >> minDistance;
				std::cout << "Enter a maximum distance: ";
				std::cin >> maxDistance;
				generateProblem(numberOfCities, minDistance, maxDistance);
				std::cout << "Problem generated and stored in the memory.\n\n";
				break;
			}
			case(2) :
			{
				std::vector<std::pair<double, double>> positions;
				unsigned int numberOfCities = 0;
				double x, y;

				std::cout << "Enter the number of cities: ";
				std::cin >> numberOfCities;
				for (unsigned int city = 0; city < numberOfCities; city++)
				{
					std::cin >> x >> y;
					positions.emplace_back(std::make_pair(x, y));
				}
				TSP_ = std::make_unique<ProblemInstance>(std::move(ProblemInstance(positions)));
				break;
			}
			case(3) :
			{
				char file[40];
				std::cout << "Type in a name of file: ";
				std::cin >> file;
				if (loadProblemFromFile(std::string(file)))
					std::cout << "Problem loaded from file.\n\n";
				else
					std::cout << "File not found!\n\n";
				break;
			}
			case(4) :
			{
				char file[40];
				std::cout << "Type in a name of file: ";
				std::cin >> file;
				if (loadCitiesFromFile(std::string(file)))
					std::cout << "Cities loaded from file.\n\n";
				else
					std::cout << "File not found!\n\n";
				break;
			}
			case(5) :
				char file[40];
				std::cout << "Type in a name of file: ";
				std::cin >> file;
				saveProblemToFile(std::string(file));
				std::cout << "Problem saved to file.\n\n";
				break;

			case(6) :
				printDistanceChart();
				break;

			case(7) :
			{
				std::cout << "Choose algorithm: \n";
				std::cout << "1. Brute Force\n";
				std::cout << "2. Nearest Neighbour\n";
				std::cout << "3. Simulated Annealing\n";
				std::cout << "4. Genetic Algorithm\n";
				std::cout << "> ";
				std::cin >> selection;
				auto start = std::chrono::high_resolution_clock::now();	
				solveProblem(static_cast<Algorithms>(selection - 1));
				auto end = std::chrono::high_resolution_clock::now();
				double duration = static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()) / 1000.0;
				std::cout << "Algorithm finished in " << duration << "s.\n";
				break;
			}
			case(8) :
				selection = -1;
				break;

			default:
			{
				std::cout << "Enter number 1 - 8 ! ! !\n\n";
				selection = 0;
				break;
			}
		}
	}
}

Driver::Driver() : 
	TSP_(std::make_unique<ProblemInstance>(ProblemInstance(0))), 
	generator_(), BF(*TSP_), NN(*TSP_), SA(*TSP_), GA(*TSP_)
{
	
}

Driver::~Driver()
{
}
