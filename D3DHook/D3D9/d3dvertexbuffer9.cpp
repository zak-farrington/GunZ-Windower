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

NewIDirect3DVertexBuffer9::NewIDirect3DVertexBuffer9(NewIDirect3DDevice9 *pDevice, IDirect3DVertexBuffer9 *pVertexBuf)
{
	m_refCount		= 0;
	m_pd3dDevice	= pDevice;
	m_pd3dVertexBuf	= pVertexBuf;	
}

HRESULT __stdcall NewIDirect3DVertexBuffer9::QueryInterface(REFIID iid, void ** ppvObject)
{
	return m_pd3dVertexBuf->QueryInterface(iid, ppvObject);
}

ULONG	__stdcall NewIDirect3DVertexBuffer9::AddRef(void)
{
	m_refCount++;
	m_refCount = m_pd3dVertexBuf->AddRef();
	return m_refCount;
}

ULONG	__stdcall NewIDirect3DVertexBuffer9::Release(void)
{
	m_refCount--;
	m_refCount = m_pd3dVertexBuf->Release();

	if(m_refCount == 0)
	{
		ULONG ref = m_pd3dDevice->m_pd3dDevice->AddRef();
		ref = m_pd3dDevice->m_pd3dDevice->Release();

		m_pd3dDevice->RemoveNewVertexBuf(this); 
		delete this;
		return 0;
	}

	return m_refCount;
}


HRESULT __stdcall NewIDirect3DVertexBuffer9::GetDevice(IDirect3DDevice9** ppDevice)
{
	return m_pd3dDevice->GetDevice(ppDevice); 
}

HRESULT __stdcall NewIDirect3DVertexBuffer9::SetPrivateData(REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags)
{
	return m_pd3dVertexBuf->SetPrivateData(refguid, pData, SizeOfData, Flags) ;
}

HRESULT __stdcall NewIDirect3DVertexBuffer9::GetPrivateData(REFGUID refguid,void* pData,DWORD* pSizeOfData)
{
	return m_pd3dVertexBuf->GetPrivateData(refguid, pData, pSizeOfData) ;
}

HRESULT __stdcall NewIDirect3DVertexBuffer9::FreePrivateData(REFGUID refguid)
{
	return m_pd3dVertexBuf->FreePrivateData(refguid);
}

DWORD   __stdcall NewIDirect3DVertexBuffer9::SetPriority(DWORD PriorityNew)
{
	return m_pd3dVertexBuf->SetPriority(PriorityNew);
}

DWORD   __stdcall NewIDirect3DVertexBuffer9::GetPriority() 
{
	return m_pd3dVertexBuf->GetPriority();
}

void    __stdcall NewIDirect3DVertexBuffer9::PreLoad()
{
	m_pd3dVertexBuf->PreLoad() ;
}

D3DRESOURCETYPE __stdcall NewIDirect3DVertexBuffer9::GetType()
{
	return m_pd3dVertexBuf->GetType();
}

HRESULT __stdcall NewIDirect3DVertexBuffer9::Lock(UINT OffsetToLock,UINT SizeToLock,void** ppbData,DWORD Flags)
{
	return m_pd3dVertexBuf->Lock( OffsetToLock, SizeToLock, ppbData, Flags);
}

HRESULT __stdcall NewIDirect3DVertexBuffer9::Unlock()
{	
	HRESULT hr = m_pd3dVertexBuf->Unlock() ;	
	return hr;
}

HRESULT __stdcall NewIDirect3DVertexBuffer9::GetDesc(D3DVERTEXBUFFER_DESC *pDesc)
{
	return m_pd3dVertexBuf->GetDesc(pDesc) ;
}
