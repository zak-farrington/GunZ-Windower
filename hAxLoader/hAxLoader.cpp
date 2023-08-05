/*
		hAx Injecter/Loader v1.1 by Zak Farrington alias fritz <fritz@hax-studios.net>
		A Generic DLL Injector and Loader.
		Copyright (C) 2005 hAx Studios Ltd.
		All rights reserved.

		http://hax-studios.net
*/

#define STRICT
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <tlhelp32.h> //** For CreateToolhelp32Snapshot()
#include <commdlg.h>  //** For Open File common dialog
#include <cstdio>

#include "hAxLoader.h"
#include "Injector.h"
#include "resource.h"

HINSTANCE g_hInstance = NULL;

//** hAxLoader.cpp: Our main function
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	g_hInstance = hInstance;
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_MAINDLG), NULL, DialogProc, NULL); //** Create dialog

	return 0;
}

//** hAxLoader.cpp: Our dialog callback
BOOL CALLBACK DialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
		case WM_INITDIALOG:
			SendMessage(hWnd, WM_SETICON, IMAGE_ICON, (LPARAM)LoadIcon(g_hInstance, MAKEINTRESOURCE(IDI_MAINICO))); //** Set icon
		
			if(ReadConfigFile(hWnd) != FALSE) //** Get saved HookPath and etc
			{
				SetWindowText(GetDlgItem(hWnd, IDC_GUNZPATH), strGunzPath);
			}
			
			/*
			if(EnumerateProcesses(hWnd) == FALSE)
			{
				MessageBox(hWnd, "Error: Could not EnumerateProcesses();\n", "[:: hAx Windower ::]", MB_OK + MB_ICONERROR);
			}

			//** Set timers
			SetTimer(hWnd, ENUMERATE_PROC_TIMER, 10000, NULL);
			*/
			GetCurrentDirectory(sizeof(strHookDir), strHookDir);

			/* SetTimer(hWnd, EDIT_MODIFY_TIMER, 1000, NULL); */
		break;



		case WM_COMMAND:
			switch(wParam)
			{
				case IDC_BROWSEGUNZ:
				{
					OPENFILENAME ofOpenFile;									//** OpenFile common dialog struct	

					//** Initialize ofOpenFile
					ZeroMemory(&ofOpenFile, sizeof(ofOpenFile));
					ofOpenFile.lStructSize = sizeof(ofOpenFile);
					ofOpenFile.hInstance =  g_hInstance;
					ofOpenFile.lpstrFile = strGunzPath;

					ofOpenFile.lpstrFile[0] = '\0';
					ofOpenFile.nMaxFile = sizeof(strGunzPath);
					ofOpenFile.lpstrFilter = "Gunz Launcher Binary (GunzLauncher.exe)\0*.exe\0";	//** Filter
					ofOpenFile.nFilterIndex = 1;
					ofOpenFile.lpstrFileTitle = NULL;
					ofOpenFile.nMaxFileTitle = 0;
					ofOpenFile.lpstrInitialDir = NULL;
					ofOpenFile.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY; //** Flags
					ofOpenFile.lpstrTitle = "Browse for GunzLauncher\0";

					if(GetOpenFileName(&ofOpenFile) == TRUE) //** User hit OK
					{
						SetWindowText(GetDlgItem(hWnd, IDC_GUNZPATH), strGunzPath);
						WriteConfigFile(hWnd);	//** Save new data
					}
				}
				break;

				case IDC_INJECT:
				{	
					DWORD dwAttr;
					dwAttr = GetFileAttributes(strGunzPath);
					if(dwAttr != 0xFFFFFFFF)
					{
						char *strLastSlash;
						strLastSlash = strrchr(strGunzPath, '\\');
						int iLength = strLastSlash - strGunzPath + 1;

						if(iLength < 0)
						{
							break;
						}

						LPTSTR strDirectory = new TCHAR[MAX_PATH];
						LPTSTR strDirectory2 = new TCHAR[MAX_PATH];
						strncpy(strDirectory, strGunzPath, iLength);
						strncpy(strDirectory2, strGunzPath, iLength);

						strDirectory[iLength] = '\0';

						strcat(strDirectory, "D3D9.dll");

						CopyFile("D3D9.dll",  strDirectory, FALSE);
			
						STARTUPINFO         siStartupInfo;
						PROCESS_INFORMATION piProcessInfo;

						memset(&siStartupInfo, 0, sizeof(siStartupInfo));
						memset(&piProcessInfo, 0, sizeof(piProcessInfo));

						siStartupInfo.cb = sizeof(siStartupInfo);
					
						//** Launch our applicatiom... If it fails, let the user know
						CreateProcess(strGunzPath, " /internationaledt", 0, 0, FALSE, CREATE_DEFAULT_ERROR_MODE, 0, strDirectory2, &siStartupInfo, &piProcessInfo);
						
						strcat(strHookDir, "\\APIHook.dll");
						//InjectDLL(piProcessInfo.dwProcessId, strHookDir);
					}
					else
					{
						DWORD dwError = GetLastError();

						switch(dwError)
						{
							case ERROR_FILE_NOT_FOUND:
								sprintf(strMessage, "Error: Could not find \"%s\".", strGunzPath);
								MessageBox(GetActiveWindow(), strMessage, "[:: hAx Windower ::]", MB_OK + MB_ICONERROR);
							break;
			
							case ERROR_PATH_NOT_FOUND:
								MessageBox(GetActiveWindow(), "Error: Invalid path to Gunz Launcher", "[:: hAx Windower ::]", MB_OK + MB_ICONERROR);
							break;
			
							case ERROR_ACCESS_DENIED:
								sprintf(strMessage, "Error: Access denied to '%s'.", strGunzPath);
								MessageBox(GetActiveWindow(),  strMessage, "[:: hAx Windower ::]", MB_OK + MB_ICONERROR);
							break;

							default:
								MessageBox(GetActiveWindow(), "Error: A unknown error has occured.", "[:: hAx Windower ::]", MB_OK + MB_ICONERROR);
							break;
						}
					}

					/*
					x = SendMessage(GetDlgItem(hWnd, IDC_PROCESSES), CB_GETCURSEL, NULL, NULL);

					if(x != CB_ERR)
					{
						SendMessage(GetDlgItem(hWnd, IDC_PROCESSES), CB_GETLBTEXT, (WPARAM)x, (LPARAM)strBuffer0);
						if(InjectDLL(GetProcessID("gunz.exe"), strGunzPath) == TRUE) //** Call the inject proc
						{
							sprintf(strBuffer1, "Successfully injected '%s' into '%s'!", strGunzPath, strBuffer0);
							MessageBox(hWnd, strBuffer1, "[:: hAx Windower ::]", MB_OK + MB_ICONINFORMATION);
						}
					}
					else
					{
						MessageBox(hWnd, "Error: No process selected.", "[:: hAx Windower ::]", MB_OK + MB_ICONERROR);
					}
					*/
					PostQuitMessage(0);
				}
				break;

				case IDC_REG:
				{

					DWORD dwAttr = GetFileAttributes(strGunzPath);
					if(dwAttr != 0xFFFFFFFF)
					{
						char *strLastSlash;
						strLastSlash = strrchr(strGunzPath, '\\');
						int iLength = strLastSlash - strGunzPath + 1;

						if(iLength < 0)
						{
							break;
						}

						LPTSTR strDirectory = new TCHAR[MAX_PATH];
						LPTSTR strDirectory2 = new TCHAR[MAX_PATH];
						strncpy(strDirectory, strGunzPath, iLength);
						strncpy(strDirectory2, strGunzPath, iLength);

						strDirectory[iLength] = '\0';

						strcat(strDirectory, "D3D9.dll");

						DeleteFile(strDirectory);

						STARTUPINFO         siStartupInfo;
						PROCESS_INFORMATION piProcessInfo;

						memset(&siStartupInfo, 0, sizeof(siStartupInfo));
						memset(&piProcessInfo, 0, sizeof(piProcessInfo));

						siStartupInfo.cb = sizeof(siStartupInfo);
				
						//** Launch our applicatiom... If it fails, let the user know
						CreateProcess(strGunzPath, " /internationaledt", 0, 0, FALSE, CREATE_DEFAULT_ERROR_MODE, 0, strDirectory2, &siStartupInfo, &piProcessInfo);
					}
					else
					{
						DWORD dwError = GetLastError();

						switch(dwError)
						{
							case ERROR_FILE_NOT_FOUND:
								sprintf(strMessage, "Error: Could not find \"%s\".", strGunzPath);
								MessageBox(GetActiveWindow(), strMessage, "[:: hAx Windower ::]", MB_OK + MB_ICONERROR);
							break;
			
							case ERROR_PATH_NOT_FOUND:
								MessageBox(GetActiveWindow(), "Error: Invalid path to GunZ EXE", "[:: hAx Windower ::]", MB_OK + MB_ICONERROR);
							break;
			
							case ERROR_ACCESS_DENIED:
								sprintf(strMessage, "Error: Access denied to '%s'.", strGunzPath);
								MessageBox(GetActiveWindow(),  strMessage, "[:: hAx Windower ::]", MB_OK + MB_ICONERROR);
							break;

							default:
								MessageBox(GetActiveWindow(), "Error: A unknown error has occured.", "[:: hAx Windower ::]", MB_OK + MB_ICONERROR);
							break;
						}
					}

					EndDialog(hWnd, 0);
				}
				break;

				case IDC_ABOUT:
				{
					MessageBox(hWnd, "hAx Windower for GunZ\r\nModified hAx Studios Ltd. DLL Injector by fritz\r\n\r\nA windower for GunZ\r\n- Function:\tInjects two hook DLL's into GunZ to obtain windowed mode.\r\n- Platform(s):\tWindows 2000/XP ONLY!\r\n- Language:\tC++ Win32 API\r\n- Version:\t\t1.2\r\n- Author:\t\tZak Farrington alias fritz\r\n- Homepage:\thttp://hax-studios.net\r\n\r\nCopyright (C) 2005 hAx Studios Ltd. All rights reserved.\r\n\r\nThis program nor hAx Studios Ltd. are in no way affiliated or associated with MAIET entertainment, Inc. or \"GunZ: The Duel\".\r\nAll trademarks are copyright of their respective owners.", "[:: hAx Windower ::]", MB_OK + MB_ICONINFORMATION);
				}
				break;
				
				case IDC_CLOSE:
				{
					EndDialog(hWnd, 0);
				}
				break;
			}
		break;

		case WM_TIMER:
			OnTimer(hWnd, wParam);	//** Our timer event
		break;

		case WM_CLOSE:
			//** Kill timers
			/* KillTimer(hWnd, ENUMERATE_PROC_TIMER); */
		    //** KillTimer(hWnd, EDIT_MODIFY_TIMER);
			
			//** End
			EndDialog(hWnd, 0);
		break;
	}
	
	return FALSE;
}

