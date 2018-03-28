#include "stage.h"

void Stage::Action()
{
	solver.Action();

	fence.SetPos(static_cast<float>(model.carX));
	carriage.SetPos(static_cast<float>(model.carY), static_cast<float>(model.carX));
	mass.SetPos(static_cast<float>(model.carY), static_cast<float>(model.carX), static_cast<float>(model.alphaY), static_cast<float>(model.alphaX), static_cast<float>(params.l));
}

Stage::Stage() : action(true), solver(model, params)
{
	params.Reset();
	model.Reset(params);
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
	mass.SetPos(0, 0, 0, 0, static_cast<float>(params.l));
	SetTimer(controlsWindow, reinterpret_cast<UINT_PTR>(this), 10, &Stage::ActionTimer);
	action = true;
}
void Stage::StopAction()
{
	KillTimer(controlsWindow, reinterpret_cast<UINT_PTR>(this));
	action = false;
}
void CALLBACK Stage::ActionTimer(HWND hwnd, UINT uMsg, UINT_PTR idParam, DWORD dwTime)
{
	Stage* stage = reinterpret_cast<Stage*>(idParam);

	try
	{
		for (int i = 0; i < static_cast<int>(round(1/(stage->params.dt * 100))); ++i)
			stage->Action();	
		PostMessage(hwnd, SIMM_STEP, 0, 0);
	}
	catch (std::exception& e)
	{
		stage->StopAction();
		MessageBoxA(0, e.what(), "Error!", MB_OK);
		stage->model.Reset(stage->RetParams());
		SendMessage(hwnd, SIMM_ERROR, 0, 0);
		stage->StartAction();
	}
}