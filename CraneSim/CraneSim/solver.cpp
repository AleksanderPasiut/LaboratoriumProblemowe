#include "solver.h"

void Solver::Euler(double dt)
{
	model.Step(params);

	model.vcX += model.acX * dt;
	model.vcY += model.acY * dt;
	model.omegaX += model.epsilonX * dt;
	model.omegaY += model.epsilonY * dt;

	model.carX += model.vcX * dt;
	model.carY += model.vcY * dt;
	model.alphaX += model.omegaX * dt;
	model.alphaY += model.omegaY * dt;
}
void Solver::RungeKutta(double dt)
{
	Model k1 = model;
	k1.Step(params);

	Model k2 = model;
	k2.Add(k1, 0.5);
	k2.Step(params);

	Model k3 = model;
	k3.Add(k2, 0.5);
	k3.Step(params);

	Model k4 = model;
	k4.Add(k3, 1.0);
	k4.Step(params);

	model.carX += (k1.vcX/6 + k2.vcX/3 + k3.vcX/3 + k4.vcX/6) * dt;
	model.carY += (k1.vcY/6 + k2.vcY/3 + k3.vcY/3 + k4.vcY/6) * dt;
	model.alphaX += (k1.omegaX/6 + k2.omegaX/3 + k3.omegaX/3 + k4.omegaX/6) * dt;
	model.alphaY += (k1.omegaY/6 + k2.omegaY/3 + k3.omegaY/3 + k4.omegaY/6) * dt;

	model.vcX += (k1.acX/6 + k2.acX/3 + k3.acX/3 + k4.acX/6) * dt;
	model.vcY += (k1.acY/6 + k2.acY/3 + k3.acY/3 + k4.acY/6) * dt;
	model.omegaX += (k1.epsilonX/6 + k2.epsilonX/3 + k3.epsilonX/3 + k4.epsilonX/6) * dt;
	model.omegaY += (k1.epsilonY/6 + k2.epsilonY/3 + k3.epsilonY/3 + k4.epsilonY/6) * dt;
}
void Solver::CheckErrs()
{
	if (model.alphaX > 1.57)
		throw std::logic_error("Odchylenie alphaX przekroczy³o wartoœæ pi/2.");
	if (model.alphaX < -1.57)
		throw std::logic_error("Odchylenie alphaX przekroczy³o wartoœæ -pi/2.");
	if (model.alphaY > 1.57)
		throw std::logic_error("Odchylenie alphaY przekroczy³o wartoœæ pi/2.");
	if (model.alphaY < -1.57)
		throw std::logic_error("Odchylenie alphaY przekroczy³o wartoœæ -pi/2.");
}
void Solver::Action()
{
	switch (params.solverType)
	{
		case Params::EULER: Euler(params.dt); break;
		case Params::RUNGE_KUTTA_4: RungeKutta(params.dt); break;
	}

	CheckErrs();
}