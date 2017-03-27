#pragma once

#ifdef _WIN32_WCE
#error "Windows CE ��֧�� CDialog��"
#endif 
#include "PEFileInfo.h"
// CDataDirectoryDlg �Ի���

class CDataDirectoryDlg : public CDialog
{
	DECLARE_DYNCREATE(CDataDirectoryDlg)

public:
	CDataDirectoryDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDataDirectoryDlg();
	void InitDataDirectory();
// �Ի�������
	enum { IDD = IDD_DATA_DIRECTORY_DLG, IDH = IDR_HTML_DATADIRECTORYDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()
public:
	CPeFileInfo *m_pPefileInfo;
	afx_msg void OnBnClickedBtnImportTable();
	afx_msg void OnBnClickedBtnExportTable();
};
