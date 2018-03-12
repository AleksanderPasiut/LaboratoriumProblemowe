#pragma once

#include "include.h"

class ProgressBar
{
private:
	HWND core;

public:
	ProgressBar()
	{
		int cx = GetSystemMetrics(SM_CXSCREEN);
		int cy = GetSystemMetrics(SM_CYSCREEN);
	
		core = CreateWindowEx(0,
							  L"EDIT",
							  L"Identification ...",
							  WS_BORDER | WS_CAPTION | ES_CENTER | ES_READONLY,
							  cx/2 - 100,
							  cy/2 - 30,
							  200,
							  60,
							  0,
							  0,
							  GetModuleHandle(0),
							  0);

		SendMessage(core, WM_SETFONT, reinterpret_cast<WPARAM>(GetStockObject(DEFAULT_GUI_FONT)), 0);
		ShowWindow(core, SW_SHOWNORMAL);
	}
	void Close()
	{
		DestroyWindow(core);
	}
};