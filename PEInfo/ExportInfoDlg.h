#pragma once
#include "afxcmn.h"
#include "PeFileInfo.h"

// CExportInfoDlg 对话框

class CExportInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CExportInfoDlg)

public:
	CExportInfoDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CExportInfoDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void InitInfo();
	afx_msg BOOL OnInitDialog();
	void ShowExportTableInfo();
	void ShowFunctionInfo();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_FuncInfoList;
	CPeFileInfo* m_pPeFileInfo;
};