void OnTimer(HWND hWnd, UINT nID)
{
	//** This event will enumerate our processes every ten seconds and update our process list
	/*
	if(nID == ENUMERATE_PROC_TIMER)
	{
		if(EnumerateProcesses(hWnd) == FALSE)
		{
			MessageBox(hWnd, "Error: Could not EnumerateProcesses();\n", "[:: hAx Windower ::]", MB_OK + MB_ICONERROR);
		}
	}
	else 
	*/
	/*
	if(nID == EDIT_MODIFY_TIMER)
	{
		SendMessage(GetDlgItem(hWnd, IDC_GUNZPATH), EM_GETLINE, NULL, (LPARAM)strBuffer0); //** Get data from IDC_HOOKPATH and stick it in strBuffer0

		if(stricmp(strBuffer0, strGunzPath) != 0)	//** Strings are not equal, update data
		{
			strcpy(strGunzPath, strBuffer0);		//** Update
			WriteConfigFile(hWnd);					//** Save new data to config file
		}
	}
	*/
}

/*
BOOL EnumerateProcesses(HWND hWnd)
{
		HANDLE hProcessSnap;
		PROCESSENTRY32 pe32;
		//int nListAmount;

		x = SendMessage(GetDlgItem(hWnd, IDC_PROCESSES), CB_GETCURSEL, NULL, NULL);

		if(x != CB_ERR)
		{
			SendMessage(GetDlgItem(hWnd, IDC_PROCESSES), CB_GETLBTEXT, (WPARAM)x, (LPARAM)strBuffer0);
		}
		

		hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		if(hProcessSnap == INVALID_HANDLE_VALUE)
		{
			MessageBox(hWnd, "Error: Could not CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);\n", "[:: hAx Windower ::]", MB_OK + MB_ICONERROR);
			CloseHandle(hProcessSnap);
			return FALSE;
		}
		else
		{
			SendMessage(GetDlgItem(hWnd, IDC_PROCESSES), CB_RESETCONTENT, NULL, NULL); //** Clear list


			pe32.dwSize = sizeof(PROCESSENTRY32); //** I had problems for weeks until I realized this was missing -.-

	
			if(Process32First(hProcessSnap, &pe32) == NULL)
			{
				CloseHandle(hProcessSnap);
				MessageBox(hWnd, "Error: Could not Process32First(hProcessSnap, ...);\n", "[:: hAx Windower ::]", MB_OK + MB_ICONERROR);
				return FALSE;
			}
			else
			{

				do
				{
					if(SendMessage(GetDlgItem(hWnd, IDC_PROCESSES), CB_FINDSTRING, (WPARAM)-1, (LPARAM)pe32.szExeFile) == CB_ERR)
					{
						SendMessage(GetDlgItem(hWnd, IDC_PROCESSES), CB_ADDSTRING, NULL, (LPARAM)pe32.szExeFile); //** Add the process to our list of processes
					}

				} while(Process32Next(hProcessSnap, &pe32));
			}

		}

		CloseHandle(hProcessSnap);

		if(x != CB_ERR)
		{
			SendMessage(GetDlgItem(hWnd, IDC_PROCESSES), CB_SELECTSTRING, NULL, (LPARAM)strBuffer0);
		}
		
		return TRUE;
}
*/

