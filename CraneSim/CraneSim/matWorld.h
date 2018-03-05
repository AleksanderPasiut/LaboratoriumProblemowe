#pragma once

#include "graphics3d.h"

class MatWorld
{
private:
	D3DXMATRIX mat;

	//D3DXVECTOR3 translation;
	//float scale;

public:
	MatWorld()
	{
		D3DXMatrixIdentity(&mat);
	}

	const D3DXMATRIX* Set(const D3DXVECTOR3& translation, float scale)
	{
		//this->translation = translation;
		//this->scale = scale;

		D3DXMATRIX m1, m2;
		D3DXMatrixScaling(&m1, scale, scale, scale);
		D3DXMatrixTranslation(&m2, translation.x, translation.y, translation.z);
		D3DXMatrixMultiply(&mat, &m1, &m2);
		return &mat;
	}
	const D3DXMATRIX* Set(const D3DXVECTOR3& translation, const D3DXVECTOR3& scale)
	{
		D3DXMATRIX m1, m2;
		D3DXMatrixScaling(&m1, scale.x, scale.y, scale.z);
		D3DXMatrixTranslation(&m2, translation.x, translation.y, translation.z);
		D3DXMatrixMultiply(&mat, &m1, &m2);
		return &mat;
	}
	const D3DXMATRIX* Set(const D3DXVECTOR3& translation, const D3DXVECTOR3& scale, float azimuth, float elevation, bool dir = true)
	{
		D3DXMATRIX m1, m2, m3;
		D3DXMatrixScaling(&m1, scale.x, scale.y, scale.z);
		if (dir)
		{
			D3DXMatrixRotationYawPitchRoll(&m2, elevation, 0, azimuth);
			D3DXMatrixMultiply(&m3, &m1, &m2);
		}
		else
		{
			D3DXMatrixRotationX(&m3, elevation);
			D3DXMatrixMultiply(&m2, &m1, &m3);
			D3DXMatrixRotationZ(&m1, azimuth);
			D3DXMatrixMultiply(&m3, &m2, &m1);
		}
		
		D3DXMatrixTranslation(&m1, translation.x, translation.y, translation.z);
		D3DXMatrixMultiply(&mat, &m3, &m1);
		return &mat;
	}
	const D3DXMATRIX* Set(const D3DXVECTOR3& translation, const D3DXVECTOR3& scale, float angleX, float angleY, float angleZ)
	{
		D3DXMATRIX m1, m2, m3;
		D3DXMatrixScaling(&m1, scale.x, scale.y, scale.z);

		D3DXMatrixRotationZ(&m2, angleZ);
		D3DXMatrixMultiply(&m3, &m1, &m2);

		D3DXMatrixRotationY(&m1, angleX);
		D3DXMatrixMultiply(&m2, &m3, &m1);

		D3DXMatrixRotationX(&m1, angleY);
		D3DXMatrixMultiply(&m3, &m2, &m1);

		D3DXMatrixTranslation(&m1, translation.x, translation.y, translation.z);
		D3DXMatrixMultiply(&mat, &m3, &m1);
		return &mat;
	}
	const D3DXMATRIX* Mat() const { return &mat; }
};