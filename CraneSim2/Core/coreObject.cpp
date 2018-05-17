#include "core.h"

double Core::bx(const Vec& x)
{
	return -bX * x[2];
}
double Core::by(const Vec& x)
{
	return -bY * x[3];
}

double Core::Ax(const Vec& x, const Vec& u)
{
	return l*l*Mx + m*x[4]*x[4];
}
double Core::Ay(const Vec& x, const Vec& u)
{
	return l*l*My + m*x[5]*x[5];
}
double Core::B(const Vec& x, const Vec& u)
{
	return m*x[4]*x[5];
}
double Core::Cx(const Vec& x, const Vec& u)
{
	return l*l*(u[0] + bx(x)) + m*g*x[4] * sqrt(l*l - x[4]*x[4] - x[5]*x[5]);
}
double Core::Cy(const Vec& x, const Vec& u)
{
	return l*l*(u[1] + by(x)) + m*g*x[5] * sqrt(l*l - x[4]*x[4] - x[5]*x[5]);
}

double Core::dbx(const Vec& x, int n)
{
	switch (n)
	{
		case 2: return -bX;
		default: return 0;
	}
}
double Core::dby(const Vec& x, int n)
{
	switch (n)
	{
		case 3: return -bY;
		default: return 0;
	}
}

double Core::dAx(const Vec& x, const Vec& u, int n)
{
	switch (n)
	{
		case 4: return 2*m*x[4];
		default: return 0;
	}
}
double Core::dAy(const Vec& x, const Vec& u, int n)
{
	switch (n)
	{
		case 5: return 2*m*x[5];
		default: return 0;
	}
}
double Core::dB(const Vec& x, const Vec& u, int n)
{
	switch (n)
	{
		case 4: return m*x[5];
		case 5: return m*x[4];
		default: return 0;
	}
}
double Core::dCx(const Vec& x, const Vec& u, int n)
{
	switch (n)
	{
		case 2: return l*l*dbx(x, n);
		case 4: 
			{
				double s = sqrt(l*l - x[4]*x[4] - x[5]*x[5]);
				return m*g*(s - x[4]*x[4] / s);
			}
		case 5: return -m*g*x[4]*x[5] / sqrt(l*l - x[4]*x[4] - x[5]*x[5]);
		default: return 0;
	}
}
double Core::dCy(const Vec& x, const Vec& u, int n)
{
	switch (n)
	{
		case 3: return l*l*dby(x, n);
		case 4: 
			{
				double s = sqrt(l*l - x[4]*x[4] - x[5]*x[5]);
				return m*g*(s - x[5]*x[5] / s);
			}
		case 5: return -m*g*x[4]*x[5] / sqrt(l*l - x[4]*x[4] - x[5]*x[5]);
		default: return 0;
	}
}

double Core::der(const Vec& x, const Vec& u, int n, int m)
{
	switch (m)
	{
		case 0: return n == 2 ? 1.0 : 0.0;
		case 1: return n == 3 ? 1.0 : 0.0;
		case 2:
		{
			double bracket1 = dCx(x, u, n)*Ay(x, u) + dAy(x, u, n)*Cx(x, u) - dB(x, u, n)*Cy(x, u) - dCy(x, u, n)*B(x, u);
			double bracket2 = dAx(x, u, n)*Ay(x, u) + dAy(x, u, n)*Ax(x, u) - 2*dB(x, u, n)*B(x, u);
			double AxAyB2 = Ax(x, u) * Ay(x, u) - B(x, u)*B(x, u);
			double CxAyBCy = Cx(x, u) * Ay(x, u) - B(x, u)*Cy(x, u);
			return (bracket1 - bracket2 * CxAyBCy / AxAyB2) / AxAyB2;
		}
		case 3:
		{
			double bracket1 = dCy(x, u, n)*Ax(x, u) + dAx(x, u, n)*Cy(x, u) - dB(x, u, n)*Cx(x, u) - dCx(x, u, n)*B(x, u);
			double bracket2 = dAx(x, u, n)*Ay(x, u) + dAy(x, u, n)*Ax(x, u) - 2*dB(x, u, n)*B(x, u);
			double AxAyB2 = Ax(x, u) * Ay(x, u) - B(x, u)*B(x, u);
			double CyAxBCx = Cy(x, u) * Ax(x, u) - B(x, u)*Cx(x, u);
			return (bracket1 - bracket2 * CyAxBCx / AxAyB2) / AxAyB2;
		}
		case 4: return n == 6 ? 1.0 : 0.0;
		case 5: return n == 7 ? 1.0 : 0.0;
		case 6: return (dbx(x, n) - (Mx + m)*der(x, u, n, 2))/m;
		case 7: return (dby(x, n) - (My + m)*der(x, u, n, 3))/m;
	}
	return NAN;
}

