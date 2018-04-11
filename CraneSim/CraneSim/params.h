#pragma once

#include <vector>
#include "alglib\\src\\optimization.h"

struct Params
{
	// masy i d³ugoœæ
	double l;
	double m;
	double mF;
	double mC;

	// przyspieszenie ziemskie
	double g;

	// wspó³czynniki t³umienia
	std::vector<double> bX;
	std::vector<double> bY;

	// wspó³czynniki dodatkowe
	double auxX;
	double auxY;

	// warunki pocz¹tkowe
	double x0;
	double y0;

	double vx0;
	double vy0;

	double ax0;
	double ay0;

	double wx0;
	double wy0;

	// rodzaj solvera
	enum SolverType
	{
		EULER = 0,
		RUNGE_KUTTA_4 = 1
	};
	SolverType solverType;
	double dt;

	void Reset()
	{
		m = 1.5;
		mF = 3;
		mC = 1;
		l = 0.7;
		g = 9.81;
		bX = {10, 0, 0};
		bY = {20, 0, 0};
		dt = 0.0001;
		solverType = RUNGE_KUTTA_4;

		auxX = 1.0;
		auxY = 1.0;

		x0 = 0;
		y0 = 0;

		vx0 = 0;
		vy0 = 0;

		ax0 = 0;
		ay0 = 0;

		wx0 = 0;
		wy0 = 0;
	}

	void FromRealArray(const alglib::real_1d_array& x)
	{
		int i = 0;
		l = x[i++];
		m = x[i++];
		mF = x[i++];
		mC = x[i++];
		bX = { x[i++], x[i++] };
		bY = { x[i++], x[i++] };
		auxX = x[i++];
		auxY = x[i++];
		x0 = x[i++];
		y0 = x[i++];
		vx0 = x[i++];
		vy0 = x[i++];
		ax0 = x[i++];
		ay0 = x[i++];
		wx0 = x[i++];
		wy0 = x[i++];
	}
	void ToRealArray(alglib::real_1d_array& x)
	{
		int i = 0;
		x[i++] = l;
		x[i++] = m;
		x[i++] = mF;
		x[i++] = mC;
		x[i++] = bX[0];
		x[i++] = bX[1];
		x[i++] = bY[0];
		x[i++] = bY[1];
		x[i++] = auxX;
		x[i++] = auxY;
		x[i++] = x0;
		x[i++] = y0;
		x[i++] = vx0;
		x[i++] = vy0;
		x[i++] = ax0;
		x[i++] = ay0;
		x[i++] = wx0;
		x[i++] = wy0;
	}
};