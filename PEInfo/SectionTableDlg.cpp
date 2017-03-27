// SectionTableDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PEInfo.h"
#include "SectionTableDlg.h"


// CSectionTableDlg 对话框

IMPLEMENT_DYNAMIC(CSectionTableDlg, CDialog)

CSectionTableDlg::CSectionTableDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSectionTableDlg::IDD, pParent)
{

}

CSectionTableDlg::~CSectionTableDlg()
{
}

void CSectionTableDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SECTION, m_SectionInfoCtrl);
}


BEGIN_MESSAGE_MAP(CSectionTableDlg, CDialog)
END_MESSAGE_MAP()


// CSectionTableDlg 消息处理程序

BOOL CSectionTableDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_SectionInfoCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT );
	m_SectionInfoCtrl.InsertColumn(0, _T("Name"), LVCFMT_LEFT, 40); //名称
	m_SectionInfoCtrl.InsertColumn(1, _T("VAddress"), LVCFMT_LEFT, 80); //RVA
	m_SectionInfoCtrl.InsertColumn(2, _T("VSize"), LVCFMT_LEFT, 80);//在内存中的大小
	m_SectionInfoCtrl.InsertColumn(3, _T("ROffset"), LVCFMT_LEFT, 80);//在磁盘中的偏移
	m_SectionInfoCtrl.InsertColumn(4, _T("RSize"), LVCFMT_LEFT, 80);//在磁盘中的大小
	m_SectionInfoCtrl.InsertColumn(5, _T("Flags"), LVCFMT_LEFT, 80);//标志
	ShowSectionInfo();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CSectionTableDlg::ShowSectionInfo()
{
	if (NULL != m_pPeFileInfo)
	{
		vector<IMAGE_SECTION_HEADER> &SectionTable = m_pPeFileInfo->GetSectionTable();
		int i = 0;
		CString strInfo = _T("");
		for (vector<IMAGE_SECTION_HEADER>::iterator it = SectionTable.begin(); it != SectionTable.end(); it++)
		{
			#ifdef UNICODE
				WCHAR szName[10] = _T("");
				MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, (char*)(it->Name), IMAGE_SIZEOF_SHORT_NAME, szName, 10);
				m_SectionInfoCtrl.InsertItem(i, szName);
			#else
			m_SectionInfoCtrl.InsertItem(i, (TCHAR*)(it->Name));
			#endif

			strInfo.Format(_T("0x%08x"), it->VirtualAddress);
			m_SectionInfoCtrl.SetItemText(i, 1, strInfo);
			
			strInfo.Format(_T("0x%08x"), it->Misc.VirtualSize);
			m_SectionInfoCtrl.SetItemText(i, 2, strInfo);
			
			strInfo.Format(_T("0x%08x"), it->PointerToRawData);
			m_SectionInfoCtrl.SetItemText(i, 3, strInfo);

			strInfo.Format(_T("0x%08x"), it->SizeOfRawData);
			m_SectionInfoCtrl.SetItemText(i, 4, strInfo);

			strInfo.Format(_T("0x%08x"), it->Characteristics);
			m_SectionInfoCtrl.SetItemText(i, 5, strInfo);
			i++;
		}
	}
}
