#include "GeneticAlgorithm.h"


GeneticAlgorithm::GeneticAlgorithm(ProblemInstance instance) 
	: TSPSolver(instance)
{
	//randomEngine_.seed(static_cast<unsigned long>(std::chrono::system_clock::now().time_since_epoch().count()));
	randomEngine_.seed(20);
}


GeneticAlgorithm::~GeneticAlgorithm()
{
}

void GeneticAlgorithm::initialize()
{
	unsigned int numberOfCities = instance_.getNumberOfCities() - 1;

	population = std::vector<Chromosome>(populationSize_, Chromosome(numberOfCities, instance_.startingCity));
	std::cout << "Population size: " << population.size() << "\n";
	for (auto& chromosome : population)
	{
		std::shuffle(chromosome.begin(), chromosome.end(), randomEngine_);
	}
	updateFitnesses();
}

unsigned long long GeneticAlgorithm::updateFitness(Chromosome& chromosome)
{
	unsigned int numberOfCities = instance_.getNumberOfCities() - 1;

	chromosome.fitness = 0;
	for (unsigned int city = 0; city < numberOfCities - 1; city++)
		chromosome.fitness += instance_(chromosome[city], chromosome[city + 1]);
	chromosome.fitness += instance_(chromosome[0], instance_.startingCity);
	chromosome.fitness += instance_(chromosome[numberOfCities - 1], instance_.startingCity);

	return chromosome.fitness;
}

unsigned long long GeneticAlgorithm::updateFitnesses()
{
	unsigned long long elite = ULLONG_MAX;

	for (auto& chromosome : population)
	{
		updateFitness(chromosome);
		if (chromosome.fitness < elite)
			elite = chromosome.fitness;
	}

	return elite;
}

unsigned long long GeneticAlgorithm::optSwap(Chromosome& chromosome, unsigned int cityA, unsigned int cityB)
{
	int difference = (instance_(chromosome[cityA], chromosome[cityA + 1]) + instance_(chromosome[cityB], chromosome[cityB + 1])) -
		(instance_(chromosome[cityA], chromosome[cityB]) + instance_(chromosome[cityA + 1], chromosome[cityB + 1]));
	if (difference <= 0)
		return 0;
	else
	{
		unsigned int numberOfSwaps = (cityB - cityA) / 2;
		while (numberOfSwaps)
		{
			std::swap(chromosome[cityA + numberOfSwaps], chromosome[cityB - numberOfSwaps + 1]);
			--numberOfSwaps;
		}
		return difference;
	}
}

unsigned long long GeneticAlgorithm::optMethod(Chromosome& chromosome)
{
	bool improvementMade = true;
	unsigned int numberOfCities = instance_.getNumberOfCities() - 1;
	unsigned long long singleDifference = 0, difference = 0;

	while (improvementMade)
	{
		improvementMade = false;
		for (unsigned int cityA = 0; cityA < numberOfCities - 1; cityA++)
		{
			for (unsigned int cityB = cityA + 2; cityB < numberOfCities - 1; cityB++)
			{
				singleDifference = optSwap(chromosome, cityA, cityB);
				if (singleDifference > 0)
				{
					difference += singleDifference;
					improvementMade = true;
				}
			}
		}
	}
	chromosome.fitness = chromosome.fitness - difference;
	return difference;
}

