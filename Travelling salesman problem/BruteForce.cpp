#include "BruteForce.h"

BruteForce::BruteForce(ProblemInstance instance) :
TSPSolver(instance),
bestSolution_(Solution(ULLONG_MAX, std::vector<unsigned int>(instance.getNumberOfCities())))
{
}

std::vector<unsigned int> BruteForce::firstPathPermutation()
{
	unsigned int numberOfCities = instance_.getNumberOfCities();
	std::vector<unsigned int> path(numberOfCities + 1);

	path[0] = path[numberOfCities] = instance_.startingCity;
	for (unsigned int i = 1, j = 0; i < numberOfCities; i++)
	{
		if (j == instance_.startingCity)
			++j;
		path[i] = j++;
	}

	return path;
}

Solution BruteForce::solve()
{
	unsigned int numberOfCities = instance_.getNumberOfCities();
	
	std::vector<unsigned int> path = firstPathPermutation();

	do
	{
		unsigned long long distance = calculateDistance(std::make_shared<std::vector<unsigned int>>(path));
		if (distance < bestSolution_.first)
			bestSolution_ = std::make_pair(distance, path);
	} while (std::next_permutation(path.begin() + 1, path.end() - 1));
	
	std::cout << bestSolution_.first << "\n";

	return bestSolution_;
}
