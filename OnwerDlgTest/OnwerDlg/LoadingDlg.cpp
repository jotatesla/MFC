// LoadingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LoadingDlg.h"
#include "afxdialogex.h"


#define RES_ID_STATIC						2512				// 静态框资源ID
#define BK_COLOR							RGB(240,240,240)			// 背景色（透明处理用到）
#define TIMER_ID_SHOW_TIME_LONG				5214


// CLoadingDlg 对话框

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


// CLoadingDlg 消息处理程序




void CLoadingDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialog::OnPaint()

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

	// 设置窗口置顶
	//SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	//ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);

	// TODO:  在此添加额外的初始化
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
	// 开启监控线程
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
			// 等于0不显示
			ShowWindow(SW_HIDE);
		}
		else if (m_nShowTimeLong < 0 && !bVisible)
		{
			// 小于0一直显示
			ShowWindow(SW_SHOW);
		}
		else if (m_nShowTimeLong > 0)
		{
			// 大于0定时显示
			if (!bVisible)
			{
				ShowWindow(SW_SHOW);
			}

			ULONGLONG nTimespan = GetTickCount64() - m_nTimeTick;
			if (nTimespan >= m_nShowTimeLong)
			{
				// 到达指定时长，隐藏
				m_nShowTimeLong = 0;
				m_nTimeTick = 0;
				ShowWindow(SW_HIDE);
			}
		}

		Sleep(1);
	}
}

