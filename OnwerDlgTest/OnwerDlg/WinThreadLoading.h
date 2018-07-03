#pragma once
#include "afxwin.h"
#include "LoadingDlg.h"


/////////////////////////////////////////////////////////////////////////////
// CMyUIThread thread

// #ifdef UICONTROL_EXPORTS
// #define UICONTROL_API    __declspec(dllexport)
// #else
// #define UICONTROL_API    __declspec(dllimport)
// #endif


class CWinThreadLoading : public CWinThread
{
	DECLARE_DYNCREATE(CWinThreadLoading)

protected:
	CWinThreadLoading();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	// ������ʾʱ�������룬����0��ʱ��ʾ������0����ʾ��С��0һֱ��ʾ
	bool SetShowTime(int nShowTimeLong);
	void SetOwner(CWnd* pWnd);

protected:
	virtual ~CWinThreadLoading();

	DECLARE_MESSAGE_MAP()

private:
	CLoadingDlg				m_LoadingDlg;
};

// ��װCWinThreadLoading�ķ������������
class  CGifLoading
{
public:
	CGifLoading();
	~CGifLoading();

	// ������ʾʱ�������룬����0��ʱ��ʾ������0����ʾ��С��0һֱ��ʾ
	void SetShowTime(int nShowTimeLong);
	void SetOwner(CWnd* pWnd);

private:
	CWinThreadLoading*		m_pWndThread;
};