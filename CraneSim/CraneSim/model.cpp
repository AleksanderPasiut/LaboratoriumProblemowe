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
	return -params.bX[0] * abs(params.bX[0]) * vcX;// * (1 + abs(params.bX[1]));
}
double Model::by(const Params& params)
{
	return -params.bY[0] * abs(params.bY[0]) * vcY;// * (1 + abs(params.bY[1]));
}
void Model::ComputeCosSinAlpha(const Params& params)
{
	sinAlphaX = sin(alphaX);
	sinAlphaY = sin(alphaY);
	double ss = sinAlphaX * sinAlphaX + sinAlphaY * sinAlphaY;
	cosAlpha = sqrt(1 - ss);
	sinAlpha = sqrt(ss);
}
bool Model::ChkEq(double A1, double A2, double B1, double B2, double C1, double C2, double epsilon)
{
	return  (abs(A1 + B1 * sqrt(acX * acX + acY * acY) - C1* acX) < epsilon) &&
			(abs(A2 + B2 * sqrt(acX * acX + acY * acY) - C2* acY) < epsilon);
}
void Model::ComputeLinearAccelerations(const Params& params)
{
	// obliczenie współczynników układu równań (18)
	double A1 = ux + params.g * params.m * sinAlphaX * cosAlpha + bx(params);
	double A2 = uy + params.g * params.m * sinAlphaY * cosAlpha + by(params);

	double B1 = params.m*sinAlphaX * sinAlpha;
	double B2 = params.m*sinAlphaY * sinAlpha;

	double C1 = params.mC + params.mF;
	double C2 = params.mC;

	// obliczenie współczynników równań (23) i symetrycznego do (24)
	double A2B1mA1B2 = A2*B1 - A1*B2;
	double A1B2mA2B1 = -A2B1mA1B2;

	double AA = C1*C1*C2*C2 - C2*C2*B1*B1 - C1*C1*B2*B2;
	double BB1 = 2*(C1*B2*A1B2mA2B1 - A1*C1*C2*C2);
	double BB2 = 2*(C2*B1*A2B1mA1B2 - A2*C2*C1*C1);

	double A2B1mA1B2sqr = A2B1mA1B2 * A2B1mA1B2;
	double CC1 = A1*A1*C2*C2 - A2B1mA1B2sqr;
	double CC2 = A2*A2*C1*C1 - A2B1mA1B2sqr;

	if (AA != 0)
	{
		double Delta1 = sqrt(BB1*BB1 - 4*AA*CC1);
		double Delta2 = sqrt(BB2*BB2 - 4*AA*CC2);

		if (std::isnan(Delta1))
			Delta1 = 0;

		if (std::isnan(Delta2))
			Delta2 = 0;

		acX = (-BB1 - Delta1) / (2*AA);
		acY = (-BB2 - Delta2) / (2*AA);

		if (ChkEq(A1, A2, B1, B2, C1, C2, 0.1))
			return;

		acX = (-BB1 + Delta1) / (2*AA);
		acY = (-BB2 - Delta2) / (2*AA);

		if (ChkEq(A1, A2, B1, B2, C1, C2, 0.1))
			return;

		acX = (-BB1 - Delta1) / (2*AA);
		acY = (-BB2 + Delta2) / (2*AA);

		if (ChkEq(A1, A2, B1, B2, C1, C2, 0.1))
			return;

		acX = (-BB1 + Delta1) / (2*AA);
		acY = (-BB2 + Delta2) / (2*AA);

		if (!ChkEq(A1, A2, B1, B2, C1, C2, 0.1))
			throw std::logic_error("No solution fits the soe solutions. :(");
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
	double xySqr = sqrt(acX * acX * params.auxX * params.auxX + acY * acY * params.auxY * params.auxY);
	double gcsSqr = params.g * cosAlpha + sinAlpha * xySqr;
	epsilonX = (params.l * omegaX * omegaX * sinAlphaX - acX * params.auxX - sinAlphaX * gcsSqr) / (params.l * cos(alphaX));
	epsilonY = (params.l * omegaY * omegaY * sinAlphaY - acY * params.auxY - sinAlphaY * gcsSqr) / (params.l * cos(alphaY));
}
void Model::Step(const Params& params)
{
	ComputeCosSinAlpha(params);

	ComputeLinearAccelerations(params);
	ComputeAngleAccelerations(params);
}

void Model::Reset(const Params& params)
{
	ux = 0;
	uy = 0;

	carX = params.x0;
	carY = params.y0;
	alphaX = params.ax0;
	alphaY = params.ay0;

	vcX = params.vx0;
	vcY = params.vy0;
	omegaX = params.wx0;
	omegaY = params.wy0;

	acX = 0;
	acY = 0;
	epsilonX = 0;
	epsilonY = 0;

	sinAlphaX = 0;
	sinAlphaY = 0;
	cosAlpha = 1;
	sinAlpha = 0;
}