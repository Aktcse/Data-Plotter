// PlottingAppView.cpp : implementation of the CPlottingAppView class
//

//#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PlottingApp.h"
#endif

#include "Resource.h"
#include "pch.h"
#include "PlottingAppDoc.h"
#include "PlottingAppView.h"
#include "PlotData.h"
#include "PlotInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <afxwin.h>


// CPlottingAppView

IMPLEMENT_DYNCREATE(CPlottingAppView, CView)

BEGIN_MESSAGE_MAP(CPlottingAppView, CView)
	ON_COMMAND(ID_VIEW_RANGEVSTIME, &CPlottingAppView::OnViewRangevstime)
	ON_COMMAND(ID_VIEW_AZIMUTHVSTIME, &CPlottingAppView::OnViewAzimuthvstime)
	ON_COMMAND(ID_VIEW_ELI, &CPlottingAppView::OnViewEli)
END_MESSAGE_MAP()

// CPlottingAppView construction/destruction

CPlottingAppView::CPlottingAppView():
	m_plotinfo(),
	plotId(0)
{
	// TODO: add construction code here

}

CPlottingAppView::~CPlottingAppView()
{
}

BOOL CPlottingAppView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CPlottingAppView drawing

void CPlottingAppView::OnDraw(CDC* pDC)
{
	CPlottingAppDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	GetClientRect(&m_plotinfo.fullArea);
	
	DrawPlot(pDC);


	// TODO: add draw code for native data here
}


// CPlottingAppView diagnostics

#ifdef _DEBUG
void CPlottingAppView::AssertValid() const
{
	CView::AssertValid();
}

void CPlottingAppView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlottingAppDoc* CPlottingAppView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlottingAppDoc)));
	return (CPlottingAppDoc*)m_pDocument;
}
#endif //_DEBUG

//const AFX_MSGMAP* CPlottingAppView::GetThisMessageMap()
//{
//	return nullptr;
//}

//const AFX_MSGMAP* CPlottingAppView::GetMessageMap() const
//{
//	return nullptr;
//}

void CPlottingAppView::DrawPlot(CDC* pDC)
{
	SetPlotExtents();
	DrawBackground(pDC);
	DrawTextMarkings(pDC);
	PlotData(pDC);
}

void CPlottingAppView::DrawBackground(CDC* pDC)
{
	m_plotinfo.SetPlotArea();
	
	CPen rectPen(PS_SOLID, 2, RGB(10, 10, 10));	
	auto nOldPen = pDC->SelectObject(&rectPen);
	pDC->Rectangle(m_plotinfo.plotArea);
	pDC->SelectObject(nOldPen);

	const auto noOfDiv = 10;
	auto xDiv = m_plotinfo.plotArea.Width() / noOfDiv;
	auto yDiv = m_plotinfo.plotArea.Height() / noOfDiv;

	CPen gridPen(PS_DOT, 1, RGB(80, 80, 80));
	nOldPen = pDC->SelectObject(&gridPen);
	for(int i = 1; i < noOfDiv  ; ++i)
	{
		pDC->MoveTo(m_plotinfo.plotArea.left, m_plotinfo.plotArea.top + i * yDiv);
		pDC->LineTo(m_plotinfo.plotArea.right, m_plotinfo.plotArea.top + i * yDiv);
	}
	for(int i = 1; i < noOfDiv  ; ++i)
	{
		pDC->MoveTo(m_plotinfo.plotArea.left + i * xDiv, m_plotinfo.plotArea.bottom);
		pDC->LineTo(m_plotinfo.plotArea.left + i * xDiv, m_plotinfo.plotArea.top);
	}	
	pDC->SelectObject(nOldPen);

	//Scale markings
	CPen scalePen(PS_SOLID, 1, RGB(30, 30, 180));
	nOldPen = pDC->SelectObject(&scalePen);
	for(int i = 0; i < noOfDiv + 1 ; ++i)
	{
		pDC->MoveTo(m_plotinfo.plotArea.left - 10 , m_plotinfo.plotArea.top + i * yDiv);
		pDC->LineTo(m_plotinfo.plotArea.left - 25, m_plotinfo.plotArea.top + i * yDiv);
	}
	for(int i = 0; i < noOfDiv + 1 ; ++i)
	{
		pDC->MoveTo(m_plotinfo.plotArea.left + i * xDiv, m_plotinfo.plotArea.bottom + 10);
		pDC->LineTo(m_plotinfo.plotArea.left + i * xDiv, m_plotinfo.plotArea.bottom + 25);
	}	
	pDC->SelectObject(nOldPen);

	//value markings
	CFont textFont;
	textFont.CreatePointFont(100, _T("Cambria"));
	auto nOldFont = pDC->SelectObject(&textFont);
	pDC->SetTextColor(RGB(20, 160, 20));
	const auto xInterval = m_plotinfo.getXDiff() / noOfDiv;
	const auto yInterval = m_plotinfo.getYDiff() / noOfDiv;
	for(int i = 0; i < noOfDiv + 1 ; ++i)
	{
		CString string;
		string.Format(_T("%5.2lf"), m_plotinfo.GetYmax() - i * yInterval);
		pDC->TextOut(m_plotinfo.plotArea.left - 50 , m_plotinfo.plotArea.top + i * yDiv - 5, string);
		//pDC->LineTo(m_plotinfo.plotArea.left - 25, m_plotinfo.plotArea.top + i * yDiv);
	}
	for(int i = 0; i < noOfDiv + 1 ; ++i)
	{
		CString string;
		string.Format(_T("%5.2lf"), m_plotinfo.GetXmin() + i * xInterval);
		pDC->TextOut(m_plotinfo.plotArea.left + i * xDiv - 5, m_plotinfo.plotArea.bottom + 30, string);
		//pDC->LineTo(m_plotinfo.plotArea.left + i * xDiv, m_plotinfo.plotArea.bottom + 25);
	}
	pDC->SelectObject(nOldFont);
}

