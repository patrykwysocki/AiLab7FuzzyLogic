#include "FuzzyLogic.h"

double FuzzyLogic::FuzzyGrade(double t_value, double t_x0, double t_x1)
{
	double result = 0;
	double x = t_value;
	if (x <= t_x0)
	{
		result = 0;
	}
	else if (x > t_x1)
	{
		result = 1;
	}
	else
	{
		result = ((x - t_x0) / (t_x1 - t_x0));
	}
	return result;
}

double FuzzyLogic::FuzzyTriangle(double t_value, double t_x0, double t_x1, double t_x2)
{
	double result = 0;
	double x = t_value;
	if ((x <= t_x0) || (x >= t_x2))
	{
		result = 0;
	}
	else if (x==t_x1)
	{
		result = 1;
	}
	else if ((x < t_x1) && (x > t_x0))
	{
		result = ((x - t_x0) / (t_x1 - t_x0));
	}
	else
	{
		result = ((t_x2 - x) / (t_x2 - t_x1));
	}
	return result;
}

double FuzzyLogic::FuzzyTrapezoid(double t_value, double t_x0, double t_x1, double t_x2, double t_x3)
{
	double result = 0;
	double x = t_value;
	if ((x <= t_x0) || (x >= t_x3))
	{
		result = 0;
	}
	else if ((x <= t_x2) && (x >= t_x1))
	{
		result = 1;
	}
	else if ((x < t_x1) && (x > t_x0))
	{
		result = ((x - t_x0) / (t_x1 - t_x0));
	}
	else
	{
		result = ((t_x3 - x) / (t_x3 - t_x2));
	}
	return result;
}
