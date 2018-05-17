#pragma once

#define EXPORT __declspec(dllexport) 

#include "core.h"

extern "C"
{
	EXPORT Core* Init();
	EXPORT void Free(Core*);

	EXPORT void SetParam(Core*, int id, double value);
	EXPORT void Simulate(Core*);

	EXPORT size_t GetOutputLength(Core*, int id);
	EXPORT double GetOutputX(Core*, int id, size_t index);
	EXPORT double GetOutputY(Core*, int id, size_t index);
}