#pragma once
#include "afxcmn.h"
#include "PeFileInfo.h"

// CSectionTableDlg �Ի���

class CSectionTableDlg : public CDialog
{
	DECLARE_DYNAMIC(CSectionTableDlg)

public:
	CSectionTableDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSectionTableDlg();

// �Ի�������
	enum { IDD = IDD_DLG_SECTION_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	void ShowSectionInfo();
public:
	CListCtrl m_SectionInfoCtrl;
	CPeFileInfo *m_pPeFileInfo;
	virtual BOOL OnInitDialog();
};
