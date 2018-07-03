/*************************************************
File Name	: LoadingDlg.h
Author		: shaoyiju
Version		: v1.00
DateTime	: 2018-06-21
Description : ʵ��һ��Loading����
*************************************************/

#ifndef _LOADINGDLG_H_
#define _LOADINGDLG_H_

#include "PictureEx.h"

// CLoadingDlg �Ի���

#define MY_DIALOG_ID_LOADING		5263

class CLoadingDlg : public CWnd
{
	DECLARE_DYNAMIC(CLoadingDlg)

public:
	CLoadingDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLoadingDlg();



protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnPaint();

	// �������ڣ�Ĭ�Ͼ������ö�
	bool CreateWnd();
	void DestroyWnd();

	// ��ʾ����
	bool InitWnd();

	// ������ʾʱ��
	void SetShowTime(int nShowTimeLong);

private:
	// ����߳�
	static unsigned int CALLBACK MonitorThreadCallback(void* param);
	void MonitorThreadCallbackProc();

	CPictureEx*			m_pPictureEx;
	int					m_nShowTimeLong;		// ��ʾʱ�������룬����0��ʱ��ʾ������0����ʾ��С��0һֱ��ʾ
	ULONGLONG			m_nTimeTick;
	HANDLE				m_hThread;
	bool				m_bExitThread;
	
};

#endif // _LOADINGDLG_H_