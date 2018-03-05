#pragma once

#include <vector>
#include "graphics3d.h"

class Shapes
{
public:
	enum Type
	{
		ST_SQUARE = 0,
		ST_DISC = 1,
		ST_CUBE = 2,
		ST_SPHERE = 3,
		ST_AMOUNT = 4
	};

private:
	std::vector<IDirect3DVertexBuffer9*> tab;

	IDirect3DDevice9* device;
	unsigned precision;

private:
	void InitSquare();
	void InitDisc();
	void InitCube();
	void InitSphere();

public:
	Shapes(IDirect3DDevice9* device, unsigned precision);
	~Shapes() noexcept;

	void Draw(Type type) const noexcept;
};

