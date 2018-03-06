#include "model.h"

void Model::Add(const Model& arg, double factor)
{
	carX += factor * arg.carX;
	carY += factor * arg.carY;
	alphaX += factor * arg.alphaX;
	alphaY += factor * arg.alphaY;

	vcX += factor * arg.vcX;
	vcY += factor * arg.vcY;
	omegaX += factor * arg.omegaX;
	omegaY += factor * arg.omegaY;
}

double Model::bx(const Params& params)
{
	return -params.bX * vcX;
}
double Model::by(const Params& params)
{
	return -params.bY * vcY;
}
void Model::ComputeCosSinAlpha(const Params& params)
{
	sinAlphaX = sin(alphaX);
	sinAlphaY = sin(alphaY);
	double ss = sinAlphaX * sinAlphaX + sinAlphaY * sinAlphaY;
	cosAlpha = sqrt(1 - ss);
	sinAlpha = sqrt(ss);
}
void Model::ComputeLinearAccelerations(const Params& params)
{
	// obliczenie wspó³czynników uk³adu równañ (17)
	double B1 = params.m*sinAlphaX;
	double B2 = params.m*sinAlphaY;

	double A1 = ux + params.g*B1 * cosAlpha + bx(params);
	double A2 = uy + params.g*B2 * cosAlpha + by(params);
	
	double C1 = params.mC;
	double C2 = params.mC + params.mF;

	// obliczenie wspó³czynników równañ (22) i symetrycznego do (22)
	double A2B1mA1B2 = A2*B1 - A1*B2;
	double A1B2mA2B1 = -A2B1mA1B2;

	double AA = C1*C1*C2*C2 - C2*C2*B1*B1 - C1*C1*B2*B2;
	double BB1 = 2*(C1*B2*A2B1mA1B2 - A1*C1*C2*C2);
	double BB2 = 2*(C2*B1*A1B2mA2B1 - A2*C2*C1*C1);

	double A2B1mA1B2sqr = A2B1mA1B2 * A2B1mA1B2;
	double CC1 = A1*A1*C2*C2 + A2B1mA1B2sqr;
	double CC2 = A2*A2*C1*C1 + A2B1mA1B2sqr;

	if (AA != 0)
	{
		double Delta1 = BB1*BB1 - 4*AA*CC1;
		double Delta2 = BB2*BB2 - 4*AA*CC2;

		acX = (-BB1 - Delta1) / (2*AA);
		acY = (-BB2 - Delta2) / (2*AA);
	}
	else
	{
		if (BB1 == 0 || BB2 == 0)
			throw std::logic_error("Zero division error!");

		acX = -CC1 / BB1;
		acY = -CC2 / BB2;
	}
}
void Model::ComputeAngleAccelerations(const Params& params)
{
	double xySqr = sqrt(acX * acX + acY * acY);
	double gcsSqr = params.g * cosAlpha + sinAlpha * xySqr;
	epsilonX = (params.l * omegaX * omegaX * sinAlphaX - acX - sinAlphaX * gcsSqr) / (params.l * cos(alphaX));
	epsilonY = (params.l * omegaY * omegaY * sinAlphaY - acY - sinAlphaY * gcsSqr) / (params.l * cos(alphaY));
}
void Model::Step(const Params& params)
{
	ComputeCosSinAlpha(params);

	ComputeLinearAccelerations(params);
	ComputeAngleAccelerations(params);
}

void Model::Reset()
{
	ux = 0;
	uy = 0;

	carX = 0;
	carY = 0;
	alphaX = 0;
	alphaY = 0;

	vcX = 0;
	vcY = 0;
	omegaX = 0;
	omegaY = 0;

	acX = 0;
	acY = 0;
	epsilonX = 0;
	epsilonY = 0;

	sinAlphaX = 0;
	sinAlphaY = 0;
	cosAlpha = 1;
	sinAlpha = 0;
}