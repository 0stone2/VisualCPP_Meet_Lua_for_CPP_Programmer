// LuaExt.h : LuaExt DLL�� �⺻ ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CLuaExtApp
// �� Ŭ������ ������ ������ LuaExt.cpp�� �����Ͻʽÿ�.
//

#define __LUA_532__
//#define __LUA_515__


#define __LUA_532__
//#define __LUA_515__

#if defined(__LUA_532__)
#include "C:/Script/Lua/5.3.2/Library/include/lua.hpp"
#include "C:/Script/Lua/5.3.2/Library/include/luaconf.h"
#pragma comment(lib,"C:/Script/Lua/5.3.2/Library/x86/lua53.lib")
#elif defined(__LUA_515__)
#include "C:/Script/Lua/5.1.5/Library/include/lua.hpp"
#include "C:/Script/Lua/5.1.5/Library/include/luaconf.h"
#pragma comment(lib,"C:/Script/Lua/5.1.5/Library/x86/lua51.lib")
#endif

extern "C" {
	int DbgString(lua_State *pLuaState);
	int SumAndAverage(lua_State *pLuaState);
}

class CLuaExtApp : public CWinApp
{
public:
	CLuaExtApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
