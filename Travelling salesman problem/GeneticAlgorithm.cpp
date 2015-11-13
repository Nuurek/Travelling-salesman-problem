#include "GeneticAlgorithm.h"


GeneticAlgorithm::GeneticAlgorithm(ProblemInstance instance) 
	: TSPSolver(instance)
{
	randomEngine_.seed(static_cast<unsigned long>(std::chrono::system_clock::now().time_since_epoch().count()));
	//randomEngine_.seed(20);
}

GeneticAlgorithm::~GeneticAlgorithm()
{
}

void GeneticAlgorithm::initialize()
{
	unsigned int numberOfCities = instance_.getNumberOfCities();

	population = std::vector<Chromosome>(populationCap_, Chromosome(numberOfCities));
	for (auto& chromosome : population)
	{
		std::shuffle(chromosome.begin(), chromosome.end(), randomEngine_);
		updateFitness(chromosome);
	}
}

unsigned long long GeneticAlgorithm::updateFitness(Chromosome& chromosome)
{
	unsigned int numberOfCities = instance_.getNumberOfCities();

	chromosome.fitness = 0;
	for (unsigned int city = 0; city < numberOfCities - 1; city++)
		chromosome.fitness += instance_(chromosome[city], chromosome[city + 1]);
	chromosome.fitness += instance_(chromosome[0], chromosome[numberOfCities - 1]);

	return chromosome.fitness;
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
	unsigned int numberOfCities = instance_.getNumberOfCities();
	unsigned long long singleDifference = 0, difference = 0;
	unsigned int cityA, cityB;

	chromosome.mutated_ = true;

	while (improvementMade)
	{
		improvementMade = false;
		for (cityA = 0; cityA < numberOfCities - 1; cityA++)
		{
			for (cityB = cityA + 2; cityB < numberOfCities - 1; cityB++)
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
	Chromosome child(numberOfCities);
	Chromosome taken;
	unsigned int sizeOfTaken = 1;
	distribiution_ = std::uniform_int_distribution<unsigned int>(0, numberOfCities - 1);
	unsigned int firstCity;

	firstCity = distribiution_(randomEngine_);
	childPrototype.push_back(firstCity);
	taken.emplace_back(firstCity);

	cityAIndex = std::find(parentA.begin(), parentA.end(), firstCity) - parentA.begin();
	cityBIndex = std::find(parentB.begin(), parentB.end(), firstCity) - parentB.begin();
	while (smthToTakeA || smthToTakeB)
	{
		if (smthToTakeA)
		{
			--cityAIndex;
			if (cityAIndex == UINT32_MAX)
				cityAIndex = numberOfCities - 1;
			if (std::find(childPrototype.begin(), childPrototype.end(), parentA[cityAIndex]) == childPrototype.end())
			{
				unsigned int city = parentA[cityAIndex];
				childPrototype.push_front(city);
				taken.emplace_back(city);
				++sizeOfTaken;
			}
			else
				smthToTakeA = false;
		}
		if (smthToTakeB)
		{
			cityBIndex = (cityBIndex + 1) % (numberOfCities);
			if (std::find(childPrototype.begin(), childPrototype.end(), parentB[cityBIndex]) == childPrototype.end())
			{
				unsigned int city = parentB[cityBIndex];
				childPrototype.push_back(city);
				taken.emplace_back(city);
				++sizeOfTaken;
			}
			else
				smthToTakeB = false;
		}
	}

	Chromosome notTaken = taken.complementChromosome(numberOfCities);

	int i = 0;
	for (auto city : childPrototype)
		child[i++] = city;

	for (unsigned int i = 0; i < notTaken.size(); i++)
		child[taken.size() + i] = notTaken[i];

	return child;
}

unsigned int GeneticAlgorithm::eliminateDuplicates()
{
	unsigned int duplicatesCount = 0;

	for (unsigned int chromosome = 0; chromosome < populationCap_ - 1; chromosome++)
	{
		if (population[chromosome] == population[chromosome + 1])
		{
			population[chromosome] = Chromosome::emptyChromosome();
			++duplicatesCount;
		}
	}
	populationSize_ -= duplicatesCount;

	return populationSize_;
}

unsigned int GeneticAlgorithm::eliminateImpotents()
{
	unsigned int targetSize = static_cast<unsigned int>((1.0 - crossoverPercentage_) * static_cast<double>(populationCap_));
	
	if (((populationCap_ - populationSize_) % 2) == 1)
	{
		population[populationSize_ - 1] = Chromosome::emptyChromosome();
		--populationSize_;
	}
	if (targetSize >= populationSize_)
		return populationSize_;

	if (((populationCap_ - targetSize) % 2) == 1)
		++targetSize;
	for (unsigned int chromosome = targetSize; chromosome < populationSize_; chromosome++)
		population[chromosome] = Chromosome::emptyChromosome();
	populationSize_ = targetSize;

	return populationSize_;
}

void GeneticAlgorithm::recombine()
{
	unsigned int numberOfParents = populationSize_;
	if (numberOfParents == 0)
		return;
	for (unsigned chromosome = populationSize_; chromosome < populationCap_; chromosome++)
	{
		distribiution_ = std::uniform_int_distribution<unsigned int>(0, (numberOfParents * numberOfParents + numberOfParents) / 2 - 1);
		unsigned rand = distribiution_(randomEngine_);
		unsigned int parentA = numberOfParents - static_cast<unsigned int>((1.0 + sqrt(8 * rand + 1)) / 2);
		rand = distribiution_(randomEngine_);
		unsigned int parentB = numberOfParents - static_cast<unsigned int>((1.0 + sqrt(8 * rand + 1)) / 2);
		population[chromosome] = crossover(population[parentA], population[parentB]);
		updateFitness(population[chromosome]);
		++populationSize_;
	}
}

void GeneticAlgorithm::mutate()
{
	if (!population[0].mutated_)
		optMethod(population[0]);
	unsigned int numberOfMutations = static_cast<unsigned int>(mutationPercentage_ * static_cast<double>(populationCap_));
	distribiution_ = std::uniform_int_distribution<unsigned int>(1, populationCap_ - 1);
	while (numberOfMutations--)
	{
		unsigned int rand = distribiution_(randomEngine_);
		if (!population[rand].mutated_)
			optMethod(population[rand]);
	}
}

void GeneticAlgorithm::setAttributes(unsigned int populationCap, double crossoverPercentage, double mutationPercentage)
{
	populationCap_ = populationSize_ = populationCap;
	crossoverPercentage_ = crossoverPercentage;
	mutationPercentage_ = mutationPercentage;
}

void GeneticAlgorithm::setRestrictions(unsigned int epochs, std::chrono::seconds time)
{
	maxEpochs_ = epochs;
	maxTime_ = time;
}

unsigned long long GeneticAlgorithm::sort()
{
	std::sort(population.begin(), population.end(), [](const Chromosome& chromosomeA, const Chromosome& chromosomeB)
	{
		return chromosomeA < chromosomeB;
	});

	return population[0].fitness;
}

void GeneticAlgorithm::epoch()
{
	sort();
	eliminateDuplicates();
	sort();
	//std::cout << "DUPLICATES ELIMINATED\n";
	//print();
	eliminateImpotents();
	//std::cout << "IMPOTENTS ELIMINATED\n";
	//print();
	recombine();
	//std::cout << "AFTER RECOMBINATION\n";
	//print();
	mutate();
	sort();
	//std::cout << "AFTER MUTATION\n";
	//print();
}

Solution GeneticAlgorithm::solve()
{
	initialize();
	
	unsigned int epochs = maxEpochs_;
	auto start = std::chrono::steady_clock::now();


	while (epochs-- && std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start) < maxTime_)
		epoch();

	unsigned int size = instance_.getNumberOfCities();
	unsigned int zeroCityIndex = std::find(population[0].begin(), population[0].end(), instance_.startingCity) - population[0].begin();
	Chromosome elite(size + 1);
	for (unsigned int city = 0; city < size; city++)
		elite[city] = population[0][(zeroCityIndex + city) % size];
	elite[size] = instance_.startingCity;
	elite.fitness = population[0].fitness;

	return Solution(elite.fitness, elite);
}

void GeneticAlgorithm::print()
{
	for (auto& chromosome : population)
	{
		chromosome.print();
	}
	std::cout << "\n\n";
}