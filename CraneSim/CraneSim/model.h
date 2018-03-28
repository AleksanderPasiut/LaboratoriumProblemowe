#pragma once

#include "include.h"
#include "params.h"

struct Model
{
	// sterowanie
	double ux;
	double uy;

	// zmienne stanu
	double carX;
	double carY;
	double alphaX;
	double alphaY;

	// pochodne zmiennych stanu
	double vcX;
	double vcY;
	double omegaX;
	double omegaY;

	// drugie pochodne zmiennych stanu
	double acX;
	double acY;
	double epsilonX;
	double epsilonY;

	// zmienne pomocnicze
	double sinAlphaX;
	double sinAlphaY;
	double cosAlpha;
	double sinAlpha;

public:
	void Add(const Model& arg, double factor);

private:
	double bx(const Params& params);
	double by(const Params& params);
	void ComputeCosSinAlpha(const Params& params);
	bool ChkEq(double A1, double A2, double B1, double B2, double C1, double C2, double epsilon);
	void ComputeLinearAccelerations(const Params& params);
	void ComputeAngleAccelerations(const Params& params);

public:
	void Step(const Params& params);

	void Reset(const Params& params);
};