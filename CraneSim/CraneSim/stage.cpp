#include "stage.h"

void Stage::Euler(double dt)
{
	model.Step(params);

	model.vcX += model.acX * dt;
	model.vcY += model.acY * dt;
	model.omegaX += model.epsilonX * dt;
	model.omegaY += model.epsilonY * dt;

	model.carX += model.vcX * dt;
	model.carY += model.vcY * dt;
	model.alphaX += model.omegaX * dt;
	model.alphaY += model.omegaY * dt;
}
void Stage::RungeKutta(double dt)
{
	Model k1 = model;
	k1.Step(params);

	Model k2 = model;
	k2.Add(k1, 0.5);
	k2.Step(params);

	Model k3 = model;
	k3.Add(k2, 0.5);
	k3.Step(params);

	Model k4 = model;
	k4.Add(k3, 1.0);
	k4.Step(params);

	model.carX += (k1.vcX/6 + k2.vcX/3 + k3.vcX/3 + k4.vcX/6) * dt;
	model.carY += (k1.vcY/6 + k2.vcY/3 + k3.vcY/3 + k4.vcY/6) * dt;
	model.alphaX += (k1.omegaX/6 + k2.omegaX/3 + k3.omegaX/3 + k4.omegaX/6) * dt;
	model.alphaY += (k1.omegaY/6 + k2.omegaY/3 + k3.omegaY/3 + k4.omegaY/6) * dt;

	model.vcX += (k1.acX/6 + k2.acX/3 + k3.acX/3 + k4.acX/6) * dt;
	model.vcY += (k1.acY/6 + k2.acY/3 + k3.acY/3 + k4.acY/6) * dt;
	model.omegaX += (k1.epsilonX/6 + k2.epsilonX/3 + k3.epsilonX/3 + k4.epsilonX/6) * dt;
	model.omegaY += (k1.epsilonY/6 + k2.epsilonY/3 + k3.epsilonY/3 + k4.epsilonY/6) * dt;
}
void Stage::CheckErrs()
{
	if (model.alphaX > 1.57)
		throw std::logic_error("Odchylenie alphaX przekroczy³o wartoœæ pi/2.");
	if (model.alphaX < -1.57)
		throw std::logic_error("Odchylenie alphaX przekroczy³o wartoœæ -pi/2.");
	if (model.alphaY > 1.57)
		throw std::logic_error("Odchylenie alphaY przekroczy³o wartoœæ pi/2.");
	if (model.alphaY < -1.57)
		throw std::logic_error("Odchylenie alphaY przekroczy³o wartoœæ -pi/2.");
}
void Stage::Action(double dt)
{
	switch (params.solverType)
	{
		case Params::EULER: Euler(dt); break;
		case Params::RUNGE_KUTTA_4: RungeKutta(dt); break;
	}

	CheckErrs();

	fence.SetPos(static_cast<float>(model.carY));
	carriage.SetPos(static_cast<float>(model.carX), static_cast<float>(model.carY));
	mass.SetPos(static_cast<float>(model.carX), static_cast<float>(model.carY), static_cast<float>(model.alphaX), static_cast<float>(model.alphaY), static_cast<float>(params.l));
}

Stage::Stage()
{
	params.Reset();
	model.Reset();
}

void Stage::Control(double ux, double uy, double u1, double u2)
{
	model.ux = ux;
	model.uy = uy;
}
void Stage::Render(CustomScene& scene, Shapes& shapes, Materials& materials) const
{
	frame.Render(scene, shapes, materials);
	fence.Render(scene, shapes, materials);
	carriage.Render(scene, shapes, materials);
	mass.Render(scene, shapes, materials);
}

void Stage::SetControlsWindow(HWND hwnd)
{
	controlsWindow = hwnd;
}
void Stage::StartAction()
{
	SetTimer(controlsWindow, reinterpret_cast<UINT_PTR>(this), 10, &Stage::ActionTimer);
}
void Stage::StopAction()
{
	KillTimer(controlsWindow, reinterpret_cast<UINT_PTR>(this));
}
void CALLBACK Stage::ActionTimer(HWND hwnd, UINT uMsg, UINT_PTR idParam, DWORD dwTime)
{
	Stage* stage = reinterpret_cast<Stage*>(idParam);

	try
	{
		//for (int i = 0; i < 100; ++i)
		stage->Action(0.01);	
		PostMessage(hwnd, SIMM_STEP, 0, 0);
	}
	catch (std::exception& e)
	{
		stage->StopAction();
		MessageBoxA(0, e.what(), "Error!", MB_OK);
		stage->model.Reset();
		SendMessage(hwnd, SIMM_ERROR, 0, 0);
		stage->StartAction();
	}
}