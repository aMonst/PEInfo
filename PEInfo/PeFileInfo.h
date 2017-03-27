#pragma once
#include <vector>
using namespace std;
struct IMAGE_DATA_DIRECTORY_INFO
{
	PVOID pVirtualAddress;
	PVOID pFileOffset;
	DWORD dwVirtualSize;
};

class CPeFileInfo
{
public:
	CPeFileInfo(void);
	~CPeFileInfo(void);

	BOOL LoadFile();
	void UnLoadFile();
	BOOL IsPeFile();
	PIMAGE_NT_HEADERS GetNtHeaders();
	PIMAGE_FILE_HEADER GetFileHeader();
	PIMAGE_OPTIONAL_HEADER GetOptionalHeader();
	void GetTargetPlatform(CString &strMachine);
	void GetFileCharacteristics(CString &strCharacter);
	PIMAGE_SECTION_HEADER GetSectionHeader();
	void InitSectionTable();
	void InitDataDirectoryTable();
	vector<IMAGE_SECTION_HEADER> &GetSectionTable();
	vector<IMAGE_DATA_DIRECTORY_INFO> &GetDataDirectoryTable();
	PIMAGE_IMPORT_DESCRIPTOR GetImportDescriptor();
	DWORD RVA2fOffset(DWORD dwRVA, DWORD dwImageBase); //将RVA转化为在文件的偏移
	PIMAGE_EXPORT_DIRECTORY GetExportDeirectory();
public:
	CString strFilePath;
	HANDLE hFile;
	PVOID pImageBase;
	HANDLE hMapping;

	vector<IMAGE_SECTION_HEADER> m_SectionTable;
	vector<IMAGE_DATA_DIRECTORY_INFO> m_DataDirectoryTable;
};
