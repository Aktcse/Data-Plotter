
// PlottingApp.cpp : Defines the class behaviors for the application.
//

//#include "stdafx.h"
#include "pch.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "PlottingApp.h"
#include "MainFrm.h"

#include "PlottingAppDoc.h"
#include "PlottingAppView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlottingAppApp

BEGIN_MESSAGE_MAP(CPlottingAppApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CPlottingAppApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CPlottingAppApp::OnFileOpen)
END_MESSAGE_MAP()


// CPlottingAppApp construction

CPlottingAppApp::CPlottingAppApp()
{
	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("PlottingApp.AppID.NoVersion"));

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	m_bHiColorIcons = _T("");
}

CContextMenuManager* CPlottingAppApp::GetContextMenuManager()
{
	return nullptr;
}

// The one and only CPlottingAppApp object

CPlottingAppApp theApp;


// CPlottingAppApp initialization

BOOL CPlottingAppApp::InitInstance()
{
	CWinApp::InitInstance();


	EnableTaskbarInteraction(FALSE);

	// AfxInitRichEdit2() is required to use RichEdit control	
	// AfxInitRichEdit2();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)


	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CPlottingAppDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CPlottingAppView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

// CPlottingAppApp message handlers


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

//const AFX_MSGMAP* CAboutDlg::GetThisMessageMap()
//{
//	return nullptr;
//}
//
//const AFX_MSGMAP* CAboutDlg::GetMessageMap() const
//{
//	return nullptr;
//}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// App command to run the dialog
void CPlottingAppApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

//const AFX_MSGMAP* CPlottingAppApp::GetThisMessageMap()
//{
//	return nullptr;
//}
//
//const AFX_MSGMAP* CPlottingAppApp::GetMessageMap() const
//{
//	return nullptr;
//}

//const AFX_MSGMAP* CPlottingAppApp::GetThisMessageMap()
//{
//	return nullptr;
//}
//
//const AFX_MSGMAP* CPlottingAppApp::GetMessageMap() const
//{
//	return nullptr;
//}

// CPlottingAppApp message handlers

void CPlottingAppApp::OnFileOpen()
{
	CFileDialog fileDlg(TRUE);
	if (fileDlg.DoModal() == IDOK)
	{
		CString path = fileDlg.GetPathName();

		auto pDoc = ((CFrameWnd*)AfxGetMainWnd())->GetActiveDocument();
		if (pDoc)
		{
			(CPlottingAppDoc*)pDoc->OnOpenDocument(path);
		}
	}
	//((CFrameWnd*)AfxGetMainWnd())->GetActiveView()->Invalidate();
}



bool CPlottingAppApp::operator==(const CPlottingAppApp& other) const
{
	return false;
}
