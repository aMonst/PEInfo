
// PEInfoDlg.h : ͷ�ļ�
//

#pragma once
#include "PeFileInfo.h"

// CPEInfoDlg �Ի���
class CPEInfoDlg : public CDialog
{
// ����
public:
	CPEInfoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PEINFO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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

	void InitCommandCtrl(); //��ʼ�����пؼ�
private:
	CPeFileInfo m_PeFileInfo;
public:
	afx_msg void OnBnClickedBtnCharInfo();
	afx_msg void OnBnClickedBtnSectionInfo();
	afx_msg void OnBnClickedBtnCalc();
	afx_msg void OnBnClickedBtnDataDirInfo();
};
