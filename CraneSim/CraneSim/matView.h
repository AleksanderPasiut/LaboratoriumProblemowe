#pragma once

#include "graphics3d.h"

class MatView
{
private:
	D3DXMATRIX mat;

	//D3DXVECTOR3 cameraPos;
	//D3DXVECTOR3 lookAtPoint;
	//D3DXVECTOR3 upDirection;

public:
	MatView()
	{
		D3DXMatrixIdentity(&mat);
	}

	const D3DXMATRIX* Set(const D3DXVECTOR3& cameraPos, const D3DXVECTOR3& lookAtPoint, const D3DXVECTOR3& upDirection)
	{
		//this->cameraPos = cameraPos;
		//this->lookAtPoint = lookAtPoint;
		//this->upDirection = upDirection;

		D3DXMatrixLookAtLH(&mat, &cameraPos, &lookAtPoint, &upDirection);
		return &mat;
	}

	const D3DXMATRIX* Mat() const { return &mat; }
};