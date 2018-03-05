#pragma once

#include "item.h"

class Mass : public Item
{
private:
	MatWorld matLine;
	MatWorld matMass;

	float lineLength;
	float posX;
	float posY;
	float angleX;
	float angleY;

public:
	Mass() : Item()
	{
		SetPos(0, 0, 0, 0, 0);
	}
	void Render(CustomScene& scene, Shapes& shapes, Materials& materials) const
	{
		scene.SetMaterial(materials.Ret(materials.MT_BLUE));
		scene.SetWorld(matLine);
		shapes.Draw(shapes.ST_CUBE);

		scene.SetMaterial(materials.Ret(materials.MT_PURPLE));
		scene.SetWorld(matMass);
		shapes.Draw(shapes.ST_SPHERE);
	}
	
	void SetPos(float posX, float posY, float angleX, float angleY, float lineLength)
	{
		this->posX;
		this->posY;

		this->angleX = angleX;
		this->angleY = angleY;

		float sinAlphaX = sin(angleX);
		float sinAlphaY = sin(angleY);
		float cosAlpha = sqrt(1 - sinAlphaX * sinAlphaX - sinAlphaY * sinAlphaY);

		float azimuth = atan(-angleX / angleY);
		if (angleY < 0)
			azimuth += 3.141529f;

		/*matLine.Set(D3DXVECTOR3(sinAlphaX * lineLength/2 + posX,
								sinAlphaY * lineLength/2 + posY,
								0.985f - cosAlpha * lineLength/2), D3DXVECTOR3(0.01f, 0.01f, lineLength), azimuth, acos(cosAlpha), false);*/

		matLine.Set(D3DXVECTOR3(sinAlphaX * lineLength/2 + posX,
								sinAlphaY * lineLength/2 + posY,
								0.985f - cosAlpha * lineLength/2), D3DXVECTOR3(0.01f, 0.01f, lineLength), -angleX, asin(sin(angleY)/cos(angleX)), (float)0);

		matMass.Set(D3DXVECTOR3(sinAlphaX * lineLength + posX,
								sinAlphaY * lineLength + posY,
								0.985f - cosAlpha * lineLength), D3DXVECTOR3(0.05f, 0.05f, 0.05f));
	}

	float RetLineLength() { return lineLength; }
	float RetAngleX() { return angleX; }
	float RetAngleY() { return angleY; }
};