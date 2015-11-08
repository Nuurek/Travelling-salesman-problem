#pragma once
#include "TSPSolver.h"
#include "BruteForce.h"
#include <climits>
#include <chrono>
#include <random>


class SimulatedAnnealing :
	public BruteForce
{

	double T;     // current temperature
    double Tmin;  // minimum temperature
    double coolingTempo;

    double P(long long int deltaDistance, double temp);

public:
    SimulatedAnnealing(ProblemInstance instance) : BruteForce(instance), T(10000.0), Tmin(0.0001), coolingTempo(0.99999) { };
    Solution solve() override;
	void setAttributes(double temp, double temp_min, double tempo)
	{
		T = temp;
		Tmin = temp_min;
		coolingTempo = tempo;
	}
};



