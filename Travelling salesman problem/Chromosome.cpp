#include "Chromosome.h"


Chromosome::Chromosome(unsigned int size) 
	: fitness(0), std::vector<unsigned int>(size)
{
}


Chromosome::Chromosome(unsigned int size, unsigned int startingCity) 
	: fitness(0), std::vector<unsigned int>(size)
{
	for (unsigned int i = 0, j = 0; i < size; i++)
	{
		if (j == startingCity)
			++j;
		at(i) = j++;
	}
}
