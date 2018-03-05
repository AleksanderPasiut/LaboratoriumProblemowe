#pragma once

#include "graphics3d.h"

class MatProjection
{
private:
	D3DXMATRIX mat;

	//float angle;
	//float pNear;
	//float pFar;

public:
	MatProjection()
	{
		D3DXMatrixIdentity(&mat);
	}

	const D3DXMATRIX* Set(HWND hwnd, float angle, float pNear, float pFar)
	{
		//this->angle = angle;
		//this->pNear = pNear;
		//this->pFar = pFar;

		RECT rect;
		GetClientRect(hwnd, &rect);

		D3DXMatrixPerspectiveFovLH(&mat,
			D3DXToRadian(angle),
			static_cast<float>(rect.right-rect.left)/static_cast<float>(rect.bottom-rect.top),
			pNear,
			pFar);

		return &mat;
	}

	const D3DXMATRIX* Mat() const { return &mat; }
};