#include "FuzzyOperations.h"

double FuzzyOperations::FuzzyAND(double t_A, double t_B)
{
	return std::min(t_A, t_B);
}

double FuzzyOperations::FuzzyOR(double t_A, double t_B)
{
	return std::max(t_A, t_B);
}

double FuzzyOperations::FuzzyNOT(double t_A)
{
	return 1.0 - t_A;
}
