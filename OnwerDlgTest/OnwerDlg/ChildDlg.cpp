// ChildDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OnwerDlg.h"
#include "ChildDlg.h"


// CChildDlg �Ի���

IMPLEMENT_DYNAMIC(CChildDlg, CDialog)

CChildDlg::CChildDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChildDlg::IDD, pParent)
{

}

CChildDlg::~CChildDlg()
{
}

void CChildDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CChildDlg, CDialog)
END_MESSAGE_MAP()


// CChildDlg ��Ϣ�������
