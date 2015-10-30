#include "GeneticAlgorithm.h"


GeneticAlgorithm::GeneticAlgorithm(ProblemInstance instance) 
	: TSPSolver(instance)
{
	randomEngine_.seed(static_cast<unsigned long>(std::chrono::system_clock::now().time_since_epoch().count()));
}


GeneticAlgorithm::~GeneticAlgorithm()
{
}

void GeneticAlgorithm::initialize()
{
	unsigned int numberOfCities = instance_.getNumberOfCities();

	population = std::vector<Chromosome>(populationSize_, Chromosome(numberOfCities));
	std::cout << "Population size: " << population.size() << "\n";
	for (auto& chromosome : population)
	{
		chromosome.resize(numberOfCities);
		for (unsigned int city = 0; city < numberOfCities; city++)
			chromosome[city] = city;
		std::shuffle(chromosome.begin(), chromosome.end(), randomEngine_);
	}
	updateFitnesses();
}

unsigned long long GeneticAlgorithm::updateFitnesses()
{
	unsigned int numberOfCities = instance_.getNumberOfCities();
	unsigned long long elite = ULLONG_MAX;
	
	for (auto& chromosome : population)
	{
		for (unsigned int city = 0; city < numberOfCities - 1; city++)
			chromosome.fitness += instance_(chromosome[city], chromosome[city + 1]);
		chromosome.fitness += instance_(numberOfCities - 1, 0);
		if (chromosome.fitness < elite)
			elite = chromosome.fitness;
	}

	return elite;
}

void GeneticAlgorithm::setAttributes(unsigned int populationSize)
{
	populationSize_ = populationSize;
}

auto GeneticAlgorithm::solve() -> Solution
{
	return Solution();
}

void GeneticAlgorithm::print()
{
	for (auto& chromosome : population)
	{
		for (auto city : chromosome)
			std::cout << city << "->";
		std::cout << "\nfitness = " << chromosome.fitness << "\n";
	}
}