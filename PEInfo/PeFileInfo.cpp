#include "StdAfx.h"
#include "PeFileInfo.h"
#include <imagehlp.h>
CPeFileInfo::CPeFileInfo(void)
{
	pImageBase = NULL;
	hFile = NULL;
	hMapping = NULL;
}

CPeFileInfo::~CPeFileInfo(void)
{
}

BOOL CPeFileInfo::LoadFile()
{
	if(strFilePath.IsEmpty())
	{
		return FALSE;
	}
	hFile = CreateFile(strFilePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE  == hFile)
	{
		return FALSE;
	}

	hMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
	if (NULL == hMapping)
	{
		CloseHandle(hFile);
		hFile = NULL;
		return FALSE;
	}

	pImageBase = MapViewOfFile(hMapping, FILE_MAP_READ, 0, 0, 0);
	if (NULL == pImageBase)
	{
		CloseHandle(hMapping);
		CloseHandle(hFile);

		hMapping = NULL;
		hFile = NULL;
		return FALSE;
	}
	
	return TRUE;
}

void CPeFileInfo::UnLoadFile()
{
	if(pImageBase != NULL)
	{
		UnmapViewOfFile(pImageBase);
	}

	if(NULL != hMapping)
	{
		CloseHandle(hMapping);
	}

	if (NULL != hFile)
	{
		CloseHandle(hFile);
	}

	pImageBase = NULL;
	hFile = NULL;
	hMapping = NULL;
}

BOOL CPeFileInfo::IsPeFile()
{
	PIMAGE_DOS_HEADER pDosHeader = NULL;
	PIMAGE_NT_HEADERS pNtHeader = NULL;
	if (NULL == pImageBase)
	{
		return FALSE;
	}

	pDosHeader = (PIMAGE_DOS_HEADER)pImageBase;
	if (pDosHeader->e_magic != IMAGE_DOS_SIGNATURE)
	{
		return FALSE;
	}

	pNtHeader = (PIMAGE_NT_HEADERS)((DWORD)(pDosHeader->e_lfanew) + (DWORD)pImageBase);
	if (pNtHeader->Signature != IMAGE_NT_SIGNATURE)
	{
		return FALSE;
	}

	return TRUE;
}

PIMAGE_NT_HEADERS CPeFileInfo::GetNtHeaders()
{
	PIMAGE_DOS_HEADER pDosHeader = NULL;
	PIMAGE_NT_HEADERS pNtHeader = NULL;
	if (NULL == pImageBase)
	{
		return NULL;
	}
	
	pDosHeader = (PIMAGE_DOS_HEADER)pImageBase;
	pNtHeader = (PIMAGE_NT_HEADERS)((DWORD)pImageBase + (DWORD)(pDosHeader->e_lfanew));
	return pNtHeader;
}

PIMAGE_FILE_HEADER CPeFileInfo::GetFileHeader()
{
	PIMAGE_DOS_HEADER pDosHeader = NULL;
	PIMAGE_NT_HEADERS pNtHeader = NULL;
	if (NULL == pImageBase)
	{
		return NULL;
	}

	pDosHeader = (PIMAGE_DOS_HEADER)pImageBase;
	pNtHeader = (PIMAGE_NT_HEADERS)((DWORD)pImageBase + (DWORD)(pDosHeader->e_lfanew));
	return &(pNtHeader->FileHeader);
}

PIMAGE_OPTIONAL_HEADER CPeFileInfo::GetOptionalHeader()
{
	PIMAGE_DOS_HEADER pDosHeader = NULL;
	PIMAGE_NT_HEADERS pNtHeader = NULL;
	if (NULL == pImageBase)
	{
		return NULL;
	}

	pDosHeader = (PIMAGE_DOS_HEADER)pImageBase;
	pNtHeader = (PIMAGE_NT_HEADERS)((DWORD)pImageBase + (DWORD)(pDosHeader->e_lfanew));
	return &(pNtHeader->OptionalHeader);
}

void CPeFileInfo::GetTargetPlatform(CString &strMachine)
{
	DWORD dwMachine = 0;
	PIMAGE_FILE_HEADER pFileHeader = GetFileHeader();
	if (NULL!= pFileHeader)
	{
		dwMachine = pFileHeader->Machine;
		switch (dwMachine)
		{
		case IMAGE_FILE_MACHINE_I386:
			strMachine = _T("x86");
			break;
		case IMAGE_FILE_MACHINE_IA64:
			strMachine = _T("Intel Itanium");
			break;
		case IMAGE_FILE_MACHINE_AMD64:
			strMachine = _T("x64");
			break;
		default:
			strMachine = _T("Unknow");
			break;
		}
	}
}

