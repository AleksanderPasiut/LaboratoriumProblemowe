#pragma once

#include "include.h"
#include "stage.h"
#include "model.h"
#include "progressBar.h"

#include <thread>

class Identifier
{
private:
	Model& model;
	Params& params;

	void Core();
public:
	Identifier(Model& model, Params& params) : model(model), params(params)
	{
		
	}
	void Launch()
	{
		std::thread th(&Identifier::Core, this);
		ProgressBar pb;
		th.join();
		pb.Close();
	}
};