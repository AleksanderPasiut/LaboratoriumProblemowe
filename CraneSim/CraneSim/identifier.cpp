#include "identifier.h"

#include "chart.h"
#include "alglib\\src\\optimization.h"

typedef std::vector<double> Vec;
typedef std::vector<Vec> VecN;

void TimeVector(Vec& t, double dt, double Tstart, double Tend)
{
	t.resize(static_cast<size_t>(ceil((Tend - Tstart) / dt)));

	t[0] = Tstart;
	auto it = t.begin();
	auto jt = t.begin()+1;
	for (; jt != t.end(); ++it, ++jt)
		(*jt) = (*it) + dt;
}
void Step(Vec& u, double val, double timeout, double dt)
{
	auto it = u.begin();
	for (double t = 0; t < timeout; t += dt, ++it)
		*it = 0;

	for (; it < u.end(); ++it)
		*it = val;
}
void Simulate(VecN& x, const VecN& u, Params& params)
{
	Model model;
	model.Reset();

	const Vec& UX = u[0];
	const Vec& UY = u[1];

	x.resize(8);
	for (auto ix = x.begin(); ix != x.end(); ++ix)
		ix->reserve(UX.size());

	Solver solver(model, params);
	for (size_t i = 0; i < UX.size(); ++i)
	{
		model.ux = UX[i];
		model.uy = UY[i];

		solver.Action();

		x[0].push_back(model.carX);
		x[1].push_back(model.carY);

		x[2].push_back(model.alphaX);
		x[3].push_back(model.alphaY);

		x[4].push_back(model.vcX);
		x[5].push_back(model.vcY);

		x[6].push_back(model.omegaX);
		x[7].push_back(model.omegaY);
	}
}
void Plot(const Vec& t, const VecN& x)
{
	std::string name[] = { "x", "y", "ax", "ay", "vx", "vy", "wx", "wy" };

	for (size_t i = 0; i < 8; ++i)
	{
		xChart xc(name[i], "t", name[i]);
		xc.AddLine(t.data(), x[i].data(), t.size());
		xc.Export("output\\" + name[i]);
	}
}

void Identifier::Core()
{
	Params params;
	params.Reset();
	params.dt = 0.01;

	Vec t;
	TimeVector(t, params.dt, 0, 10);

	VecN u(2);
	u[0].resize(t.size());
	u[1].resize(t.size());
	Step(u[0], 1.0, 1.0, params.dt);
	
	VecN x;
	Simulate(x, u, params);

	Plot(t, x);
}