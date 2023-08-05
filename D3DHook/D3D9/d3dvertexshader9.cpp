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

NewIDirect3DVertexShader9::NewIDirect3DVertexShader9(NewIDirect3DDevice9 *pDevice,IDirect3DVertexShader9 *pVShader)
{
	m_refCount = 0;
	m_pd3dDevice	= pDevice;
	m_pd3dVShader	= pVShader;
}

HRESULT __stdcall NewIDirect3DVertexShader9::QueryInterface(REFIID iid, void ** ppvObject)
{
	return m_pd3dVShader->QueryInterface(iid, ppvObject);
}

ULONG	__stdcall NewIDirect3DVertexShader9::AddRef(void)
{
	m_refCount++;
	m_refCount = m_pd3dVShader->AddRef();
	return m_refCount;

}

ULONG	__stdcall NewIDirect3DVertexShader9::Release(void)
{
	m_refCount--;
	m_refCount = m_pd3dVShader->Release();

	if(m_refCount <=0)
	{
		m_pd3dDevice->RemoveNewVShader(this); 
		delete this;
		return 0;
	}

	return m_refCount;
	
}

HRESULT __stdcall NewIDirect3DVertexShader9::GetDevice(IDirect3DDevice9** ppDevice) 
{
	return m_pd3dDevice->GetDevice(ppDevice); 
}

HRESULT __stdcall NewIDirect3DVertexShader9::GetFunction(void* pData,UINT* pSizeOfData) 
{
	return m_pd3dVShader->GetFunction(pData, pSizeOfData); 
}
