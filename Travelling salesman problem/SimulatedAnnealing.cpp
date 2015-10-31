#include "SimulatedAnnealing.h"
#include <chrono>

#define calcDistance(path)  calculateDistance(std::make_shared<std::vector<unsigned int>>(path))

double SimulatedAnnealing::P(long long int deltaDistance) {
    return std::exp((-deltaDistance / T));
}

Solution SimulatedAnnealing::solve() {
    unsigned int numberOfCities = instance_.getNumberOfCities();
    std::vector<unsigned int> path = firstPathPermutation();

    auto engine = std::default_random_engine{std::time(nullptr)};
    std::uniform_int_distribution<unsigned int> distribution(1, numberOfCities - 1);
    std::uniform_int_distribution<unsigned int> distribution01(0, 1);

    std::shuffle(path.begin() + 1, path.end() - 1, engine);
    unsigned long long distance = calcDistance(path);
    bestSolution_ = Solution(distance, path);

    while (T > Tmin)
    {
        unsigned int index1;
        unsigned int index2;
        do  // Pick up two random indexes
        {
            index1 = distribution(engine);
            index2 = distribution(engine);
        } while (index1 == index2);
        std::swap(path[index1], path[index2]);  // Create a new path by swapping two random elements
        distance = calcDistance(path);          // Calculate the distance of new path
        long long int deltaDistance = distance - bestSolution_.first;
        if ((deltaDistance < 0) || (P(deltaDistance) > distribution01(engine)))
            bestSolution_ = Solution(distance, path);  // The new path is shorter or temperature is high enough to risk
        T *= coolingTempo;  // Decrease the temperature
    }

    return bestSolution_;
}
