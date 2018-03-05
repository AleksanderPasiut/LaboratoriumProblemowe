#pragma once

#include "winTemplate.h"
#include "exampleMenu.h"

class MenuWindow : public WinT<MenuWindow>
{
private:
	ExampleMenu menu;

public:
	MenuWindow() : WinT<MenuWindow>(L"MenuWindowClass", L"Menu window")
	{
		SetMenu(hwnd, menu.Ret());

		ShowWindow(hwnd, SW_SHOWNORMAL);
	}
	~MenuWindow() noexcept
	{
		 
	}

	LRESULT EventProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
};