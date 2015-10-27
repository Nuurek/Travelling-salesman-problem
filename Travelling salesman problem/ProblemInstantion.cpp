#include "ProblemInstantion.h"


ProblemInstantion::ProblemInstantion(unsigned int numberOfCities) :
numberOfCities_(numberOfCities), distances_(numberOfCities)
{

}

unsigned int& ProblemInstantion::operator()(unsigned int start, unsigned int destination)
{
	return distances_(start, destination);
}

unsigned int ProblemInstantion::operator()(unsigned int start, unsigned int destination) const
{
	return distances_(start, destination);
}

void ProblemInstantion::setStartingCity(unsigned int start)
{
	startingCity_ = start;
}

void ProblemInstantion::print()
{
	for (unsigned int row = 1; row < numberOfCities_; row++)
	{
		for (unsigned int column = 0; column < row; column++)
			std::cout << distances_(row, column) << " ";
		std::cout << "\n";
	}
}