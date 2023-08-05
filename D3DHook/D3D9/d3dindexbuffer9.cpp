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


NewIDirect3DIndexBuffer9::NewIDirect3DIndexBuffer9(NewIDirect3DDevice9 *pDevice, IDirect3DIndexBuffer9 *pIndexBuf)
{
	m_refCount		= 0;
	m_pd3dDevice	= pDevice;
	m_pd3dIndexBuf	= pIndexBuf;
}

HRESULT __stdcall NewIDirect3DIndexBuffer9::QueryInterface(REFIID iid, void ** ppvObject)
{
	return m_pd3dIndexBuf->QueryInterface(iid, ppvObject);
}

ULONG	__stdcall NewIDirect3DIndexBuffer9::AddRef(void)
{
	m_refCount++;
	m_refCount = m_pd3dIndexBuf->AddRef();
	return m_refCount;
}

ULONG	__stdcall NewIDirect3DIndexBuffer9::Release(void)
{
	m_refCount--;
	m_refCount = m_pd3dIndexBuf->Release();	
	if(m_refCount <= 0)
	{
		m_pd3dDevice->RemoveNewIndexBuf(this); 
		delete this;
		return 0;
	}
	return m_refCount;
}

HRESULT __stdcall NewIDirect3DIndexBuffer9::GetDevice(IDirect3DDevice9** ppDevice)
{
	return m_pd3dDevice->GetDevice(ppDevice);
}

HRESULT __stdcall NewIDirect3DIndexBuffer9::SetPrivateData(REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags)
{
	return m_pd3dIndexBuf->SetPrivateData(refguid, pData, SizeOfData,Flags);
}
 
HRESULT __stdcall NewIDirect3DIndexBuffer9::GetPrivateData(REFGUID refguid,void* pData,DWORD* pSizeOfData)
{
	return m_pd3dIndexBuf->GetPrivateData(refguid, pData, pSizeOfData) ;
}

HRESULT __stdcall NewIDirect3DIndexBuffer9::FreePrivateData(REFGUID refguid)
{
	return m_pd3dIndexBuf->FreePrivateData(refguid);
}

DWORD   __stdcall NewIDirect3DIndexBuffer9::SetPriority(DWORD PriorityNew)
{
	return m_pd3dIndexBuf->SetPriority( PriorityNew);
}

DWORD   __stdcall NewIDirect3DIndexBuffer9::GetPriority()
{
	return m_pd3dIndexBuf->GetPriority();
}

void    __stdcall NewIDirect3DIndexBuffer9::PreLoad()
{
	m_pd3dIndexBuf->PreLoad();
}

D3DRESOURCETYPE __stdcall NewIDirect3DIndexBuffer9::GetType()
{
	return m_pd3dIndexBuf->GetType();
}

HRESULT __stdcall NewIDirect3DIndexBuffer9::Lock(UINT OffsetToLock,UINT SizeToLock,void** ppbData,DWORD Flags)
{
	return m_pd3dIndexBuf->Lock(OffsetToLock, SizeToLock, ppbData,  Flags);
}


HRESULT __stdcall NewIDirect3DIndexBuffer9::Unlock()
{
	return m_pd3dIndexBuf->Unlock();
}

HRESULT __stdcall NewIDirect3DIndexBuffer9::GetDesc(D3DINDEXBUFFER_DESC *pDesc)
{
	return m_pd3dIndexBuf->GetDesc(pDesc);
}

