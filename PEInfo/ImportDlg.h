#pragma once
#include "afxcmn.h"
#include "PeFileInfo.h"

// CImportDlg �Ի���

class CImportDlg : public CDialog
{
	DECLARE_DYNAMIC(CImportDlg)
public:
	CImportDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CImportDlg();

// �Ի�������
	enum { IDD = IDD_IMPORT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	void InitImportTable();
	void ShowImportTable();
	BOOL IsEndOfTable(PIMAGE_IMPORT_DESCRIPTOR pImportTable);//������β��
	void ShowFunctionInfoByDllIndex(int nIndex); //����ѡ�е�dll��Ϣ����ʾ���еĺ���
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