void CPeFileInfo::GetFileCharacteristics(CString &strCharacter)
{
	DWORD dwMachine = 0;
	PIMAGE_FILE_HEADER pFileHeader = GetFileHeader();
	if (0 != (pFileHeader->Characteristics & IMAGE_FILE_RELOCS_STRIPPED))
	{
		strCharacter += _T("文件中不存在重定位信息\r\n");
	}
	if(0 != (pFileHeader->Characteristics & IMAGE_FILE_EXECUTABLE_IMAGE))
	{
		strCharacter += _T("文件可执行\r\n");
	}

	if (0 != (pFileHeader->Characteristics & IMAGE_FILE_LARGE_ADDRESS_AWARE))
	{
		strCharacter += _T("可以处理大于2GB内容\r\n");
	}
	if(0 != (pFileHeader->Characteristics & IMAGE_FILE_32BIT_MACHINE))
	{
		strCharacter += _T("目标平台为32位机器\r\n");
	}

	if (0 != (pFileHeader->Characteristics & IMAGE_FILE_SYSTEM))
	{
		strCharacter += _T("该文件是系统文件\r\n");
	}
	if (0 != (pFileHeader->Characteristics & IMAGE_FILE_DLL))
	{
		strCharacter += _T("该文件是dll文件\r\n");
	}
	if(0 != (pFileHeader->Characteristics & IMAGE_FILE_UP_SYSTEM_ONLY))
	{
		strCharacter += _T("该程序只能运行在单核处理器上");
	}
}

PIMAGE_SECTION_HEADER CPeFileInfo::GetSectionHeader()
{
	PIMAGE_FILE_HEADER pFileHeader = GetFileHeader();
	PIMAGE_SECTION_HEADER pSectionHeader = NULL;
	if (NULL == pFileHeader)
	{
		return NULL;
	}
	PIMAGE_OPTIONAL_HEADER pOptionHeader = GetOptionalHeader();
	pSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)(pOptionHeader) + pFileHeader->SizeOfOptionalHeader);
	return pSectionHeader;
}

void CPeFileInfo::InitSectionTable()
{
	if (!m_SectionTable.empty())
	{
		return ;
	}
	PIMAGE_SECTION_HEADER pSectionHeader = GetSectionHeader();
	PIMAGE_FILE_HEADER pFileHeader = GetFileHeader();
	if (NULL != pSectionHeader && NULL != pFileHeader)
	{
		DWORD dwCountOfSection = pFileHeader->NumberOfSections;
		int nCount = 0;
		while (nCount < dwCountOfSection)
		{
			IMAGE_SECTION_HEADER ImageSec = pSectionHeader[nCount];
			m_SectionTable.push_back(ImageSec);
			nCount++;
		}
	}
}

vector<IMAGE_SECTION_HEADER> &CPeFileInfo::GetSectionTable()
{
	return m_SectionTable;
}

DWORD CPeFileInfo::RVA2fOffset(DWORD dwRVA, DWORD dwImageBase)
{
	InitSectionTable();
	vector<IMAGE_SECTION_HEADER>::iterator it;
	for (it = m_SectionTable.begin(); it != m_SectionTable.end(); it++)
	{
		if (dwRVA >= (DWORD)(it->VirtualAddress) && 
			dwRVA <= (DWORD)((DWORD)(it->VirtualAddress) + it->Misc.VirtualSize)
			)
		{
			break;
		}
	}

	if (it == m_SectionTable.end())
	{
		return -1;
	}

	return (DWORD)(dwRVA - (DWORD)(it->VirtualAddress) + (DWORD)(it->PointerToRawData) + dwImageBase);
}

void CPeFileInfo::InitDataDirectoryTable()
{
	if (!m_DataDirectoryTable.empty())
	{
		//先清空之前的内容
		m_DataDirectoryTable.clear();
	}

	PIMAGE_SECTION_HEADER pSectionHeader = GetSectionHeader();
	PIMAGE_OPTIONAL_HEADER pOptionalHeader = GetOptionalHeader();
	PIMAGE_DATA_DIRECTORY pDataHeader = pOptionalHeader->DataDirectory;

	IMAGE_DATA_DIRECTORY_INFO dataInfo;
	for (int i = 0; i < IMAGE_NUMBEROF_DIRECTORY_ENTRIES; i++)
	{
		dataInfo.pVirtualAddress = (PVOID)(pDataHeader[i].VirtualAddress);
		dataInfo.dwVirtualSize = pDataHeader[i].Size;
		dataInfo.pFileOffset = (PVOID)RVA2fOffset((DWORD)(dataInfo.pVirtualAddress), 0); //PE文件在磁盘中时，一般它的基址为0
		m_DataDirectoryTable.push_back(dataInfo);
	}
}

vector<IMAGE_DATA_DIRECTORY_INFO> &CPeFileInfo::GetDataDirectoryTable()
{
	return m_DataDirectoryTable;
}

PIMAGE_IMPORT_DESCRIPTOR CPeFileInfo::GetImportDescriptor()
{
	//由于这个表中保存的是RVA，要在文件中遍历，需要转为在文件中的偏移
	PVOID pImportRVA = m_DataDirectoryTable[1].pVirtualAddress;
	//在读取这些数据的时候，是从内存中读取的，从内存中读取时，需要考虑文件被加载到内存中的基址
	return (PIMAGE_IMPORT_DESCRIPTOR)RVA2fOffset((DWORD)pImportRVA, (DWORD)pImageBase);
}

PIMAGE_EXPORT_DIRECTORY CPeFileInfo::GetExportDeirectory()
{
	PVOID pExportRVA = m_DataDirectoryTable[0].pVirtualAddress;
	return (PIMAGE_EXPORT_DIRECTORY)RVA2fOffset((DWORD)pExportRVA, (DWORD)pImageBase);
}