// ExportInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PEInfo.h"
#include "ExportInfoDlg.h"


// CExportInfoDlg 对话框

IMPLEMENT_DYNAMIC(CExportInfoDlg, CDialog)

CExportInfoDlg::CExportInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CExportInfoDlg::IDD, pParent)
{

}

CExportInfoDlg::~CExportInfoDlg()
{
}

void CExportInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPORT_FUNC_LIST, m_FuncInfoList);
}


BEGIN_MESSAGE_MAP(CExportInfoDlg, CDialog)

END_MESSAGE_MAP()


// CExportInfoDlg 消息处理程序
void CExportInfoDlg::InitInfo()
{
	m_FuncInfoList.InsertColumn(0, _T("Ordinal"), LVCFMT_LEFT, 100);
	m_FuncInfoList.InsertColumn(1, _T("FunctionName"), LVCFMT_LEFT, 100);
	m_FuncInfoList.InsertColumn(2, _T("FunctionRva"), LVCFMT_LEFT, 100);
}

BOOL CExportInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitInfo();
	ShowExportTableInfo();
	ShowFunctionInfo();
	return TRUE;
}

void CExportInfoDlg::ShowExportTableInfo()
{
	if (NULL == m_pPeFileInfo)
	{
		return;
	}
	PIMAGE_EXPORT_DIRECTORY pExportTable = m_pPeFileInfo->GetExportDeirectory();
	CString strInfo = _T("");
	char* pszName = (char*)(m_pPeFileInfo->RVA2fOffset(pExportTable->Name, (DWORD)m_pPeFileInfo->pImageBase));
	if (NULL != pszName && -1 != (int)(pszName))
	{
#ifdef UNICODE
		WCHAR wszName[256] = _T("");
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pszName, strlen(pszName), wszName, 256);
		strInfo = wszName;
#else
	strInfo = pszName;
#endif
	GetDlgItem(IDC_FUNC_NAME)->SetWindowText(strInfo);
	}

	strInfo.Format(_T("%08x"), pExportTable->Base);
	GetDlgItem(IDC_FUNC_BASE)->SetWindowText(strInfo);

	strInfo.Format(_T("%08x"), pExportTable->NumberOfFunctions);
	GetDlgItem(IDC_FUNC_NUM)->SetWindowText(strInfo);

	strInfo.Format(_T("%08x"), pExportTable->NumberOfNames);
	GetDlgItem(IDC_FUNC_NAME_NUM)->SetWindowText(strInfo);

	strInfo.Format(_T("%08x"), pExportTable->AddressOfNames);
	GetDlgItem(IDC_NAME_ADDRESS)->SetWindowText(strInfo);

	strInfo.Format(_T("%08x"), pExportTable->AddressOfFunctions);
	GetDlgItem(IDC_FUNC_ADDR)->SetWindowText(strInfo);

	strInfo.Format(_T("%08x"), pExportTable->AddressOfNameOrdinals);
	GetDlgItem(IDC_FUNC_ORDINALS)->SetWindowText(strInfo);
}

void CExportInfoDlg::ShowFunctionInfo()
{
	if (NULL == m_pPeFileInfo)
	{
		return;
	}
	PIMAGE_EXPORT_DIRECTORY pExportTable = m_pPeFileInfo->GetExportDeirectory();
	PDWORD pAddressOfFunc = (PDWORD)m_pPeFileInfo->RVA2fOffset((DWORD)pExportTable->AddressOfFunctions, (DWORD)m_pPeFileInfo->pImageBase);
	PWORD pOriginals = (PWORD)m_pPeFileInfo->RVA2fOffset((DWORD)pExportTable->AddressOfNameOrdinals, (DWORD)m_pPeFileInfo->pImageBase);
	PDWORD pFuncName = (PDWORD)m_pPeFileInfo->RVA2fOffset((DWORD)pExportTable->AddressOfNames, (DWORD)m_pPeFileInfo->pImageBase);
	int nCount = pExportTable->NumberOfFunctions;
	CString strInfo = _T("");
	if (pAddressOfFunc == NULL || (int)pAddressOfFunc == -1 ||
		pOriginals == NULL || (int)pOriginals == -1 ||
		pFuncName == NULL || (int)pFuncName == -1)
	{
		return;
	}
	for (int  i = 0; i < nCount; i++)
	{
		//导出序号等于base + 在数组中的索引（pOriginals数组保存的值）
		if (pOriginals[i] > nCount)
		{
			//这个索引值无效
			strInfo = _T("-");
		}else
		{
			strInfo.Format(_T("%04x"), pOriginals[i] + pExportTable->Base);
		}
		m_FuncInfoList.InsertItem(i, strInfo);

		strInfo.Format(_T("%08x"), pAddressOfFunc[pOriginals[i]]);
		m_FuncInfoList.SetItemText(i, 2, strInfo);

		char *pszName = (char*)m_pPeFileInfo->RVA2fOffset(pFuncName[i], (DWORD)m_pPeFileInfo->pImageBase);
#ifdef UNICODE
		WCHAR wszName[256] = _T("");
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pszName, strlen(pszName), wszName, 256);
		strInfo = wszName;
#else
		strInfo = pszName;
#endif
		m_FuncInfoList.SetItemText(i, 1, strInfo);
	}
}