#include "scene.h"

DWORD Scene::AntiAliasing() const noexcept
{
	DWORD quality = 0;
	graphics.D3D()->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		D3DFMT_X8R8G8B8,
		true,
		D3DMULTISAMPLE_8_SAMPLES,
		&quality);
	return quality;
}
void Scene::InitDevice(HWND hwnd)
{
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	d3dpp.Windowed = true;
	d3dpp.hDeviceWindow = hwnd;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_8_SAMPLES;
	d3dpp.MultiSampleQuality = AntiAliasing() - 1;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	RECT rect;
	GetClientRect(hwnd, &rect);
	d3dpp.BackBufferWidth = rect.right-rect.left;
	d3dpp.BackBufferHeight = rect.bottom-rect.top;

	// device creation
	if (FAILED(graphics.D3D()->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hwnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev)))
		throw std::exception("Failed to create Direct3D device.");
}
void Scene::InitAdditionalRenderSettings()
{
	// setting additional render states
	if (FAILED(d3ddev->SetRenderState(D3DRS_ZENABLE, true)))							throw std::exception("Direct3D additional settings error.");
	if (FAILED(d3ddev->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, true)))				throw std::exception("Direct3D additional settings error.");
	if (FAILED(d3ddev->SetRenderState(D3DRS_NORMALIZENORMALS, true)))				throw std::exception("Direct3D additional settings error.");

	if (FAILED(d3ddev->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL)))	throw std::exception("Direct3D additional settings error.");
	//if (FAILED(d3ddev->SetRenderState(D3DRS_SPECULARENABLE, true)))						throw std::exception("Direct3D additional settings error.");
	//if (FAILED(d3ddev->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL)))	throw std::exception("Direct3D additional settings error.");
	//if (FAILED(d3ddev->SetRenderState(D3DRS_EMISSIVEMATERIALSOURCE, D3DMCS_MATERIAL)))	throw std::exception("Direct3D additional settings error.");

	//if (FAILED(d3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, true)))					throw std::exception("Direct3D additional settings error.");
 	//if (FAILED(d3ddev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD)))					throw std::exception("Direct3D additional settings error.");
 	//if (FAILED(d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA)))				throw std::exception("Direct3D additional settings error.");
 	//if (FAILED(d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA)))			throw std::exception("Direct3D additional settings error.");
}
void Scene::InitLights()
{
	d3ddev->SetRenderState(D3DRS_AMBIENT, 0x007f7f7f);
	d3ddev->SetRenderState(D3DRS_LIGHTING, true);

	if (true)
	{
		D3DLIGHT9 light;
		ZeroMemory(&light, sizeof(D3DLIGHT9));
		light.Type = D3DLIGHT_POINT;
		light.Diffuse = D3DXCOLOR(1.0f, 0.9f, 0.9f, 1.0f);
		light.Position = D3DXVECTOR3(5.0f, 8.0f, 15.0f);
		light.Range = 50.0f;
		light.Attenuation0 = 1.0f;

		d3ddev->SetLight(0, &light);
		d3ddev->LightEnable(0, true);
	}

	if (false)
	{
		D3DLIGHT9 light;
		ZeroMemory(&light, sizeof(D3DLIGHT9));
		light.Type = D3DLIGHT_POINT;
		light.Diffuse = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
		light.Position = D3DXVECTOR3(0.0f, 10.0f, 10.0f);
		light.Range = 50.0f;
		light.Attenuation0 = 0.5f;

		d3ddev->SetLight(1, &light);
		d3ddev->LightEnable(1, true);
	}

	if (false)
	{
		D3DLIGHT9 light;
		ZeroMemory(&light, sizeof(D3DLIGHT9));
		light.Type = D3DLIGHT_POINT;
		light.Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		light.Position = D3DXVECTOR3(-10.0f, 10.0f, 10.0f);
		light.Range = 50.0f;
		light.Attenuation0 = 0.5f;

		d3ddev->SetLight(2, &light);
		d3ddev->LightEnable(2, true);
	}
}
void Scene::InitWVP()
{
	matView.Set(D3DXVECTOR3(10.0, 0.0, 0.0), D3DXVECTOR3(0.0, 0.0, 0.0), D3DXVECTOR3(0.0, 0.0, 1.0));
	d3ddev->SetTransform(D3DTS_VIEW, matView.Mat());

	matProjection.Set(d3dpp.hDeviceWindow, 30, 0.1f, 80);
	d3ddev->SetTransform(D3DTS_PROJECTION, matProjection.Mat());
}

void Scene::Begin() noexcept
{
	d3ddev->Clear(0, 0, D3DCLEAR_TARGET, colorBack, 1.0f, 0);
	d3ddev->Clear(0, 0, D3DCLEAR_ZBUFFER, colorBack, 1.0f, 0);

	d3ddev->BeginScene();	

	d3ddev->SetFVF(CUSTOMFVF_TYPE);
}
void Scene::End() noexcept
{
	d3ddev->EndScene();
	d3ddev->Present(0, 0, 0, 0);
}