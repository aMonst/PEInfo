#pragma once

#ifdef _WIN32_WCE
#error "Windows CE 不支持 CDialog。"
#endif 

// CCharacterDlg 对话框
#include "PeFileInfo.h"

class CCharacterDlg : public CDialog
{
	DECLARE_DYNCREATE(CCharacterDlg)

public:
	CCharacterDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCharacterDlg();
// 重写
	HRESULT OnButtonOK(IHTMLElement *pElement);
	HRESULT OnButtonCancel(IHTMLElement *pElement);

// 对话框数据
	enum { IDD = IDD_DIALOG1, IDH = IDR_HTML_CHARACTERDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	
	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()
public:
	CPeFileInfo *m_pPeFileInfo;
};
