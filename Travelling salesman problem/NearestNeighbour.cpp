#include "NearestNeighbour.h"


NearestNeighbour::NearestNeighbour(ProblemInstance instance) 
	: TSPSolver(instance) 
{
}

Solution NearestNeighbour::solve()
{
	unsigned int currentCity = instance_.startingCity;
	unsigned int citiesToVisit = instance_.getNumberOfCities() - 1;
	unsigned int distance, shortestDistance, nextCity;
	unsigned int numberOfCities = instance_.getNumberOfCities();
	
	unsigned long long fullPathDistance = 0;
	std::vector<unsigned int> path = { instance_.startingCity };

	isVisited = std::vector<bool>(numberOfCities, false);
	
	while (citiesToVisit--)
	{
		shortestDistance = UINT_MAX;
		for (int i = 0; i < numberOfCities; i++)
			if (i != currentCity && i != instance_.startingCity && !isVisited[i])
			{
				distance = instance_(currentCity, i);
				if (distance < shortestDistance)
				{
					nextCity = i;
					shortestDistance = distance;
				}
			}
		currentCity = nextCity;
		isVisited[currentCity] = true;
		fullPathDistance += shortestDistance;
		path.emplace_back(currentCity);
	}

	fullPathDistance += instance_(currentCity, instance_.startingCity);
	path.emplace_back(instance_.startingCity);

	return Solution(fullPathDistance, path);
}