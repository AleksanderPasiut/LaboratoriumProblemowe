#pragma once

#include "include.h"

class SolverSwitch
{
private:
	HWND parent;
	HWND switchEuler;
	HWND switchRK4;

public:
	SolverSwitch(__int64 idEuler, __int64 idRK4, HWND parent, RECT rect) :
		parent(parent)
	{
		switchEuler = CreateWindowEx(0,
									 L"BUTTON",
									 L"Euler",
									 WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
									 rect.left,
									 rect.top,
									 rect.right,
									 rect.bottom,
									 parent,
									 reinterpret_cast<HMENU>(idEuler),
									 GetModuleHandle(0),
									 NULL);
		switchRK4 = CreateWindowEx(0,
								   L"BUTTON",
								   L"RK4",
								   WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
								   rect.left,
								   rect.top + rect.bottom + 5,
								   rect.right,
								   rect.bottom,
								   parent,
								   reinterpret_cast<HMENU>(idRK4),
								   GetModuleHandle(0),
								   NULL);
		
		SendMessage(switchEuler, WM_SETFONT, reinterpret_cast<WPARAM>(GetStockObject(DEFAULT_GUI_FONT)), 0);
		SendMessage(switchRK4, WM_SETFONT, reinterpret_cast<WPARAM>(GetStockObject(DEFAULT_GUI_FONT)), 0);
	}
	int RetValue()
	{
		return SendMessage(switchEuler, BM_GETCHECK, 0, 0) == BST_CHECKED ? 0 : 1;
	}
	void SetValue(int solver)
	{
		SendMessage(switchEuler, BM_SETCHECK, solver == 0 ? BST_CHECKED : BST_UNCHECKED, 0);
		SendMessage(switchRK4, BM_SETCHECK, solver == 1 ? BST_CHECKED : BST_UNCHECKED, 0);
	}
	__int64 RetIdEuler() const noexcept { return static_cast<__int64>(GetWindowLongPtr(switchEuler, GWLP_ID)); }
	__int64 RetIdRK4() const noexcept { return static_cast<__int64>(GetWindowLongPtr(switchRK4, GWLP_ID)); }

	void SetReadOnly(bool readonly)
	{
		EnableWindow(switchEuler, !readonly);
		EnableWindow(switchRK4, !readonly);
	}
};