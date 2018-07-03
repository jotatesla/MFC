// Child.cpp : 实现文件
//

#include "stdafx.h"
#include "Demo.h"
#include "Child.h"


// CChild 对话框

IMPLEMENT_DYNAMIC(CChild, CDialog)

CChild::CChild(CWnd* pParent /*=NULL*/)
	: CDialog(CChild::IDD, pParent)
{

}

CChild::~CChild()
{
	if (m_hEventSetting != INVALID_HANDLE_VALUE)
	{
		char buf[64] = {0};
		m_TickCount = GetTickCount64();
		SetEvent(m_hEventSetting);
		sprintf_s(buf, "SetEvent耗时：%ld\n", GetTickCount64() - m_TickCount);
		OutputDebugString(buf);
	}

	if (m_hThreadSetting != INVALID_HANDLE_VALUE)
	{
		// 等待线程执行完，线程句柄会自动释放
		WaitForSingleObject(m_hThreadSetting, INFINITE);
	}

	CloseHandle(m_hEventSetting);
	m_hEventSetting = INVALID_HANDLE_VALUE;
}

void CChild::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CChild, CDialog)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_WM_NCDESTROY()
END_MESSAGE_MAP()


// CChild 消息处理程序

BOOL CChild::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_hEventSetting  = ::CreateEvent(NULL, FALSE, FALSE, NULL);
	m_hThreadSetting = (HANDLE)_beginthreadex(NULL, 0, ThreadProcSetting, (LPVOID)this, 0, NULL);


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

unsigned __stdcall CChild::ThreadProcSetting(void * pParam)
{
	CChild* pThis = (CChild*)pParam;
	if (pThis != NULL)
	{
		pThis->DealThreadProc();
	}

	return 1;
}

void CChild::DealThreadProc()
{
	while (WaitForSingleObject(m_hEventSetting, 1)  != WAIT_OBJECT_0)
	{
		Sleep(1);
		m_TickCount = GetTickCount64();
	}

	char buf[64] = {0};
	sprintf_s(buf, "线程退出耗时：%ld\n", GetTickCount64() - m_TickCount);
	OutputDebugString(buf);
}


void CChild::PostNcDestroy()
{
	// TODO: 在此添加专用代码和/或调用基类
	CDialog::PostNcDestroy();

	delete this;
}

void CChild::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnClose();
}

void CChild::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnOK();
	DestroyWindow();
}

void CChild::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnCancel();
	DestroyWindow();
}

void CChild::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}

void CChild::OnNcDestroy()
{
	CDialog::OnNcDestroy();

	// TODO: 在此处添加消息处理程序代码
}
