#include "materials.h"

void Materials::SetStd(D3DMATERIAL9& mat, const D3DXCOLOR& std)
{
	mat.Diffuse = std;
	mat.Ambient = std;
}
void Materials::SetStd(D3DMATERIAL9& mat, const D3DXCOLOR& diffuse, const D3DXCOLOR& ambient)
{
	mat.Diffuse = diffuse;
	mat.Ambient = ambient;
}

Materials::Materials()
{
	tab.resize(MT_AMOUNT);
	ZeroMemory(&tab[0], sizeof(D3DMATERIAL9) * MT_AMOUNT);

	SetStd(tab[MT_RED],		D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), D3DXCOLOR(0.6f, 0.0f, 0.0f, 1.0f));
	SetStd(tab[MT_ORANGE],	D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f), D3DXCOLOR(0.6f, 0.3f, 0.0f, 1.0f));
	SetStd(tab[MT_YELLOW],	D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), D3DXCOLOR(0.6f, 0.6f, 0.0f, 1.0f));
	SetStd(tab[MT_GREEN],	D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), D3DXCOLOR(0.0f, 0.6f, 0.0f, 1.0f));
	SetStd(tab[MT_BLUE],	D3DXCOLOR(0.6f, 0.6f, 1.0f, 1.0f), D3DXCOLOR(0.3f, 0.3f, 0.6f, 1.0f));
	SetStd(tab[MT_PURPLE],	D3DXCOLOR(0.5f, 0.0f, 1.0f, 1.0f), D3DXCOLOR(0.3f, 0.0f, 0.6f, 1.0f));
	SetStd(tab[MT_GRAY],	D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f), D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f));
	SetStd(tab[MT_LTGRAY],	D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f), D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f));
	SetStd(tab[MT_DKGRAY],	D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f), D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f));
}