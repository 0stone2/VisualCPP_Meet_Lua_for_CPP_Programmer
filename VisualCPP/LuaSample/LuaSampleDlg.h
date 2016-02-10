
// LuaSampleDlg.h : 헤더 파일
//

#pragma once


// CLuaSampleDlg 대화 상자
class CLuaSampleDlg : public CDialogEx
{
// 생성입니다.
public:
	CLuaSampleDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LUASAMPLE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedExample01Button();
	afx_msg void OnBnClickedExample02Button();
	afx_msg void OnBnClickedExample03Button();
	afx_msg void OnBnClickedExample04Button();
	afx_msg void OnBnClickedExample05Button();
	afx_msg void OnBnClickedExample06Button();
	afx_msg void OnBnClickedExample07Button();
};
