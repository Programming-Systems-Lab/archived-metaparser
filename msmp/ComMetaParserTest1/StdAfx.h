// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__E3A15F7E_4B63_4CEB_A4CE_C462EA6F1818__INCLUDED_)
#define AFX_STDAFX_H__E3A15F7E_4B63_4CEB_A4CE_C462EA6F1818__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif
#ifndef _WIN32_DCOM
#define _WIN32_DCOM
#endif
#define _ATL_FREE_THREADED

#import <msxml4.dll>
using namespace MSXML2;

#import "Q:\Project\Visual Studio\RuleEngine1\Debug\RuleEngine1.dll"
using namespace RULEENGINE1Lib;

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
class CExeModule : public CComAutoThreadModule <CComSimpleThreadAllocator>
{
public:
	LONG Unlock();
	DWORD dwThreadID;
	HANDLE hEventShutdown;
	void MonitorShutdown();
	bool StartMonitor();
	bool bActivity;
};
extern CExeModule _Module;
#include <atlcom.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__E3A15F7E_4B63_4CEB_A4CE_C462EA6F1818__INCLUDED)
