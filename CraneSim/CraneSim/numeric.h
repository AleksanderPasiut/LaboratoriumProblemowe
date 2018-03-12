#pragma once

#include "include.h"

class Numeric
{
private:
	std::wstring name;
	std::wstring valueStr;
	HWND parent;
	HWND desc;
	HWND editbox;

public:
	Numeric(__int64 id, const std::wstring& name, HWND parent, const RECT& rect) :
		name(name),
		parent(parent)
	{
		desc = CreateWindowEx(0,
							  L"EDIT",
							  (name+L":").c_str(),
							  WS_CHILD | WS_VISIBLE | ES_READONLY | ES_RIGHT,
							  rect.left - 50,
							  rect.top+2,
							  45,
							  rect.bottom - 4,
							  parent,
							  0,
							  GetModuleHandle(0),
							  NULL);

		SendMessage(desc, WM_SETFONT, reinterpret_cast<WPARAM>(GetStockObject(DEFAULT_GUI_FONT)), 0);

		editbox = CreateWindowEx(WS_EX_CLIENTEDGE,
								 L"EDIT",
								 L"",
								 WS_CHILD | WS_VISIBLE | ES_READONLY | ES_LEFT | WS_BORDER,
								 rect.left,
								 rect.top,
								 rect.right,
								 rect.bottom,
								 parent,
								 reinterpret_cast<HMENU>(id),
								 GetModuleHandle(0),
								 NULL);

		SendMessage(editbox, WM_SETFONT, reinterpret_cast<WPARAM>(GetStockObject(DEFAULT_GUI_FONT)), 0);
	}
	void SetValue(double value)
	{
		std::wstringstream ss;
		ss << std::fixed << std::setprecision(5) << value;
		if (valueStr != ss.str())
		{
			valueStr = ss.str();
			SetWindowText(editbox, ss.str().c_str());
		}
	}
	double RetValue()
	{
		valueStr.resize(GetWindowTextLength(editbox)+1);
		GetWindowText(editbox, &valueStr[0], static_cast<int>(valueStr.size())+1);
		return std::stod(valueStr);
	}
	void SetReadOnly(bool arg)
	{
		SendMessage(editbox, EM_SETREADONLY, arg, 0);
	}
	__int64 RetId() const noexcept { return static_cast<__int64>(GetWindowLongPtr(editbox, GWLP_ID)); }
};