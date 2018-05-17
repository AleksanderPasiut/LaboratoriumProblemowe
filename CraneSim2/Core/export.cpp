#include "export.h"

Core* Init()
{
	return new Core();
}
void Free(Core* core)
{
	delete core;
}

void SetParam(Core* core, int id, double value)
{
	core->SetParam(id, value);
}
void Simulate(Core* core)
{
	core->Simulate();
}

size_t GetOutputLength(Core* core, int id)
{
	return core->GetOutputLength(id);
}
double GetOutputX(Core* core, int id, size_t index)
{
	return core->GetOutputX(id, index);
}
double GetOutputY(Core* core, int id, size_t index)
{
	return core->GetOutputY(id, index);
}
