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


NewIDirect3DSwapChain9::NewIDirect3DSwapChain9(NewIDirect3DDevice9 *pDevice, IDirect3DSwapChain9 *pSwapChain)
{
	m_refCount = 0;
	m_pd3dDevice	= pDevice;
	m_pd3dSwapChain	= pSwapChain;
}

HRESULT __stdcall NewIDirect3DSwapChain9::QueryInterface(REFIID iid, void ** ppvObject)
{
	return m_pd3dSwapChain->QueryInterface(iid,  ppvObject);
}

ULONG	__stdcall NewIDirect3DSwapChain9::AddRef(void)
{
	m_refCount++;
	m_refCount = m_pd3dSwapChain->AddRef();
	return m_refCount;
}

ULONG	__stdcall NewIDirect3DSwapChain9::Release(void)
{
	m_refCount--;
	m_refCount = m_pd3dSwapChain->Release();
	if(m_refCount <=0)
	{
		ULONG ref = m_pd3dDevice->m_pd3dDevice->AddRef();
		ref = m_pd3dDevice->m_pd3dDevice->Release();

		m_pd3dDevice->RemoveNewSwapChain (this); 
		delete this;
		return 0;
	}		

	return m_refCount;
}

HRESULT __stdcall NewIDirect3DSwapChain9::Present(CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion,DWORD dwFlags) 
{
	return m_pd3dSwapChain->Present( pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion, dwFlags) ;
}

HRESULT __stdcall NewIDirect3DSwapChain9::GetFrontBufferData(IDirect3DSurface9* pDestSurface)
{
	if(pDestSurface == NULL)
		return D3DERR_INVALIDCALL;

	return m_pd3dSwapChain->GetFrontBufferData
		(
		((NewIDirect3DSurface9*)pDestSurface)->m_pd3dSurface
		); 	
}

HRESULT __stdcall NewIDirect3DSwapChain9::GetBackBuffer(UINT iBackBuffer,D3DBACKBUFFER_TYPE Type,IDirect3DSurface9** ppBackBuffer) 
{
	HRESULT hr;
	IDirect3DSurface9 *pBuffer=NULL;

	if(ppBackBuffer == NULL)
		return D3DERR_INVALIDCALL;

	hr = m_pd3dSwapChain->GetBackBuffer(iBackBuffer, Type, &pBuffer); 

	if(hr == D3D_OK)
	{
		NewIDirect3DSurface9 * pNewSurface = m_pd3dDevice->GetNewSurface(pBuffer);
		if(pNewSurface  == NULL)
		{
			pNewSurface  = new NewIDirect3DSurface9(m_pd3dDevice, pBuffer);
		}
		*ppBackBuffer = pNewSurface; 
	}
	else
	{
		*ppBackBuffer = NULL; 
	}

	return hr;
}

HRESULT __stdcall NewIDirect3DSwapChain9::GetRasterStatus(D3DRASTER_STATUS* pRasterStatus) 
{
	return m_pd3dSwapChain->GetRasterStatus(pRasterStatus); 
}

HRESULT __stdcall NewIDirect3DSwapChain9::GetDisplayMode(D3DDISPLAYMODE* pMode) 
{
	return m_pd3dSwapChain->GetDisplayMode(pMode); 
}

HRESULT __stdcall NewIDirect3DSwapChain9::GetDevice(IDirect3DDevice9** ppDevice) 
{
	return m_pd3dDevice->GetDevice(ppDevice);
}

HRESULT __stdcall NewIDirect3DSwapChain9::GetPresentParameters(D3DPRESENT_PARAMETERS* pPresentationParameters) 
{
	return m_pd3dSwapChain->GetPresentParameters(pPresentationParameters); 
}