void Core::MObject(Vec& dx, const Vec& x, const Vec& u)
{
	dx[0] = x[2];
	dx[1] = x[3];

	double valAx = Ax(x, u);
	double valAy = Ay(x, u);
	double valB = B(x, u);
	double valCx = Cx(x, u);
	double valCy = Cy(x, u);

	double den = valAx * valAy - valB*valB;
	dx[2] = (valCx * valAy - valB * valCy) / den;
	dx[3] = (valCy * valAx - valB * valCx) / den;

	dx[4] = x[6];
	dx[5] = x[7];

	dx[6] = (u[0] + bx(x) - (Mx + m)*dx[2]) / m;
	dx[7] = (u[1] + by(x) - (Mx + m)*dx[3]) / m;
}
void Core::CObject(Vec& dx, const Vec& x, const Vec& u)
{
	for (int i = 0; i < 8; ++i)
	{
		dx[8+i] = 0;
		for (int j = 0; j < 8; ++j)
			dx[8+i] -= der(x, u, i, j) * x[8+j];
	}
}
void Core::Controller(Vec& u, const Vec& x)
{
	double factor = l*l / (Ax(x, u)*Ay(x, u) - pow(B(x, u), 2));
	double uFactor0 = factor * (Ay(x, u)*x[10] - B(x, u)*x[11]) + x[14] / m;
	double uFactor1 = factor * (Ax(x, u)*x[11] - B(x, u)*x[10]) + x[15] / m;

	u[0] = uFactor0 < 0 ? 1.0 : -1.0;
	u[1] = uFactor1 < 0 ? 1.0 : -1.0;
}

void Core::Object(Vec& dx, const Vec& x, const Vec& u)
{
	MObject(dx, x, u);
	CObject(dx, x, u);
}
double Core::Objective()
{
	/*double finalNorm = 0;
	for (int i = 0; i < 8; ++i)
		finalNorm += (*x[i].rbegin()) * (*x[i].rbegin());

	return finalNorm*rho + T;*/

	double finalNorm = 0;
	for (int i = 0; i < 8; ++i)
	{
		double xT = *x[i].rbegin();
		double psiT = *x[8+i].rbegin();
		finalNorm += (psiT - 2*rho*xT)*(psiT - 2*rho*xT);
	}
	return finalNorm;
}

void objectiveWrapper(const alglib::real_1d_array& x, double& out, void* ptr)
{
	Core* core = reinterpret_cast<Core*>(ptr);

	for (int i = 0; i < 8; ++i)
		core->x0[8+i] = x[i];

	core->T = x[8];

	core->SingleSimulation();
	out = core->Objective();
}
void objectiveWrapper(const alglib::real_1d_array& x, alglib::real_1d_array& out, void* ptr)
{
	Core* core = reinterpret_cast<Core*>(ptr);

	for (int i = 0; i < 8; ++i)
		core->x0[8+i] = x[i];

	core->T = x[8];

	core->SingleSimulation();
	out[0] = core->Objective();
}

