// LoadingDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LoadingDlg.h"
#include "afxdialogex.h"


#define RES_ID_STATIC						2512				// ��̬����ԴID
#define BK_COLOR							RGB(240,240,240)			// ����ɫ��͸�������õ���
#define TIMER_ID_SHOW_TIME_LONG				5214


// CLoadingDlg �Ի���

IMPLEMENT_DYNAMIC(CLoadingDlg, CWnd)

CLoadingDlg::CLoadingDlg(CWnd* pParent /*=NULL*/)
	: m_pPictureEx(NULL)
	, m_nShowTimeLong(0)
	, m_nTimeTick(0)
	, m_hThread(NULL)
	, m_bExitThread(false)
{
	
}

CLoadingDlg::~CLoadingDlg()
{
	if (m_pPictureEx != NULL)
	{
		delete m_pPictureEx;
		m_pPictureEx = NULL;
	}
}


BEGIN_MESSAGE_MAP(CLoadingDlg, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CLoadingDlg ��Ϣ�������




void CLoadingDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()

	CBrush newBrush;
	CRect cliRect;
	GetClientRect(&cliRect);
	newBrush.CreateSolidBrush(BK_COLOR);
	dc.FillRect(&cliRect, &newBrush);
	newBrush.DeleteObject();
}

bool CLoadingDlg::CreateWnd()
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	m_hWnd = CreateWindow("#32770", "CLoadingDlg", WS_VISIBLE|WS_POPUP,0,0,300,200,0,0,0,0);
	if (m_hWnd == NULL)
	{
		return false;
	}

	CenterWindow();

	// ���ô����ö�
	//SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	//ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	HWND hWnd = GetSafeHwnd();
	SetWindowLong(GetSafeHwnd(), GWL_EXSTYLE, GetWindowLong(GetSafeHwnd(), GWL_EXSTYLE) | WS_EX_LAYERED);
	BOOL bRet = SetLayeredWindowAttributes(BK_COLOR, 0, LWA_COLORKEY);

	if (m_pPictureEx != NULL)
	{
		return FALSE;
	}

	m_pPictureEx = new CPictureEx();
	if (m_pPictureEx == NULL)
	{
		return FALSE;
	}

	//AFX_MANAGE_STATE(AfxGetStaticModuleState());
	m_pPictureEx->Create(NULL, WS_CHILD | WS_VISIBLE | SS_ENHMETAFILE, CRect(0, 0, 300, 200), this, RES_ID_STATIC);
	if (m_pPictureEx->Load(_T("./res/loading.gif")))
	//if (m_pPictureEx->Load(MAKEINTRESOURCE(IDR_GIFTYPE_CIRCLE), _T("GIFTYPE")))
	{
		m_pPictureEx->SetBkColor(BK_COLOR);
		m_pPictureEx->Draw();
	}

	return true;
}

void CLoadingDlg::DestroyWnd()
{
	m_bExitThread = true;
	if (m_hThread != NULL)
	{
		WaitForSingleObject(m_hThread, INFINITE);
		CloseHandle(m_hThread);
		m_hThread = NULL;
	}
	m_nShowTimeLong = 0;
	m_nTimeTick = 0;
	//OnOK();
	PostMessage(WM_QUIT,0,0);
}

bool CLoadingDlg::InitWnd()
{
	if (IsWindowVisible())
	{
		return true;
	}

	ShowWindow(SW_HIDE);
	// ��������߳�
	unsigned int nMonitorThdID = 0;
	m_hThread = (HANDLE)_beginthreadex(NULL, 0, MonitorThreadCallback, this, 0, &nMonitorThdID);
	if (m_hThread == NULL)
	{
		return false;
	}

	return true;
}


void CLoadingDlg::SetShowTime(int nShowTimeLong)
{
	m_nShowTimeLong = nShowTimeLong;
	m_nTimeTick = GetTickCount64();
}

unsigned int CALLBACK CLoadingDlg::MonitorThreadCallback(void* param)
{
	CLoadingDlg* pThis = (CLoadingDlg*)param;
	if (pThis != NULL)
	{
		pThis->MonitorThreadCallbackProc();
	}

	return 0;
}

void CLoadingDlg::MonitorThreadCallbackProc()
{
	while (!m_bExitThread)
	{
		bool bVisible = IsWindowVisible();
		if (m_nShowTimeLong == 0 && bVisible)
		{
			// ����0����ʾ
			ShowWindow(SW_HIDE);
		}
		else if (m_nShowTimeLong < 0 && !bVisible)
		{
			// С��0һֱ��ʾ
			ShowWindow(SW_SHOW);
		}
		else if (m_nShowTimeLong > 0)
		{
			// ����0��ʱ��ʾ
			if (!bVisible)
			{
				ShowWindow(SW_SHOW);
			}

			ULONGLONG nTimespan = GetTickCount64() - m_nTimeTick;
			if (nTimespan >= m_nShowTimeLong)
			{
				// ����ָ��ʱ��������
				m_nShowTimeLong = 0;
				m_nTimeTick = 0;
				ShowWindow(SW_HIDE);
			}
		}

		Sleep(1);
	}
}

