#include "ProblemInstance.h"

ProblemInstance::ProblemInstance() : numberOfCities_(0), distances_(0), startingCity(0)
{

}

ProblemInstance::ProblemInstance(unsigned int numberOfCities) :
	numberOfCities_(numberOfCities), distances_(numberOfCities), startingCity(0)
{

}

ProblemInstance::ProblemInstance(std::vector<std::pair<double, double>> vectorOfCities) :
	numberOfCities_(vectorOfCities.size()), distances_(vectorOfCities.size()), startingCity(0)
{
	for (unsigned int cityA = 0; cityA < numberOfCities_; cityA++)
		for (unsigned cityB = cityA + 1; cityB < numberOfCities_; cityB++)
		{
			double deltaX = vectorOfCities[cityA].first - vectorOfCities[cityB].first;
			double deltaY = vectorOfCities[cityA].second - vectorOfCities[cityB].second;
			deltaX = deltaX * deltaX;
			deltaY = deltaY * deltaY;
			distances_(cityB, cityA) = static_cast<unsigned int>(std::move(std::sqrt(deltaX + deltaY)));
		}
}

unsigned int& ProblemInstance::operator()(unsigned int start, unsigned int destination)
{
	return distances_(start, destination);
}

unsigned int ProblemInstance::operator()(unsigned int start, unsigned int destination) const
{
	return distances_(start, destination);
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