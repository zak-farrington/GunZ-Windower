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


NewIDirect3DVertexDeclaration9::NewIDirect3DVertexDeclaration9(NewIDirect3DDevice9 *pDevice, IDirect3DVertexDeclaration9* pVertexDcl)
{
	m_refCount = 0;
	m_pd3dDevice = pDevice;
	m_pd3dVtxDeclaration = pVertexDcl;
}

HRESULT __stdcall NewIDirect3DVertexDeclaration9::QueryInterface(REFIID iid, void ** ppvObject)
{	
	return m_pd3dVtxDeclaration->QueryInterface( iid, ppvObject);
}

ULONG	__stdcall NewIDirect3DVertexDeclaration9::AddRef(void)
{
	m_refCount++; 
	m_refCount = m_pd3dVtxDeclaration->AddRef(); 
	return m_refCount;
}

ULONG	__stdcall NewIDirect3DVertexDeclaration9::Release(void)
{
	m_refCount--;
	m_refCount = m_pd3dVtxDeclaration->Release(); 
	if(m_refCount <= 0)
	{
		m_pd3dDevice->RemoveNewDcl(this); 
		delete this;
		return 0;
	}
	return m_refCount;	
}

HRESULT __stdcall NewIDirect3DVertexDeclaration9::GetDevice(IDirect3DDevice9** ppDevice) 
{
	return m_pd3dDevice->GetDevice(ppDevice); 
}

HRESULT __stdcall NewIDirect3DVertexDeclaration9::GetDeclaration(D3DVERTEXELEMENT9* pDecl,UINT* pNumElements) 
{
	return m_pd3dVtxDeclaration->GetDeclaration(pDecl, pNumElements); 
}
