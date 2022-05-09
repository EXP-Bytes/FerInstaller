#pragma once

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <Windows.h>
#include <time.h>
#include <CommCtrl.h>
#include <gdiplus.h>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <TlHelp32.h>

#include "data.h"
#include "resource.h"

#pragma comment(lib, "Msimg32.lib")
#pragma comment(lib, "Comctl32.lib")

void RemoveTempFile();
void Finishing();
void TerminateProcessName(LPCWSTR lpProcessname);
bool FindProcess(const wchar_t* processName);

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
