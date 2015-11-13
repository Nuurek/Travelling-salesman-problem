#pragma once
#include "TSPSolver.h"
#include "BruteForce.h"
#include <climits>
#include <chrono>
#include <random>
#include <iostream>
#include <iomanip>


class SimulatedAnnealing :
	public BruteForce
{

	double T;     // current temperature
    double Tmin;  // minimum temperature
    double coolingTempo;

    double P(long long int deltaDistance);

public:
    SimulatedAnnealing(ProblemInstance instance) : BruteForce(instance), T(10000.0), Tmin(0.00001), coolingTempo(0.9999) { };
    Solution solve() override;
	void setAttributes(double tempo = 0.9999, double Tstart = 10000.0, double Tminimum = 0.00001)
	{
		coolingTempo = tempo;
		T = Tstart;
		Tmin = Tminimum;
	}
};



