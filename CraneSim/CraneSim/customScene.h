#pragma once

#include "include.h"
#include "scene.h"

class CustomScene : public Scene
{
private:
	bool cameraMove;
	float cameraAzimuth;
	float cameraElevation;
	float cameraDistance;

	int refX;
	int refY;
	float refAzimuth;
	float refElevation;

private:
	void RefreshView()
	{
		SetView(D3DXVECTOR3(cameraDistance * cos(cameraAzimuth) * cos(cameraElevation),
							cameraDistance * sin(cameraAzimuth) * cos(cameraElevation),
							cameraDistance * sin(cameraElevation) + 0.7f),
				D3DXVECTOR3(0, 0, 0.7f), D3DXVECTOR3(0, 0, 1));
	}

public:
	CustomScene(Graphics3D& graphics, HWND hwnd) : Scene(graphics, hwnd),
		cameraMove(false),
		cameraAzimuth(1.2f),
		cameraElevation(0.3f),
		cameraDistance(5.0f)
	{ 
		RefreshView();
	}

	void StartCameraMove(LPARAM lParam)
	{
		cameraMove = true;
		refX = GET_X_LPARAM(lParam);
		refY = GET_Y_LPARAM(lParam);
		refAzimuth = cameraAzimuth;
		refElevation = cameraElevation;
	}
	void CameraMove(LPARAM lParam)
	{
		if (cameraMove)
		{
			cameraAzimuth = refAzimuth + (GET_X_LPARAM(lParam) - refX) * 0.005f;
			cameraElevation = refElevation + (GET_Y_LPARAM(lParam) - refY) * 0.005f;

			const float PI = 3.141529f;

			if (cameraElevation > (PI/2))
				cameraElevation = PI/2;

			if (cameraElevation < -PI/2)
				cameraElevation = -PI/2;

			RefreshView();
		}
	}
	void StopCameraMove(LPARAM lParam)
	{
		cameraMove = false;
	}
	void Zoom(WPARAM wParam)
	{
		if (GET_WHEEL_DELTA_WPARAM(wParam) < 0)
			cameraDistance *= 1.1f;
		else
			cameraDistance /= 1.1f;

		RefreshView();
	}
};