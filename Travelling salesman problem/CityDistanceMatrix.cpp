#include "CityDistanceMatrix.h"


CityDistanceMatrix::CityDistanceMatrix(unsigned int numberOfCities)
{
	vectorOfDistances_.resize((numberOfCities * (numberOfCities - 1)) / 2);
}

unsigned int& CityDistanceMatrix::operator()(unsigned int start, unsigned int destination)
{
	if (destination > start)
		std::swap(start, destination);
	return vectorOfDistances_[(start * (start - 1)) / 2 + destination];
}

unsigned int CityDistanceMatrix::operator()(unsigned int start, unsigned int destination) const
{
	if (destination > start)
		std::swap(start, destination);
	return vectorOfDistances_[(start * (start - 1)) / 2 + destination];
}