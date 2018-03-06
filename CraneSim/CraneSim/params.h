#pragma once

struct Params
{
	// masy i d�ugo��
	double l;
	double m;
	double mF;
	double mC;

	// przyspieszenie ziemskie
	double g;

	// wsp�czynniki t�umienia
	double bX;
	double bY;

	// rodzaj solvera
	enum SolverType
	{
		EULER,
		RUNGE_KUTTA_4
	};
	SolverType solverType;

	void Reset()
	{
		m = 0.5;
		mF = 3;
		mC = 1;
		l = 0.7;
		g = 9.81;
		bX = 10;
		bY = 20;
	}
};