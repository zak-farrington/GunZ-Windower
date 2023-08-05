/*
		hAx D3D Hook v1.0 by Zak Farrington alias fritz <fritz@hax-studios.net>
		A D3D9 Wrapper for GunZ
		Copyright (C) 2005 hAx Studios Ltd.
		All rights reserved.

		http://hax-studios.net

		Original Wrapper by Jian Yang (ph.D) <fsword73@hotmail.com>
*/

#define STRICT
#include <windows.h>
#include "Direct3D9.h"

NewIDirect3DVolume9::NewIDirect3DVolume9(NewIDirect3DDevice9 *pDevice, IDirect3DVolume9* pVolume)
{
	m_refCount = 0;
	m_pd3dDevice = pDevice;
	m_pd3dVolume = pVolume;
}


HRESULT __stdcall NewIDirect3DVolume9::QueryInterface(REFIID iid, void ** ppvObject)
{
	return m_pd3dVolume->QueryInterface(iid, ppvObject);
}


ULONG	__stdcall NewIDirect3DVolume9::AddRef(void)
{
	m_refCount++;
	m_pd3dVolume->AddRef();
	return m_refCount;
}


ULONG	__stdcall NewIDirect3DVolume9::Release(void)
{
	m_refCount--;
	m_refCount = m_pd3dVolume->Release();
	if(m_refCount  <=0)
	{
		m_pd3dDevice->RemoveNewVolume(this); 
		delete this;
		return 0;
	}
	return m_refCount;
}

HRESULT __stdcall NewIDirect3DVolume9::GetDevice(IDirect3DDevice9** ppDevice)
{
	return m_pd3dDevice->GetDevice(ppDevice); 
}

HRESULT __stdcall NewIDirect3DVolume9::SetPrivateData(REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags)
{
	return m_pd3dVolume->SetPrivateData(refguid, pData, SizeOfData, Flags);
}

HRESULT __stdcall NewIDirect3DVolume9::GetPrivateData(REFGUID refguid,void* pData,DWORD* pSizeOfData)
{
	return m_pd3dVolume->GetPrivateData(refguid, pData, pSizeOfData);
}


HRESULT __stdcall NewIDirect3DVolume9::FreePrivateData(REFGUID refguid)
{
	return m_pd3dVolume->FreePrivateData(refguid);
}

HRESULT __stdcall NewIDirect3DVolume9::GetContainer(REFIID riid,void** ppContainer)
{
	return m_pd3dVolume->GetContainer(riid, ppContainer);
}

HRESULT __stdcall NewIDirect3DVolume9::GetDesc(D3DVOLUME_DESC *pDesc)
{
	return m_pd3dVolume->GetDesc(pDesc);
}

HRESULT __stdcall NewIDirect3DVolume9::LockBox(D3DLOCKED_BOX * pLockedVolume,CONST D3DBOX* pBox,DWORD Flags)
{
	return m_pd3dVolume->LockBox(pLockedVolume, pBox, Flags);
}

HRESULT __stdcall NewIDirect3DVolume9::UnlockBox()
{
	return m_pd3dVolume->UnlockBox();
}
