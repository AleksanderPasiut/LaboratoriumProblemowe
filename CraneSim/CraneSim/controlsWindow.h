#pragma once

#include "winTemplate.h"
#include "slider.h"
#include "numeric.h"
#include "bistable.h"
#include "solverSwitch.h"

class ControlsWindow : public WinT<ControlsWindow>
{
private:
	Stage& stage;
	Identifier& identifier;

	Slider sliderX;
	Slider sliderY;

	static const int numLeft = 180;
	static const int numHSize = 60;
	static const int numVSize = 20; 
	Numeric numericX;
	Numeric numericY;
	Numeric numericVX;
	Numeric numericVY;
	Numeric numericAX;
	Numeric numericAY;

	Numeric numericAlphaX;
	Numeric numericAlphaY;
	Numeric numericOmegaX;
	Numeric numericOmegaY;
	Numeric numericEpsilonX;
	Numeric numericEpsilonY;

	Numeric numericL;
	Numeric numericM;
	Numeric numericMF;
	Numeric numericMC;
	Numeric numericG;
	Numeric numericBX;
	Numeric numericBY;

	Bistable bistable;
	Bistable reset;
	Bistable identify;

	Numeric numericDt;
	SolverSwitch solverSwitch;

public:
	ControlsWindow(Stage& stage, Identifier& identifier) : WinT<ControlsWindow>(L"ControlsWindowClass",
														L"Controls",
														WS_BORDER | WS_CAPTION,
														50,
														50,
														280,
														700,
														WS_EX_TOOLWINDOW),
		stage(stage),
		identifier(identifier),
		sliderX(0x8001, L"ux", hwnd, {20, 10, 70, 520}, {20, 530, 70, 540}, -10.0, 10.0, 0.25, 0),
		sliderY(0x8002, L"uy", hwnd, {80, 10, 130, 520}, {80, 530, 130, 540}, -10.0, 10.0, 0.25, 0),
		numericX(0x8101, L"x", hwnd, {numLeft, 20, numHSize, numVSize}),
		numericY(0x8102, L"y", hwnd, {numLeft, 45, numHSize, numVSize}),
		numericVX(0x8103, L"vx", hwnd, {numLeft, 70, numHSize, numVSize}),
		numericVY(0x8104, L"vy", hwnd, {numLeft, 95, numHSize, numVSize}),
		numericAX(0x8105, L"ax", hwnd, {numLeft, 120, numHSize, numVSize}),
		numericAY(0x8106, L"ay", hwnd, {numLeft, 145, numHSize, numVSize}),
		numericAlphaX(0x8107, L"alphaX", hwnd, {numLeft, 170, numHSize, numVSize}),
		numericAlphaY(0x8108, L"alphaY", hwnd, {numLeft, 195, numHSize, numVSize}),
		numericOmegaX(0x8109, L"omegaX", hwnd, {numLeft, 220, numHSize, numVSize}),
		numericOmegaY(0x810a, L"omegaY", hwnd, {numLeft, 245, numHSize, numVSize}),
		numericEpsilonX(0x810b, L"epsilonX", hwnd, {numLeft, 270, numHSize, numVSize}),
		numericEpsilonY(0x810c, L"epsilonY", hwnd, {numLeft, 295, numHSize, numVSize}),
		numericL(0x810d, L"l", hwnd, {numLeft, 320, numHSize, numVSize}),
		numericM(0x810e, L"m", hwnd, {numLeft, 345, numHSize, numVSize}),
		numericMF(0x810f, L"mF", hwnd, {numLeft, 370, numHSize, numVSize}),
		numericMC(0x8110, L"mC", hwnd, {numLeft, 395, numHSize, numVSize}),
		numericG(0x8111, L"g", hwnd, {numLeft, 420, numHSize, numVSize}),
		numericBX(0x8112, L"bx", hwnd, {numLeft, 445, numHSize, numVSize}),
		numericBY(0x8113, L"by", hwnd, {numLeft, 470, numHSize, numVSize}),
		bistable(0x8201, L"Stop simulation", hwnd, {numLeft - 30, 500, numHSize + 30, numVSize}),
		reset(0x8202, L"Reset simulation", hwnd, {numLeft - 30, 525, numHSize + 30, numVSize}),
		numericDt(0x8301, L"dt", hwnd, {numLeft, 560, numHSize, numVSize}),
		solverSwitch(0x8302, 0x8303, hwnd, {numLeft, 590, numHSize, numVSize}),
		identify(0x8304, L"IDENTIFY", hwnd, {20, 580, 110, 20})
	{
		ChangeBackground(GetSysColorBrush(COLOR_BTNFACE));
		FreezeControls(true, false);
	}

