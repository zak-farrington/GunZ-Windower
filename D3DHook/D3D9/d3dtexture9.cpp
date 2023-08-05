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

NewIDirect3DTexture9::NewIDirect3DTexture9(NewIDirect3DDevice9* pDevice, IDirect3DTexture9 *pTexture)
{
	m_refCount		= 0;
	m_pd3dDevice	= pDevice;
	m_pd3dTexture	= pTexture;	
}


HRESULT __stdcall NewIDirect3DTexture9::QueryInterface(REFIID iid, void ** ppvObject)
{	
	return m_pd3dTexture->QueryInterface(iid, ppvObject);
}

ULONG	__stdcall NewIDirect3DTexture9::AddRef(void)
{
	m_refCount++;
	m_refCount = m_pd3dTexture->AddRef();
	return m_refCount;
}

ULONG	__stdcall NewIDirect3DTexture9::Release(void)
{
	m_refCount--;	

	m_refCount = m_pd3dTexture->Release();	
	if(m_refCount <=0)
	{

		m_pd3dDevice->RemoveNewTexture(this); 
		delete this;
		return 0;
	}

	return m_refCount; 
}

HRESULT __stdcall NewIDirect3DTexture9::GetDevice(IDirect3DDevice9** ppDevice) 
{
	return m_pd3dDevice->GetDevice(ppDevice); 
}

HRESULT __stdcall NewIDirect3DTexture9::SetPrivateData(REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) 
{
	return m_pd3dTexture->SetPrivateData(refguid, pData, SizeOfData, Flags); 
}

HRESULT __stdcall NewIDirect3DTexture9::GetPrivateData(REFGUID refguid,void* pData,DWORD* pSizeOfData) 
{
	return m_pd3dTexture->GetPrivateData(refguid, pData, pSizeOfData); 
}

HRESULT __stdcall NewIDirect3DTexture9::FreePrivateData(REFGUID refguid) 
{
	return m_pd3dTexture->FreePrivateData(refguid); 	
}

DWORD   __stdcall NewIDirect3DTexture9::SetPriority(DWORD PriorityNew) 
{
	return m_pd3dTexture->SetPriority(PriorityNew); 	
}

DWORD   __stdcall NewIDirect3DTexture9::GetPriority() 
{
	return m_pd3dTexture->GetPriority(); 	
}

void    __stdcall NewIDirect3DTexture9::PreLoad() 
{
	m_pd3dTexture->PreLoad();	
}

D3DRESOURCETYPE __stdcall NewIDirect3DTexture9::GetType() 
{
	return m_pd3dTexture->GetType(); 	
}

DWORD   __stdcall NewIDirect3DTexture9::SetLOD(DWORD LODNew) 
{
	return m_pd3dTexture->SetLOD(LODNew); 	
}

DWORD   __stdcall NewIDirect3DTexture9::GetLOD() 
{
	return m_pd3dTexture->GetLOD();	
}

DWORD   __stdcall NewIDirect3DTexture9::GetLevelCount() 
{
	return m_pd3dTexture->GetLevelCount(); 	
}
HRESULT __stdcall NewIDirect3DTexture9::SetAutoGenFilterType(D3DTEXTUREFILTERTYPE FilterType) 
{
	return m_pd3dTexture->SetAutoGenFilterType(FilterType);
}

D3DTEXTUREFILTERTYPE __stdcall NewIDirect3DTexture9::GetAutoGenFilterType() 
{
	return m_pd3dTexture->GetAutoGenFilterType(); 	
}
void __stdcall NewIDirect3DTexture9::GenerateMipSubLevels() 
{
	m_pd3dTexture->GenerateMipSubLevels(); 	
}


HRESULT __stdcall NewIDirect3DTexture9::GetLevelDesc(UINT Level,D3DSURFACE_DESC *pDesc)
{
	return m_pd3dTexture->GetLevelDesc( Level, pDesc);	
}

HRESULT __stdcall NewIDirect3DTexture9::GetSurfaceLevel(UINT Level,IDirect3DSurface9** ppSurfaceLevel)
{
	HRESULT hr;
	IDirect3DSurface9* pSurfaceLevel = NULL;
	if(ppSurfaceLevel == NULL)
	{
		return m_pd3dTexture->GetSurfaceLevel(Level, ppSurfaceLevel);
	}

	hr = m_pd3dTexture->GetSurfaceLevel(Level, &pSurfaceLevel);

	if(hr == D3D_OK)
	{
		NewIDirect3DSurface9* pNewSurface = m_pd3dDevice->GetNewSurface(pSurfaceLevel);  
		if(pNewSurface  == NULL)
		{			
			pNewSurface  = new NewIDirect3DSurface9(m_pd3dDevice, pSurfaceLevel);
			m_pd3dDevice->AddNewSurface(pNewSurface);
		}
		*ppSurfaceLevel = pNewSurface;
	}
	else
	{
		ppSurfaceLevel = NULL;
	}

	return hr;
}

HRESULT __stdcall NewIDirect3DTexture9::LockRect(UINT Level,D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags)
{
	return m_pd3dTexture->LockRect(Level, pLockedRect, pRect, Flags);	
}

HRESULT __stdcall NewIDirect3DTexture9::UnlockRect(UINT Level)
{
	return m_pd3dTexture->UnlockRect(Level);	
}

HRESULT __stdcall NewIDirect3DTexture9::AddDirtyRect(CONST RECT* pDirtyRect)
{
	return m_pd3dTexture->AddDirtyRect(pDirtyRect);	
}
