#include "identifier.h"

#include "chart.h"
#include "alglib\\src\\optimization.h"

typedef std::vector<double> Vec;
typedef std::vector<Vec> VecN;

// time vector and control trajectories creation (unused)
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
void MultiStep(Vec& u, const std::vector<double>& times, const std::vector<double>& vals, double dt)
{
	auto it = u.begin();
	double t = 0;

	double v = 0;
	for (size_t i = 0; i < times.size(); ++i)
	{
		for (; t < times[i]; t += dt)
		{
			*it = v;
			
			++it;
			if (it == u.end())
				return;
		}
		v = vals[i];
	}

	for (; it != u.end(); ++it)
		*it = *(vals.rbegin());
}

// simulation
void Simulate(VecN& x, const VecN& u, Params& params)
{
	Model model;
	model.Reset(params);

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

// output plotting
void Plot8(const Vec& t, const VecN& u, const VecN& x)
{
	std::string nameU[] = { "ux", "uy" };

	for (size_t i = 0; i < 2; ++i)
	{
		xChart xc(nameU[i], "t", nameU[i]);
		xc.AddLine(t.data(), u[i].data(), t.size());
		xc.Export("output\\" + nameU[i]);
	}

	std::string name[] = { "x", "y", "ax", "ay", "vx", "vy", "wx", "wy" };
	for (size_t i = 0; i < 8; ++i)
	{
		xChart xc(name[i], "t", name[i]);
		xc.AddLine(t.data(), x[i].data(), t.size());
		xc.Export("output\\" + name[i]);
	}
}
void Plot4(const Vec& t, const VecN& u, const VecN& x)
{
	std::string nameU[] = { "ux", "uy" };

	for (size_t i = 0; i < 2; ++i)
	{
		xChart xc(nameU[i], "t", nameU[i]);
		xc.AddLine(t.data(), u[i].data(), t.size());
		xc.Export("output\\" + nameU[i]);
	}

	std::string name[] = { "x", "y", "ax", "ay" };
	for (size_t i = 0; i < 4; ++i)
	{
		xChart xc(name[i], "t", name[i]);
		xc.AddLine(t.data(), x[i].data(), t.size());
		xc.Export("output\\" + name[i]);
	}
}
void Plot4C(const Vec& t, const VecN& u, const VecN& x, const VecN& s, const string& suffix)
{
	std::string nameU[] = { "ux", "uy" };

	for (size_t i = 0; i < 2; ++i)
	{
		xChart xc(nameU[i], "t", nameU[i]);
		xc.AddLine(t.data(), u[i].data(), t.size());
		xc.Export("output\\" + suffix + "_" + nameU[i]);
	}

	std::string name[] = { "x", "y", "ax", "ay" };
	for (size_t i = 0; i < 4; ++i)
	{
		xChart xc(name[i], "t", name[i]);
		xc.AddLine(t.data(), x[i].data(), t.size());
		xc.AddLine(t.data(), s[i].data(), t.size());
		xc.Export("output\\" + suffix + "_" + name[i]);
	}
}

// obtain reference time, control trajectory and state trajectory from specified file
void GetDataFromFile(Vec& t, VecN& u, VecN& x, const std::string& name)
{
	std::fstream file(name, std::fstream::in);
	if (!file)
		throw std::logic_error("Failed to open data file!");

	u.resize(2);
	x.resize(4);

	const size_t N = 8000;
	t.reserve(N);

	for (size_t i = 0; i < 2; ++i)
		u[i].reserve(N);
	
	for (size_t i = 0; i < 4; ++i)
		x[i].reserve(N);

	for (size_t i = 0; i < 8000; ++i)
	{
		double v;
		file >> v;
		if (file.eof())
			break;

		t.push_back(v);

		for (size_t i = 0; i < 2; ++i)
		{
			file >> v;
			u[i].push_back(v);
		}

		for (size_t i = 0; i < 2; ++i)
		{
			file >> v;
			x[i].push_back(v);
		}

		// beta -> alpha angles recalculation
		double betaX, betaY;
		file >> betaX;
		file >> betaY;
		x[2].push_back(asin(cos(betaY) * sin(betaX)));
		x[3].push_back(betaY);

		file >> v;
	}

	double alphaXbias = x[2][0];
	double alphaYbias = x[3][0];
	for (size_t i = 0; i < x[0].size(); ++i)
	{
		x[2][i] -= alphaXbias;
		x[3][i] -= alphaYbias;
	}

	file.close();
}

// optimization 
using namespace alglib;
struct OuterData
{
	const Vec& t;	
	const VecN& u;
	const VecN& x;
};

void Phi(const real_1d_array &x, real_1d_array& phi, void* ptr)
{
	try
	{
		OuterData& data = *reinterpret_cast<OuterData*>(ptr);

		Params params;
		params.FromRealArray(x);
		params.dt = data.t[1] - data.t[0];
		params.g = 9.81;
		params.solverType = Params::RUNGE_KUTTA_4;

		VecN s;
		Simulate(s, data.u, params);

		size_t N = data.x[0].size();
		for (size_t j = 0; j < 3; ++j)
			for (size_t i = 0; i < N; ++i)
			{
				if (abs(data.x[j][i]) > 0.000001)
				{
					double absE = s[j][i] - data.x[j][i];
					double relE = absE / data.x[j][i];
					phi[i + j * N] = relE;
				}
				else phi[i + j * N] = 0;
			}
	}
	catch (std::exception& e)
	{
		//MessageBoxA(0, e.what(), 0, 0);
	}
}
void Phi(const real_1d_array& x, double& func, void* ptr)
{
	try
	{
		func = 0;

		OuterData& data = *reinterpret_cast<OuterData*>(ptr);

		Params params;
		params.FromRealArray(x);
		params.dt = data.t[1] - data.t[0];
		params.g = 9.81;
		params.solverType = Params::RUNGE_KUTTA_4;

		VecN s;
		Simulate(s, data.u, params);

		size_t N = data.x[0].size();
		for (size_t j = 0; j < 4; ++j)
			for (size_t i = 0; i < N; ++i)
			{
				double absE = s[j][i] - data.x[j][i];
				func += absE * absE;// * ((j < 2) ? 1.0 : 2.0);
			}
	}
	catch (std::exception& e)
	{
		func = 1000;
		//MessageBoxA(0, e.what(), 0, 0);
	}
}

void Optimize(Params& params, const Vec& t, const VecN& u, const VecN& x, fstream& results)
{
	OuterData data = { t, u, x };

	real_1d_array params0;
	params0.setlength(18);
	params.ToRealArray(params0);
		
	minbcstate state;
	//real_1d_array bndl = "[0.01, 0.0000001, 0.0000001, 0.0000001, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]";
	real_1d_array bndl = "[0.001, 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]";
	real_1d_array bndu = "[9.0, 10.0, 10.0, 10.0, 20, 0.0, 20, 0.0, 1000.0, 1000.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]";

	double epsg = 0;//0.00000000001;
	double epsf = 0;
	double epsx = 0;
	ae_int_t maxits = 200;
	double diffstep = 1.0e-6;
	
	minbccreatef(params0, diffstep, state);
	minbcsetbc(state, bndl, bndu);
	minbcsetcond(state, epsg, epsf, epsx, maxits);
	minbcoptimize(state, Phi, 0, &data);

	double value;
	Phi(params0, value, &data);

	minbcreport rep;
	minbcresults(state, params0, rep);
	
	params.FromRealArray(params0);

	string delim = "; ";
	results << value << delim;
	results << rep.iterationscount << delim;
	results << rep.terminationtype << delim;
	results << params.l << delim;
	results << params.m << delim;
	results << params.mF << delim;
	results << params.mC << delim;
	results << params.bX[0] << delim;
	results << params.bX[1] << delim;
	results << params.bY[0] << delim;
	results << params.bY[1] << delim;
	results << params.auxX << delim;
	results << params.auxY << delim;
	results << params.x0 << delim;
	results << params.y0 << delim;
	results << params.vx0 << delim;
	results << params.vy0 << delim;
	results << params.ax0 << delim;
	results << params.ay0 << delim;
	results << params.wx0 << delim;
	results << params.wy0 << delim << endl;

	/*string resp;
	resp += "value: " + to_string(value) + "\n";
	resp += "itcount: " + to_string(rep.iterationscount) + "\n";
	resp += "term. type: " + to_string(rep.terminationtype) + "\n";
	resp += "l: " + to_string(params.l) + "\n";
	resp += "m: " + to_string(params.m) + "\n";
	resp += "mF: " + to_string(params.mF) + "\n";
	resp += "mC: " + to_string(params.mC) + "\n";
	resp += "bX: " + to_string(params.bX[0]) + " " + to_string(params.bX[1]) + "\n";
	resp += "bY: " + to_string(params.bY[0]) + " " + to_string(params.bY[1]) + "\n";
	resp += "auxX: " + to_string(params.auxX) + "\n";
	resp += "auxY: " + to_string(params.auxY) + "\n";
	resp += "x: " + to_string(params.x0) + "\n";
	resp += "y: " + to_string(params.y0) + "\n";
	resp += "vx: " + to_string(params.vx0) + "\n";
	resp += "vy: " + to_string(params.vy0) + "\n";
	resp += "ax: " + to_string(params.ax0) + "\n";
	resp += "ay: " + to_string(params.ay0) + "\n";
	resp += "wx: " + to_string(params.wx0) + "\n";
	resp += "wy: " + to_string(params.wy0) + "\n";
	MessageBoxA(0, resp.c_str(), "resp", MB_OK);*/
}

// ---------------------------------------
void SingleFileAnalysis(const std::string& dir, const std::string& name, fstream& results)
{
	Vec t;
	VecN u, x;
	GetDataFromFile(t, u, x, dir + name + ".txt");

	Params params;
	params.Reset();
	params.m = 0.008;
	params.mF = 0.32;
	params.mC = 0.03;
	params.l = 0.63;
	params.bX = {4.9, 0};
	params.bY = {3.7, 0};
	params.auxX = 4;
	params.auxY = 5.9;
	params.dt = t[1] - t[0];
	/*params.x0 = x[0][0];
	params.y0 = x[1][0];
	params.vy0 = 0.05;
	params.ax0 = x[2][0];
	params.ay0 = x[3][0];*/

	results << name << "; ";
	Optimize(params, t, u, x, results);

	VecN s;
	try
	{
		Simulate(s, u, params);
	}
	catch (std::exception& e)
	{
		MessageBoxA(0, e.what(), 0, 0);
	}
	Plot4C(t, u, x, s, name);
}
void Identifier::Core()
{
	fstream results("output\\results.csv", fstream::out);

	std::string dir = "identification\\";
	std::string names[] = { "1", "1a", "2", "2a", "3", "3a", "4", "4_special", "4a", "5", "5a", "6", "6a" };//"out", "out2x", "out2xy" };

	for (size_t i = 0; i < sizeof(names); ++i)
		SingleFileAnalysis(dir, names[i], results);
	
	results.close();
}