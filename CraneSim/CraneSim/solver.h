#pragma once

#include "include.h"

#include "params.h"
#include "model.h"

class Solver
{
private:
	Model& model;
	Params& params;
	
public:
	Solver(Model& model, Params& params) : model(model), params(params) {}

public:
	void Euler(double dt);
	void RungeKutta(double dt);
	void CheckErrs();
	void Action();
};