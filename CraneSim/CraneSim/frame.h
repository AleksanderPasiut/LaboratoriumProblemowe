#pragma once

#include "item.h"

class Frame : public Item
{
private:
	MatWorld matBase[3];
	MatWorld matFloor;

	MatWorld matVert[4];
	MatWorld matHorz[4];

public:
	Frame() : Item()
	{
		matBase[0].Set(D3DXVECTOR3(0, 0, -0.05f), D3DXVECTOR3(2.0f, 2.0f, 0.1f));
		matBase[1].Set(D3DXVECTOR3(0, 1.05f, -0.05f), D3DXVECTOR3(0.1f, 0.1f, 0.1f));
		matBase[2].Set(D3DXVECTOR3(1.05f, 0, -0.05f), D3DXVECTOR3(0.1f, 0.1f, 0.1f));

		matFloor.Set(D3DXVECTOR3(0.0f, 0.0f, 0.05f), D3DXVECTOR3(1.2f, 1.2f, 0.1f));

		matVert[0].Set(D3DXVECTOR3(-0.5f, -0.5f, 0.60f), D3DXVECTOR3(0.05f, 0.05f, 1.0f));
		matVert[1].Set(D3DXVECTOR3(-0.5f,  0.5f, 0.60f), D3DXVECTOR3(0.05f, 0.05f, 1.0f));
		matVert[2].Set(D3DXVECTOR3( 0.5f, -0.5f, 0.60f), D3DXVECTOR3(0.05f, 0.05f, 1.0f));
		matVert[3].Set(D3DXVECTOR3( 0.5f,  0.5f, 0.60f), D3DXVECTOR3(0.05f, 0.05f, 1.0f));

		matHorz[0].Set(D3DXVECTOR3(-0.5f, 0.0f, 1.025f), D3DXVECTOR3(0.03f, 0.95f, 0.03f));
		matHorz[1].Set(D3DXVECTOR3( 0.5f, 0.0f, 1.025f), D3DXVECTOR3(0.03f, 0.95f, 0.03f));

		matHorz[2].Set(D3DXVECTOR3(0.0f, -0.5f, 1.025f), D3DXVECTOR3(0.95f, 0.03f, 0.03f));
		matHorz[3].Set(D3DXVECTOR3(0.0f,  0.5f, 1.025f), D3DXVECTOR3(0.95f, 0.03f, 0.03f));
	}
	void Render(CustomScene& scene, Shapes& shapes, Materials& materials) const
	{
		scene.SetMaterial(materials.Ret(materials.MT_GRAY));
		scene.SetWorld(matBase[0]);
		shapes.Draw(shapes.ST_CUBE);

		scene.SetMaterial(materials.Ret(materials.MT_RED));
		scene.SetWorld(matBase[1]);
		shapes.Draw(shapes.ST_CUBE);

		scene.SetMaterial(materials.Ret(materials.MT_GREEN));
		scene.SetWorld(matBase[2]);
		shapes.Draw(shapes.ST_CUBE);

		scene.SetMaterial(materials.Ret(materials.MT_DKGRAY));
		scene.SetWorld(matFloor);
		shapes.Draw(shapes.ST_CUBE);

		scene.SetMaterial(materials.Ret(materials.MT_YELLOW));

		for (int i = 0; i < 4; ++i)
		{
			scene.SetWorld(matVert[i]);
			shapes.Draw(shapes.ST_CUBE);

			scene.SetWorld(matHorz[i]);
			shapes.Draw(shapes.ST_CUBE);
		}
	}
};