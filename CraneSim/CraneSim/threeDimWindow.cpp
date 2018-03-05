#include "threeDimWindow.h"

ThreeDimWindow::ThreeDimWindow(Graphics3D& graphics, Stage& stage) : 
	WinT<ThreeDimWindow>(L"ThreeDimWindowClass",
						 L"ThreeDimWindow",
						 WS_POPUP | WS_VISIBLE,
						 0,
						 0,
						 1920,
						 1080,
						 WS_EX_TOOLWINDOW),
	graphics(graphics), scene(graphics, hwnd), shapes(scene.RetDevice(), 50), stage(stage)
{
	SetTimer(hwnd, 0, 10, 0);
}
ThreeDimWindow::~ThreeDimWindow() noexcept
{
	KillTimer(hwnd, 0);
}

void ThreeDimWindow::Render()
{
	scene.Begin();
	stage.Render(scene, shapes, materials);
	scene.End();
}

LRESULT ThreeDimWindow::EventProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_LBUTTONDOWN: SetCapture(hwnd); scene.StartCameraMove(lParam); break;
		case WM_MOUSEMOVE: scene.CameraMove(lParam); break;
		case WM_LBUTTONUP: ReleaseCapture(); scene.StopCameraMove(lParam); break;
		case WM_MOUSEWHEEL: scene.Zoom(wParam); break;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}