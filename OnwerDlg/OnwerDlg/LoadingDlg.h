/*************************************************
File Name	: LoadingDlg.h
Author		: shaoyiju
Version		: v1.00
DateTime	: 2018-06-21
Description : 实现一个Loading动画
*************************************************/

#ifndef _LOADINGDLG_H_
#define _LOADINGDLG_H_

#include "PictureEx.h"

// CLoadingDlg 对话框

#define MY_DIALOG_ID_LOADING		5263

class CLoadingDlg : public CWnd
{
	DECLARE_DYNAMIC(CLoadingDlg)

public:
	CLoadingDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLoadingDlg();



protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnPaint();

	// 创建窗口，默认居中且置顶
	bool CreateWnd();
	void DestroyWnd();

	// 显示窗口
	bool InitWnd();

	// 设置显示时长
	void SetShowTime(int nShowTimeLong);

private:
	// 监控线程
	static unsigned int CALLBACK MonitorThreadCallback(void* param);
	void MonitorThreadCallbackProc();

	CPictureEx*			m_pPictureEx;
	int					m_nShowTimeLong;		// 显示时长，毫秒，大于0定时显示，等于0不显示，小于0一直显示
	ULONGLONG			m_nTimeTick;
	HANDLE				m_hThread;
	bool				m_bExitThread;
	
};

#endif // _LOADINGDLG_H_