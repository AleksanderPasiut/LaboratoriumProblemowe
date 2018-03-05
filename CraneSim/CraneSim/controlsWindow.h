#pragma once

#include "winTemplate.h"
#include "slider.h"

class ControlsWindow : public WinT<ControlsWindow>
{
private:
	Stage& stage;

	Slider sliderX;
	Slider sliderY;
	//Slider slider1;
	//Slider slider2;

public:
	ControlsWindow(Stage& stage) : WinT<ControlsWindow>(L"ControlsWindowClass",
														L"Controls",
														WS_BORDER | WS_CAPTION,
														50,
														50,
														160, //280
														600,
														WS_EX_TOOLWINDOW),
		stage(stage),
		sliderX(L"ux", hwnd, {20, 10, 60, 520}, {20, 530, 60, 540}, -10.0, 10.0, 0.25, 0),
		sliderY(L"uy", hwnd, {80, 10, 120, 520}, {80, 530, 120, 540}, -10.0, 10.0, 0.25, 0)
		//slider1(hwnd, {140, 10, 180, 520}, {140, 530, 180, 540}, -0.75, 0.75, 0.03, 0),
		//slider2(hwnd, {200, 10, 240, 520}, {200, 530, 240, 540}, -0.75, 0.75, 0.03, 0)
	{
		ChangeBackground(GetSysColorBrush(COLOR_BTNFACE));
	}
	~ControlsWindow() noexcept
	{
		 
	}

	void Show()
	{
		ShowWindow(hwnd, SW_SHOWNORMAL);
	}

	LRESULT EventProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
			case WM_VSCROLL:
			{
				//stage.Control(sliderX.RetPos(), sliderY.RetPos(), slider1.RetPos(), slider2.RetPos());
				stage.Control(sliderX.RetPos(), sliderY.RetPos(), 0, 0);
				break;
			}
		}

		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
};