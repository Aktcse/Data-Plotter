#include "pch.h"
//#include "stdafx.h"
#include "PlotData.h"


PlotData::PlotData(void)
{
}


PlotData::~PlotData(void)
{
}

void PlotData::AddPoint(const Measurement& meas)
{
	measurements.push_back(meas);
}

const std::vector<Measurement>& PlotData::GetMeasurements() const
{
	return measurements;
}