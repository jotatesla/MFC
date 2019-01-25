// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <atltime.h>
using namespace std;

const int nArryKey[] = { 1,2,3,4,5 };

char EncryptChar(char c, int key)
{
	return c = c^key;
}

// 简单加密
string SimpleEncrypt(string& strValue, const int *pkey = nArryKey)
{
	string strRet;
	int len = strValue.length();//获取长度
	for (int i = 0; i < len; i++)
	{
		char ch = EncryptChar(strValue[i], pkey[i % 5]);
		strRet.push_back(ch);
	}

	return strRet;
}

const __int64 g_nCodeKey = 7460132889;

//单个字符异或运算
__int64 EncryptInt(__int64 nValue, __int64 nKey = g_nCodeKey)
{
	return nValue = nValue ^ nKey;
}

//单个字符解密
__int64 DecryptInt(__int64 nValue, __int64 nKey = g_nCodeKey)
{
	return nValue ^ g_nCodeKey;
}

int main()
{
	CTime time = CTime::GetCurrentTime();
	__int64 nCurTime = time.GetTime();
	//nCurTime = 7460132889;
	cout << nCurTime << endl;
	__int64 nCode = EncryptInt(nCurTime);
	cout << nCode << endl;
	cout << DecryptInt(nCode) << endl;

	system("pause");
	
    return 0;
}

