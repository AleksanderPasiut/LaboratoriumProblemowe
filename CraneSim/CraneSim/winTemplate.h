#pragma once

#include "include.h"
#include "docker.h"

template<typename WinSubT>
class WinT
{
protected:
	WNDCLASSEX wc;
	HWND hwnd;

	std::list<Docker> dockerList;

public:
	WinT(const std::wstring& className,
		 const std::wstring& windowName,
		 DWORD windowStyle = WS_OVERLAPPEDWINDOW,
		 int x = CW_USEDEFAULT,
		 int y = CW_USEDEFAULT,
		 int width = CW_USEDEFAULT,
		 int height = CW_USEDEFAULT,
		 DWORD windowExStyle = 0);
	WinT(const WinT&) = delete;
	WinT& operator= (const WinT&) = delete;
	virtual ~WinT() noexcept;

	void AddDocker(HWND target, Docker::Position position, float percent);
	void AddDocker(HWND target, Docker::Position position, int fixed);
	void DelDocker(HWND target);

	void ChangeBackground(HBRUSH hbr);

	static LRESULT CALLBACK WindowEventProc(HWND, UINT, WPARAM, LPARAM);
	HWND RetHwnd() const noexcept { return hwnd; }
};

template<typename WinSubT>
WinT<WinSubT>::WinT(const std::wstring& className, const std::wstring& windowName, DWORD windowStyle, int x, int y, int width, int height, DWORD windowExStyle)
{
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpszClassName = className.c_str();
	wc.lpfnWndProc = DefWindowProc;
	wc.hInstance = GetModuleHandle(0);
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	
	if (!RegisterClassEx(&wc))
		throw std::exception("Failed to register window class.");

	try
	{
		hwnd = CreateWindowEx(windowExStyle, wc.lpszClassName, windowName.c_str(), windowStyle, x, y, width, height, 0, 0, wc.hInstance, 0);

		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
		SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WindowEventProc));
	}
	catch (...) { UnregisterClass(wc.lpszClassName, wc.hInstance); throw; }
}

template<typename WinSubT>
WinT<WinSubT>::~WinT() noexcept
{
	SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(DefWindowProc));
	DestroyWindow(hwnd);
	UnregisterClass(wc.lpszClassName, wc.hInstance);
}

template<typename WinSubT>
void WinT<WinSubT>::AddDocker(HWND target, Docker::Position position, float percent)
{
	dockerList.push_back(Docker(hwnd, target, position, percent));
}
template<typename WinSubT>
void WinT<WinSubT>::AddDocker(HWND target, Docker::Position position, int fixed)
{
	dockerList.push_back(Docker(hwnd, target, position, fixed));
}
template<typename WinSubT>
void WinT<WinSubT>::DelDocker(HWND target)
{
	for (auto it = dockerList.begin(); it != dockerList.end(); ++it)
		if (it->operator()(target))
		{
			dockerList.erase(it);
			break;
		}
}

template<typename WinSubT>
void WinT<WinSubT>::ChangeBackground(HBRUSH hbr)
{
	SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, reinterpret_cast<LONG_PTR>(hbr));
}

template<typename WinSubT>
LRESULT CALLBACK WinT<WinSubT>::WindowEventProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	WinSubT* sub = reinterpret_cast<WinSubT*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

	switch (uMsg)
	{
		case WM_SIZE:
		{
			for (auto it = sub->dockerList.begin(); it != sub->dockerList.end(); ++it)
				(*it)(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

			break;
		}
	}

	return sub->EventProc(hwnd, uMsg, wParam, lParam);
}