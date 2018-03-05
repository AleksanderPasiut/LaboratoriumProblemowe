#pragma once

#include "item.h"

class Carriage : public Item
{
private:
	MatWorld matMain;

	float posX;
	float posY;

public:
	Carriage() : Item()
	{
		SetPos(0, 0);
	}
	void Render(CustomScene& scene, Shapes& shapes, Materials& materials) const
	{
		scene.SetMaterial(materials.Ret(materials.MT_ORANGE));
		scene.SetWorld(matMain);
		shapes.Draw(shapes.ST_CUBE);
	}

	void SetPos(float posX, float posY)
	{
		this->posX = posX;
		this->posY = posY;
		matMain.Set(D3DXVECTOR3(posX, posY, 1.015f), D3DXVECTOR3(0.1f, 0.14f, 0.06f));
	}
	float RetPosX() { return posX; }
	float RetPosY() { return posY; }
};