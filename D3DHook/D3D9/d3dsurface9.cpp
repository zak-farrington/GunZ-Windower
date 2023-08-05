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


NewIDirect3DSurface9::NewIDirect3DSurface9(NewIDirect3DDevice9* pDevice, IDirect3DSurface9 *pSurface)
{
	m_refCount		= 0;
	m_pd3dDevice	= pDevice;
	m_pd3dSurface	= pSurface;
}


HRESULT __stdcall NewIDirect3DSurface9::QueryInterface(REFIID iid, void ** ppvObject)
{
	return m_pd3dSurface->QueryInterface(iid, ppvObject);
}


ULONG	__stdcall NewIDirect3DSurface9::AddRef(void)
{
	m_refCount++;
	m_refCount = m_pd3dSurface->AddRef();
	return m_refCount;

}

ULONG	__stdcall NewIDirect3DSurface9::Release(void)
{
	m_refCount--;
	m_refCount = m_pd3dSurface->Release();
	if(m_refCount <= 0)
	{
		m_pd3dDevice->RemoveNewSurface(this); 
		delete this;
		return 0;
	}
	return m_refCount;
}

HRESULT __stdcall NewIDirect3DSurface9::GetDevice(IDirect3DDevice9** ppDevice)
{
	return m_pd3dDevice->GetDevice(ppDevice);
}

HRESULT __stdcall NewIDirect3DSurface9::SetPrivateData(REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags)
{
	return m_pd3dSurface->SetPrivateData(refguid,  pData, SizeOfData, Flags);
}

HRESULT __stdcall NewIDirect3DSurface9::GetPrivateData(REFGUID refguid,void* pData,DWORD* pSizeOfData)
{
	return m_pd3dSurface->GetPrivateData(refguid,  pData, pSizeOfData);
}

HRESULT __stdcall NewIDirect3DSurface9::FreePrivateData(REFGUID refguid)
{
	return m_pd3dSurface->FreePrivateData(refguid);
}


DWORD   __stdcall NewIDirect3DSurface9::SetPriority(DWORD PriorityNew)
{
	return m_pd3dSurface->SetPriority(PriorityNew);
}

DWORD   __stdcall NewIDirect3DSurface9::GetPriority()
{
	return m_pd3dSurface->GetPriority();
}

void    __stdcall NewIDirect3DSurface9::PreLoad()
{
	m_pd3dSurface->PreLoad();
}

D3DRESOURCETYPE __stdcall NewIDirect3DSurface9::GetType()
{
	return m_pd3dSurface->GetType();
}

HRESULT __stdcall NewIDirect3DSurface9::GetContainer(REFIID riid,void** ppContainer)
{
	return m_pd3dSurface->GetContainer(riid,  ppContainer);
}

HRESULT __stdcall NewIDirect3DSurface9::GetDesc(D3DSURFACE_DESC *pDesc)
{
	return m_pd3dSurface->GetDesc(pDesc);
}

HRESULT __stdcall NewIDirect3DSurface9::LockRect(D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags)
{
	return  m_pd3dSurface->LockRect( pLockedRect, pRect, Flags);
}

HRESULT __stdcall NewIDirect3DSurface9::UnlockRect()
{
	return  m_pd3dSurface->UnlockRect();
}

HRESULT __stdcall NewIDirect3DSurface9::GetDC(HDC *phdc)
{
	return  m_pd3dSurface->GetDC(phdc);
}


HRESULT __stdcall NewIDirect3DSurface9::ReleaseDC(HDC hdc)
{
	return  m_pd3dSurface->ReleaseDC(hdc);
}

