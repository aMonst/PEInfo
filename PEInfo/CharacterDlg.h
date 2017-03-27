#pragma once

#ifdef _WIN32_WCE
#error "Windows CE ��֧�� CDialog��"
#endif 

// CCharacterDlg �Ի���
#include "PeFileInfo.h"

class CCharacterDlg : public CDialog
{
	DECLARE_DYNCREATE(CCharacterDlg)

public:
	CCharacterDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCharacterDlg();
// ��д
	HRESULT OnButtonOK(IHTMLElement *pElement);
	HRESULT OnButtonCancel(IHTMLElement *pElement);

// �Ի�������
	enum { IDD = IDD_DIALOG1, IDH = IDR_HTML_CHARACTERDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	
	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()
public:
	CPeFileInfo *m_pPeFileInfo;
};
