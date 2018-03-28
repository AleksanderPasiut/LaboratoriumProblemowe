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
		l = x[0];
		m = x[1];
		mF = x[2];
		mC = x[3];
		bX = { x[4], x[5] };
		bY = { x[6], x[7] };
		x0 = x[8];
		y0 = x[9];
		vx0 = x[10];
		vy0 = x[11];
		ax0 = x[12];
		ay0 = x[13];
		wx0 = x[14];
		wy0 = x[15];
	}
	void ToRealArray(alglib::real_1d_array& x)
	{
		x[0] = l;
		x[1] = m;
		x[2] = mF;
		x[3] = mC;
		x[4] = bX[0];
		x[5] = bX[1];
		x[6] = bY[0];
		x[7] = bY[1];
		x[8] = x0;
		x[9] = y0;
		x[10] = vx0;
		x[11] = vy0;
		x[12] = ax0;
		x[13] = ay0;
		x[14] = wx0;
		x[15] = wy0;
	}
};