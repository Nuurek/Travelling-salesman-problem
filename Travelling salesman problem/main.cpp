#pragma once
#include "ProblemInstantion.h"
#include "ProblemGenerator.h"

int main()
{
	ProblemGenerator generator;
	ProblemInstantion TSP = generator.generateProblem(10, 0, 50);
	TSP.print();
	system("PAUSE");
}