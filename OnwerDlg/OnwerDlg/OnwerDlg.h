
// OnwerDlg.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// COnwerDlgApp:
// �йش����ʵ�֣������ OnwerDlg.cpp
//

class COnwerDlgApp : public CWinAppEx
{
public:
	COnwerDlgApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern COnwerDlgApp theApp;