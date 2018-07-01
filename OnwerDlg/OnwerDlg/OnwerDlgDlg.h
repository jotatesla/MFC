
// OnwerDlgDlg.h : 头文件
//

#pragma once

#include "ChildDlg.h"
#include "WinThreadLoading.h"


// COnwerDlgDlg 对话框
class COnwerDlgDlg : public CDialog
{
// 构造
public:
	COnwerDlgDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_ONWERDLG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();


	CChildDlg		m_OwnerChildDlg;
	CChildDlg		m_ParentChildDlg;
	CGifLoading		m_loadingDlg;
};
