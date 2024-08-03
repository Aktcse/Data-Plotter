
// MainFrm.cpp : implementation of the CMainFrame class
//

//#include "stdafx.h"
#include "pch.h"
#include "PlottingApp.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <afxwin.h>

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));

	return 0;
}

//const AFX_MSGMAP* CMainFrame::GetThisMessageMap()
//{
//	return nullptr;
//}
//
//const AFX_MSGMAP* CMainFrame::GetMessageMap() const
//{
//	return nullptr;
//}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CFrameWnd::PreCreateWindow(cs))
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style &= ~FWS_ADDTOTITLE;		// Set before adding Title
	cs.lpszName = _T("RADAR DATA PLOTTER");
	cs.style = WS_OVERLAPPED | WS_SYSMENU | WS_BORDER | WS_MAXIMIZEBOX | WS_MINIMIZEBOX;

	cs.cy = ::GetSystemMetrics(SM_CYSCREEN);
	cs.cx = ::GetSystemMetrics(SM_CXSCREEN);
	cs.y = (::GetSystemMetrics(SM_CYSCREEN) - cs.cy) / 2;
	cs.x = (::GetSystemMetrics(SM_CXSCREEN) - cs.cx) / 2;
	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG

// CMainFrame message handlers