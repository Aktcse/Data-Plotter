#include "pch.h"0
//#include "stdafx.h"
#include "PlotInfo.h"

const int xmargin = 120;
const int tmargin = 80;
const int bmargin = 120;

PlotInfo::PlotInfo(void) :
	xmax(1000),
	xmin(0),
	ymax(3000),
	ymin(0),
	plotname("Plot Name"),
	xLabel("X Label"),
	yLabel("Y Label")
{
}


PlotInfo::~PlotInfo(void)
{
}

void PlotInfo::SetPlotArea()
{
	plotArea.SetRect(fullArea.left + xmargin, fullArea.top + tmargin, fullArea.right - xmargin, fullArea.bottom - bmargin);
}