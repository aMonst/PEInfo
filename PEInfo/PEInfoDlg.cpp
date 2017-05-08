
// PEInfoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PEInfo.h"
#include "PEInfoDlg.h"
#include <time.h>
#include "CharacterDlg.h"
#include "SectionTableDlg.h"
#include "DataDirectoryDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CPEInfoDlg �Ի���




CPEInfoDlg::CPEInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPEInfoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_MAINICON);
}

void CPEInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPEInfoDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CPEInfoDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_OPEN, &CPEInfoDlg::OnBnClickedBtnOpen)
	ON_BN_CLICKED(IDC_BTN_CHAR_INFO, &CPEInfoDlg::OnBnClickedBtnCharInfo)
	ON_BN_CLICKED(IDC_BTN_SECTION_INFO, &CPEInfoDlg::OnBnClickedBtnSectionInfo)
	ON_BN_CLICKED(IDC_BTN_CALC, &CPEInfoDlg::OnBnClickedBtnCalc)
	ON_BN_CLICKED(IDC_BTN_DATA_DIR_INFO, &CPEInfoDlg::OnBnClickedBtnDataDirInfo)
END_MESSAGE_MAP()


// CPEInfoDlg ��Ϣ�������

BOOL CPEInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	InitCommandCtrl();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CPEInfoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPEInfoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CPEInfoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CPEInfoDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CAboutDlg about_dlg;
	about_dlg.DoModal();
}

void CPEInfoDlg::OnBnClickedBtnOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TCHAR szFilePath[MAX_PATH] = _T("");
	OPENFILENAME ofn = {0};
	ofn.lStructSize      = sizeof(ofn);
	ofn.hwndOwner        = m_hWnd;
	ofn.hInstance        = GetModuleHandle(NULL);
	ofn.nMaxFile         = MAX_PATH;
	ofn.lpstrInitialDir  = _T(".");
	ofn.lpstrFile        = szFilePath;
	ofn.lpstrTitle       = _T("Open ...[PEInfo] by liuhao");
	ofn.Flags            = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrFilter      = _T("*.*\0*.*\0");
	GetOpenFileName(&ofn);

	m_PeFileInfo.strFilePath = szFilePath;
	GetDlgItem(IDC_FILE_PATH)->SetWindowText(szFilePath);

	m_PeFileInfo.UnLoadFile();
	BOOL bLoadSuccess = m_PeFileInfo.LoadFile();
	if (bLoadSuccess)
	{
		//�ɹ���
		if (m_PeFileInfo.IsPeFile())
		{
			ShowFileHeaderInfo();
			ShowOptionHeaderInfo();
			GetDlgItem(IDC_BTN_CALC)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_DATA_DIR_INFO)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_SECTION_INFO)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_CHAR_INFO)->EnableWindow(TRUE);
			GetDlgItem(IDC_RVA)->EnableWindow(TRUE);

		}else
		{
			MessageBox(_T("�򿪵��ļ�����PE�ļ�"));
			InitCommandCtrl();
		}
	}
}

void CPEInfoDlg::ShowFileHeaderInfo()
{
	PIMAGE_FILE_HEADER pFileHeader = m_PeFileInfo.GetFileHeader();
	if (NULL != pFileHeader)
	{
		CString strTemp = _T("");
		m_PeFileInfo.GetTargetPlatform(strTemp);
		GetDlgItem(IDC_MACHINE)->SetWindowText(strTemp);

		strTemp.Format(_T("%d"), pFileHeader->NumberOfSections);
		GetDlgItem(IDC_NUM_SECTION)->SetWindowText(strTemp);

		//ʱ���תΪ����ʱ��
		tm p;
		errno_t err1;
		err1 = gmtime_s(&p,(time_t*)&pFileHeader->TimeDateStamp);
		TCHAR s[100] = {0};
		_tcsftime (s, sizeof(s) / sizeof(TCHAR), _T("%Y-%m-%d %H:%M:%S"), &p);
		GetDlgItem(IDC_TIME_STAMP)->SetWindowText(s);

		strTemp.Format(_T("0x%08x"), pFileHeader->PointerToSymbolTable);
		GetDlgItem(IDC_SYM_TABLE)->SetWindowText(strTemp);

		strTemp.Format(_T("%d"), pFileHeader->NumberOfSymbols);
		GetDlgItem(IDC_SYM_NUM)->SetWindowText(strTemp);

		strTemp.Format(_T("0x%08x"), pFileHeader->SizeOfOptionalHeader);
		GetDlgItem(IDC_OPTION_HEADER_NUM)->SetWindowText(strTemp);
		strTemp.Format(_T("0x%08x"), pFileHeader->Characteristics);
		GetDlgItem(IDC_CHARACTERISTIC)->SetWindowText(strTemp);
	}
	else
	{
		MessageBox(_T("��ʾ���ݴ���"));
	}
}