void Core::SingleSimulation()
{
	size_t N = (T > 0) ? static_cast<size_t>(ceil(T / dt)) : 1;
	time.resize(N);
	
	// init history
	double t = dt;
	for (int i = 0; i < 16; ++i)
	{
		x[i].resize(N);
		x[i][0] = x0[i];
	}

	u[0].resize(N);
	u[1].resize(N);

	// init solver memory
	Vec xArg(16);
	for (int i = 0; i < 16; ++i)
		xArg[i] = x[i][0];
	Vec uArg = { u[0][0], u[1][0] };
	Vec dx(16, 0.0);

	for (size_t i = 1; i < N; ++i, t += dt)
	{		
		RungeKutta4(dx, xArg, uArg);
		xArg += dx;
		
		Controller(uArg, xArg);

		// save to memory
		time[i] = t;

		for (int j = 0; j < 16; ++j)
			x[j][i] = xArg[j];

		u[0][i] = uArg[0];
		u[1][i] = uArg[1];
	}
}
void Core::OptimizationRan()
{
	std::uniform_real_distribution<double> distPhi(-4.0, 4.0);
	std::uniform_real_distribution<double> distT(1.0, 15.0);
	std::default_random_engine gen = std::default_random_engine(GetTickCount());

	Vec best(9);
	double bestObjective = INFINITY;

	for (int i = 0; i < 2000; ++i)
	{
		for (int i = 0; i < 8; ++i)
			x0[8+i] = distPhi(gen);
		T = distT(gen);

		SingleSimulation();
		double objective = Objective();

		if (objective < bestObjective)
		{
			bestObjective = objective;

			for (int i = 0; i < 8; ++i)
				best[i] = x0[8+i];
			best[8] = T;
		}
	}

	for (int i = 0; i < 8; ++i)
			x0[8+i] = best[i];
	T = best[8];
}
void Core::OptimizationBC()
{
	using namespace alglib;
	
	real_1d_array x;
	x.setlength(9);
	for (int i = 0; i < 8; ++i)
		x[i] = x0[8+i];
	x[8] = T;

    double diffstep = 0.02;
    minbcstate state;
    minbccreatef(x, diffstep, state);

	real_1d_array bndl = "[-Inf, -Inf, -Inf, -Inf, -Inf, -Inf, -Inf, -Inf, 1]";
    real_1d_array bndu = "[+Inf, +Inf, +Inf, +Inf, +Inf, +Inf, +Inf, +Inf, +Inf]";
    minbcsetbc(state, bndl, bndu);

	double epsg = 0;
    double epsf = 0;
    double epsx = 0;
    ae_int_t maxits = 150;
    minbcsetcond(state, epsg, epsf, epsx, maxits);

    minbcoptimize(state, objectiveWrapper, 0, this);
	
	minbcreport rep;
    minbcresults(state, x, rep);

	std::string str;
	str += "termination type " + std::to_string(rep.terminationtype);
	str += "result " + state.x.tostring(3);
	str += "value " + std::to_string(state.f);
	MessageBoxA(0, str.c_str(), 0, 0);

	for (int i = 0; i < 8; ++i)
		x0[8+i] = state.x[i];
	T = state.x[8];
}
void Core::OptimizationNS(double diffstep, double radius, alglib::ae_int_t maxits)
{
	using namespace alglib;
	
	real_1d_array x;// = "[2.84, 0.287, 4.211, 0.303, 1.194, -1.112, 3.357, -0.204, 2.741]";
	x.setlength(9);
	for (int i = 0; i < 8; ++i)
		x[i] = x0[8+i];
	x[8] = T;

    minnsstate state;
    minnscreatef(x, diffstep, state);

	real_1d_array bndl = "[-Inf, -Inf, -Inf, -Inf, -Inf, -Inf, -Inf, -Inf, 1]";
    real_1d_array bndu = "[+Inf, +Inf, +Inf, +Inf, +Inf, +Inf, +Inf, +Inf, +Inf]";
    minnssetbc(state, bndl, bndu);
	
	double epsx = 0;
    minnssetcond(state, epsx, maxits);

	minnssetalgoags(state, radius, 0.0);

    minnsoptimize(state, objectiveWrapper, 0, this);
	
	minnsreport rep;
    minnsresults(state, x, rep);
	
	std::string str;
	str += "termination type " + std::to_string(rep.terminationtype);
	str += "result " + state.x.tostring(3);
	str += "value " + std::to_string(state.fi[0]);
	MessageBoxA(0, str.c_str(), 0, 0);

	for (int i = 0; i < 8; ++i)
		x0[8+i] = state.x[i];
	T = state.x[8];
}