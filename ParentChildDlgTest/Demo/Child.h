#pragma once


// CChild 对话框

class CChild : public CDialog
{
	DECLARE_DYNAMIC(CChild)

public:
	CChild(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CChild();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()


public:
	virtual BOOL OnInitDialog();


private:
	static unsigned __stdcall ThreadProcSetting(void * pParam);
	void DealThreadProc();

	HANDLE                               m_hEventSetting;
	HANDLE                               m_hThreadSetting;

	bool								m_bExit;
	ULONGLONG							m_TickCount;
protected:
	virtual void PostNcDestroy();
public:
	afx_msg void OnClose();
protected:
	virtual void OnOK();
	virtual void OnCancel();
public:
	afx_msg void OnDestroy();
	afx_msg void OnNcDestroy();
};
