#pragma once

#ifdef _WIN32_WCE
#error "Windows CE 不支持 CDialog。"
#endif 
#include "PEFileInfo.h"
// CDataDirectoryDlg 对话框

class CDataDirectoryDlg : public CDialog
{
	DECLARE_DYNCREATE(CDataDirectoryDlg)

public:
	CDataDirectoryDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDataDirectoryDlg();
	void InitDataDirectory();
// 对话框数据
	enum { IDD = IDD_DATA_DIRECTORY_DLG, IDH = IDR_HTML_DATADIRECTORYDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()
public:
	CPeFileInfo *m_pPefileInfo;
	afx_msg void OnBnClickedBtnImportTable();
	afx_msg void OnBnClickedBtnExportTable();
};
