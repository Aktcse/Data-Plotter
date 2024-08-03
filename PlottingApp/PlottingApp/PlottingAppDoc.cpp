// PlottingAppDoc.cpp : implementation of the CPlottingAppDoc class

//#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PlottingApp.h"
#endif

#include "pch.h"
#include "PlottingAppDoc.h"
#include <fstream>
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPlottingAppDoc

IMPLEMENT_DYNCREATE(CPlottingAppDoc, CDocument)

BEGIN_MESSAGE_MAP(CPlottingAppDoc, CDocument)
END_MESSAGE_MAP()


// CPlottingAppDoc construction/destruction

CPlottingAppDoc::CPlottingAppDoc() :
	m_data(),
	maxTime(0.0),
	minTime(0.0),
	maxRange(0.0),
	minRange(0.0),
	maxAzimuth(0.0),
	minAzimuth(360.0),
	maxElevation(0.0),
	minElevation(90.0)
{
	// TODO: add one-time construction code here

}

CPlottingAppDoc::~CPlottingAppDoc()
{
}

BOOL CPlottingAppDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CPlottingAppDoc serialization

void CPlottingAppDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CPlottingAppDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CPlottingAppDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

const AFX_MSGMAP* CPlottingAppDoc::GetThisMessageMap()
{
	return nullptr;
}

const AFX_MSGMAP* CPlottingAppDoc::GetMessageMap() const
{
	return nullptr;
}

void CPlottingAppDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl* pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CPlottingAppDoc diagnostics

#ifdef _DEBUG
void CPlottingAppDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPlottingAppDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

// CPlottingAppDoc commands
BOOL CPlottingAppDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	m_data.clear();
	ResetLimits();
	std::ifstream file(lpszPathName);
	int dummy = 0;
	int rSts = 0;
	int aSts = 0;
	while (!file.eof())
	{
		Measurement measEntry{};
		file >> measEntry.time >> measEntry.range >> measEntry.azimuth >> measEntry.elevation >> dummy >> rSts >> aSts;
		if ((rSts == 3 || rSts == 2) && aSts == 2)
		{
			m_data.AddPoint(measEntry);
			if (measEntry.time > maxTime)
				maxTime = measEntry.time;
			if (measEntry.time < minTime)
				minTime = measEntry.time;
			if (measEntry.range > maxRange)
				maxRange = measEntry.range;
			if (measEntry.range < minRange)
				minRange = measEntry.range;
			if (measEntry.azimuth > maxAzimuth)
				maxAzimuth = measEntry.azimuth;
			if (measEntry.azimuth < minAzimuth)
				minAzimuth = measEntry.azimuth;
			if (measEntry.elevation > maxElevation)
				maxElevation = measEntry.elevation;
			if (measEntry.elevation < minElevation)
				minElevation = measEntry.elevation;
		}
	}
	return TRUE;
}

double CPlottingAppDoc::normaliseMaxValue(double val, int limit) const
{
	//const int limit = 50;
	int abs = (val / limit);
	return (abs + 1) * limit;
}

double CPlottingAppDoc::normaliseMinValue(double val, int limit) const
{
	if (val == 0)
		return 0;
	int abs = (val / limit);
	return (abs <= 0) ? (abs - 1) * limit : abs * limit;
}