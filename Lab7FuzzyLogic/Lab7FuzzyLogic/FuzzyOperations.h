#ifndef FUZZYOPERATIONS_H
#define FUZZYOPERATIONS_H
#include <algorithm>
class FuzzyOperations
{
public:
	static double FuzzyAND(double t_A, double t_B);
	static double FuzzyOR(double t_A, double t_B);
	static double FuzzyNOT(double t_A);
private:
};
 
#endif // !FUZZYOPERATIONS_H
