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

NewIDirect3DCubeTexture9::NewIDirect3DCubeTexture9(NewIDirect3DDevice9 *pDevice, IDirect3DCubeTexture9 *pCubeTexture)
{
	m_refCount = 0;
	m_pd3dDevice = pDevice;
	m_pd3dCubeTexture = pCubeTexture;
}

HRESULT __stdcall NewIDirect3DCubeTexture9::QueryInterface(REFIID iid, void ** ppvObject)
{
	return m_pd3dCubeTexture->QueryInterface(iid, ppvObject);
}


ULONG	__stdcall NewIDirect3DCubeTexture9::AddRef(void)
{
	m_refCount++;
	m_refCount = m_pd3dCubeTexture->AddRef();
	return m_refCount;
}


ULONG	__stdcall NewIDirect3DCubeTexture9::Release(void)
{
	m_refCount--;
	m_refCount =  m_pd3dCubeTexture->Release();

	if(m_refCount <=0)
	{
		m_pd3dDevice->RemoveNewCubeTexture(this); 
		delete this;
		return 0;
	}

	return m_refCount;
}

HRESULT __stdcall NewIDirect3DCubeTexture9::GetDevice(IDirect3DDevice9** ppDevice)
{
	return m_pd3dDevice->GetDevice(ppDevice);
}


HRESULT __stdcall NewIDirect3DCubeTexture9::SetPrivateData(REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags)
{
	return m_pd3dCubeTexture->SetPrivateData( refguid, pData, SizeOfData, Flags);
}

HRESULT __stdcall NewIDirect3DCubeTexture9::GetPrivateData(REFGUID refguid,void* pData,DWORD* pSizeOfData)
{
	return m_pd3dCubeTexture->GetPrivateData( refguid, pData, pSizeOfData);
}

HRESULT __stdcall NewIDirect3DCubeTexture9::FreePrivateData(REFGUID refguid)
{

	return m_pd3dCubeTexture->FreePrivateData(refguid);
}

DWORD   __stdcall NewIDirect3DCubeTexture9::SetPriority(DWORD PriorityNew)
{
	return m_pd3dCubeTexture->SetPriority(PriorityNew);
}

DWORD   __stdcall NewIDirect3DCubeTexture9::GetPriority()
{

	return m_pd3dCubeTexture->GetPriority();
}

void    __stdcall NewIDirect3DCubeTexture9::PreLoad()
{
	m_pd3dCubeTexture->PreLoad();
}

D3DRESOURCETYPE __stdcall NewIDirect3DCubeTexture9::GetType()
{

	return m_pd3dCubeTexture->GetType();
}

DWORD   __stdcall NewIDirect3DCubeTexture9::SetLOD(DWORD LODNew)
{

	return m_pd3dCubeTexture->SetLOD(LODNew);
}

DWORD   __stdcall NewIDirect3DCubeTexture9::GetLOD()
{

	return m_pd3dCubeTexture->GetLOD();
}

DWORD   __stdcall NewIDirect3DCubeTexture9::GetLevelCount()
{

	return m_pd3dCubeTexture->GetLevelCount();
}

HRESULT __stdcall NewIDirect3DCubeTexture9::SetAutoGenFilterType(D3DTEXTUREFILTERTYPE FilterType)
{

	return m_pd3dCubeTexture->SetAutoGenFilterType(FilterType);
}

D3DTEXTUREFILTERTYPE __stdcall NewIDirect3DCubeTexture9::GetAutoGenFilterType()
{

	return m_pd3dCubeTexture->GetAutoGenFilterType();
}

void    __stdcall NewIDirect3DCubeTexture9::GenerateMipSubLevels() 
{
	m_pd3dCubeTexture->GenerateMipSubLevels() ;
}

HRESULT __stdcall NewIDirect3DCubeTexture9::GetLevelDesc(UINT Level,D3DSURFACE_DESC *pDesc)
{
	return m_pd3dCubeTexture->GetLevelDesc(Level, pDesc);
}

HRESULT __stdcall NewIDirect3DCubeTexture9::GetCubeMapSurface(D3DCUBEMAP_FACES FaceType,UINT Level,IDirect3DSurface9** ppCubeMapSurface)
{
	HRESULT hr;
	IDirect3DSurface9* pCubeMapSurface= NULL;

	if(ppCubeMapSurface == NULL) 
	{
		return m_pd3dCubeTexture->GetCubeMapSurface(FaceType, Level, ppCubeMapSurface);
	}

	hr = m_pd3dCubeTexture->GetCubeMapSurface(FaceType, Level, &pCubeMapSurface);
	if(hr == D3D_OK)
	{
		NewIDirect3DSurface9 *pNewSurface = m_pd3dDevice->GetNewSurface(pCubeMapSurface);
		if(pNewSurface == NULL)
		{
			pNewSurface = new NewIDirect3DSurface9(m_pd3dDevice, pCubeMapSurface); 
			m_pd3dDevice->AddNewSurface(pNewSurface );
		}
		*ppCubeMapSurface = pNewSurface;
	}
	else
	{
		*ppCubeMapSurface = NULL;
	}
	return hr;
}

HRESULT __stdcall NewIDirect3DCubeTexture9::LockRect(D3DCUBEMAP_FACES FaceType,UINT Level,D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags) 
{
	return m_pd3dCubeTexture->LockRect(FaceType, Level, pLockedRect, pRect, Flags); 
}

HRESULT __stdcall NewIDirect3DCubeTexture9::UnlockRect(D3DCUBEMAP_FACES FaceType,UINT Level)
{

	return m_pd3dCubeTexture->UnlockRect(FaceType,  Level);
}

HRESULT __stdcall NewIDirect3DCubeTexture9::AddDirtyRect(D3DCUBEMAP_FACES FaceType,CONST RECT* pDirtyRect) 
{

	return m_pd3dCubeTexture->AddDirtyRect(FaceType, pDirtyRect); 
}