void CPEInfoDlg::ShowOptionHeaderInfo()
{
	PIMAGE_OPTIONAL_HEADER pOptionHeader = m_PeFileInfo.GetOptionalHeader();
	if (NULL != pOptionHeader)
	{
		CString strTemp = _T("");
		strTemp.Format(_T("0x%08x"), pOptionHeader->AddressOfEntryPoint);
		GetDlgItem(IDC_ENTRY_POINT)->SetWindowText(strTemp);

		strTemp.Format(_T("0x%08x"), pOptionHeader->BaseOfCode);
		GetDlgItem(IDC_CODE_BASE)->SetWindowText(strTemp);

		strTemp.Format(_T("0x%08x"), pOptionHeader->BaseOfData);
		GetDlgItem(IDC_DATA_BASE)->SetWindowText(strTemp);
		
		strTemp.Format(_T("0x%08x"), pOptionHeader->ImageBase);
		GetDlgItem(IDC_IMAGE_BASE)->SetWindowText(strTemp);

		strTemp.Format(_T("0x%08x"), pOptionHeader->SectionAlignment);
		GetDlgItem(IDC_SECTION_ALIGN)->SetWindowText(strTemp);
		
		strTemp.Format(_T("0x%08x"), pOptionHeader->FileAlignment);
		GetDlgItem(IDC_FILE_ALIGN)->SetWindowText(strTemp);
		
		strTemp.Format(_T("0x%08x"), pOptionHeader->SizeOfImage);
		GetDlgItem(IDC_IMAGE_SIZE)->SetWindowText(strTemp);

	}else
	{
		MessageBox(_T("��ʾ���ݴ���"));
	}
}

void CPEInfoDlg::InitCommandCtrl()
{
	//���ü�����ť
	GetDlgItem(IDC_BTN_CALC)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_DATA_DIR_INFO)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_SECTION_INFO)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_CHAR_INFO)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_RVA)->EnableWindow(FALSE);
	//�������ı�������Ϊ��
	GetDlgItem(IDC_FILE_PATH)->SetWindowText(_T(""));
	GetDlgItem(IDC_MACHINE)->SetWindowText(_T(""));
	GetDlgItem(IDC_NUM_SECTION)->SetWindowText(_T(""));
	GetDlgItem(IDC_TIME_STAMP)->SetWindowText(_T(""));
	GetDlgItem(IDC_SYM_TABLE)->SetWindowText(_T(""));
	GetDlgItem(IDC_SYM_NUM)->SetWindowText(_T(""));
	GetDlgItem(IDC_OPTION_HEADER_NUM)->SetWindowText(_T(""));
	GetDlgItem(IDC_CHARACTERISTIC)->SetWindowText(_T(""));
	GetDlgItem(IDC_ENTRY_POINT)->SetWindowText(_T(""));
	GetDlgItem(IDC_CODE_BASE)->SetWindowText(_T(""));
	GetDlgItem(IDC_DATA_BASE)->SetWindowText(_T(""));
	GetDlgItem(IDC_IMAGE_BASE)->SetWindowText(_T(""));
	GetDlgItem(IDC_SECTION_ALIGN)->SetWindowText(_T(""));
	GetDlgItem(IDC_FILE_ALIGN)->SetWindowText(_T(""));
	GetDlgItem(IDC_IMAGE_SIZE)->SetWindowText(_T(""));
}

void CPEInfoDlg::OnBnClickedBtnCharInfo()
{
	CCharacterDlg dlg;
	dlg.m_pPeFileInfo = &m_PeFileInfo;
	dlg.DoModal();
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CPEInfoDlg::OnBnClickedBtnSectionInfo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CSectionTableDlg SectionTableDlg;
	SectionTableDlg.m_pPeFileInfo = &m_PeFileInfo;
	m_PeFileInfo.InitSectionTable();
	SectionTableDlg.DoModal();
}

void CPEInfoDlg::OnBnClickedBtnCalc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strRVA;
	GetDlgItem(IDC_RVA)->GetWindowText(strRVA);
	
	DWORD dwRva = 0;
	_stscanf_s(strRVA.GetBuffer(), _T("%x"), &dwRva);
	DWORD dwfRva = m_PeFileInfo.RVA2fOffset(dwRva, 0);
	if (-1 == dwfRva)
	{
		MessageBox(_T("������ִ���"));
		return;
	}
	strRVA.Format(_T("%08x"), dwfRva);
	SetDlgItemText(IDC_FRVA, strRVA);
}

void CPEInfoDlg::OnBnClickedBtnDataDirInfo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDataDirectoryDlg dlg;
	dlg.m_pPefileInfo = &m_PeFileInfo;
	m_PeFileInfo.InitDataDirectoryTable();
	dlg.DoModal();
}
