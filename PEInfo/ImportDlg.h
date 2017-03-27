#pragma once
#include "afxcmn.h"
#include "PeFileInfo.h"

// CImportDlg 对话框

class CImportDlg : public CDialog
{
	DECLARE_DYNAMIC(CImportDlg)
public:
	CImportDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CImportDlg();

// 对话框数据
	enum { IDD = IDD_IMPORT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void InitImportTable();
	void ShowImportTable();
	BOOL IsEndOfTable(PIMAGE_IMPORT_DESCRIPTOR pImportTable);//到达表的尾部
	void ShowFunctionInfoByDllIndex(int nIndex); //根据选中的dll信息，显示其中的函数
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ImportList;
	CListCtrl m_TunkList;
	virtual BOOL OnInitDialog();
	CPeFileInfo* m_pPeFileInfo;
protected:
	vector<IMAGE_IMPORT_DESCRIPTOR> m_ImportTable;
public:
	afx_msg void OnNMClickImportList(NMHDR *pNMHDR, LRESULT *pResult);
};
