// ChildDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "OnwerDlg.h"
#include "ChildDlg.h"


// CChildDlg 对话框

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


// CChildDlg 消息处理程序
