#pragma once
#include "ProblemInstance.h"
#include "ProblemGenerator.h"

int main()
{
	ProblemGenerator generator;
	ProblemInstance TSP = generator.generateProblem(10, 0, 50);
	TSP.print();
	system("PAUSE");
}