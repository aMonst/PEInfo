// DataDirectoryDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PEInfo.h"
#include "DataDirectoryDlg.h"
#include "ImportDlg.h"
#include "ExportInfoDlg.h"

// CDataDirectoryDlg 对话框

IMPLEMENT_DYNCREATE(CDataDirectoryDlg, CDialog)

CDataDirectoryDlg::CDataDirectoryDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDataDirectoryDlg::IDD, pParent)
{

}

CDataDirectoryDlg::~CDataDirectoryDlg()
{
}

void CDataDirectoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BOOL CDataDirectoryDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitDataDirectory();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

BEGIN_MESSAGE_MAP(CDataDirectoryDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_EXPORT_TABLE, &CDataDirectoryDlg::OnBnClickedBtnExportTable)
	ON_BN_CLICKED(IDC_BTN_IMPORT_TABLE, &CDataDirectoryDlg::OnBnClickedBtnImportTable)
END_MESSAGE_MAP()

BEGIN_DHTML_EVENT_MAP(CDataDirectoryDlg)
END_DHTML_EVENT_MAP()
void CDataDirectoryDlg::InitDataDirectory()
{
	if (NULL!= m_pPefileInfo)
	{
		m_pPefileInfo->InitDataDirectoryTable();
		vector<IMAGE_DATA_DIRECTORY_INFO> &DataDirectoryTable = m_pPefileInfo->GetDataDirectoryTable();
		CString strInfo = _T("");
		//ExportTable
		if (DataDirectoryTable[0].pVirtualAddress == 0)
		{
			SetDlgItemText(IDC_EXPORT_RVA, _T("0x00000000"));
			SetDlgItemText(IDC_EXPORT_SIZE, _T("0x00000000"));
			SetDlgItemText(IDC_EXPORT_OFFSET, _T("0x00000000"));
		}else
		{
			strInfo.Format(_T("0x%08x"), DataDirectoryTable[0].pVirtualAddress);
			SetDlgItemText(IDC_EXPORT_RVA, strInfo);
			strInfo.Format(_T("0x%08x"), DataDirectoryTable[0].dwVirtualSize);
			SetDlgItemText(IDC_EXPORT_SIZE, strInfo);
			strInfo.Format(_T("0x%08x"), DataDirectoryTable[0].pFileOffset);
			SetDlgItemText(IDC_EXPORT_OFFSET, strInfo);
		}
		
		//ImportTable
		if (DataDirectoryTable[1].pVirtualAddress == 0)
		{
			SetDlgItemText(IDC_IMPORT_RVA, _T("0x00000000"));
			SetDlgItemText(IDC_IMPORT_SIZE, _T("0x00000000"));
			SetDlgItemText(IDC_IMPORT_OFFSET, _T("0x00000000"));
		}else
		{
			strInfo.Format(_T("0x%08x"), DataDirectoryTable[1].pVirtualAddress);
			SetDlgItemText(IDC_IMPORT_RVA, strInfo);
			strInfo.Format(_T("0x%08x"), DataDirectoryTable[1].dwVirtualSize);
			SetDlgItemText(IDC_IMPORT_SIZE, strInfo);
			strInfo.Format(_T("0x%08x"), DataDirectoryTable[1].pFileOffset);
			SetDlgItemText(IDC_IMPORT_OFFSET, strInfo);
		}
		
		//Resource
		if (DataDirectoryTable[2].pVirtualAddress == 0)
		{
			SetDlgItemText(IDC_RES_RVA, _T("0x00000000"));
			SetDlgItemText(IDC_RES_SIZE, _T("0x00000000"));
			SetDlgItemText(IDC_RES_OFFSET, _T("0x00000000"));
		}else
		{
			strInfo.Format(_T("0x%08x"), DataDirectoryTable[2].pVirtualAddress);
			SetDlgItemText(IDC_RES_RVA, strInfo);
			strInfo.Format(_T("0x%08x"), DataDirectoryTable[2].dwVirtualSize);
			SetDlgItemText(IDC_RES_SIZE, strInfo);
			strInfo.Format(_T("0x%08x"), DataDirectoryTable[2].pFileOffset);
			SetDlgItemText(IDC_RES_OFFSET, strInfo);
		}

		//Exception
		if (DataDirectoryTable[3].pVirtualAddress == 0)
		{
			SetDlgItemText(IDC_EXCEPTION_RVA, _T("0x00000000"));
			SetDlgItemText(IDC_EXCEPTION_SIZE, _T("0x00000000"));
			SetDlgItemText(IDC_EXCEPTION_OFFSET, _T("0x00000000"));
		}else
		{
			strInfo.Format(_T("0x%08x"), DataDirectoryTable[3].pVirtualAddress);
			SetDlgItemText(IDC_EXCEPTION_RVA, strInfo);
			strInfo.Format(_T("0x%08x"), DataDirectoryTable[3].dwVirtualSize);
			SetDlgItemText(IDC_EXCEPTION_SIZE, strInfo);
			strInfo.Format(_T("0x%08x"), DataDirectoryTable[3].pFileOffset);
			SetDlgItemText(IDC_EXCEPTION_OFFSET, strInfo);

		}

		//Security
		if (DataDirectoryTable[4].pVirtualAddress == 0)
		{
			SetDlgItemText(IDC_SECURITY_RVA, _T("0x00000000"));
			SetDlgItemText(IDC_SECURITY_SIZE, _T("0x00000000"));
			SetDlgItemText(IDC_SECURITY_OFFSET, _T("0x00000000"));
		}else
		{
			strInfo.Format(_T("0x%08x"), DataDirectoryTable[4].pVirtualAddress);
			SetDlgItemText(IDC_SECURITY_RVA, strInfo);
			strInfo.Format(_T("0x%08x"), DataDirectoryTable[4].dwVirtualSize);
			SetDlgItemText(IDC_SECURITY_SIZE, strInfo);
			strInfo.Format(_T("0x%08x"), DataDirectoryTable[4].pFileOffset);
			SetDlgItemText(IDC_SECURITY_OFFSET, strInfo);

		}

		//Relocation
		if (DataDirectoryTable[4].pVirtualAddress == 0)
		{
			SetDlgItemText(IDC_RELOC_RVA, _T("0x00000000"));
			SetDlgItemText(IDC_RELOC_SIZE, _T("0x00000000"));
			SetDlgItemText(IDC_RELOC_OFFSET, _T("0x00000000"));
		}else
		{
			strInfo.Format(_T("0x%08x"), DataDirectoryTable[5].pVirtualAddress);
			SetDlgItemText(IDC_RELOC_RVA, strInfo);
			strInfo.Format(_T("0x%08x"), DataDirectoryTable[5].dwVirtualSize);
			SetDlgItemText(IDC_RELOC_SIZE, strInfo);
			strInfo.Format(_T("0x%08x"), DataDirectoryTable[5].pFileOffset);
			SetDlgItemText(IDC_RELOC_OFFSET, strInfo);
		}

		//Debug
		if (DataDirectoryTable[6].pVirtualAddress == 0)
		{
			SetDlgItemText(IDC_DEBUG_RVA, _T("0x00000000"));
			SetDlgItemText(IDC_DEBUG_SIZE, _T("0x00000000"));
			SetDlgItemText(IDC_DEBUG_OFFSET, _T("0x00000000"));
		}else
		{
			strInfo.Format(_T("0x%08x"), DataDirectoryTable[6].pVirtualAddress);
			SetDlgItemText(IDC_DEBUG_RVA, strInfo);
			strInfo.Format(_T("0x%08x"), DataDirectoryTable[6].dwVirtualSize);
			SetDlgItemText(IDC_DEBUG_SIZE, strInfo);
			strInfo.Format(_T("0x%08x"), DataDirectoryTable[6].pFileOffset);
			SetDlgItemText(IDC_DEBUG_OFFSET, strInfo);
		}

		//Copyright
		if (DataDirectoryTable[7].pVirtualAddress == 0)
		{
			SetDlgItemText(IDC_COPYRIGHT_RVA, _T("0x00000000"));
			SetDlgItemText(IDC_COPYRIGHT_SIZE, _T("0x00000000"));
			SetDlgItemText(IDC_COPYRIGHT_OFFSET, _T("0x00000000"));
		}else
		{
			strInfo.Format(_T("0x%08x"), DataDirectoryTable[7].pVirtualAddress);
			SetDlgItemText(IDC_COPYRIGHT_RVA, strInfo);
			strInfo.Format(_T("0x%08x"), DataDirectoryTable[7].dwVirtualSize);
			SetDlgItemText(IDC_COPYRIGHT_SIZE, strInfo);
			strInfo.Format(_T("0x%08x"), DataDirectoryTable[7].pFileOffset);
			SetDlgItemText(IDC_COPYRIGHT_OFFSET, strInfo);
		}


		//Globalprt
		if (DataDirectoryTable[8].pVirtualAddress == 0)
		{
			SetDlgItemText(IDC_GLOBAL_RVA, _T("0x00000000"));
			SetDlgItemText(IDC_GLOBAL_SIZE, _T("0x00000000"));
			SetDlgItemText(IDC_GLOBAL_OFFSET, _T("0x00000000"));
		}else
		{
			strInfo.Format(_T("0x%08x"), DataDirectoryTable[8].pVirtualAddress);
			SetDlgItemText(IDC_GLOBAL_RVA, strInfo);
			strInfo.Format(_T("0x%08x"), DataDirectoryTable[8].dwVirtualSize);
			SetDlgItemText(IDC_GLOBAL_SIZE, strInfo);
			strInfo.Format(_T("0x%08x"), DataDirectoryTable[8].pFileOffset);
			SetDlgItemText(IDC_GLOBAL_OFFSET, strInfo);
		}

		//TlsTable
		if (DataDirectoryTable[9].pVirtualAddress == 0)
		{
			SetDlgItemText(IDC_TLS_RVA, _T("0x00000000"));
			SetDlgItemText(IDC_TLS_SIZE, _T("0x00000000"));
			SetDlgItemText(IDC_TLS_OFFSET, _T("0x00000000"));
		}else
		{
			strInfo.Format(_T("0x%08x"), DataDirectoryTable[9].pVirtualAddress);
			SetDlgItemText(IDC_TLS_RVA, strInfo);
			strInfo.Format(_T("0x%08x"), DataDirectoryTable[9].dwVirtualSize);
			SetDlgItemText(IDC_TLS_SIZE, strInfo);
			strInfo.Format(_T("0x%08x"), DataDirectoryTable[9].pFileOffset);
			SetDlgItemText(IDC_TLS_OFFSET, strInfo);
		}


		//LocalConfig
		if (DataDirectoryTable[10].pVirtualAddress == 0)
		{
			SetDlgItemText(IDC_CONFIG_RVA, _T("0x00000000"));
			SetDlgItemText(IDC_CONFIG_SIZE, _T("0x00000000"));
			SetDlgItemText(IDC_CONFIG_OFFSET, _T("0x00000000"));
		}else
		{
			strInfo.Format(_T("0x%08x"), DataDirectoryTable[10].pVirtualAddress);
			SetDlgItemText(IDC_CONFIG_RVA, strInfo);
			strInfo.Format(_T("0x%08x"), DataDirectoryTable[10].dwVirtualSize);
			SetDlgItemText(IDC_CONFIG_SIZE, strInfo);
			strInfo.Format(_T("0x%08x"), DataDirectoryTable[10].pFileOffset);
			SetDlgItemText(IDC_CONFIG_OFFSET, strInfo);
		}


		//IAT
		if (DataDirectoryTable[11].pVirtualAddress == 0)
		{
			SetDlgItemText(IDC_IAT_RVA, _T("0x00000000"));
			SetDlgItemText(IDC_IAT_SIZE, _T("0x00000000"));
			SetDlgItemText(IDC_IAT_OFFSET, _T("0x00000000"));
		}else
		{
			strInfo.Format(_T("0x%08x"), DataDirectoryTable[11].pVirtualAddress);
			SetDlgItemText(IDC_IAT_RVA, strInfo);
			strInfo.Format(_T("0x%08x"), DataDirectoryTable[11].dwVirtualSize);
			SetDlgItemText(IDC_IAT_SIZE, strInfo);
			strInfo.Format(_T("0x%08x"), DataDirectoryTable[11].pFileOffset);
			SetDlgItemText(IDC_IAT_OFFSET, strInfo);
		}

		//BoundImport
		if (DataDirectoryTable[12].pVirtualAddress == 0)
		{
			SetDlgItemText(IDC_BOUND_RVA, _T("0x00000000"));
			SetDlgItemText(IDC_BOUND_SIZE, _T("0x00000000"));
			SetDlgItemText(IDC_BOUND_OFFSET, _T("0x00000000"));
		}else
		{
			strInfo.Format(_T("0x%08x"), DataDirectoryTable[12].pVirtualAddress);
			SetDlgItemText(IDC_BOUND_RVA, strInfo);
			strInfo.Format(_T("0x%08x"), DataDirectoryTable[12].dwVirtualSize);
			SetDlgItemText(IDC_BOUND_SIZE, strInfo);
			strInfo.Format(_T("0x%08x"), DataDirectoryTable[12].pFileOffset);
			SetDlgItemText(IDC_BOUND_OFFSET, strInfo);
		}

		//COM
		if (DataDirectoryTable[13].pVirtualAddress == 0)
		{
			SetDlgItemText(IDC_COM_RVA, _T("0x00000000"));
			SetDlgItemText(IDC_COM_SIZE, _T("0x00000000"));
			SetDlgItemText(IDC_COM_OFFSET, _T("0x00000000"));
		}else
		{
			strInfo.Format(_T("0x%08x"), DataDirectoryTable[13].pVirtualAddress);
			SetDlgItemText(IDC_COM_RVA, strInfo);
			strInfo.Format(_T("0x%08x"), DataDirectoryTable[13].dwVirtualSize);
			SetDlgItemText(IDC_COM_SIZE, strInfo);
			strInfo.Format(_T("0x%08x"), DataDirectoryTable[13].pFileOffset);
			SetDlgItemText(IDC_COM_OFFSET, strInfo);
		}

		//DelayImport
		if (DataDirectoryTable[14].pVirtualAddress == 0)
		{
			SetDlgItemText(IDC_DELAY_RVA, _T("0x00000000"));
			SetDlgItemText(IDC_DELAY_SIZE, _T("0x00000000"));
			SetDlgItemText(IDC_DELAY_OFFSET, _T("0x00000000"));
		}else
		{
			strInfo.Format(_T("0x%08x"), DataDirectoryTable[14].pVirtualAddress);
			SetDlgItemText(IDC_DELAY_RVA, strInfo);
			strInfo.Format(_T("0x%08x"), DataDirectoryTable[14].dwVirtualSize);
			SetDlgItemText(IDC_DELAY_SIZE, strInfo);
			strInfo.Format(_T("0x%08x"), DataDirectoryTable[14].pFileOffset);
			SetDlgItemText(IDC_DELAY_OFFSET, strInfo);

		}

		//NoUsse
		if (DataDirectoryTable[15].pVirtualAddress == 0)
		{
			SetDlgItemText(IDC_NOUSE_RVA, _T("0x00000000"));
			SetDlgItemText(IDC_NOUSE_SIZE, _T("0x00000000"));
			SetDlgItemText(IDC_NOUSE_OFFSET, _T("0x00000000"));
		}else
		{
			strInfo.Format(_T("0x%08x"), DataDirectoryTable[15].pVirtualAddress);
			SetDlgItemText(IDC_NOUSE_RVA, strInfo);
			strInfo.Format(_T("0x%08x"), DataDirectoryTable[15].dwVirtualSize);
			SetDlgItemText(IDC_NOUSE_SIZE, strInfo);
			strInfo.Format(_T("0x%08x"), DataDirectoryTable[15].pFileOffset);
			SetDlgItemText(IDC_NOUSE_OFFSET, strInfo);
		}
	}
}


// CDataDirectoryDlg 消息处理程序

void CDataDirectoryDlg::OnBnClickedBtnExportTable()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pPefileInfo->InitDataDirectoryTable();
	vector<IMAGE_DATA_DIRECTORY_INFO> &DataDirectoryTable = m_pPefileInfo->GetDataDirectoryTable();
	if(DataDirectoryTable[0].pVirtualAddress == 0)
	{
		MessageBox(_T("没有导出表"));
		return ;
	}

	CExportInfoDlg dlg;
	dlg.m_pPeFileInfo = m_pPefileInfo;
	dlg.DoModal();
}

void CDataDirectoryDlg::OnBnClickedBtnImportTable()
{
	// TODO: 在此添加控件通知处理程序代码
	vector<IMAGE_DATA_DIRECTORY_INFO> &DataDirectoryTable = m_pPefileInfo->GetDataDirectoryTable();
	if(DataDirectoryTable[1].pVirtualAddress == 0)
	{
		MessageBox(_T("没有导入表"));
		return;
	}
	CImportDlg dlg;
	dlg.m_pPeFileInfo = m_pPefileInfo;
	dlg.DoModal();
}
