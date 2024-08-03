#pragma once
#include <vector>

struct Measurement
{
	double time;
	double range;
	double azimuth;
	double elevation;
};

class PlotData
{
public:
	PlotData(void);
	~PlotData(void);
	void AddPoint(const Measurement& meas);
	const std::vector<Measurement>& GetMeasurements() const;
	void clear()
	{
		measurements.clear();
	}
private:
	std::vector<Measurement> measurements;
};

