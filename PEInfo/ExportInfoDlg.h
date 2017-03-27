#pragma once
#include "afxcmn.h"
#include "PeFileInfo.h"

// CExportInfoDlg �Ի���

class CExportInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CExportInfoDlg)

public:
	CExportInfoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CExportInfoDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	void InitInfo();
	afx_msg BOOL OnInitDialog();
	void ShowExportTableInfo();
	void ShowFunctionInfo();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_FuncInfoList;
	CPeFileInfo* m_pPeFileInfo;
};
