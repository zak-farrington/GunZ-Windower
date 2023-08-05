/*
		hAx D3D Hook v1.0 by Zak Farrington alias fritz <fritz@hax-studios.net>
		A D3D9 Wrapper for GunZ
		Copyright (C) 2005 hAx Studios Ltd.
		All rights reserved.

		http://hax-studios.net

		Original Wrapper by Jian Yang (ph.D) <fsword73@hotmail.com>
*/

#include <stdio.h>
#include <d3d9.h>
#include "Direct3D9.h"
#include "Hook.h"

extern "C" 
{
	IDirect3D9 * WINAPI Direct3DCreate9(UINT SDKVersion)
	{
		
		if(SDKVersion != D3D_SDK_VERSION)
		{
			MessageBox(GetActiveWindow(), "WARNING: Direct3D SDK versions don't match!", "[:: Alert ::]", MB_OK + MB_ICONWARNING);
		}	
	
		OpenMSD3D9();

		NewIDirect3D9 *pNewd3d9 = new NewIDirect3D9();

		return pNewd3d9;

	}


	void WINAPI D3DPERF_SetMarker(D3DCOLOR col, LPCWSTR wszName)
	{
		D3DPERF_SetMarker(col, wszName);
	}


	int WINAPI D3DPERF_BeginEvent(D3DCOLOR col, LPCWSTR wszName)
	{
		return D3DPERF_BeginEvent(col, wszName);
	}


	int WINAPI D3DPERF_EndEvent(VOID)
	{
		return D3DPERF_EndEvent();
	}

	
	void WINAPI D3DPERF_SetRegion(D3DCOLOR col, LPCWSTR wszName)
	{
		D3DPERF_SetRegion(col, wszName);
	}


	bool WINAPI D3DPERF_QueryRepeatFrame(VOID)
	{
		return D3DPERF_QueryRepeatFrame();
	}
	
}
