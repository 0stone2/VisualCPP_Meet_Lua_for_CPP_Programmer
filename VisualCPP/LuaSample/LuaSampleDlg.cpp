
// LuaSampleDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "LuaSample.h"
#include "LuaSampleDlg.h"
#include "afxdialogex.h"


#include "C:/Lua/Library/include/lua.hpp"
#include "C:/Lua/Library/include/luaconf.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLuaSampleDlg ��ȭ ����



CLuaSampleDlg::CLuaSampleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLuaSampleDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLuaSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLuaSampleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SAMPLE1_BUTTON, &CLuaSampleDlg::OnBnClickedSample1Button)
	ON_BN_CLICKED(IDC_SAMPLE2_BUTTON, &CLuaSampleDlg::OnBnClickedSample2Button)
	ON_BN_CLICKED(IDC_SAMPLE3_BUTTON, &CLuaSampleDlg::OnBnClickedSample3Button)
END_MESSAGE_MAP()


// CLuaSampleDlg �޽��� ó����

BOOL CLuaSampleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CLuaSampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CLuaSampleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CLuaSampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CLuaSampleDlg::OnBnClickedSample1Button()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	char			szDbgString[MAX_PATH]{0, };
	lua_State *		m_pLuaState{ NULL };

	__try {
		m_pLuaState = luaL_newstate();
		if (NULL == m_pLuaState) __leave;

		if (luaL_dofile(m_pLuaState, "Sample01.lua")) {
			const char *pError = lua_tostring(m_pLuaState, -1);
			sprintf_s(szDbgString, "error running function `f': %s\n", pError);
			OutputDebugStringA(szDbgString);
			__leave;
		}
	}
	__finally {

	}
}


void CLuaSampleDlg::OnBnClickedSample2Button()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	char			szDbgString[MAX_PATH]{0, };
	lua_State *		m_pLuaState{ NULL };
	const char *	szWelcomMessage{ NULL };
	const char *	szWhoamI{ NULL };


	__try {
		m_pLuaState = luaL_newstate();
		if (NULL == m_pLuaState) __leave;

		if (luaL_dofile(m_pLuaState, "Sample02.lua")) {
			const char *pError = lua_tostring(m_pLuaState, -1);
			sprintf_s(szDbgString, "error running function `f': %s\n", pError);
			OutputDebugStringA(szDbgString);
			__leave;
		}

		lua_getglobal(m_pLuaState, "szWelcomMessage");
		lua_getglobal(m_pLuaState, "szWhoamI");


		if (!lua_isstring(m_pLuaState, -1)) {
			// error(L, "`height' should be a number\n");
			OutputDebugStringA("`szWhoAmI' should be a string\n");
			__leave;
		}
		szWhoamI = lua_tostring(m_pLuaState, -1);

		if (!lua_isstring(m_pLuaState, -2)) {
			// error(L, "`height' should be a number\n");
			OutputDebugStringA("`szWelcomMessage' should be a string\n");
			__leave;
		}
		szWelcomMessage = lua_tostring(m_pLuaState, -2);
		

		/*
		Executing Lua Code

		int lua_dofile   (lua_State *L, const char *filename);
		int lua_dostring (lua_State *L, const char *string);
		int lua_dobuffer (lua_State *L, const char *buff,
		size_t size, const char *name);



		int         lua_isnil       (lua_State *L, int index);
		int         lua_isnumber    (lua_State *L, int index);
		int         lua_isstring    (lua_State *L, int index);
		int         lua_istable     (lua_State *L, int index);
		int         lua_isfunction  (lua_State *L, int index);
		int         lua_iscfunction (lua_State *L, int index);
		int         lua_isuserdata  (lua_State *L, int index);

		int lua_equal    (lua_State *L, int index1, int index2);
		int lua_lessthan (lua_State *L, int index1, int index2);

		int				lua_toboolean (lua_State *L, int index);
		double			lua_tonumber (lua_State *L, int index);
		const char    *	lua_tostring (lua_State *L, int index);
		size_t			lua_strlen (lua_State *L, int index);
		int				lua_tag (lua_State *L, int index);
		int				lua_type(lua_State *L, int index);
		const char    *	lua_typename(lua_State *L, int type)

		double         lua_tonumber    (lua_State *L, int index);
		const char    *lua_tostring    (lua_State *L, int index);
		size_t         lua_strlen      (lua_State *L, int index);
		lua_CFunction  lua_tocfunction (lua_State *L, int index);
		void          *lua_touserdata  (lua_State *L, int index);

		int		lua_stackspace (lua_State *L);
		int		lua_gettop (lua_State *L);
		void	lua_settop (lua_State *L, int index);
		void	lua_pushvalue (lua_State *L, int index);
		void	lua_remove (lua_State *L, int index);
		void	lua_insert (lua_State *L, int index);
		void	lua_replace (lua_State *L, int index);




		-- The Stack and Indices
		int lua_gettop (lua_State *L);
		int lua_stackspace (lua_State *L);




		-- Stack Manipulation
		void lua_settop    (lua_State *L, int index);
		void lua_pushvalue (lua_State *L, int index);
		void lua_remove    (lua_State *L, int index);
		void lua_insert    (lua_State *L, int index);



		-- Querying the Stack
		int         lua_type        (lua_State *L, int index);
		int         lua_tag         (lua_State *L, int index);
		int         lua_isnil       (lua_State *L, int index);
		int         lua_isnumber    (lua_State *L, int index);
		int         lua_isstring    (lua_State *L, int index);
		int         lua_istable     (lua_State *L, int index);
		int         lua_isfunction  (lua_State *L, int index);
		int         lua_iscfunction (lua_State *L, int index);
		int         lua_isuserdata  (lua_State *L, int index);



		-- Pushing values onto the Stack
		void lua_pushnumber    (lua_State *L, double n);
		void lua_pushlstring   (lua_State *L, const char *s, size_t len);
		void lua_pushstring    (lua_State *L, const char *s);
		void lua_pushusertag   (lua_State *L, void *u, int tag);
		void lua_pushnil       (lua_State *L);
		void lua_pushcfunction (lua_State *L, lua_CFunction f);
		*/




		szWelcomMessage = lua_tostring(m_pLuaState, 1);
		szWhoamI = lua_tostring(m_pLuaState, 2);
	}
	__finally {

	}
}


void CLuaSampleDlg::OnBnClickedSample3Button()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
