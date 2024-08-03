
// PlottingAppDoc.h : interface of the CPlottingAppDoc class
//


#pragma once
#include "PlotData.h"

class CPlottingAppDoc : public CDocument
{
protected: // create from serialization only
	CPlottingAppDoc();
	DECLARE_DYNCREATE(CPlottingAppDoc)

	// Attributes
public:

	// Operations
public:
	const PlotData& GetData() const {
		return m_data;
	}
	double GetMaxTime() const {
		return normaliseMaxValue(maxTime, 5);
	}
	double GetMinTime() const {
		return minTime;
	}
	double GetMaxRange() const {
		return normaliseMaxValue(maxRange / 1000, 5);
	}
	double GetMinRange() const {
		return minRange / 1000;
	}
	double GetMaxAzimuth() const {
		return normaliseMaxValue(maxAzimuth, 2);
	}
	double GetMinAzimuth() const {
		return normaliseMinValue(minAzimuth, 2);
	}
	double GetMaxElevation() const {
		return normaliseMaxValue(maxElevation, 2);
	}
	double GetMinElevation() const {
		return normaliseMinValue(minElevation, 2);
	}
	void ResetLimits() {
		maxTime = 0;
		minTime = 0;
		maxRange = 0;
		minRange = 0;
		maxAzimuth = 0;
		minAzimuth = 360;
		maxElevation = 0;
		minElevation = 90;
	}
	double normaliseMaxValue(double val, int limit) const;
	double normaliseMinValue(double val, int limit) const;
	// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

	// Implementation
public:
	virtual ~CPlottingAppDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
private:
	PlotData m_data;
	double maxTime;
	double minTime;
	double maxRange;
	double minRange;
	double maxAzimuth;
	double minAzimuth;
	double maxElevation;
	double minElevation;
};
