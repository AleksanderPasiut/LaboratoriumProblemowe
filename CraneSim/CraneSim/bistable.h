#pragma once

#include "include.h"

class Bistable
{
private:
	WNDPROC buttonWindowProc;
	std::wstring name;
	HWND parent;
	HWND button;

public:
	Bistable(__int64 id, const std::wstring& name, HWND parent, const RECT& rect) :
		name(name),
		parent(parent)
	{
		button = CreateWindowEx(0,
								L"BUTTON",
								name.c_str(),
								WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
								rect.left,
								rect.top,
								rect.right,
								rect.bottom,
								parent,
								reinterpret_cast<HMENU>(id),
								GetModuleHandle(0),
								NULL);
		
		SendMessage(button, WM_SETFONT, reinterpret_cast<WPARAM>(GetStockObject(DEFAULT_GUI_FONT)), 0);
	}

	void SetName(const std::wstring& name)
	{
		if (this->name != name)
		{
			this->name = name;
			SetWindowText(button, name.c_str());
		}
	}
	__int64 RetId() const noexcept { return static_cast<__int64>(GetWindowLongPtr(button, GWLP_ID)); }


};
