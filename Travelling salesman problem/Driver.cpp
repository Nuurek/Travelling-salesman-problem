#include "Driver.h"



void Driver::loadProblemFromFile(std::string file)
{
	std::ifstream in(file);
	unsigned int distance, cityA = 0, cityB = 0, numberOfCities = 0;
	
	in >> numberOfCities;
	ProblemInstance newTSP(numberOfCities);

	while (in >> distance)
	{
		if (cityA == cityB)
		{
			++cityA;
			cityB = 0;
		}
		newTSP(cityA, cityB) = distance;
		++cityB;
	}
	delete TSP_;
	TSP_ = &newTSP;
}

void Driver::saveProblemToFile(std::string file)
{
	std::ofstream out(file);
	std::streambuf *coutbuf = std::cout.rdbuf();
	std::cout.rdbuf(out.rdbuf());

	std::cout << TSP_->getNumberOfCities() << "\n";
	TSP_->print();

	std::cout.rdbuf(coutbuf);
}

Driver::Driver() : TSP_(new ProblemInstance(0)), generator_()
{
}


Driver::~Driver()
{
}
