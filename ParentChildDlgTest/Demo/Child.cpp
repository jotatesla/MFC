// Child.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Demo.h"
#include "Child.h"


// CChild �Ի���

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
		sprintf_s(buf, "SetEvent��ʱ��%ld\n", GetTickCount64() - m_TickCount);
		OutputDebugString(buf);
	}

	if (m_hThreadSetting != INVALID_HANDLE_VALUE)
	{
		// �ȴ��߳�ִ���꣬�߳̾�����Զ��ͷ�
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


// CChild ��Ϣ�������

BOOL CChild::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	m_hEventSetting  = ::CreateEvent(NULL, FALSE, FALSE, NULL);
	m_hThreadSetting = (HANDLE)_beginthreadex(NULL, 0, ThreadProcSetting, (LPVOID)this, 0, NULL);


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
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
	sprintf_s(buf, "�߳��˳���ʱ��%ld\n", GetTickCount64() - m_TickCount);
	OutputDebugString(buf);
}


void CChild::PostNcDestroy()
{
	// TODO: �ڴ����ר�ô����/����û���
	CDialog::PostNcDestroy();

	delete this;
}

void CChild::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialog::OnClose();
}

void CChild::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	//CDialog::OnOK();
	DestroyWindow();
}

void CChild::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	//CDialog::OnCancel();
	DestroyWindow();
}

void CChild::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
}

void CChild::OnNcDestroy()
{
	CDialog::OnNcDestroy();

	// TODO: �ڴ˴������Ϣ����������
}
