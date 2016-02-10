// LuaExt.h : LuaExt DLL의 기본 헤더 파일입니다.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"		// 주 기호입니다.


// CLuaExtApp
// 이 클래스의 구현을 보려면 LuaExt.cpp를 참조하십시오.
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

// 재정의입니다.
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