BOOL ReadConfigFile(HWND hWnd)
{
	HANDLE hConfigHandle;

	//** Get the working directory of our exectuable
	if(GetCurrentDirectory(sizeof(strConfigPath), strConfigPath) == NULL) //** If it fails,
	{
		//** Let the user know...
		
		sprintf(strMessage, "Error: Could not GetCurrentDirectory(%d, \"%s\");\n\nThis program will now close.", sizeof(strConfigPath), strConfigPath);

		MessageBox(hWnd, strMessage, "[:: hAx Windower ::]", MB_OK + MB_ICONERROR); 
		return FALSE;

	}
	else //** Path retrieved
	{
		strcat(strConfigPath, "\\hAxWindower.cfg"); //** Append our filename to the path(ConfigPath)
		
		
		//** Attempt to open our configuration file, if it can't, it doesn't exist yet
		hConfigHandle = CreateFile(strConfigPath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);


		if(hConfigHandle == INVALID_HANDLE_VALUE) //** Configuration doesn't exist
		{
			return FALSE;
		}
		else //** File exists, read it
		{
			DWORD dwBytesRead;

			for(int x = 0; dwBytesRead != 0; x++)
			{
				ReadFile(hConfigHandle, &strBuffer0[x], 1, &dwBytesRead, NULL);

				if((strBuffer0[x] == 0xA) && (strBuffer0[x-1] == 0xD))
				{
					if(sscanf(strBuffer0, "%[^=]= %[^\r\n]", strBuffer1, strBuffer2) == 2)
					{
						if(stricmp(strBuffer1, "GunZPath") == 0)
						{
							strcpy(strGunzPath, strBuffer2);
						}
					}
				}
			}

			CloseHandle(hConfigHandle); //** Close file handle
		}
	}

	return TRUE;
}

