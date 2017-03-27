#pragma once
#include "afxcmn.h"
#include "PeFileInfo.h"

// CSectionTableDlg 对话框

class CSectionTableDlg : public CDialog
{
	DECLARE_DYNAMIC(CSectionTableDlg)

public:
	CSectionTableDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSectionTableDlg();

// 对话框数据
	enum { IDD = IDD_DLG_SECTION_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void ShowSectionInfo();
public:
	CListCtrl m_SectionInfoCtrl;
	CPeFileInfo *m_pPeFileInfo;
	virtual BOOL OnInitDialog();
};
