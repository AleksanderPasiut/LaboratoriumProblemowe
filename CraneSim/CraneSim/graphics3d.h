#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <exception>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

#define CUSTOMFVF_TYPE D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1

struct CUSTOMFVF
{
	float x;
	float y;
	float z;
	D3DVECTOR normal;
	float tu;
	float tv;

	CUSTOMFVF(float in_x, float in_y, float in_z, D3DVECTOR in_normal) : 
		x(in_x),
		y(in_y),
		z(in_z),
		normal(in_normal),
		tu(0),
		tv(0) {}

	CUSTOMFVF(float in_x, float in_y, float in_z, D3DVECTOR in_normal, float in_tu, float in_tv) : 
		x(in_x),
		y(in_y),
		z(in_z),
		normal(in_normal),
		tu(in_tu),
		tv(in_tv) {}
};

class Graphics3D
{
private:
	IDirect3D9* d3d;
	
public:
	Graphics3D();
	~Graphics3D() noexcept;

	IDirect3D9* D3D() const noexcept { return d3d; }
};