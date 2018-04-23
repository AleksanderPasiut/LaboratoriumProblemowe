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
	return -params.bX[0] * vcX;// * abs(vcX);//atan(20 * vcX / params.bX[0]);
}
double Model::by(const Params& params)
{
	return -params.bY[0] * vcY;// * abs(vcY);//atan(20 * vcY / params.bY[0]);
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
	double A1 = ux * params.auxX + params.g * params.m * sinAlphaX * cosAlpha + bx(params);
	double A2 = uy * params.auxY + params.g * params.m * sinAlphaY * cosAlpha + by(params);

	double B1 = params.m*sinAlphaX * sinAlpha;
	double B2 = params.m*sinAlphaY * sinAlpha;

	double C1 = params.mF;// + params.mC;
	double C2 = params.mC;

	// obliczenie współczynników równania (23)
	double AA = B1*B1*C2*C2 + B2*B2*C1*C1 - C1*C1*C2*C2;
	double R0;
	if (AA != 0)
	{
		double Delta = A1*A1*C2*C2 + A2*A2*C1*C1 - (A1*B2 - A2*B1) * (A1*B2 - A2*B1);

		R0 = (- A1*B1*C2*C2 - A2*B2*C1*C1 - sqrt(Delta)) / AA;
	}
	else
	{
		R0 = -0.5 * (A1*A1*C2*C2 + A2*A2*C1*C1) / (A1*B1*C2*C2 + A2*B2*C1*C1);
	}
	
	acX = (A1 + B1*R0) / C1;
	acY = (A2 + B2*R0) / C2;
}
void Model::ComputeAngleAccelerations(const Params& params)
{
	double& acXscale = acX;
	double& acYscale = acY;
	double xySqr = sqrt(acXscale * acXscale + acYscale * acYscale);
	double gcsSqr = params.g * cosAlpha + sinAlpha * xySqr;
	epsilonX = (params.l * omegaX * omegaX * sinAlphaX - acXscale - sinAlphaX * gcsSqr) / (params.l * cos(alphaX));
	epsilonY = (params.l * omegaY * omegaY * sinAlphaY - acYscale - sinAlphaY * gcsSqr) / (params.l * cos(alphaY));
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