#include "Chromosome.h"


Chromosome::Chromosome(unsigned int size) 
	: fitness(0), std::vector<unsigned int>(size)
{
}
