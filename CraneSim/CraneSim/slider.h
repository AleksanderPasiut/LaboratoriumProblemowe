#pragma once

#include "include.h"

class Slider
{
private:
	WNDPROC trackbarWindowProc;
	std::wstring name;
	HWND parent;
	HWND trackbar;
	HWND editbox;

	double rngMin;
	double rngMax;
	double rngTick;
	double value;

public:
	Slider(const std::wstring& name, HWND parent, const RECT& rect, const RECT& rectEdit, double rngMin, double rngMax, double rngTick, double value) :
		name(name),
		parent(parent),
		rngMin(rngMin),
		rngMax(rngMax),
		rngTick(rngTick),
		value(value)
	{
		trackbar = CreateWindowEx(0,
								  TRACKBAR_CLASS,
								  L"Trackbar",
								  WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS | TBS_ENABLESELRANGE | TBS_VERT,
								  rect.left,
								  rect.top,
								  rect.right - rect.left,
								  rect.bottom - rect.top,
								  parent,
								  0,
								  GetModuleHandle(0),
								  NULL);
		SetWindowLongPtr(trackbar, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
		trackbarWindowProc = reinterpret_cast<WNDPROC>(GetWindowLongPtr(trackbar, GWLP_WNDPROC));
		SetWindowLongPtr(trackbar, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(SliderWindowProc));

		unsigned max = static_cast<unsigned>(round((rngMax - rngMin) / rngTick));
		SendMessage(trackbar, TBM_SETRANGEMIN, FALSE, 0);
		SendMessage(trackbar, TBM_SETRANGEMAX, FALSE, max);
		SendMessage(trackbar, TBM_SETTICFREQ, 1, 0);

		editbox = CreateWindowEx(0,
								 L"EDIT",
								 L"",
								 WS_CHILD | WS_VISIBLE | ES_READONLY | ES_CENTER,
								 rectEdit.left,
								 rectEdit.top,
								 rectEdit.right - rectEdit.left,
								 rectEdit.bottom - rectEdit.top,
								 parent,
								 0,
								 GetModuleHandle(0),
								 NULL);

		SendMessage(editbox, WM_SETFONT, reinterpret_cast<WPARAM>(GetStockObject(DEFAULT_GUI_FONT)), 0);

		
		SetPos(value);
	}
	static LRESULT CALLBACK SliderWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		Slider* slider = reinterpret_cast<Slider*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

		switch (uMsg)
		{
			case WM_MOUSEMOVE:
			{
				if (wParam & MK_LBUTTON)
					slider->SetEditBoxValue(slider->RetPos());

				break;
			}
		}

		return CallWindowProc(slider->trackbarWindowProc, hwnd, uMsg, wParam, lParam);
	}
	void SetPos(double pos)
	{
		unsigned conv = static_cast<unsigned>(round((pos - rngMin) / rngTick));
		SendMessage(trackbar, TBM_SETPOS, TRUE, conv);
		SetEditBoxValue(pos);
	}
	double RetPos()
	{
		unsigned conv = static_cast<unsigned>(SendMessage(trackbar, TBM_GETPOS, 0, 0));
		return rngMax - rngTick * conv;
	}
	void SetEditBoxValue(double value)
	{
		std::wstringstream ss;
		ss << std::fixed << std::setprecision(3) << value;
		SetWindowText(editbox, (name + L": " +ss.str()).c_str());
	}
};