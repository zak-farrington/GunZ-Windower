/*
		hAx D3D Hook v1.0 by Zak Farrington alias fritz <fritz@hax-studios.net>
		A D3D9 Wrapper for GunZ
		Copyright (C) 2005 hAx Studios Ltd.
		All rights reserved.

		http://hax-studios.net

		Original Wrapper by Jian Yang (ph.D) <fsword73@hotmail.com>
*/

#include <windows.h>
#include "Hook.h"
#include "Main.h"


BOOL APIENTRY DllMain(HINSTANCE hModule, DWORD uMsg, LPVOID lpReserved)
{	
	switch(uMsg)
	{
		case DLL_PROCESS_ATTACH:
		{
			//** Successful attach
			if(GetModuleFileName(hModule, strModuleName, sizeof(strModuleName)) != NULL)
			{
				char strCurrentDirectory[128];											//** Will hold the current directory path
					
				GetCurrentDirectory(sizeof(strCurrentDirectory), strCurrentDirectory); //** Get current directory
					
				//** Setup logfile stuff
				strcpy(strLogFile, strCurrentDirectory);
				strcat(strLogFile, "\\hAxGunZHook.log");
		
				//** Format log string
				sprintf(strBuffer, "<%s>\r\n\t- 'gunz.exe' -> Successfully attached to process.\r\n\t- Command line: %s\r\n\r\n", GetDateTime(), GetCommandLine());

				WriteLog(strLogFile, strBuffer); //** Write to our log
			}
		}break;

		case DLL_THREAD_ATTACH:		
		
		break;

		case DLL_THREAD_DETACH:
		
		break;

		case DLL_PROCESS_DETACH:
		{
			CloseMSD3D9();

			sprintf(strBuffer,"<%s>\r\n\t- 'gunz.exe' -> Process end.\r\n\r\n----------------------------------\r\n\r\n", GetDateTime());
			WriteLog(strLogFile, strBuffer);
		}break;
	}

	return TRUE;
}

//** main.cpp:  I didn't really need this...
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

//** main.cpp: For logging
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