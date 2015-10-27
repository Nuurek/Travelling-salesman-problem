#include "ProblemInstance.h"

ProblemInstance::ProblemInstance() : numberOfCities_(0), distances_(0)
{

}

ProblemInstance::ProblemInstance(unsigned int numberOfCities) :
numberOfCities_(numberOfCities), distances_(numberOfCities)
{

}

unsigned int& ProblemInstance::operator()(unsigned int start, unsigned int destination)
{
	return distances_(start, destination);
}

unsigned int ProblemInstance::operator()(unsigned int start, unsigned int destination) const
{
	return distances_(start, destination);
}

void ProblemInstance::setStartingCity(unsigned int start)
{
	startingCity_ = start;
}

void ProblemInstance::print()
{
	for (unsigned int row = 1; row < numberOfCities_; row++)
	{
		for (unsigned int column = 0; column < row; column++)
			std::cout << distances_(row, column) << " ";
		std::cout << "\n";
	}
}