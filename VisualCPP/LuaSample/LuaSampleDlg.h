
// LuaSampleDlg.h : ��� ����
//

#pragma once


// CLuaSampleDlg ��ȭ ����
class CLuaSampleDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CLuaSampleDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LUASAMPLE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedExample01Button();
	afx_msg void OnBnClickedExample02Button();
	afx_msg void OnBnClickedExample03Button();
};