	void Show()
	{
		ShowWindow(hwnd, SW_SHOWNORMAL);
	}

	void FreezeControls(bool enable, bool ctrls2stage)
	{
		numericL.SetReadOnly(enable);
		numericM.SetReadOnly(enable);
		numericMF.SetReadOnly(enable);
		numericMC.SetReadOnly(enable);
		numericG.SetReadOnly(enable);
		numericBX.SetReadOnly(enable);
		numericBY.SetReadOnly(enable);

		numericDt.SetReadOnly(enable);
		solverSwitch.SetReadOnly(enable);

		if (ctrls2stage)
		{
			stage.RetParams().l = numericL.RetValue();
			stage.RetParams().m = numericM.RetValue();
			stage.RetParams().mF = numericMF.RetValue();
			stage.RetParams().mC = numericMC.RetValue();
			stage.RetParams().g = numericG.RetValue();
			stage.RetParams().bX = numericBX.RetValue();
			stage.RetParams().bY = numericBY.RetValue();
			
			stage.RetParams().dt = numericDt.RetValue();
			stage.RetParams().solverType = static_cast<Params::SolverType>(solverSwitch.RetValue());
		}
	}
	void RefreshControls()
	{
		numericX.SetValue(stage.RetModel().carX);
		numericY.SetValue(stage.RetModel().carY);
		numericVX.SetValue(stage.RetModel().vcX);
		numericVY.SetValue(stage.RetModel().vcY);
		numericAX.SetValue(stage.RetModel().acX);
		numericAY.SetValue(stage.RetModel().acY);

		numericAlphaX.SetValue(stage.RetModel().alphaX);
		numericAlphaY.SetValue(stage.RetModel().alphaY);
		numericOmegaX.SetValue(stage.RetModel().omegaX);
		numericOmegaY.SetValue(stage.RetModel().omegaY);
		numericEpsilonX.SetValue(stage.RetModel().epsilonX);
		numericEpsilonY.SetValue(stage.RetModel().epsilonY);

		numericL.SetValue(stage.RetParams().l);
		numericM.SetValue(stage.RetParams().m);
		numericMF.SetValue(stage.RetParams().mF);
		numericMC.SetValue(stage.RetParams().mC);
		numericG.SetValue(stage.RetParams().g);
		numericBX.SetValue(stage.RetParams().bX);
		numericBY.SetValue(stage.RetParams().bY);

		numericDt.SetValue(stage.RetParams().dt);
		solverSwitch.SetValue(static_cast<int>(stage.RetParams().solverType));
	}
	LRESULT EventProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
			case WM_VSCROLL:
			{
				stage.Control(sliderX.RetPos(), sliderY.RetPos(), 0, 0);
				break;
			}
			case WM_COMMAND:
			{
				if (lParam)
				{
					if (bistable.RetId() == LOWORD(wParam) && HIWORD(wParam) == BN_CLICKED)
					{
						if (stage.IsAction())
						{
							stage.StopAction();
							bistable.SetName(L"Start simulation");
							FreezeControls(false, false);
						}
						else
						{
							bistable.SetName(L"Stop simulation");
							FreezeControls(true, true);
							stage.StartAction();
						}
					}

					if (reset.RetId() == LOWORD(wParam) && HIWORD(wParam) == BN_CLICKED)
					{
						stage.RetModel().Reset();
						sliderX.SetPos(0);
						sliderY.SetPos(0);

						RefreshControls();
					}

					if (solverSwitch.RetIdEuler() == LOWORD(wParam) && HIWORD(wParam) == BN_CLICKED)
						solverSwitch.SetValue(0);

					if (solverSwitch.RetIdRK4() == LOWORD(wParam) && HIWORD(wParam) == BN_CLICKED)
						solverSwitch.SetValue(1);

					if (identify.RetId() == LOWORD(wParam) && HIWORD(wParam) == BN_CLICKED)
						Identify();
				}
				break;
			}
			case Stage::SIMM_ERROR:
			{
				sliderX.SetPos(0);
				sliderY.SetPos(0);
				break;
			}
			case Stage::SIMM_STEP:
			{
				RefreshControls();
				break;
			}
		}

		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	void Identify()
	{
		stage.StopAction();
		identifier.Launch();
		stage.StartAction();
	}
};