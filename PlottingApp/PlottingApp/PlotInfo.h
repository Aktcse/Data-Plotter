#pragma once
#include <atltypes.h>
#include <afxstr.h>
class PlotInfo
{
public:
	PlotInfo(void);
	~PlotInfo(void);
	void SetPlotArea();
	CRect fullArea;
	CRect plotArea;
	double GetXmax() const {
		return xmax;
	}
	double GetXmin() const {
		return xmin;
	}
	double GetYmax() const {
		return ymax;
	}
	double GetYmin() const {
		return ymin;
	}
	void SetXmax(double val)
	{
		xmax = val;
	}
	void SetXmin(double val)
	{
		xmin = val;
	}
	void SetYmax(double val)
	{
		ymax = val;
	}
	void SetYmin(double val)
	{
		ymin = val;
	}
	double getXDiff() const {
		return xmax - xmin;
	}
	double getYDiff() const {
		return ymax - ymin;
	}
	CString GetPlotName() const {
		return plotname;
	}
	void SetPlotName(CString string) {
		plotname = string;
	}
	CString GetXLabel() const {
		return xLabel;
	}
	void SetXLabel(CString string) {
		xLabel = string;
	}
	CString GetYLabel() const {
		return yLabel;
	}
	void SetYLabel(CString string) {
		yLabel = string;
	}
private:
	double xmax;
	double xmin;
	double ymax;
	double ymin;
	CString plotname;
	CString xLabel;
	CString yLabel;
};

