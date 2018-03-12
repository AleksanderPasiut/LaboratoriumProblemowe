#include "winTemplate.h"

#include "stage.h"
#include "identifier.h"
#include "mainWindow.h"
#include "controlsWindow.h"
#include "threeDimWindow.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Stage stage;
	Identifier identifier(stage.RetModel(), stage.RetParams());
	ControlsWindow controlsWindow(stage, identifier);
	MainWindow mainWindow(controlsWindow.RetHwnd());

	Graphics3D graphics3D;
	ThreeDimWindow threeDimWindow(graphics3D, stage);
	mainWindow.AddDocker(threeDimWindow.RetHwnd(), Docker::Position::FillAR, 1920.0f / 1080.0f);

	stage.SetControlsWindow(controlsWindow.RetHwnd());

	mainWindow.Show();
	controlsWindow.Show();

	stage.StartAction();

	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			threeDimWindow.Render();
		}
	}

	stage.StopAction();

	return static_cast<int>(msg.wParam);
}