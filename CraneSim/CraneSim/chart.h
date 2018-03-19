#pragma once

#include "include.h"
using namespace std;

#include "ChartDirector\\include\\chartdir.h"
#pragma comment(lib,"ChartDirector\\lib64\\chartdir60.lib")

class xChart
{
private:
	XYChart core;

public:
	xChart(string title, string xlabel, string ylabel);

	void AddLine(const double* x, const double* y, size_t size, int color = -1);
	void AddScatter(const double* x, const double* y, size_t size);
	void AutoAdjustAxes();
	void AdjustAxes(double xMin, double xMax, double yMin, double yMax);

	void Export(string name);
};

class xChart2
{
private:
	ThreeDScatterChart core;

public:
	xChart2(string title, string xlabel, string ylabel, string zlabel);

	void SetData(const double* x, const double* y, const double* z, size_t size);

	void Export(string name);
};

class xChart3
{
private:
	XYChart core;
	ColorAxis* cAxis;

public:
	xChart3(string title, string xlabel, string ylabel);

	void SetData(const double* x, const double* y, const double* z, size_t size);
	void SetLogScale(double bottom, double top, double tick);
	void Export(string name);
};

class xChart4
{
private:
	SurfaceChart core;

public:
	xChart4(string title, string xlabel, string ylabel, string zlabel);

	void SetData(const double* x, const double* y, const double* z, size_t size);
	void LogScale(bool mode);

	void Export(string name);
};

class Histogram
{
private:
	XYChart core;

public:
	Histogram(string title, string xlabel, string ylabel);

	void SetData(const double* x, size_t size, double xMin, double xMax, size_t barCount);

	void Export(string name);
};