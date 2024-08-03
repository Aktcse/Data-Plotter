
// PlottingApp.h : main header file for the PlottingApp application
//
#pragma once

#ifndef __AFXWIN_H__
#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols
#include "afxwinappex.h"

// CPlottingAppApp:
// See PlottingApp.cpp for the implementation of this class
//

class CPlottingAppApp : public CWinApp
{
public:
	CPlottingAppApp();
	CString m_bHiColorIcons;
	CContextMenuManager* GetContextMenuManager();

	// Overrides
public:
	virtual BOOL InitInstance();
	void OnFileOpen();
	bool operator==(const CPlottingAppApp& other) const;
	// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	//bool operator==(const CPlottingAppApp& other) const;
};

extern CPlottingAppApp theApp;
