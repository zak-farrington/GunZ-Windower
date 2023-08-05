/*
		hAx D3D Hook v1.0 by Zak Farrington alias fritz <fritz@hax-studios.net>
		A D3D9 Wrapper for GunZ
		Copyright (C) 2005 hAx Studios Ltd.
		All rights reserved.

		http://hax-studios.net

		Original Wrapper by Jian Yang (ph.D) <fsword73@hotmail.com>
*/

#include <windows.h>
#include "Direct3D9.h"
#include "Hook.h"
#include "resource.h"

NewIDirect3D9::NewIDirect3D9()
{
	m_refCount   = 1;
	m_pDirect3D9 = (IDirect3D9*)pDirect3DCreate9(D3D_SDK_VERSION);
}

HRESULT __stdcall NewIDirect3D9::QueryInterface(REFIID iid, void ** ppvObject)
{
	return  m_pDirect3D9->QueryInterface(iid, ppvObject);
}

ULONG	__stdcall NewIDirect3D9::AddRef(void)
{	
	m_refCount++; 
	m_refCount = m_pDirect3D9->AddRef();
	return m_refCount;
}

ULONG	__stdcall NewIDirect3D9::Release(void)
{
	m_refCount--; 
	m_refCount = m_pDirect3D9->Release();	
	if(m_refCount <= 0)
	{			
		delete this;
		return 0;
	}
	return m_refCount;
}

/*** IDirect3D9 methods ***/
HRESULT __stdcall NewIDirect3D9::RegisterSoftwareDevice(void* pInitializeFunction)
{
	return m_pDirect3D9->RegisterSoftwareDevice(pInitializeFunction);
}


UINT    __stdcall NewIDirect3D9::GetAdapterCount()
{
	
	return m_pDirect3D9->GetAdapterCount();
}

HRESULT  __stdcall NewIDirect3D9::GetAdapterIdentifier(UINT Adapter, DWORD Flags, D3DADAPTER_IDENTIFIER9* pIdentifier)
{
	return m_pDirect3D9->GetAdapterIdentifier(Adapter, Flags, pIdentifier);
}

UINT    __stdcall NewIDirect3D9::GetAdapterModeCount(UINT Adapter, D3DFORMAT Format) 
{
	return m_pDirect3D9->GetAdapterModeCount(Adapter,Format);
}

HRESULT __stdcall NewIDirect3D9::EnumAdapterModes(UINT Adapter, D3DFORMAT Format,UINT Mode,D3DDISPLAYMODE* pMode)
{
	return m_pDirect3D9->EnumAdapterModes(Adapter, Format, Mode, pMode);
}


HRESULT __stdcall NewIDirect3D9::GetAdapterDisplayMode(UINT Adapter, D3DDISPLAYMODE* pMode)
{
	return m_pDirect3D9->GetAdapterDisplayMode(Adapter, pMode);
}


HRESULT __stdcall NewIDirect3D9::CheckDeviceType(UINT iAdapter, D3DDEVTYPE DevType, D3DFORMAT DisplayFormat, D3DFORMAT BackBufferFormat,BOOL bWindowed)
{
	return m_pDirect3D9->CheckDeviceType(iAdapter,DevType,DisplayFormat,BackBufferFormat,bWindowed);
}

HRESULT __stdcall NewIDirect3D9::CheckDeviceFormat(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat,DWORD Usage,D3DRESOURCETYPE RType,D3DFORMAT CheckFormat)
{
	return m_pDirect3D9->CheckDeviceFormat(Adapter, DeviceType, AdapterFormat,Usage, RType,CheckFormat);
}

HRESULT __stdcall NewIDirect3D9::CheckDeviceMultiSampleType(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SurfaceFormat,BOOL Windowed,D3DMULTISAMPLE_TYPE MultiSampleType,DWORD* pQualityLevels)
{
	return m_pDirect3D9->CheckDeviceMultiSampleType(Adapter, DeviceType, SurfaceFormat, Windowed, MultiSampleType, pQualityLevels);
}

HRESULT __stdcall NewIDirect3D9::CheckDepthStencilMatch(UINT Adapter, D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,D3DFORMAT RenderTargetFormat,D3DFORMAT DepthStencilFormat)
{
	return m_pDirect3D9->CheckDepthStencilMatch(Adapter, DeviceType, AdapterFormat, RenderTargetFormat, DepthStencilFormat);
}

HRESULT __stdcall NewIDirect3D9::CheckDeviceFormatConversion(UINT Adapter, D3DDEVTYPE DeviceType,D3DFORMAT SourceFormat,D3DFORMAT TargetFormat)
{
	return m_pDirect3D9->CheckDeviceFormatConversion( Adapter, DeviceType, SourceFormat, TargetFormat);
}

