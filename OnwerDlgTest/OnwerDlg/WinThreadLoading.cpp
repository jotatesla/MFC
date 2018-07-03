#include "StdAfx.h"
#include "WinThreadLoading.h"


// CWinThreadLoading

IMPLEMENT_DYNCREATE(CWinThreadLoading, CWinThread)

CWinThreadLoading::CWinThreadLoading()
{}

CWinThreadLoading::~CWinThreadLoading()
{}

BOOL CWinThreadLoading::InitInstance()
{
	m_LoadingDlg.CreateWnd();
	m_pMainWnd = &m_LoadingDlg;
	m_LoadingDlg.InitWnd();

	return TRUE;
}

int CWinThreadLoading::ExitInstance()
{
	m_LoadingDlg.DestroyWnd();

	return CWinThread::ExitInstance();
}

bool CWinThreadLoading::SetShowTime(int nShowTimeLong)
{
	m_LoadingDlg.SetShowTime(nShowTimeLong);

	return true;
}

void CWinThreadLoading::SetOwner(CWnd* pWnd)
{
	m_LoadingDlg.SetOwner(pWnd);
}

BEGIN_MESSAGE_MAP(CWinThreadLoading, CWinThread)
END_MESSAGE_MAP()


CGifLoading::CGifLoading()
	: m_pWndThread(NULL)
{
	if (m_pWndThread == NULL)
	{
		// 返回的指针会自动删除
		m_pWndThread = (CWinThreadLoading*)AfxBeginThread(RUNTIME_CLASS(CWinThreadLoading));
	}
}

CGifLoading::~CGifLoading()
{
	if (m_pWndThread != NULL)
	{
		m_pWndThread->PostThreadMessage(WM_QUIT, 0, 0);
		WaitForSingleObject(m_pWndThread->m_hThread, INFINITE);
	}
}

void CGifLoading::SetShowTime(int nShowTimeLong)
{
	if (m_pWndThread != NULL)
	{
		m_pWndThread->SetShowTime(nShowTimeLong);
	}
}

void CGifLoading::SetOwner(CWnd* pWnd)
{
	if (m_pWndThread != NULL)
	{
		m_pWndThread->SetOwner(pWnd);
	}
}
