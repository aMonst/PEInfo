// CharacterDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PEInfo.h"
#include "CharacterDlg.h"


// CCharacterDlg �Ի���

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
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

BEGIN_MESSAGE_MAP(CCharacterDlg, CDialog)
END_MESSAGE_MAP()

BEGIN_DHTML_EVENT_MAP(CCharacterDlg)
END_DHTML_EVENT_MAP()



// CCharacterDlg ��Ϣ�������

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