Chromosome GeneticAlgorithm::crossover(Chromosome& parentA, Chromosome& parentB)
{
	bool smthToTakeA = true, smthToTakeB = true;
	unsigned int cityAIndex, cityBIndex;
	unsigned int numberOfCities = instance_.getNumberOfCities();
	std::list<unsigned int> childPrototype;
	Chromosome child(numberOfCities - 1);
	std::vector<unsigned int> notTaken, taken;
	unsigned int sizeOfTaken = 1;
	distribiution_ = std::uniform_int_distribution<unsigned int>(0, numberOfCities - 1);
	unsigned int firstCity;
	
	do
	{
		firstCity = distribiution_(randomEngine_);
	} while (firstCity == instance_.startingCity);
	std::cout << "Number of cities = " << numberOfCities << ", First city = " << firstCity << "\n";
	childPrototype.push_back(firstCity);
	taken.emplace_back(firstCity);
	cityAIndex = std::find(parentA.begin(), parentA.end(), firstCity) - parentA.begin();
	std::cout << "First city found in ParentA, index " << cityAIndex << "\n";
	cityBIndex = std::find(parentB.begin(), parentB.end(), firstCity) - parentB.begin();
	std::cout << "First city found in ParentB, index " << cityBIndex << "\n";
	while (smthToTakeA || smthToTakeB)
	{
		std::cout << "Still something to take.\n";
		
		if (smthToTakeA)
		{
			cityAIndex = (cityAIndex - 1);
			if (cityAIndex == UINT32_MAX)
				cityAIndex = numberOfCities - 2;
			std::cout << "Aindex = " << cityAIndex << "\n";

			if (std::find(childPrototype.begin(), childPrototype.end(), parentA[cityAIndex]) == childPrototype.end())
			{
				unsigned int city = unsigned int(parentA[cityAIndex]);
				std::cout << "Nie znaleziono miasta z CityA w dziecku: miasto: " << city << " na pozycji " << cityAIndex << "\n";
				childPrototype.push_front(city);
				taken.emplace_back(city);
				++sizeOfTaken;
			}
			else
				smthToTakeA = false;
		}
		if (smthToTakeB)
		{
			cityBIndex = (cityBIndex + 1) % (numberOfCities - 1);
			std::cout << "Bindex = " << cityBIndex << "\n";
			if (std::find(childPrototype.begin(), childPrototype.end(), parentB[cityBIndex]) == childPrototype.end())
			{
				unsigned int city = unsigned int(parentB[cityBIndex]);
				std::cout << "Nie znaleziono miasta z CityB w dziecku: miasto: " << city << " na pozycji " << cityBIndex << "\n";
				childPrototype.push_back(city);
				taken.emplace_back(city);
				++sizeOfTaken;
			}
			else
				smthToTakeB = false;
		}
		for (auto city : childPrototype)
			std::cout << city << "->";
		std::cout << "\n";
	}

	Chromosome genericChromosome(numberOfCities - 1, instance_.startingCity);
	std::sort(taken.begin(), taken.end());

	for (unsigned int i = 0, j = 0; (i < numberOfCities - 1) && (j < taken.size()); i++)
	{
		if (genericChromosome[i] < taken[j])
			notTaken.emplace_back(genericChromosome[j]);
		else if (genericChromosome[i] == taken[j])
			++j;
	}

	std::random_shuffle(notTaken.begin(), notTaken.end());

	int i = 0;
	for (auto city : childPrototype)
		child[i++] = city;

	std::cout << "\nCHILD:\n";
	for (auto city : child)
		std::cout << city << "->";
	std::cout << "\nTAKEN:\n";
	for (auto city : taken)
		std::cout << city << "->";
	std::cout << "\nNOTTAKEN\n";
	for (auto city : notTaken)
		std::cout << city << "->";

	for (unsigned int i = 0; i < notTaken.size(); i++)
		child[taken.size() + i] = notTaken[i];

	std::cout << "ParentA:\n";
	for (auto city : parentA)
		std::cout << city << "->";
	std::cout << "\nfitness = " << parentA.fitness << "\n\n";

	std::cout << "ParentB:\n";
	for (auto city : parentB)
		std::cout << city << "->";
	std::cout << "\nfitness = " << parentB.fitness << "\n\n";

	std::cout << "Child:\n";
	for (auto city : child)
		std::cout << city << "->";
	updateFitness(child);
	std::cout << "\nfitness = " << child.fitness << "\n\n";
	
	return child;
}

void GeneticAlgorithm::setAttributes(unsigned int populationSize)
{
	populationSize_ = populationSize;
}

unsigned long long GeneticAlgorithm::sort()
{
	std::sort(population.begin(), population.end(), [](Chromosome& chromosomeA, Chromosome& chromosomeB)
	{
		return chromosomeA.fitness < chromosomeB.fitness;
	});

	return population[0].fitness;
}

auto GeneticAlgorithm::solve() -> Solution
{
	return Solution();
}

void GeneticAlgorithm::print()
{
	sort();
	for (auto& chromosome : population)
	{
		std::cout << "################################\n";
		for (auto city : chromosome)
			std::cout << city << "->";
		std::cout << "\nfitness = " << chromosome.fitness << "\n\n";
	}
	
	for (auto& chromosome : population)
	{
		optMethod(chromosome);
	}
	sort();

	std::cout << "\n################################\nAFTER IMPROVEMENT\n################################\n" << "\n";
	for (auto& chromosome : population)
	{
		std::cout << "################################\n";
		for (auto city : chromosome)
			std::cout << city << "->";
		std::cout << "\nfitness = " << chromosome.fitness << "\n\n";
	}

	for (int i = 0; i < populationSize_; i += 2)
	{
		crossover(population[i], population[i + 1]);
	}
}