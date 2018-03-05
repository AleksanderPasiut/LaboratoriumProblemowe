#include "graphics3d.h"

Graphics3D::Graphics3D()
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (!d3d)
		throw std::exception("Failed to initialize D3D9 factory.");
}
Graphics3D::~Graphics3D() noexcept
{
	d3d->Release();
}
