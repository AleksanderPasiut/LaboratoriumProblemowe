#pragma once

#include "graphics3d.h"
#include <vector>

class Materials
{
public:
	enum Type
	{
		MT_RED = 0,
		MT_ORANGE = 1,
		MT_YELLOW = 2,
		MT_GREEN = 3,
		MT_BLUE = 4,
		MT_PURPLE = 5,
		MT_GRAY = 6,
		MT_LTGRAY = 7,
		MT_DKGRAY = 8,
		MT_AMOUNT = 9
	};

private:
	std::vector<D3DMATERIAL9> tab;

private:
	void SetStd(D3DMATERIAL9& mat, const D3DXCOLOR& std);
	void SetStd(D3DMATERIAL9& mat, const D3DXCOLOR& diffuse, const D3DXCOLOR& ambient);

public:
	Materials();

	const D3DMATERIAL9* Ret(Type type) const noexcept { return &(tab[type]); }
};