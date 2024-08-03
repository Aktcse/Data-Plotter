
// PlottingAppView.h : interface of the CPlottingAppView class
//

#pragma once
#include "PlotInfo.h"
#include "Resource.h"

class CPlottingAppView : public CView
{
protected: // create from serialization only
	CPlottingAppView();
	DECLARE_DYNCREATE(CPlottingAppView);

	// Attributes;;
public:
	CPlottingAppDoc* GetDocument() const;

	// Operations
public:

	// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

	// Implementation
public:
	virtual ~CPlottingAppView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP();
private:
	PlotInfo m_plotinfo;
	UINT plotId;
private:
	void DrawPlot(CDC* pDC);
	void DrawBackground(CDC* pDC);
	void DrawTextMarkings(CDC* pDC);
	void PlotData(CDC* pDC);
	void SetPlotExtents();
public:
	afx_msg void OnViewRangevstime();
	afx_msg void OnViewAzimuthvstime();
	afx_msg void OnViewEli();
};

#ifndef _DEBUG  // debug version in PlottingAppView.cpp
inline CPlottingAppDoc* CPlottingAppView::GetDocument() const
{
	return reinterpret_cast<CPlottingAppDoc*>(m_pDocument);
}
#endif

