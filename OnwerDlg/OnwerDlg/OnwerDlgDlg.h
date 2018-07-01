
// OnwerDlgDlg.h : ͷ�ļ�
//

#pragma once

#include "ChildDlg.h"
#include "WinThreadLoading.h"


// COnwerDlgDlg �Ի���
class COnwerDlgDlg : public CDialog
{
// ����
public:
	COnwerDlgDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ONWERDLG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
