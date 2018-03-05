#pragma once

#include "winTemplate.h"

class MainWindow : public WinT<MainWindow>
{
private:
	HWND controls;

public:
	MainWindow(HWND controls) : WinT<MainWindow>(L"MainWindowClass", L"CraneSim"), controls(controls)
	{
		
	}
	~MainWindow() noexcept
	{
		 
	}

	void Show()
	{
		ShowWindow(hwnd, SW_MAXIMIZE);
	}

	LRESULT EventProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
			case WM_ACTIVATE:
			{
				SetWindowPos(controls, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
				break;
			}
			case WM_DESTROY:
			{
				PostQuitMessage(0);
				return 0;
			}
		}

		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
};