BOOL WriteConfigFile(HWND hWnd)
{
	HANDLE hConfigHandle = CreateFile(strConfigPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
				

	if(hConfigHandle == INVALID_HANDLE_VALUE)
	{
		//** Can't create config... notify the user
			
		sprintf(strMessage, "Error: Could not CreateFile(\"%s\", GENERIC_WRITE, 0, NULL, CREAT_ALWAYS, FILE_ATTRIBUTE_NORMAL);\n\nThis program will now close.", strConfigPath);
		MessageBox(NULL, strMessage, "[:: hAx Windower ::]", MB_OK + MB_ICONERROR);

		return FALSE;
	}
	else //** File created, time to write our stuffs to it
	{
		DWORD dwBytesWritten = 0;	//** Incase we need this later

		sprintf(strBuffer0, "GunZPath=%s\r\n", strGunzPath);

		//** Write one character at a time, make sure the characters decimal value is greater than 0
		for(int x = 0; x < sizeof(strBuffer0) && strBuffer0[x] > 0; x++)
		{
			WriteFile(hConfigHandle, &strBuffer0[x], 1, &dwBytesWritten, NULL);
		}

		SetEndOfFile(hConfigHandle);	//** Set EOF
	
		CloseHandle(hConfigHandle);		//** Close Handle
	}

	return TRUE;
}
