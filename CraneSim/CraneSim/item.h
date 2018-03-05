#pragma once

#include "customScene.h"
#include "shapes.h"
#include "materials.h"

class Item
{
public:
	virtual void Render(CustomScene& scene, Shapes& shapes, Materials& materials) const = 0;
};