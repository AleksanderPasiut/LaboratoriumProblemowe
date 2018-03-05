#include "stage.h"

Stage::Stage() :
	ux(0.1),
	uy(0),
	carX(0),
	carY(0),
	alphaX(0),
	alphaY(0),
	vcX(0),
	vcY(0),
	omegaX(0),
	omegaY(0),
	acX(0),
	acY(0),
	epsilonX(0),
	epsilonY(0),
	l(0.7),
	m(0.5),
	mF(3),
	mC(1),
	g(9.81),
	bX(10),
	bY(20)
{

}
void Stage::ResetPos()
{
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
}
void Stage::Action(double dt)
{
	ComputeCosSinAlpha();

	ComputeLinearAccelerations();
	ComputeAngleAccelerations();
	
	IntegrateAccelerations(dt);
	IntegrateVelocities(dt);

	fence.SetPos(carY);
	carriage.SetPos(carX, carY);
	mass.SetPos(carX, carY, alphaX, alphaY, l);
}

double Stage::bx(double v)
{
	return - bX * v;
}
double Stage::by(double v)
{
	return - bY * v;
}
void Stage::ComputeCosSinAlpha()
{
	sinAlphaX = sin(alphaX);
	sinAlphaY = sin(alphaY);
	double ss = sinAlphaX * sinAlphaX + sinAlphaY * sinAlphaY;
	cosAlpha = sqrt(1 - ss);
	sinAlpha = sqrt(ss);
}
void Stage::ComputeLinearAccelerations()
{
	// obliczenie wspó³czynników uk³adu równañ (17)
	double B1 = m*sinAlphaX;
	double B2 = m*sinAlphaY;

	double A1 = ux + g*B1 * cosAlpha + bx(vcX);
	double A2 = uy + g*B2 * cosAlpha + by(vcY);
	
	double C1 = mC;
	double C2 = mC + mF;

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
void Stage::ComputeAngleAccelerations()
{
	double xySqr = sqrt(acX * acX + acY * acY);
	double gcsSqr = g * cosAlpha + sinAlpha * xySqr;
	epsilonX = (l * omegaX * omegaX * sinAlphaX - acX - sinAlphaX * gcsSqr) / (l * cos(alphaX));
	epsilonY = (l * omegaY * omegaY * sinAlphaY - acY - sinAlphaY * gcsSqr) / (l * cos(alphaY));
}
void Stage::IntegrateAccelerations(double dt)
{
	vcX += acX * dt;
	vcY += acY * dt;
	omegaX += epsilonX * dt;
	omegaY += epsilonY * dt;
}
void Stage::IntegrateVelocities(double dt)
{
	carX += vcX * dt;
	carY += vcY * dt;
	alphaX += omegaX * dt;
	alphaY += omegaY * dt;

	if (alphaX > 1.57)
		throw std::logic_error("Odchylenie alphaX przekroczy³o wartoœæ pi/2.");
	if (alphaX < -1.57)
		throw std::logic_error("Odchylenie alphaX przekroczy³o wartoœæ -pi/2.");
	if (alphaY > 1.57)
		throw std::logic_error("Odchylenie alphaY przekroczy³o wartoœæ pi/2.");
	if (alphaY < -1.57)
		throw std::logic_error("Odchylenie alphaY przekroczy³o wartoœæ -pi/2.");

}
void Stage::Control(double ux, double uy, double u1, double u2)
{
	this->ux = ux;
	this->uy = uy;
}
void Stage::Render(CustomScene& scene, Shapes& shapes, Materials& materials) const
{
	frame.Render(scene, shapes, materials);
	fence.Render(scene, shapes, materials);
	carriage.Render(scene, shapes, materials);
	mass.Render(scene, shapes, materials);
}

void Stage::SetControlsWindow(HWND hwnd)
{
	controlsWindow = hwnd;
}
void Stage::StartAction()
{
	SetTimer(controlsWindow, reinterpret_cast<UINT_PTR>(this), 10, &Stage::ActionTimer);
}
void Stage::StopAction()
{
	KillTimer(controlsWindow, reinterpret_cast<UINT_PTR>(this));
}
void CALLBACK Stage::ActionTimer(HWND hwnd, UINT uMsg, UINT_PTR idParam, DWORD dwTime)
{
	Stage* stage = reinterpret_cast<Stage*>(idParam);

	try
	{
		stage->Action(0.01f);	
	}
	catch (std::exception& e)
	{
		stage->StopAction();
		MessageBoxA(0, e.what(), "Error!", MB_OK);
		stage->ResetPos();
		stage->StartAction();
	}
}