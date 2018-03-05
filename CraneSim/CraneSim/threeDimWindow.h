#pragma once

#include "winTemplate.h"
#include "customScene.h"
#include "shapes.h"
#include "materials.h"
#include "stage.h"

class ThreeDimWindow : public WinT<ThreeDimWindow>
{
private:
	Graphics3D& graphics;
	CustomScene scene;
	Shapes shapes;
	Materials materials;

	Stage& stage;

public:
	ThreeDimWindow(Graphics3D& graphics, Stage& stage);
	~ThreeDimWindow() noexcept;

	void Render();

	LRESULT EventProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};