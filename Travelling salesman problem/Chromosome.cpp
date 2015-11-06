#include "Chromosome.h"

Chromosome::Chromosome() : fitness(0), mutated_(false), std::vector<unsigned int>()
{ }

Chromosome::Chromosome(unsigned int size) 
	: fitness(0), mutated_(false), std::vector<unsigned int>(size)
{ 
	for (unsigned int i = 0; i < size; i++)
	{
		at(i) = i;
	}
}

Chromosome Chromosome::complementChromosome(unsigned int numberOfCities) const
{
	Chromosome set(*this);
	Chromosome genericChromosome(numberOfCities);
	Chromosome complementChromosome;

	std::sort(set.begin(), set.end());
	for (unsigned int i = 0, j = 0; (i < numberOfCities - 1) && (j < set.size()); i++)
	{
		if (genericChromosome[i] < set[j])
			complementChromosome.emplace_back(genericChromosome[i]);
		else if (genericChromosome[i] == set[j])
			++j;
	}

	std::random_shuffle(complementChromosome.begin(), complementChromosome.end());

	return complementChromosome;
}

Chromosome Chromosome::emptyChromosome()
{
	Chromosome chromosome(0);
	chromosome.fitness = 0;
	--chromosome.fitness;
	return chromosome;
}

bool Chromosome::operator==(const Chromosome & rhs)
{
	Chromosome& lhs = *this;
	if (lhs.fitness != rhs.fitness)
		return false;
	else
	{
		unsigned int size = lhs.size();
		unsigned int zeroCityIndexlhs = std::find(lhs.begin(), lhs.end(), 0) - lhs.begin();
		unsigned int zeroCityIndexrhs = std::find(rhs.begin(), rhs.end(), 0) - rhs.begin();
		for (int i = 1; i < size; i++)
			if (lhs[(zeroCityIndexlhs + i) % size] != rhs[(zeroCityIndexrhs + i) % size])
				return false;
		return true;
	}
}

bool Chromosome::operator<(const Chromosome & rhs) const
{
	const Chromosome& lhs = *this;
	if (lhs.fitness < rhs.fitness)
		return true;
	else if (lhs.fitness > rhs.fitness)
		return false;
	else
	{
		
		unsigned int size = lhs.size();
		unsigned int zeroCityIndexlhs = std::find(lhs.begin(), lhs.end(), 0) - lhs.begin();
		unsigned int zeroCityIndexrhs = std::find(rhs.begin(), rhs.end(), 0) - rhs.begin();
		for (unsigned int i = 1; i < size; i++)
		{
			if (lhs[(zeroCityIndexlhs + i) % size] < rhs[(zeroCityIndexrhs + i) % size])
				return true;
			else if (lhs[(zeroCityIndexlhs + i) % size] == rhs[(zeroCityIndexrhs + i) % size])
				continue;
			else
				return false;
		}
		return false;
	}
}

void Chromosome::print() const
{
	if (size() > 0)
	{
		for (unsigned int i = 0; i < size() - 1; i++)
			std::cout << at(i) << "->";

		std::cout << at(size() - 1);
		std::cout << "\nfitness = " << fitness << (mutated_ ? "MUTATED" : "") << "\n";
	}
}