#pragma once

#include "graphics3d.h"
#include "matWorld.h"
#include "matView.h"
#include "matProjection.h"

class Scene
{
private:
	Graphics3D& graphics;
	IDirect3DDevice9* d3ddev;
	D3DPRESENT_PARAMETERS d3dpp;
	D3DCOLOR colorBack;

	MatWorld matWorld;
	MatView matView;
	MatProjection matProjection;

private:
	DWORD AntiAliasing() const noexcept;
	void InitDevice(HWND);
	void InitAdditionalRenderSettings();
	void InitLights();
	void InitWVP();

public:
	Scene(Graphics3D& graphics, HWND hwnd) : graphics(graphics), colorBack(D3DCOLOR_XRGB(0, 0, 0))
	{
		InitDevice(hwnd);

		try
		{
			InitAdditionalRenderSettings();
			InitLights();
			InitWVP();
		}
		catch (std::exception e) { d3ddev->Release(); throw; }
	}
	~Scene() noexcept
	{
		d3ddev->Release();
	}

	void Begin() noexcept;
	void End() noexcept;

	IDirect3DDevice9* RetDevice() const noexcept { return d3ddev; }

	void SetWorld(const MatWorld& mat) { d3ddev->SetTransform(D3DTS_WORLD, mat.Mat()); }
	void SetView(const MatView& mat) { d3ddev->SetTransform(D3DTS_VIEW, mat.Mat()); }
	void SetProjection(const MatProjection& mat) { d3ddev->SetTransform(D3DTS_PROJECTION, mat.Mat()); }

	void SetWorld(const D3DXVECTOR3& translation, float scale) { d3ddev->SetTransform(D3DTS_WORLD, matWorld.Set(translation, scale)); }
	void SetWorld(const D3DXVECTOR3& translation, const D3DXVECTOR3& scale) { d3ddev->SetTransform(D3DTS_WORLD, matWorld.Set(translation, scale)); }
	void SetWorld(const D3DXVECTOR3& translation, const D3DXVECTOR3& scale, float azimuth, float elevation) { d3ddev->SetTransform(D3DTS_WORLD, matWorld.Set(translation, scale, azimuth, elevation)); }
	void SetView(const D3DXVECTOR3& cameraPos, const D3DXVECTOR3& lookAtPoint, const D3DXVECTOR3& upDirection) { d3ddev->SetTransform(D3DTS_VIEW, matView.Set(cameraPos, lookAtPoint, upDirection)); }
	void SetProjection(float angle, float nearPlane, float farPlane) { d3ddev->SetTransform(D3DTS_PROJECTION, matProjection.Set(d3dpp.hDeviceWindow, angle, nearPlane, farPlane)); }
	void SetMaterial(const D3DMATERIAL9* material) { d3ddev->SetMaterial(material); }
};