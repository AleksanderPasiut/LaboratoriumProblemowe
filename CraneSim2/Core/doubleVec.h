#pragma once

#include <vector>

typedef std::vector<double> Vec;

namespace std
{
	vector<double>& operator+= (vector<double>&, const vector<double>&);
	vector<double>& operator-= (vector<double>&, const vector<double>&);
	vector<double>& operator*= (vector<double>&, const vector<double>&);
	vector<double>& operator/= (vector<double>&, const vector<double>&);

	vector<double>& operator+= (vector<double>&, double);
	vector<double>& operator-= (vector<double>&, double);
	vector<double>& operator*= (vector<double>&, double);
	vector<double>& operator/= (vector<double>&, double);
}