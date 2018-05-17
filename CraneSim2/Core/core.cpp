#include "core.h"

void Core::SetParam(int id, double value)
{
	switch (id)
	{
		case 0: T = value; break;
		case 1: dt = value; break;
		case 2: x0[0] = value; break;
		case 3: x0[1] = value; break;
		case 4: x0[2] = value; break;
		case 5: x0[3] = value; break;
		case 6: x0[4] = value; break;
		case 7: x0[5] = value; break;
		case 8: x0[6] = value; break;
		case 9: x0[7] = value; break;
		case 10: x0[8] = value; break;
		case 11: x0[9] = value; break;
		case 12: x0[10] = value; break;
		case 13: x0[11] = value; break;
		case 14: x0[12] = value; break;
		case 15: x0[13] = value; break;
		case 16: x0[14] = value; break;
		case 17: x0[15] = value; break;
		case 18: Mx = value; break;
		case 19: My = value; break;
		case 20: m = value; break;
		case 21: l = value; break;
		case 22: bX = value; break;
		case 23: bY = value; break;
		case 24: g = value; break;
		case 25: rho = value; break;
		case 26: measId = value; break;
	}
}

void Core::Euler(Vec& dx, const Vec& x, const Vec& u)
{
	Object(dx, x, u);
	dx *= dt;
}
void Core::RungeKutta4(Vec& dx, const Vec& x, const Vec& u)
{
	Vec k1(x.size()), k2(x.size()), k3(x.size());
	
	Object(k1, x, u);

	Vec arg = k1;
	arg *= 0.5 * dt;
	arg += x;
	Object(k2, arg, u);

	arg = k2;
	arg *= 0.5 * dt;
	arg += x;
	Object(k3, arg, u);

	arg = k3;
	arg *= 0.5 * dt;
	arg += x;
	Object(dx, arg, u);

	k1 *= 1.0/6.0;
	k2 *= 1.0/3.0;
	k3 *= 1.0/3.0;
	dx *= 1.0/6.0;
	dx += k1;
	dx += k2;
	dx += k3;

	dx *= dt;
}

void Core::Simulate()
{
	OptimizationRan();
	//OptimizationBC();
	//OptimizationNS(0.01, 1.0, 600);
	//OptimizationNS(0.01, 0.1, 200);
	SingleSimulation();
}

size_t Core::GetOutputLength(int id)
{
	if (id < 18)
		return time.size();
	else
		return 0;
}
double Core::GetOutputX(int id, size_t index)
{
	return time[index];
}
double Core::GetOutputY(int id, size_t index)
{
	switch (id)
	{
		case 0: return x[0][index];
		case 1: return x[1][index];
		case 2: return x[2][index];
		case 3: return x[3][index];
		case 4: return x[4][index];
		case 5: return x[5][index];
		case 6: return x[6][index];
		case 7: return x[7][index];
		case 8: return x[8][index];
		case 9: return x[9][index];
		case 10: return x[10][index];
		case 11: return x[11][index];
		case 12: return x[12][index];
		case 13: return x[13][index];
		case 14: return x[14][index];
		case 15: return x[15][index];
		case 16: return u[0][index];
		case 17: return u[1][index];
		case 18: return meas_xM[index];
		case 19: return meas_yM[index];
		case 20: return meas_betaX[index];
		case 21: return meas_betaY[index];
	}
	return NAN;
}