void CPlottingAppView::DrawTextMarkings(CDC* pDC)
{
	// Draw PlotName at Top
	CFont nameFont;
	nameFont.CreatePointFont(200, _T("Cambria"));
	auto nOldFont = pDC->SelectObject(&nameFont);
	pDC->SetTextColor(RGB(180, 20, 150));
	
	const auto width = (m_plotinfo.GetPlotName().GetLength() * 12) / 2 ;
	pDC->TextOut(m_plotinfo.fullArea.CenterPoint().x - width, m_plotinfo.fullArea.top + 30, m_plotinfo.GetPlotName());
	pDC->SelectObject(nOldFont);

	// Draw x axis label

	CFont labelFontx;                                    
	labelFontx.CreatePointFont(150, _T("Cambria"));
	nOldFont = pDC->SelectObject(&labelFontx);
	pDC->SetTextColor(RGB(180, 20, 150));
	
	const auto widthx = (m_plotinfo.GetXLabel().GetLength() * 12) / 2 ;
	pDC->TextOut(m_plotinfo.fullArea.CenterPoint().x - widthx, m_plotinfo.fullArea.bottom - 50, m_plotinfo.GetXLabel());
	pDC->SelectObject(nOldFont);

	// Draw y axis label

	CFont labelFonty; 
	LOGFONT lf ;
	::ZeroMemory(&lf,sizeof(lf));
	lf.lfHeight = 150 ;	
	lf.lfWeight = 150 ;
	lf.lfEscapement = 900 ;	// 90 degree displacement
	lf.lfOrientation =  900 ; // 90 degree displacement
	::lstrcpy(lf.lfFaceName,_T("Cambria"));
	labelFonty.CreatePointFontIndirect(&lf);
	nOldFont = pDC->SelectObject(&labelFonty);
	pDC->SetTextColor(RGB(180, 20, 150));

	const auto height = (m_plotinfo.GetYLabel().GetLength() * 5) / 2 ;
	pDC->TextOut(m_plotinfo.plotArea.left - 80 ,m_plotinfo.fullArea.CenterPoint().y + height, m_plotinfo.GetYLabel());
	pDC->SelectObject(nOldFont);
}

void CPlottingAppView::PlotData(CDC* pDC)
{
	CPen plotPen(PS_SOLID,2,RGB(200,0,0));
	auto nOldPen = pDC->SelectObject(&plotPen); 
	for(auto&& points : GetDocument()->GetData().GetMeasurements())
	{
		CPoint point;
		auto param = points.range / 1000;
		if(plotId == 1)
			param = points.azimuth - GetDocument()->GetMinAzimuth();
		if(plotId == 2)
			param = points.elevation - GetDocument()->GetMinElevation();
		point.x = static_cast<LONG>(m_plotinfo.plotArea.left + points.time * (m_plotinfo.plotArea.Width()/ m_plotinfo.getXDiff()));
		point.y = static_cast<LONG>(m_plotinfo.plotArea.bottom - param * (m_plotinfo.plotArea.Height()/ (m_plotinfo.getYDiff())));
		pDC->Ellipse(point.x - 2, point.y - 2, point.x + 2, point.y + 2 );
	}
	pDC->SelectObject(nOldPen);
}
// CPlottingAppView message handlers
void CPlottingAppView::SetPlotExtents()
{
	switch(plotId)
	{
	case 0:
		m_plotinfo.SetXmax(GetDocument()->GetMaxTime());
		m_plotinfo.SetXmin(GetDocument()->GetMinTime());
		m_plotinfo.SetYmax(GetDocument()->GetMaxRange());
		m_plotinfo.SetYmin(GetDocument()->GetMinRange());
		break;
	case 1:
		m_plotinfo.SetXmax(GetDocument()->GetMaxTime());
		m_plotinfo.SetXmin(GetDocument()->GetMinTime());
		m_plotinfo.SetYmax(GetDocument()->GetMaxAzimuth());
		m_plotinfo.SetYmin(GetDocument()->GetMinAzimuth());
		break;  
	case 2:
		m_plotinfo.SetXmax(GetDocument()->GetMaxTime());
		m_plotinfo.SetXmin(GetDocument()->GetMinTime());
		m_plotinfo.SetYmax(GetDocument()->GetMaxElevation());
		m_plotinfo.SetYmin(GetDocument()->GetMinElevation());
		break;
	default:
		break;
	}
	
}

void CPlottingAppView::OnViewRangevstime()
{
	// TODO: Add your command handler code here
	plotId = 0;	
	m_plotinfo.SetPlotName(_T("Range vs Time"));
	m_plotinfo.SetXLabel(_T("Time (seconds)"));
	m_plotinfo.SetYLabel(_T("Range (kilometers)"));
	Invalidate();
}


void CPlottingAppView::OnViewAzimuthvstime()
{
	// TODO: Add your command handler code here
	plotId = 1;
	//SetPlotExtents();
	m_plotinfo.SetPlotName(_T("Azimuth vs Time"));
	m_plotinfo.SetXLabel(_T("Time (seconds)"));
	m_plotinfo.SetYLabel(_T("Azimuth (degrees)"));
	CWnd::Invalidate();
}


void CPlottingAppView::OnViewEli()
{
	// TODO: Add your command handler code here
	plotId = 2;
	//SetPlotExtents();
	m_plotinfo.SetPlotName(_T("Elevation vs Time"));
	m_plotinfo.SetXLabel(_T("Time (seconds)"));
	m_plotinfo.SetYLabel(_T("Elevation (degrees)"));
	Invalidate();
}