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

	// 设置显示时长，毫秒，大于0定时显示，等于0不显示，小于0一直显示
	bool SetShowTime(int nShowTimeLong);
	void SetOwner(CWnd* pWnd);

protected:
	virtual ~CWinThreadLoading();

	DECLARE_MESSAGE_MAP()

private:
	CLoadingDlg				m_LoadingDlg;
};

// 封装CWinThreadLoading的方法，方便调用
class  CGifLoading
{
public:
	CGifLoading();
	~CGifLoading();

	// 设置显示时长，毫秒，大于0定时显示，等于0不显示，小于0一直显示
	void SetShowTime(int nShowTimeLong);
	void SetOwner(CWnd* pWnd);

private:
	CWinThreadLoading*		m_pWndThread;
};