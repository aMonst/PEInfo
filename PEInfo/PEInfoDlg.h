
// PEInfoDlg.h : 头文件
//

#pragma once
#include "PeFileInfo.h"

// CPEInfoDlg 对话框
class CPEInfoDlg : public CDialog
{
// 构造
public:
	CPEInfoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PEINFO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnOpen();
	void ShowFileHeaderInfo();
	void ShowOptionHeaderInfo();

	void InitCommandCtrl(); //初始化所有控件
private:
	CPeFileInfo m_PeFileInfo;
public:
	afx_msg void OnBnClickedBtnCharInfo();
	afx_msg void OnBnClickedBtnSectionInfo();
	afx_msg void OnBnClickedBtnCalc();
	afx_msg void OnBnClickedBtnDataDirInfo();
};
