#include "main.h"

bool FindProcess(const wchar_t* processName)
{
	bool exists = false;
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (Process32First(snapshot, &entry))
		while (Process32Next(snapshot, &entry))
			if (!_wcsicmp(entry.szExeFile, processName))
				exists = true;

	CloseHandle(snapshot);
	return exists;
}

void TerminateProcessName(LPCWSTR lpProcessname)
{
	HANDLE hProcessSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32W prcs;
	prcs.dwSize = sizeof(PROCESSENTRY32W);
	BOOL bTerminateProcessRes = Process32FirstW(hProcessSnapshot, &prcs);
	while (bTerminateProcessRes)
	{
		if (!lstrcmpW(prcs.szExeFile, lpProcessname))
		{
			HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, prcs.th32ProcessID);
			if (hProcess != NULL)
			{
				TerminateProcess(hProcess, 9);
				CloseHandle(hProcess);
			}
		}
		bTerminateProcessRes = Process32NextW(hProcessSnapshot, &prcs);
	}
	CloseHandle(hProcessSnapshot);
}