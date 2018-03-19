#include "chart.h"

xChart::xChart(string title, string xlabel, string ylabel) : core(1680, 980)
{
    core.setPlotArea(50, 30, 1600, 900);

	core.addTitle(title.c_str());
	core.xAxis()->setTitle(xlabel.c_str());
	core.yAxis()->setTitle(ylabel.c_str());
}
void xChart::AddLine(const double* x, const double* y, size_t size, int color)
{
	LineLayer* layer = core.addLineLayer(DoubleArray(y, static_cast<int>(size)), color);
	layer->setXData(DoubleArray(x, static_cast<int>(size)));
}
void xChart::AddScatter(const double* x, const double* y, size_t size)
{
	core.addScatterLayer(DoubleArray(x, static_cast<int>(size)),
						 DoubleArray(y, static_cast<int>(size)));

}
void xChart::AutoAdjustAxes()
{
	core.xAxis()->setLinearScale();
	core.yAxis()->setLinearScale();
}
void xChart::AdjustAxes(double xMin, double xMax, double yMin, double yMax)
{
	core.xAxis()->setLinearScale(xMin, xMax);
	core.yAxis()->setLinearScale(yMin, yMax);
}
void xChart::Export(string name)
{
	core.makeChart((name + ".png").c_str());
}

xChart2::xChart2(string title, string xlabel, string ylabel, string zlabel) : core(1680, 980)
{
	core.addTitle(title.c_str());

	core.xAxis()->setTitle(xlabel.c_str());
	core.yAxis()->setTitle(ylabel.c_str());
	core.zAxis()->setTitle(zlabel.c_str());

	core.setPlotRegion(840, 490, 750, 750, 400);
}
void xChart2::SetData(const double* x, const double* y, const double* z, size_t size)
{
	core.addScatterGroup(DoubleArray(x, static_cast<int>(size)),
						 DoubleArray(y, static_cast<int>(size)),
						 DoubleArray(z, static_cast<int>(size)),
						 "", Chart::SolidSphereShape, 5, Chart::SameAsMainColor);
	//core.zAxis()->setLogScale1e-4, 1e2, 1.5);
}
void xChart2::Export(string name)
{
	core.makeChart((name+".png").c_str());
}

xChart3::xChart3(string title, string xlabel, string ylabel) : core(1680, 980)
{
	core.addTitle(title.c_str());

	core.xAxis()->setTitle(xlabel.c_str());
	core.yAxis()->setTitle(ylabel.c_str());

	core.xAxis()->setColors(Chart::Transparent);
	core.yAxis()->setColors(Chart::Transparent);

	core.setPlotArea(70, 100, 1600, 740);
}
void xChart3::SetData(const double* x, const double* y, const double* z, size_t size)
{
	ContourLayer* layer = core.addContourLayer(DoubleArray(x, static_cast<int>(size)),
											   DoubleArray(y, static_cast<int>(size)),
											   DoubleArray(z, static_cast<int>(size)));

	cAxis = layer->setColorAxis(840, 880, Chart::TopCenter, 1600, Chart::Top);
	cAxis->setBoundingBox(Chart::Transparent, Chart::LineColor);
}
void xChart3::SetLogScale(double bottom, double top, double tick)
{
	cAxis->setLogScale(bottom, top, tick);
}
void xChart3::Export(string name)
{
	core.makeChart((name+".png").c_str());
}

xChart4::xChart4(string title, string xlabel, string ylabel, string zlabel) : core(1680, 980)
{
	core.addTitle(title.c_str());

	core.xAxis()->setTitle(xlabel.c_str());
	core.yAxis()->setTitle(ylabel.c_str());
	core.zAxis()->setTitle(zlabel.c_str());

	core.setPlotRegion(840, 490, 750, 750, 400);
}
void xChart4::SetData(const double* x, const double* y, const double* z, size_t size)
{
	core.setData(DoubleArray(x, static_cast<int>(size)),
						 DoubleArray(y, static_cast<int>(size)),
						 DoubleArray(z, static_cast<int>(size)));
}
void xChart4::LogScale(bool mode)
{
	core.zAxis()->setLogScale(mode);
}
void xChart4::Export(string name)
{
	core.makeChart((name+".png").c_str());
}

Histogram::Histogram(string title, string xlabel, string ylabel) : core(1680, 980)
{
    core.setPlotArea(50, 30, 1600, 900);

	core.addTitle(title.c_str());
	core.xAxis()->setTitle(xlabel.c_str());
	core.yAxis()->setTitle(ylabel.c_str());
}
void Histogram::SetData(const double* x, size_t size, double xMin, double xMax, size_t barCount)
{
	std::vector<double> bar(barCount, 0);
	for (size_t i = 0; i < size; ++i)
	{
		size_t bNum = static_cast<size_t>(static_cast<double>(barCount) * (x[i] - xMin) / (xMax - xMin));

		if (bNum < bar.size())
			++bar[bNum];
	}

	BarLayer* layer = core.addBarLayer(DoubleArray(bar.data(), static_cast<int>(bar.size())));
	layer->setXData(xMin, xMax);
}
void Histogram::Export(string name)
{
	core.makeChart((name+".png").c_str());
}