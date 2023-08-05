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

HMODULE  g_hd3d9 = NULL;

Proto_Direct3DCreate9 pDirect3DCreate9 = NULL;


BOOL OpenMSD3D9()
{
	char szFileName[512];
	UINT ret;

	if(g_hd3d9 && pDirect3DCreate9)
		return TRUE;

	ret = GetSystemDirectory(szFileName, 256);
	if(ret <= 0)
	{
		MessageBox(NULL, "tell fritzy if j00 see this", "BIG ERROR NUMBER 2", MB_ICONERROR);
		return FALSE;
	}

	strcat(szFileName, "\\D3D9.dll");
	g_hd3d9 = LoadLibrary(szFileName);
	if(g_hd3d9 == NULL)
	{
		MessageBox(NULL, "tell fritzy if j00 see this", "BIG ERROR NUMBER 3", MB_ICONERROR);
		return FALSE;
	}

	pDirect3DCreate9 = (Proto_Direct3DCreate9)GetProcAddress(g_hd3d9, "Direct3DCreate9");

	if(pDirect3DCreate9 == NULL)
	{
		MessageBox(NULL, "tell fritzy if j00 see this", "BIG ERROR NUMBER 4", MB_ICONERROR);
		return FALSE;
	}
	return TRUE;
}


BOOL CloseMSD3D9()
{
	BOOL ret = TRUE;
	pDirect3DCreate9 = NULL;

	if(g_hd3d9)
	{
		ret = FreeLibrary(g_hd3d9);
	}
	g_hd3d9 = NULL;

	return ret;	
}