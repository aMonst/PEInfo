// ImportDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PEInfo.h"
#include "ImportDlg.h"


// CImportDlg �Ի���
IMPLEMENT_DYNAMIC(CImportDlg, CDialog)
CImportDlg::CImportDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImportDlg::IDD, pParent)
{

}

CImportDlg::~CImportDlg()
{
}

void CImportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IMPORT_LIST, m_ImportList);
	DDX_Control(pDX, IDC_TUNK_LIST, m_TunkList);
}


BEGIN_MESSAGE_MAP(CImportDlg, CDialog)
	ON_NOTIFY(NM_CLICK, IDC_IMPORT_LIST, &CImportDlg::OnNMClickImportList)
END_MESSAGE_MAP()


// CImportDlg ��Ϣ�������

BOOL CImportDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_ImportList.InsertColumn(0, _T("Name"), LVCFMT_LEFT, 100);
	m_ImportList.InsertColumn(1, _T("TimeDateStamp"), LVCFMT_LEFT, 100);
	m_ImportList.InsertColumn(2, _T("ForwarderChain"), LVCFMT_LEFT, 100);
	m_ImportList.InsertColumn(3, _T("OriginalFirstThunk"), LVCFMT_LEFT, 100);
	m_ImportList.InsertColumn(4, _T("FirstThunk"), LVCFMT_LEFT, 100);

	m_ImportList.SetExtendedStyle(LVS_EX_FULLROWSELECT );
	m_TunkList.InsertColumn(0, _T("ThunkRva"), LVCFMT_LEFT, 80);
	m_TunkList.InsertColumn(1, _T("ThunkValue"), LVCFMT_LEFT, 80);
	m_TunkList.InsertColumn(2, _T("Name"), LVCFMT_LEFT, 80);
	m_TunkList.InsertColumn(3, _T("Hint"), LVCFMT_LEFT, 80);
	
	//��ʼ��������Ϣ������ʾ
	InitImportTable();
	ShowImportTable();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CImportDlg::InitImportTable()
{
	//��ȡ���뺯�������ļ��е�ƫ��
	PIMAGE_IMPORT_DESCRIPTOR pImportTable = m_pPeFileInfo->GetImportDescriptor();
	if (NULL != pImportTable)
	{
		int i = 0;
		while (!IsEndOfTable(&pImportTable[i]))
		{
			m_ImportTable.push_back(pImportTable[i]);
			i++;
		}
	}
}
void CImportDlg::ShowImportTable()
{
	int i = 0;
	CString strInfo = _T("");
	for (vector<IMAGE_IMPORT_DESCRIPTOR>::iterator it = m_ImportTable.begin(); it != m_ImportTable.end(); it++)
	{
		//����Name��Ա�е�RVA����������ļ��е�ƫ��
		char *pName = (char*)m_pPeFileInfo->RVA2fOffset(it->Name, (DWORD)(m_pPeFileInfo->pImageBase));
		if (NULL == pName || -1 == (int)pName)
		{
			m_ImportList.InsertItem(i, _T("-"));
		}else
		{
#ifdef UNICODE
			//�����UNICODE�ַ�������ô��Ҫ����ת��
			WCHAR wszName[256] = _T("");
			MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pName, strlen(pName), wszName, 256);
			m_ImportList.InsertItem(i, wszName);
#else
			m_ImportList.InsertItem(i, pName);
#endif
		}
		//��ʾʱ���
		tm p;
		errno_t err1;
		err1 = gmtime_s(&p,(time_t*)&it->TimeDateStamp);
		TCHAR s[100] = {0};
		_tcsftime (s, sizeof(s) / sizeof(TCHAR), _T("%Y-%m-%d %H:%M:%S"), &p);
		m_ImportList.SetItemText(i, 1, s);
		
		strInfo.Format(_T("%08x"), it->ForwarderChain);
		m_ImportList.SetItemText(i, 2, strInfo);

		strInfo.Format(_T("%08x"), it->OriginalFirstThunk);
		m_ImportList.SetItemText(i, 3, strInfo);

		strInfo.Format(_T("%08x"), it->FirstThunk);
		m_ImportList.SetItemText(i, 4, strInfo);
	}
}

BOOL CImportDlg::IsEndOfTable(PIMAGE_IMPORT_DESCRIPTOR pImportTable)
{
	//�Ƿ񵽴���β�����������û�и����ܹ��ж������Ҫ�Լ��ж�
	//�ж����������һ����������ݶ���null
	if (0 == pImportTable->OriginalFirstThunk &&
		0 == pImportTable->TimeDateStamp &&
		0 == pImportTable->ForwarderChain &&
		0 == pImportTable->Name &&
		0 == pImportTable->FirstThunk)
	{
		return TRUE;
	}

	return FALSE;
}

void CImportDlg::ShowFunctionInfoByDllIndex(int nIndex)
{
	IMAGE_IMPORT_DESCRIPTOR ImageDesc = m_ImportTable[nIndex];
	//��ȡ����Ӧ����ָ���IMAGE_THUNK_DATA��ָ��
	PIMAGE_THUNK_DATA pThunkData = (PIMAGE_THUNK_DATA)m_pPeFileInfo->RVA2fOffset(ImageDesc.OriginalFirstThunk, (DWORD)m_pPeFileInfo->pImageBase);
	CString strInfo = _T("");
	int i = 0;
	if (NULL == pThunkData || 0xffffffff == (int)pThunkData)
	{
		return;
	}
	//����ṹ������0��β
	while (0 != pThunkData->u1.AddressOfData)
	{
		//���������λΪ0ʱ��ʾ�������ַ������͵ĺ�������ʽ���룬��ʱ�Ž��������Ϣ�õ�������
		strInfo.Format(_T("%08x"), pThunkData);
		m_TunkList.InsertItem(i, strInfo);

		strInfo.Format(_T("%08x"), pThunkData->u1.AddressOfData);
		m_TunkList.SetItemText(i, 1, strInfo);

		if (0 == (pThunkData->u1.AddressOfData & 0x80000000))
		{
			PIMAGE_IMPORT_BY_NAME  pIibn= (PIMAGE_IMPORT_BY_NAME)m_pPeFileInfo->RVA2fOffset(pThunkData->u1.AddressOfData, (DWORD)m_pPeFileInfo->pImageBase);
			//name ����򱣴���Ǻ������ĵ�һ���ַ����������ĵ�ַ���Ǻ������ַ����ĵ�ַ
			char *pszName = (char*)&(pIibn->Name);
#ifdef UNICODE
			WCHAR wszName[256] = _T("");
			MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pszName, strlen(pszName), wszName, 256);
			m_TunkList.SetItemText(i, 2, wszName);
#else
			m_TunkList.SetItemText(i, 3, pszName);
#endif

			strInfo.Format(_T("%04x"), pIibn->Hint);
			m_TunkList.SetItemText(i, 3, strInfo);
		}
		else
		{
			m_TunkList.SetItemText(i, 2, _T("-"));
			m_TunkList.SetItemText(i, 3, _T("-"));
		}
		pThunkData++;
	}
}
void CImportDlg::OnNMClickImportList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nIndex = m_ImportList.GetSelectionMark();
	if (nIndex != -1)
	{
		m_TunkList.DeleteAllItems();
		ShowFunctionInfoByDllIndex(nIndex);
	}
	*pResult = 0;
}
