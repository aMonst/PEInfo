
// PEInfo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPEInfoApp:
// �йش����ʵ�֣������ PEInfo.cpp
//

class CPEInfoApp : public CWinAppEx
{
public:
	CPEInfoApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPEInfoApp theApp;