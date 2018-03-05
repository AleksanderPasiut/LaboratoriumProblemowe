#pragma once

#include "frame.h"
#include "fence.h"
#include "carriage.h"
#include "mass.h"

class Stage
{
private:
	HWND controlsWindow;

private:
	Frame frame;
	Fence fence;
	Carriage carriage;
	Mass mass;

private:
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

	// masy i d³ugoœæ
	double l;
	double m;
	double mF;
	double mC;

	// przyspieszenie ziemskie
	double g;

	// zmienne pomocnicze
	double sinAlphaX;
	double sinAlphaY;
	double cosAlpha;
	double sinAlpha;

	// wspó³czynniki t³umienia
	double bX;
	double bY;

public:
	Stage();
	void ResetPos();
	void Action(double dt);

	double bx(double v);
	double by(double v);
	void ComputeCosSinAlpha();
	void ComputeLinearAccelerations();
	void ComputeAngleAccelerations();
	void IntegrateAccelerations(double dt);
	void IntegrateVelocities(double dt);

	void Render(CustomScene& scene, Shapes& shapes, Materials& materials) const;
	void Control(double ux, double uy, double u1, double u2);

	void SetControlsWindow(HWND hwnd);
	void StartAction();
	void StopAction();
	static void CALLBACK ActionTimer(HWND hwnd, UINT uMsg, UINT_PTR idParam, DWORD dwTime);
};