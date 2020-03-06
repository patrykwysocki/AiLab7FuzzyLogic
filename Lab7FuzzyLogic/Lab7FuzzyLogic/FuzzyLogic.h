#ifndef FUZZYLOGIC_H
#define FUZZYLOGIC_H

class FuzzyLogic
{
public:
	double FuzzyGrade(double t_value, double t_x0, double t_x1);
	double FuzzyTriangle(double t_value, double t_x0, double t_x1, double t_x2);
	double FuzzyTrapezoid(double t_value, double t_x0, double t_x1, double t_x2, double t_x3);
private:
};
#endif // !FUZZYLOGIC_H
