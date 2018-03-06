#pragma once

#include "params.h"
#include "model.h"

#include "frame.h"
#include "fence.h"
#include "carriage.h"
#include "mass.h"

class Stage
{
private:
	Frame frame;
	Fence fence;
	Carriage carriage;
	Mass mass;

private:
	Params params;
	Model model;
	
private:
	void Euler(double dt);
	void RungeKutta(double dt);
	void CheckErrs();
	void Action(double dt);

public:
	Stage();
	
private:
	HWND controlsWindow;

public:
	void Render(CustomScene& scene, Shapes& shapes, Materials& materials) const;
	void Control(double ux, double uy, double u1, double u2);

public:
	static const int SIMM_ERROR = 0x8001;
	static const int SIMM_STEP = 0x8002;

public:
	void SetControlsWindow(HWND hwnd);
	void StartAction();
	void StopAction();
	static void CALLBACK ActionTimer(HWND hwnd, UINT uMsg, UINT_PTR idParam, DWORD dwTime);
};