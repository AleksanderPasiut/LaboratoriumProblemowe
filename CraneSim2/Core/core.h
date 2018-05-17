#pragma once

#include <Windows.h>
#include <string>
#include <random>

#include "doubleVec.h"
#include "alglib\src\optimization.h"


class Core
{
private:
	double T;
	double dt;
	double x0[16];
	double Mx;
	double My;
	double m;
	double l;
	double bX;
	double bY;
	double g;
	double rho;

	Vec time;
	Vec x[16];
	Vec u[2];

	double measId;
	Vec meas_xM;
	Vec meas_yM;
	Vec meas_betaX;
	Vec meas_betaY;

private: // fragments
	double bx(const Vec& x);
	double by(const Vec& x);

	double Ax(const Vec& x, const Vec& u);
	double Ay(const Vec& x, const Vec& u);
	double B(const Vec& x, const Vec& u);
	double Cx(const Vec& x, const Vec& u);
	double Cy(const Vec& x, const Vec& u);

private: // derivatives
	double dbx(const Vec& x, int n);
	double dby(const Vec& x, int n);

	double dAx(const Vec& x, const Vec& u, int n);
	double dAy(const Vec& x, const Vec& u, int n);
	double dB(const Vec& x, const Vec& u, int n);
	double dCx(const Vec& x, const Vec& u, int n);
	double dCy(const Vec& x, const Vec& u, int n);

	double der(const Vec& x, const Vec& u, int n, int m);

private:
	void MObject(Vec& dx, const Vec& x, const Vec& u);
	void CObject(Vec& dx, const Vec& x, const Vec& u);
	void Controller(Vec& u, const Vec& x);

	void Object(Vec& dx, const Vec& x, const Vec& u);
	double Objective();

private:
	void Euler(Vec& dx, const Vec& x, const Vec& u);
	void RungeKutta4(Vec& dx, const Vec& x, const Vec& u);

private:
	void SingleSimulation();
	void OptimizationRan();
	void OptimizationBC();
	void OptimizationNS(double diffstep, double radius, alglib::ae_int_t maxits);
	friend void objectiveWrapper(const alglib::real_1d_array&, double&, void*);
	friend void objectiveWrapper(const alglib::real_1d_array&, alglib::real_1d_array&, void*);

public:
	void SetParam(int id, double value);
	void Simulate();

	size_t GetOutputLength(int id);
	double GetOutputX(int id, size_t index);
	double GetOutputY(int id, size_t index);
};
