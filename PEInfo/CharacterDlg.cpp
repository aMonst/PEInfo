// CharacterDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PEInfo.h"
#include "CharacterDlg.h"


// CCharacterDlg 对话框

IMPLEMENT_DYNCREATE(CCharacterDlg, CDialog)

CCharacterDlg::CCharacterDlg(CWnd* pParent /*=NULL*/)
:CDialog(CCharacterDlg::IDD, pParent)
{
}

CCharacterDlg::~CCharacterDlg()
{
}

void CCharacterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BOOL CCharacterDlg::OnInitDialog()
{
	if (NULL != m_pPeFileInfo)
	{
		CString strCharacter = _T("");
		m_pPeFileInfo->GetFileCharacteristics(strCharacter);
		SetDlgItemText(IDC_CHAR, strCharacter);
	}
	CDialog::OnInitDialog();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

BEGIN_MESSAGE_MAP(CCharacterDlg, CDialog)
END_MESSAGE_MAP()

BEGIN_DHTML_EVENT_MAP(CCharacterDlg)
END_DHTML_EVENT_MAP()



// CCharacterDlg 消息处理程序

HRESULT CCharacterDlg::OnButtonOK(IHTMLElement* /*pElement*/)
{
	OnOK();
	return S_OK;
}

HRESULT CCharacterDlg::OnButtonCancel(IHTMLElement* /*pElement*/)
{
	OnCancel();
	return S_OK;
}