HRESULT __stdcall NewIDirect3D9::GetDeviceCaps(UINT Adapter,D3DDEVTYPE DeviceType,D3DCAPS9* pCaps)
{
	return m_pDirect3D9->GetDeviceCaps(Adapter, DeviceType, pCaps);
}

HMONITOR  __stdcall NewIDirect3D9::GetAdapterMonitor(UINT Adapter)
{
	return m_pDirect3D9->GetAdapterMonitor(Adapter);
}

HRESULT __stdcall NewIDirect3D9::CreateDevice(UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DDevice9** ppReturnedDeviceInterface)
{ 
	D3DPRESENT_PARAMETERS* pParams = new D3DPRESENT_PARAMETERS();
	D3DDISPLAYMODE* dmode = new D3DDISPLAYMODE();

	if(m_pDirect3D9->GetAdapterDisplayMode(Adapter, dmode) == D3DERR_INVALIDCALL)
	{
		MessageBox(GetActiveWindow(), "Could not GetAdapterDisplayMode()", "[:: Error ::]", MB_OK + MB_ICONERROR);
	}

	HWND hGunz = FindWindow("RealSpace2", NULL);				//** Locate the Gunz window by it's class name
	HINSTANCE hInstance = (HINSTANCE)GetModuleHandle("Gunz");	//** Get main hInstance

	if((hGunz != NULL)) //** If Gunz window is found and it's instance retrieved
	{
		//** Set window styles so it runs in a real window
		SetWindowLong(hGunz, GWL_STYLE, WS_SYSMENU | WS_BORDER | WS_CAPTION | WS_MINIMIZEBOX | WS_CLIPCHILDREN | WS_CLIPSIBLINGS);

		//** Repaint window
		//MoveWindow(hGunz, 0, 0, 1024, 768, TRUE);

		SetWindowText(hGunz, "GunZ  -  hAx Windower v1.2 by fritz [http://hax-studios.net]"); //** Set new title
	
		SendMessage(hGunz, WM_SETICON, IMAGE_ICON, (LPARAM)LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MAIN)));	//** Set a pretty icon

		//** Bring window to top
		BringWindowToTop(hGunz);

	}
	else if(hGunz == NULL)
	{
		MessageBox(GetActiveWindow(), "Could not find Gunz window", "[:: Error ::]", MB_OK + MB_ICONERROR);
	}
	else if(hInstance == NULL)
	{
		MessageBox(GetActiveWindow(), "Could not retrieve Gunz module instance.", "[:: Error ::]", MB_OK + MB_ICONERROR);
	}


	pParams->BackBufferWidth = pPresentationParameters->BackBufferWidth;
	pParams->BackBufferHeight = pPresentationParameters->BackBufferHeight;
	pParams->BackBufferFormat = pPresentationParameters->BackBufferFormat;
	pParams->BackBufferCount = pPresentationParameters->BackBufferCount;
	pParams->MultiSampleType = pPresentationParameters->MultiSampleType;
	pParams->MultiSampleQuality = pPresentationParameters->MultiSampleQuality;
	pParams->SwapEffect = D3DSWAPEFFECT_DISCARD;
	pParams->hDeviceWindow = pPresentationParameters->hDeviceWindow;
	pParams->Windowed = true;
	pParams->EnableAutoDepthStencil = pPresentationParameters->EnableAutoDepthStencil;
	pParams->AutoDepthStencilFormat = pPresentationParameters->AutoDepthStencilFormat;
	pParams->Flags = pPresentationParameters->Flags;
	pParams->FullScreen_RefreshRateInHz = pPresentationParameters->FullScreen_RefreshRateInHz;
    pParams->PresentationInterval = pPresentationParameters->PresentationInterval;
	
	IDirect3DDevice9* pDirect3DDevice9;
	HRESULT Result = m_pDirect3D9->CreateDevice(Adapter, DeviceType, hFocusWindow, BehaviorFlags, pParams, &pDirect3DDevice9);
	
	switch(Result)
	{
		case D3DERR_NOTAVAILABLE:
			MessageBox(GetActiveWindow(), "Device does not support this method.", "[:: Error ::]", MB_OK + MB_ICONERROR);
		break;
		
		case D3DERR_INVALIDCALL:
			MessageBox(GetActiveWindow(), "Method call invalid.", "[:: Error ::]", MB_OK + MB_ICONERROR);
		break;

		case D3DERR_OUTOFVIDEOMEMORY:
			MessageBox(GetActiveWindow(), "Out of video memory.", "[:: Error ::]", MB_OK + MB_ICONERROR);
		break;

		case D3DERR_DEVICELOST:
			MessageBox(GetActiveWindow(), "Device lost.", "[:: Error ::]", MB_OK + MB_ICONERROR);
		break;
	} 

	*ppReturnedDeviceInterface = new NewIDirect3DDevice9(this, pDirect3DDevice9);


	delete pParams;
	delete dmode;



	return Result;
}