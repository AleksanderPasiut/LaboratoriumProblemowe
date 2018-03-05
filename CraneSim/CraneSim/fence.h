#pragma once

#include "item.h"

class Fence : public Item
{
private:
	MatWorld matMain;

	float pos;

public:
	Fence() : Item()
	{
		SetPos(0);
	}
	void Render(CustomScene& scene, Shapes& shapes, Materials& materials) const
	{
		scene.SetMaterial(materials.Ret(materials.MT_RED));
		scene.SetWorld(matMain);
		shapes.Draw(shapes.ST_CUBE);
	}

	void SetPos(float pos)
	{
		this->pos = pos;
		matMain.Set(D3DXVECTOR3(0, pos, 1.025f), D3DXVECTOR3(1.0f, 0.08f, 0.06f));
	}
	float RetPos() { return pos; }
};