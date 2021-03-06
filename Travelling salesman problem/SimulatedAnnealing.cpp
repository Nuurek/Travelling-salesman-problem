#include "SimulatedAnnealing.h"

/*
 * SOURCES: https://tdb0.wordpress.com/2010/12/03/symulowane-wyzarzanie/
 *          http://codecapsule.com/2010/04/06/simulated-annealing-traveling-salesman/
 *          http://www.technical-recipes.com/2012/c-implementation-of-hill-climbing-and-simulated-annealing-applied-to-travelling-salesman-problems/
 *          http://www.theprojectspot.com/tutorial-post/simulated-annealing-algorithm-for-beginners/6
 */

#define calcDistance(path)  calculateDistance(std::make_shared<std::vector<unsigned int>>(path))

double SimulatedAnnealing::P(long long int deltaDistance) {
    return std::exp((-deltaDistance) / T);
}

Solution SimulatedAnnealing::solve() {
    unsigned int numberOfCities = instance_.getNumberOfCities();
    std::vector<unsigned int> path = firstPathPermutation();

    auto engine = std::default_random_engine{static_cast<unsigned long>(std::chrono::system_clock::now().time_since_epoch().count()) };

    std::uniform_int_distribution<unsigned int> distribution(1, numberOfCities - 1);
    std::uniform_real_distribution<double> distribution01(0, 1);

    std::shuffle(path.begin() + 1, path.end() - 1, engine);
    unsigned long long distance = calcDistance(path);
    bestSolution_ = Solution(distance, path);

    unsigned int index1;
    unsigned int index2;

    while (T > Tmin)
    {
        do  // Pick up two random indexes
        {
            index1 = distribution(engine);
            index2 = distribution(engine);
        } while (index1 == index2);
        std::swap(path[index1], path[index2]);  // Create a new path by swapping two random elements
        distance = calcDistance(path);          // Calculate the distance of new path
        long long int deltaDistance = distance - bestSolution_.first;
        double distribution_randnumber = distribution01(engine);
        if ((deltaDistance < 0) || (P(deltaDistance) > distribution_randnumber)) {
            bestSolution_ = Solution(distance, path);  // The new path is shorter or temperature is high enough to risk
        }
        else {
            path = bestSolution_.second;
        }
        T *= coolingTempo;  // Decrease the temperature
    }

    return bestSolution_;
}
