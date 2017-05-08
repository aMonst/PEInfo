
// PEInfoDlg.cpp : 实现文件
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

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CPEInfoDlg 对话框




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


// CPEInfoDlg 消息处理程序

BOOL CPEInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	InitCommandCtrl();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPEInfoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPEInfoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CPEInfoDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CAboutDlg about_dlg;
	about_dlg.DoModal();
}

void CPEInfoDlg::OnBnClickedBtnOpen()
{
	// TODO: 在此添加控件通知处理程序代码
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
		//成功打开
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
			MessageBox(_T("打开的文件不是PE文件"));
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

		//时间戳转为具体时间
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
		MessageBox(_T("显示数据错误"));
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
		MessageBox(_T("显示数据错误"));
	}
}

void CPEInfoDlg::InitCommandCtrl()
{
	//禁用几个按钮
	GetDlgItem(IDC_BTN_CALC)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_DATA_DIR_INFO)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_SECTION_INFO)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_CHAR_INFO)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_RVA)->EnableWindow(FALSE);
	//将所有文本框设置为空
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
	// TODO: 在此添加控件通知处理程序代码
}

void CPEInfoDlg::OnBnClickedBtnSectionInfo()
{
	// TODO: 在此添加控件通知处理程序代码
	CSectionTableDlg SectionTableDlg;
	SectionTableDlg.m_pPeFileInfo = &m_PeFileInfo;
	m_PeFileInfo.InitSectionTable();
	SectionTableDlg.DoModal();
}

void CPEInfoDlg::OnBnClickedBtnCalc()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strRVA;
	GetDlgItem(IDC_RVA)->GetWindowText(strRVA);
	
	DWORD dwRva = 0;
	_stscanf_s(strRVA.GetBuffer(), _T("%x"), &dwRva);
	DWORD dwfRva = m_PeFileInfo.RVA2fOffset(dwRva, 0);
	if (-1 == dwfRva)
	{
		MessageBox(_T("计算出现错误"));
		return;
	}
	strRVA.Format(_T("%08x"), dwfRva);
	SetDlgItemText(IDC_FRVA, strRVA);
}

void CPEInfoDlg::OnBnClickedBtnDataDirInfo()
{
	// TODO: 在此添加控件通知处理程序代码
	CDataDirectoryDlg dlg;
	dlg.m_pPefileInfo = &m_PeFileInfo;
	m_PeFileInfo.InitDataDirectoryTable();
	dlg.DoModal();
}
