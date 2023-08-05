/*
		hAx API Hook v1.0 by Zak Farrington alias fritz <fritz@hax-studios.net>
		A Generic API Hook DLL.
		Modified for GunZ Windower.
		Copyright (C) 2005 hAx Studios Ltd.
		All rights reserved.

		http://hax-studios.net
*/

#include <windows.h>
#include <cstdio>
#include <ctime>
#include "Hook.h"
#include "resource.h"

//** START: Our function forwarders/procs (for Hook)

LONG WINAPI SetWindowLong1(HWND hWnd, int nIndex, LONG dwNewLong);

LONG WINAPI SetWindowLong2(HWND hWnd, int nIndex, LONG dwNewLong);

//** END: Our function forwarders/procs (for Hook)


//** START: Global Functions
char *GetDateTime();
BOOL WriteLog(char* strFileName, char* strLineToWrite);
//BOOL HookFunc(char *strModule, char *strFunction, int iOrdinal, void *iProc, void *iOrigProc);
//** END:	Global Functions


//** START:	Global Variables
HINSTANCE hInstance;
char strModuleName[128];		//** Will hold module name
char strLogFile[128];			//** Will hold full path to log file
char strBuffer[512];			//** We can use this in various places
char strDateTime[512];			//** Another fsking buffer... we use this in GetDateTime()
DWORD FuncAddress = 0;
BYTE OldCode[6];
//** END:	Global Variables

BOOL APIENTRY DllMain(HINSTANCE hModule, DWORD uMsg, LPVOID lpReserved)
{
	switch(uMsg)
	{
		case DLL_PROCESS_ATTACH:
		{		
			if(DisableThreadLibraryCalls(hModule) != 0) //** Disable thread notification calls
			{
				//** Successful attach
				if(GetModuleFileName(hModule, strModuleName, sizeof(strModuleName)) != NULL)
				{
					hInstance = hModule;

					char strCurrentDirectory[128];				//** Will hold the current directory path
					
					GetCurrentDirectory(sizeof(strCurrentDirectory), strCurrentDirectory); //** Get current directory
					
					//** Setup logfile stuff
					strcpy(strLogFile, strCurrentDirectory);
					strcat(strLogFile, "\\hAxAPIHook.log");
		
					//** Format log string
					sprintf(strBuffer, "<%s>\r\n\t- '%s'-> Successfully attached to process.\r\n\t- Command line: %s\r\n\r\n", GetDateTime(), strModuleName, GetCommandLine());

					WriteLog(strLogFile, strBuffer); //** Write to our log
				}

				//** Set the hook
				FuncAddress = HookGeneralFunc("user32.dll", "SetWindowLongA", SetWindowLong2, OldCode);
				HookImportFunc("user32.dll", "SetWindowLongA", 0, SetWindowLong1);
			}	

		}break;

		case DLL_PROCESS_DETACH:
			//** Restore bytes @ our function
			if(FuncAddress)
			{
				WriteProcessMemory(GetCurrentProcess(), (void*)FuncAddress, OldCode, 6, 0);
			}

			sprintf(strBuffer,"<%s>\r\n\t- '%s'-> Process end.\r\n\r\n----------------------------------\r\n\r\n", GetDateTime(), strModuleName);
			WriteLog(strLogFile, strBuffer);

		break;
	}

	return TRUE;
}

LONG WINAPI SetWindowLong1(HWND hWnd,int nIndex, LONG dwNewLong)
{
	if(nIndex == GWL_STYLE) //** If function is being used to reset styles
	{
		//** Set new styles
		dwNewLong = WS_SYSMENU | WS_BORDER | WS_CAPTION | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	}
	else
	{
		dwNewLong = dwNewLong;
	}

	return SetWindowLong2(hWnd, nIndex, dwNewLong);
}

LONG WINAPI SetWindowLong2(HWND hWnd,int nIndex, LONG dwNewLong)
{
	//** Restore code @ our function
	WriteProcessMemory(GetCurrentProcess(), (void*)FuncAddress, OldCode, 6, 0);

	//** Put back the original function
	LONG Return = SetWindowLong(hWnd, nIndex, dwNewLong);

	MoveWindow(hWnd, 0, 0, 0, 0, TRUE); //** Repait window

	SendMessage(hWnd, WM_SETICON, IMAGE_ICON, (LPARAM)LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAIN))); //** Set a pretty icon

	SetWindowText(hWnd, "GunZ  -  hAx Windower v1.1 by fritz [http://hax-studios.net]");
	
	//** Restore the hook
	FuncAddress = HookGeneralFunc("user32.dll", "SetWindowLongA", SetWindowLong2, OldCode);

	return Return;
}

/*
BOOL HookFunc(char *strModule, char *strFunction, int iOrdinal, void *iProc, void *iOrigProc)
{
	FuncAddress = HookGeneralFunc(strModule, strFunction, iOrigProc, OldCode);
	HookImportFunc(strModule, strFunction, iOrdinal, iProc);

	return TRUE;
}
*/

//** Main.cpp: I didn't really need this...
char *GetDateTime()
{
	char strTime[128];							//** Will hold the time
	SYSTEMTIME *lpTime = new SYSTEMTIME;		//** Declare and intialize a system time structure

	GetLocalTime(lpTime);						//** Get the system time and store it in lpTime
	_strtime(strTime);

	//** Format time string
	sprintf(strDateTime, "%d/%d/%d - %s", lpTime->wMonth, lpTime->wDay, lpTime->wYear, strTime);

	delete lpTime;

	return strDateTime;
}

//** Main.cpp: Didn't need this either
BOOL WriteLog(char *strFileName, char* strLineToWrite)
{
	for(int x = 0; strLineToWrite[x] != 0; x++);

	FILE *fpLogFile = fopen(strFileName, "a+");

	if(fpLogFile != NULL)							//** If we can open/create the file...
	{
		fwrite(strLineToWrite, x, 1, fpLogFile);	//** ... write the line
	}
	else											//** Error
	{
		return FALSE;
	}

	fclose(fpLogFile);								//** and close

	return TRUE;
}