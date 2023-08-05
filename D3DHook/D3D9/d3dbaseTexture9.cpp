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


NewIDirect3DBaseTexture9::NewIDirect3DBaseTexture9 (NewIDirect3DDevice9 *pDevice, IDirect3DBaseTexture9* pBaseTexture)
{
	m_refCount			= 1;
	m_pd3dDevice		= pDevice;	
	m_pd3dBaseTexture	= pBaseTexture;
}

HRESULT __stdcall NewIDirect3DBaseTexture9::QueryInterface(REFIID iid, void ** ppvObject)
{
	return m_pd3dBaseTexture->QueryInterface(iid,  ppvObject);
}

ULONG	__stdcall NewIDirect3DBaseTexture9::AddRef(void)
{
	m_refCount++;			
	m_refCount =m_pd3dBaseTexture->AddRef();	
	return m_refCount;
}

ULONG	__stdcall NewIDirect3DBaseTexture9::Release(void)
{
	m_refCount--;			
	m_refCount = m_pd3dBaseTexture->Release();		
	if(m_refCount <= 0)
	{
		m_pd3dDevice->RemoveNewBaseTexture(this); 
		delete this;
		return 0;
	}

	return m_refCount;
}

HRESULT __stdcall NewIDirect3DBaseTexture9::GetDevice(IDirect3DDevice9** ppDevice) 
{
	return m_pd3dDevice->GetDevice(ppDevice);
}

HRESULT __stdcall NewIDirect3DBaseTexture9::SetPrivateData(REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) 
{
	return m_pd3dBaseTexture->SetPrivateData( refguid, pData, SizeOfData, Flags); 
}

HRESULT __stdcall NewIDirect3DBaseTexture9::GetPrivateData(REFGUID refguid,void* pData,DWORD* pSizeOfData) 
{
	return m_pd3dBaseTexture->GetPrivateData( refguid, pData,  pSizeOfData); 
}

HRESULT __stdcall NewIDirect3DBaseTexture9::FreePrivateData(REFGUID refguid) 
{
	return m_pd3dBaseTexture->FreePrivateData(refguid); 	
}

DWORD   __stdcall NewIDirect3DBaseTexture9::SetPriority(DWORD PriorityNew) 
{
	return m_pd3dBaseTexture->SetPriority(PriorityNew); 	
}

DWORD   __stdcall NewIDirect3DBaseTexture9::GetPriority()
{
	return m_pd3dBaseTexture->GetPriority();	
}

void    __stdcall NewIDirect3DBaseTexture9::PreLoad() 
{
	m_pd3dBaseTexture->PreLoad() ;	
}

D3DRESOURCETYPE __stdcall NewIDirect3DBaseTexture9::GetType() 
{
	return m_pd3dBaseTexture->GetType() ;	
}

DWORD   __stdcall NewIDirect3DBaseTexture9::SetLOD(DWORD LODNew) 
{
	return m_pd3dBaseTexture->SetLOD(LODNew) ;	
}

DWORD   __stdcall NewIDirect3DBaseTexture9::GetLOD() 
{
	return m_pd3dBaseTexture->GetLOD(); 	
}

DWORD   __stdcall NewIDirect3DBaseTexture9::GetLevelCount() 
{
	return m_pd3dBaseTexture->GetLevelCount();	
}

HRESULT __stdcall NewIDirect3DBaseTexture9::SetAutoGenFilterType(D3DTEXTUREFILTERTYPE FilterType) 
{
	return m_pd3dBaseTexture->SetAutoGenFilterType(FilterType); 	
}

D3DTEXTUREFILTERTYPE __stdcall NewIDirect3DBaseTexture9::GetAutoGenFilterType() 
{
	return m_pd3dBaseTexture->GetAutoGenFilterType(); 	
}

void __stdcall NewIDirect3DBaseTexture9::GenerateMipSubLevels() 
{
	m_pd3dBaseTexture->GenerateMipSubLevels(); 	
}

