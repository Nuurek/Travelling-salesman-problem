#pragma once
#include "TSPSolver.h"
#include "BruteForce.h"
#include <climits>


class SimulatedAnnealing :
        public BruteForce
{

    double T = 10000.0;     // current temperature
    double Tmin = 0.00001;  // minimum temperature
    double coolingTempo = 0.9999;

    double P(long long int deltaDistance);

public:
    SimulatedAnnealing(ProblemInstance instance) : BruteForce(instance) { };
    Solution solve() override;
};



