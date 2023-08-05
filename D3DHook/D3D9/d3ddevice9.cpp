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

NewIDirect3DDevice9::NewIDirect3DDevice9(NewIDirect3D9*  pd3d9, IDirect3DDevice9* pd3ddevice)
{

	m_refCount		= 1;
	m_pd3d9			= pd3d9;
	m_pd3dDevice	= pd3ddevice;
	
}

HRESULT __stdcall NewIDirect3DDevice9::QueryInterface(REFIID iid, void ** ppvObject)
{
	return m_pd3dDevice->QueryInterface(iid, ppvObject);
}

ULONG	__stdcall NewIDirect3DDevice9::AddRef(void)
{	
	m_refCount++;
	m_refCount = m_pd3dDevice->AddRef();
 	return m_refCount;	
}

ULONG	__stdcall NewIDirect3DDevice9::Release(void)
{
	m_refCount--;
	m_refCount = m_pd3dDevice->Release();
	if(m_refCount <=0 )
	{
		Free();
		delete this;
		return 0;
	}
	return m_refCount;
}


HRESULT __stdcall NewIDirect3DDevice9::TestCooperativeLevel()
{
	return m_pd3dDevice->TestCooperativeLevel();
}


UINT	__stdcall NewIDirect3DDevice9:: GetAvailableTextureMem() 
{
	return m_pd3dDevice->GetAvailableTextureMem();
}

HRESULT __stdcall NewIDirect3DDevice9::EvictManagedResources()
{
	return m_pd3dDevice->EvictManagedResources();
}

HRESULT __stdcall NewIDirect3DDevice9::GetDirect3D(IDirect3D9** ppD3D9)
{
	if(ppD3D9 == NULL)
		return D3DERR_INVALIDCALL;


	m_pd3d9->AddRef(); 
	*ppD3D9 = m_pd3d9;
	 return S_OK;
}

HRESULT __stdcall NewIDirect3DDevice9::GetDeviceCaps(D3DCAPS9* pCaps)
{
	return m_pd3dDevice->GetDeviceCaps(pCaps);
}


HRESULT __stdcall NewIDirect3DDevice9::GetDisplayMode(UINT iSwapChain,D3DDISPLAYMODE* pMode) 
{
	return m_pd3dDevice->GetDisplayMode(iSwapChain, pMode); 
}

HRESULT __stdcall NewIDirect3DDevice9::GetCreationParameters(D3DDEVICE_CREATION_PARAMETERS *pParameters) 
{
	return m_pd3dDevice->GetCreationParameters(pParameters); 
}


HRESULT __stdcall NewIDirect3DDevice9::SetCursorProperties(UINT XHotSpot,UINT YHotSpot,IDirect3DSurface9* pCursorBitmap)
{
	if(pCursorBitmap == NULL)
	{
		return m_pd3dDevice->SetCursorProperties(XHotSpot, YHotSpot, pCursorBitmap);
	}

	return m_pd3dDevice->SetCursorProperties(XHotSpot, YHotSpot, ((NewIDirect3DSurface9*)pCursorBitmap)->m_pd3dSurface);
}

void    __stdcall NewIDirect3DDevice9::SetCursorPosition(int X,int Y,DWORD Flags)
{
	m_pd3dDevice->SetCursorPosition( X, Y, Flags);
}


BOOL    __stdcall NewIDirect3DDevice9::ShowCursor(BOOL bShow)
{
	return m_pd3dDevice->ShowCursor(bShow);
}

HRESULT __stdcall NewIDirect3DDevice9::CreateAdditionalSwapChain(D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DSwapChain9** ppSwapChain) 
{
	HRESULT hr;
	IDirect3DSwapChain9* pSwapChain = NULL;
	if(ppSwapChain == NULL)
	{
		return m_pd3dDevice->CreateAdditionalSwapChain(pPresentationParameters, ppSwapChain);
	}

	hr = m_pd3dDevice->CreateAdditionalSwapChain(pPresentationParameters, &pSwapChain);
	if(hr == D3D_OK)
	{
		NewIDirect3DSwapChain9 *pNewSwapChain = new NewIDirect3DSwapChain9(this, pSwapChain); 
		AddNewSwapChain(pNewSwapChain);
		*ppSwapChain = pNewSwapChain;
	}
	else
	{
		*ppSwapChain = NULL;
	}

	return 	hr;
}

HRESULT __stdcall NewIDirect3DDevice9::GetSwapChain(UINT iSwapChain,IDirect3DSwapChain9** ppSwapChain)
{
	HRESULT hr;
	IDirect3DSwapChain9* pSwapChain = NULL; 
	if(ppSwapChain == NULL)
	{
		return m_pd3dDevice->GetSwapChain(iSwapChain, ppSwapChain);
	}

	hr = m_pd3dDevice->GetSwapChain(iSwapChain,  &pSwapChain);
	if(hr == D3D_OK)
	{
		NewIDirect3DSwapChain9 *pNewSwapChain = GetNewSwapChain(pSwapChain);
		if(pNewSwapChain == NULL)
		{
			pNewSwapChain = new NewIDirect3DSwapChain9(this, pSwapChain); 
			AddNewSwapChain(pNewSwapChain);
		}
		*ppSwapChain = pNewSwapChain;
	}

	return  hr;
}

UINT    __stdcall NewIDirect3DDevice9::GetNumberOfSwapChains()
{
	return m_pd3dDevice->GetNumberOfSwapChains();
}

HRESULT __stdcall NewIDirect3DDevice9::Reset(D3DPRESENT_PARAMETERS* pPresentationParameters) 
{
	return m_pd3dDevice->Reset(pPresentationParameters); 
}

HRESULT __stdcall NewIDirect3DDevice9::Present(CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion) 
{
	return m_pd3dDevice->Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion); 
}

HRESULT __stdcall NewIDirect3DDevice9::GetBackBuffer(UINT iSwapChain,UINT iBackBuffer,D3DBACKBUFFER_TYPE Type,IDirect3DSurface9** ppBackBuffer  ) 
{
	HRESULT hr;
	IDirect3DSurface9* pBackBuffer = NULL;

	if(ppBackBuffer == NULL)
	{
		return m_pd3dDevice->GetBackBuffer(iSwapChain, iBackBuffer, Type, ppBackBuffer);
	}

	hr = m_pd3dDevice->GetBackBuffer(iSwapChain, iBackBuffer, Type, &pBackBuffer); 
	if(hr == D3D_OK)
	{
		NewIDirect3DSurface9 *pNewBackBuffer = GetNewSurface(pBackBuffer);
		if(pNewBackBuffer  == NULL)
		{
			pNewBackBuffer = new NewIDirect3DSurface9(this, pBackBuffer);
			AddNewSurface(pNewBackBuffer);
		}
		*ppBackBuffer = pNewBackBuffer;
	}
	else
	{
		*ppBackBuffer = NULL;
	}

	return hr;
}

HRESULT __stdcall NewIDirect3DDevice9::GetRasterStatus(UINT iSwapChain,D3DRASTER_STATUS* pRasterStatus) 
{
	return m_pd3dDevice->GetRasterStatus(iSwapChain, pRasterStatus); 
}

HRESULT __stdcall NewIDirect3DDevice9::SetDialogBoxMode(BOOL bEnableDialogs) 
{
	return m_pd3dDevice->SetDialogBoxMode(bEnableDialogs); 
}

void    __stdcall NewIDirect3DDevice9::SetGammaRamp(UINT iSwapChain,DWORD Flags,CONST D3DGAMMARAMP* pRamp) 
{
	m_pd3dDevice->SetGammaRamp(iSwapChain, Flags, pRamp); 
}

void    __stdcall NewIDirect3DDevice9::GetGammaRamp(UINT iSwapChain,D3DGAMMARAMP* pRamp) 
{
	m_pd3dDevice->GetGammaRamp(iSwapChain, pRamp); 
}

HRESULT __stdcall NewIDirect3DDevice9::CreateTexture(UINT Width,UINT Height,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DTexture9** ppTexture,HANDLE* pSharedHandle)
{

	HRESULT hr;
	IDirect3DTexture9 *pTexture=NULL;
	if(ppTexture == NULL)
	{
		return m_pd3dDevice->CreateTexture(Width, Height, Levels, Usage, Format, Pool, ppTexture , pSharedHandle);;
	}


	hr = m_pd3dDevice->CreateTexture(Width, Height, Levels, Usage, Format, Pool, &pTexture, pSharedHandle);
	if(D3D_OK == hr)
	{
		NewIDirect3DTexture9 *pNewTexture = new NewIDirect3DTexture9(this,  pTexture);
		*ppTexture = pNewTexture;
		AddNewTexture(pNewTexture);
	}
	else		
	{
		*ppTexture = NULL;
	}
	return hr;
}

HRESULT __stdcall NewIDirect3DDevice9::CreateVolumeTexture(UINT Width,UINT Height,UINT Depth,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DVolumeTexture9** ppVolumeTexture,HANDLE* pSharedHandle)
{

	HRESULT hr;
	IDirect3DVolumeTexture9* pVolTexture = NULL;
	if(ppVolumeTexture == NULL)
	{
		return m_pd3dDevice->CreateVolumeTexture( Width, Height, Depth, Levels, Usage, Format, Pool,ppVolumeTexture , pSharedHandle);;
	}

	hr = m_pd3dDevice->CreateVolumeTexture( Width, Height, Depth, Levels, Usage, Format, Pool,&pVolTexture, pSharedHandle);
	if(hr == D3D_OK)
	{
		NewIDirect3DVolumeTexture9 *pNewVolTexture = new  NewIDirect3DVolumeTexture9(this, pVolTexture); 
		*ppVolumeTexture = pNewVolTexture;
		AddNewVolTexture(pNewVolTexture);
	}
	else
	{
		*ppVolumeTexture = NULL;
	}

	return hr;
}

HRESULT __stdcall NewIDirect3DDevice9::CreateCubeTexture(UINT EdgeLength,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DCubeTexture9** ppCubeTexture,HANDLE* pSharedHandle) 
{
	HRESULT hr;
	IDirect3DCubeTexture9*  pCubeTexture = NULL;
	if(ppCubeTexture == NULL)
	{
		return m_pd3dDevice->CreateCubeTexture(EdgeLength, Levels, Usage, Format, Pool, ppCubeTexture ,  pSharedHandle); ;
	}

	hr = m_pd3dDevice->CreateCubeTexture(EdgeLength, Levels, Usage, Format, Pool, &pCubeTexture,  pSharedHandle); 
	if(hr == D3D_OK)
	{
		NewIDirect3DCubeTexture9*  pNewCubeTexture = new NewIDirect3DCubeTexture9(this, pCubeTexture );
		AddNewCubeTexture(pNewCubeTexture );

		*ppCubeTexture  = pNewCubeTexture ;
	}
	else
	{
		*ppCubeTexture  = NULL;
	}

	return hr;
}

HRESULT __stdcall NewIDirect3DDevice9::CreateVertexBuffer(UINT Length,DWORD Usage,DWORD FVF,D3DPOOL Pool,IDirect3DVertexBuffer9** ppVertexBuffer,HANDLE* pSharedHandle) 
{
	HRESULT hr;
	IDirect3DVertexBuffer9* pVertexBuffer=NULL;
	if(ppVertexBuffer == NULL)
	{
		return m_pd3dDevice->CreateVertexBuffer(Length, Usage, FVF, Pool, ppVertexBuffer , pSharedHandle); ;
	}

	hr = m_pd3dDevice->CreateVertexBuffer(Length, Usage, FVF, Pool, &pVertexBuffer, pSharedHandle); 
	if(hr == D3D_OK)
	{
		NewIDirect3DVertexBuffer9* pNewVertexBuffer = new NewIDirect3DVertexBuffer9(this,  pVertexBuffer);
		*ppVertexBuffer = pNewVertexBuffer ;
		AddNewVertexBuf(pNewVertexBuffer);
	}
	else
	{
		*ppVertexBuffer = NULL;
	}

	return hr;
}

HRESULT __stdcall NewIDirect3DDevice9::CreateIndexBuffer(UINT Length,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DIndexBuffer9** ppIndexBuffer,HANDLE* pSharedHandle) 
{
	HRESULT hr;
	IDirect3DIndexBuffer9* pIndexBuffer = NULL;
	if(ppIndexBuffer == NULL)
	{
		return hr = m_pd3dDevice->CreateIndexBuffer(Length,Usage, Format, Pool, ppIndexBuffer ,pSharedHandle);;
	}

	hr = m_pd3dDevice->CreateIndexBuffer(Length,Usage, Format, Pool, &pIndexBuffer,pSharedHandle);
	if(hr == D3D_OK)
	{
		NewIDirect3DIndexBuffer9* pNewIndexBuffer = new NewIDirect3DIndexBuffer9(this,  pIndexBuffer);
		*ppIndexBuffer = pNewIndexBuffer ;
		AddNewIndexBuf(pNewIndexBuffer);
	}
	else
	{
		*ppIndexBuffer = NULL;
	}

	return hr;
}

HRESULT __stdcall NewIDirect3DDevice9::CreateRenderTarget(UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Lockable,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle) 
{
	HRESULT hr;
	IDirect3DSurface9* pSurface = NULL;
	if(ppSurface == NULL)
	{
		return m_pd3dDevice->CreateRenderTarget( Width, Height, Format, MultiSample, MultisampleQuality, Lockable, ppSurface , pSharedHandle) ;;
	}

	hr = m_pd3dDevice->CreateRenderTarget( Width, Height, Format, MultiSample, MultisampleQuality, Lockable, &pSurface, pSharedHandle) ;
	if(hr == D3D_OK)
	{
		NewIDirect3DSurface9* pNewSurface = new NewIDirect3DSurface9(this, pSurface);
		*ppSurface = pNewSurface;
		AddNewSurface(pNewSurface);
	}
	else
	{
		*ppSurface = NULL;
	}
	return hr;
}

HRESULT __stdcall NewIDirect3DDevice9::CreateDepthStencilSurface(UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Discard,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle) 
{
	HRESULT hr;
	IDirect3DSurface9* pSurface = NULL;
	if(ppSurface == NULL)
	{
		return m_pd3dDevice->CreateDepthStencilSurface( Width, Height, Format, MultiSample, MultisampleQuality, Discard,ppSurface , pSharedHandle); ;
	}

	hr = m_pd3dDevice->CreateDepthStencilSurface( Width, Height, Format, MultiSample, MultisampleQuality, Discard,&pSurface, pSharedHandle); 
	if(hr == D3D_OK)
	{
		NewIDirect3DSurface9* pNewSurface = new NewIDirect3DSurface9(this, pSurface);
		*ppSurface = pNewSurface;
		AddNewSurface(pNewSurface);
	}
	else
	{
		*ppSurface = NULL;
	}
	return hr;
}

HRESULT __stdcall NewIDirect3DDevice9::UpdateSurface(IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,IDirect3DSurface9* pDestinationSurface,CONST POINT* pDestPoint) 
{
	if(pSourceSurface == NULL || pDestinationSurface == NULL)
	{
		return m_pd3dDevice->UpdateSurface(	pSourceSurface ,pSourceRect,pDestinationSurface,pDestPoint);
	}

	return m_pd3dDevice->UpdateSurface(
		((NewIDirect3DSurface9*)pSourceSurface)->m_pd3dSurface, 
		pSourceRect,
		((NewIDirect3DSurface9*)pDestinationSurface)->m_pd3dSurface,
		pDestPoint
		);
}																	

HRESULT __stdcall NewIDirect3DDevice9::UpdateTexture(IDirect3DBaseTexture9* pSourceTexture,IDirect3DBaseTexture9* pDestinationTexture) 
{
	if(pSourceTexture == NULL || pDestinationTexture == NULL)
	{
		return m_pd3dDevice->UpdateTexture(pSourceTexture ,pDestinationTexture ); 
	}

	return m_pd3dDevice->UpdateTexture(
		((NewIDirect3DBaseTexture9*)pSourceTexture)->m_pd3dBaseTexture ,
		((NewIDirect3DBaseTexture9*)pDestinationTexture)->m_pd3dBaseTexture
		); 
}

HRESULT __stdcall NewIDirect3DDevice9::GetRenderTargetData(IDirect3DSurface9* pRenderTarget,IDirect3DSurface9* pDestSurface) 
{
	if(pRenderTarget== NULL || pDestSurface == NULL)
	{
		return m_pd3dDevice->GetRenderTargetData( pRenderTarget, pDestSurface) ;
	}

	return m_pd3dDevice->GetRenderTargetData(
		((NewIDirect3DSurface9* )pRenderTarget)->m_pd3dSurface ,
		((NewIDirect3DSurface9*) pDestSurface)->m_pd3dSurface
		); 
}

HRESULT __stdcall NewIDirect3DDevice9::GetFrontBufferData(UINT iSwapChain,IDirect3DSurface9* pDestSurface) 
{
	if( pDestSurface == NULL)
	{
		return 	m_pd3dDevice->GetFrontBufferData(iSwapChain, pDestSurface); 
	}

	return m_pd3dDevice->GetFrontBufferData	(
		iSwapChain,
		((NewIDirect3DSurface9* )pDestSurface)->m_pd3dSurface
		); 
}

HRESULT __stdcall NewIDirect3DDevice9::StretchRect(IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,IDirect3DSurface9* pDestSurface,CONST RECT* pDestRect,D3DTEXTUREFILTERTYPE Filter)
{
	if( pSourceSurface == NULL || pDestSurface == NULL)
	{
		return m_pd3dDevice->StretchRect(
			pSourceSurface,
			pSourceRect,
			pDestSurface,
			pDestRect, 
			Filter
		);
	}

	return m_pd3dDevice->StretchRect(
		((NewIDirect3DSurface9*) pSourceSurface)->m_pd3dSurface,
		pSourceRect,
		((NewIDirect3DSurface9*) pDestSurface)->m_pd3dSurface,
		pDestRect, 
		Filter
		);
}

HRESULT __stdcall NewIDirect3DDevice9::ColorFill(IDirect3DSurface9* pSurface,CONST RECT* pRect,D3DCOLOR color)
{
	if(pSurface == NULL)	
	{
		return m_pd3dDevice->ColorFill(pSurface, pRect, color);
	}

	return m_pd3dDevice->ColorFill(
		((NewIDirect3DSurface9*) pSurface)->m_pd3dSurface,
		pRect,
		color
		);
}

HRESULT __stdcall NewIDirect3DDevice9::CreateOffscreenPlainSurface(UINT Width,UINT Height,D3DFORMAT Format,D3DPOOL Pool,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle) 
{
	HRESULT hr;
	IDirect3DSurface9* pSurface = NULL;

	if(ppSurface == NULL)
	{
		return m_pd3dDevice->CreateOffscreenPlainSurface(Width,Height, Format, Pool, ppSurface, pSharedHandle); ;
	}

	hr = m_pd3dDevice->CreateOffscreenPlainSurface(Width,Height, Format, Pool, &pSurface, pSharedHandle); 
	if(hr == D3D_OK)
	{
		NewIDirect3DSurface9* pNewSurface = new NewIDirect3DSurface9(this, pSurface);
		*ppSurface = pNewSurface;
		AddNewSurface(pNewSurface);
	}
	else
	{
		*ppSurface = NULL;
	}
	return hr;
}

HRESULT __stdcall NewIDirect3DDevice9::SetRenderTarget(DWORD RenderTargetIndex,IDirect3DSurface9* pRenderTarget)
{
	HRESULT hr ;
	if(pRenderTarget == NULL)	
	{
		return m_pd3dDevice->SetRenderTarget(RenderTargetIndex, pRenderTarget);
	}

	hr = m_pd3dDevice->SetRenderTarget(
				RenderTargetIndex,
				((NewIDirect3DSurface9* )pRenderTarget)->m_pd3dSurface
				);
	return hr; 
}

HRESULT __stdcall NewIDirect3DDevice9::GetRenderTarget(DWORD RenderTargetIndex,IDirect3DSurface9** ppRenderTarget)
{
	HRESULT hr;
	IDirect3DSurface9* pRenderTarget = NULL;
	if(ppRenderTarget == NULL)
	{
		return m_pd3dDevice->GetRenderTarget(RenderTargetIndex, ppRenderTarget);;
	}

	hr = m_pd3dDevice->GetRenderTarget(RenderTargetIndex, &pRenderTarget);
	if(hr == D3D_OK)
	{
		NewIDirect3DSurface9* pNewSurface = GetNewSurface(pRenderTarget);
		if(pNewSurface == NULL)
		{
			pNewSurface = new NewIDirect3DSurface9(this, pRenderTarget);
			AddNewSurface(pNewSurface);
		}
		*ppRenderTarget = pNewSurface;		
	}
	else
	{
		*ppRenderTarget = NULL;
	}
	return hr;
}

HRESULT __stdcall NewIDirect3DDevice9::SetDepthStencilSurface(IDirect3DSurface9* pNewZStencil) 
{	
	HRESULT hr ;

	if(pNewZStencil == NULL)
	{
		return m_pd3dDevice->SetDepthStencilSurface(pNewZStencil);
	}

	hr =  m_pd3dDevice->SetDepthStencilSurface(
		((NewIDirect3DSurface9* )pNewZStencil)->m_pd3dSurface
		);
	return hr;
}

HRESULT __stdcall NewIDirect3DDevice9::GetDepthStencilSurface(IDirect3DSurface9** ppZStencilSurface)
{
	HRESULT hr;
	IDirect3DSurface9* pSurface = NULL;
	if(ppZStencilSurface  == NULL)
	{
		return m_pd3dDevice->GetDepthStencilSurface(ppZStencilSurface);
	}

	hr = m_pd3dDevice->GetDepthStencilSurface(&pSurface);
	if(hr == D3D_OK)
	{
		NewIDirect3DSurface9* pNewSurface = GetNewSurface(pSurface);
		if(pNewSurface == NULL )
		{
			pNewSurface = new NewIDirect3DSurface9(this, pSurface );
			AddNewSurface(pNewSurface);
		}
		*ppZStencilSurface = pNewSurface;
	}
	else
	{
		*ppZStencilSurface = NULL;
	}
	return hr;
}

HRESULT __stdcall NewIDirect3DDevice9::BeginScene() 
{
	return m_pd3dDevice->BeginScene();
}

HRESULT __stdcall NewIDirect3DDevice9::EndScene() 
{
	return m_pd3dDevice->EndScene();
}

HRESULT __stdcall NewIDirect3DDevice9::Clear(DWORD Count,CONST D3DRECT* pRects,DWORD Flags,D3DCOLOR Color,float Z,DWORD Stencil)
{
	return m_pd3dDevice->Clear(Count,pRects,Flags, Color,Z,Stencil);
}

HRESULT __stdcall NewIDirect3DDevice9::SetTransform(D3DTRANSFORMSTATETYPE State,CONST D3DMATRIX* pMatrix) 
{
	return m_pd3dDevice->SetTransform( State, pMatrix); 
}

HRESULT __stdcall NewIDirect3DDevice9::GetTransform(D3DTRANSFORMSTATETYPE State,D3DMATRIX* pMatrix) 
{
	return m_pd3dDevice->GetTransform(State,pMatrix);
}

HRESULT __stdcall NewIDirect3DDevice9::MultiplyTransform(D3DTRANSFORMSTATETYPE state, CONST D3DMATRIX* pMatrix) 
{
	return m_pd3dDevice->MultiplyTransform(state, pMatrix); 
}

HRESULT __stdcall NewIDirect3DDevice9::SetViewport(CONST D3DVIEWPORT9* pViewport)
{
	return m_pd3dDevice->SetViewport(pViewport);
}

HRESULT __stdcall NewIDirect3DDevice9::GetViewport(D3DVIEWPORT9* pViewport)
{
	return m_pd3dDevice->GetViewport(pViewport);
}

HRESULT __stdcall NewIDirect3DDevice9::SetMaterial(CONST D3DMATERIAL9* pMaterial)
{
	return m_pd3dDevice->SetMaterial(pMaterial);
}

HRESULT __stdcall NewIDirect3DDevice9::GetMaterial(D3DMATERIAL9* pMaterial) 
{
	return m_pd3dDevice->GetMaterial(pMaterial);
}

HRESULT __stdcall NewIDirect3DDevice9::SetLight(DWORD Index,CONST D3DLIGHT9* pLight) 
{
	return m_pd3dDevice->SetLight(Index,pLight); 
}

HRESULT __stdcall NewIDirect3DDevice9::GetLight(DWORD Index,D3DLIGHT9* pLight) 
{
	return m_pd3dDevice->GetLight(Index,pLight); 
}

HRESULT __stdcall NewIDirect3DDevice9::LightEnable(DWORD Index,BOOL Enable) 
{
	return m_pd3dDevice->LightEnable(Index, Enable); 
}

HRESULT __stdcall NewIDirect3DDevice9::GetLightEnable(DWORD Index,BOOL* pEnable) 
{
	return m_pd3dDevice->GetLightEnable(Index, pEnable); 
}

HRESULT __stdcall NewIDirect3DDevice9::SetClipPlane(DWORD Index, CONST float* pPlane)
{
	return m_pd3dDevice->SetClipPlane( Index, pPlane);
}

HRESULT __stdcall NewIDirect3DDevice9::GetClipPlane(DWORD Index, float* pPlane) 
{
	return m_pd3dDevice->GetClipPlane( Index, pPlane);
}

HRESULT __stdcall NewIDirect3DDevice9::SetRenderState(D3DRENDERSTATETYPE State, DWORD Value)
{
	return m_pd3dDevice->SetRenderState(State, Value);
}

HRESULT __stdcall NewIDirect3DDevice9::GetRenderState(D3DRENDERSTATETYPE State, DWORD* pValue) 
{
	return m_pd3dDevice->GetRenderState(State, pValue);
}

HRESULT __stdcall NewIDirect3DDevice9::CreateStateBlock(D3DSTATEBLOCKTYPE Type,IDirect3DStateBlock9** ppSB)
{
	HRESULT hr;
	IDirect3DStateBlock9* pSB = NULL;
	
	if(ppSB == NULL)
	{
		return m_pd3dDevice->CreateStateBlock(Type, ppSB);
	}

	hr = m_pd3dDevice->CreateStateBlock(Type, &pSB);
	if(hr == D3D_OK)
	{
		NewIDirect3DStateBlock9* pNewSB = new NewIDirect3DStateBlock9(this, pSB); 
		*ppSB = pNewSB;
		AddNewStateBlock(pNewSB);
	}
	else
	{
		*ppSB = NULL;
	}
	return hr;
}

HRESULT __stdcall NewIDirect3DDevice9::BeginStateBlock()
{
	return m_pd3dDevice->BeginStateBlock();
}

HRESULT __stdcall NewIDirect3DDevice9::EndStateBlock(IDirect3DStateBlock9** ppSB) 
{
	HRESULT hr;
	IDirect3DStateBlock9* pSB = NULL;

	if(ppSB == NULL)
	{
		return m_pd3dDevice->EndStateBlock(ppSB);
	}

	hr = D3D_OK;
	if((*ppSB) == NULL)
	{
		hr = m_pd3dDevice->EndStateBlock( &pSB); 
		if(hr == D3D_OK)
		{
			NewIDirect3DStateBlock9* pNewSB = GetNewStateBlock(pSB);
			if(pNewSB  == NULL)
			{
				pNewSB = new NewIDirect3DStateBlock9(this, pSB);
				AddNewStateBlock(pNewSB);
			}		
			*ppSB = pNewSB;
		}
		else
		{
			*ppSB = NULL;
		}
	}
	else
	{
		//Do something here
	}

	return hr;
}

HRESULT __stdcall NewIDirect3DDevice9::SetClipStatus(CONST D3DCLIPSTATUS9* pClipStatus) 
{
	return m_pd3dDevice->SetClipStatus(pClipStatus); 
}

HRESULT __stdcall NewIDirect3DDevice9::GetClipStatus(D3DCLIPSTATUS9* pClipStatus) 
{
	return m_pd3dDevice->GetClipStatus(pClipStatus); 
}

HRESULT __stdcall NewIDirect3DDevice9::GetTexture(DWORD Stage,IDirect3DBaseTexture9** ppTexture) 
{
	HRESULT hr;
	IDirect3DBaseTexture9* pTexture = NULL;

	if(ppTexture == NULL)
	{
		return m_pd3dDevice->GetTexture(Stage, ppTexture);
	}

	hr = m_pd3dDevice->GetTexture(Stage, &pTexture); 
	if(hr == D3D_OK)
	{
		NewIDirect3DBaseTexture9* pNewTexture = GetNewBaseTexture(pTexture);
		*ppTexture  = pNewTexture;
	}
	else
	{
		*ppTexture  = NULL;
	}
	
	return hr; 
}

HRESULT __stdcall NewIDirect3DDevice9::SetTexture(DWORD Stage,IDirect3DBaseTexture9* pTexture)
{
	if(pTexture == NULL)
	{
		return m_pd3dDevice->SetTexture(Stage,pTexture);
	}

	return m_pd3dDevice->SetTexture(
		Stage,
		((NewIDirect3DBaseTexture9* )pTexture)->m_pd3dBaseTexture
		);
}

HRESULT __stdcall NewIDirect3DDevice9::GetTextureStageState(DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD* pValue) 
{
	return m_pd3dDevice->GetTextureStageState(Stage,Type,pValue); 
}


HRESULT __stdcall NewIDirect3DDevice9::SetTextureStageState(DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD Value) 
{
	return m_pd3dDevice->SetTextureStageState(Stage,Type,Value);
}

HRESULT __stdcall NewIDirect3DDevice9::GetSamplerState(DWORD Sampler,D3DSAMPLERSTATETYPE Type,DWORD* pValue) 
{
	return m_pd3dDevice->GetSamplerState(Sampler,Type,  pValue); 
}

HRESULT __stdcall NewIDirect3DDevice9::SetSamplerState(DWORD Sampler,D3DSAMPLERSTATETYPE Type,DWORD Value) 
{
	return m_pd3dDevice->SetSamplerState(Sampler,Type,Value); 
}

HRESULT __stdcall NewIDirect3DDevice9::ValidateDevice(DWORD* pNumPasses) 
{
	return m_pd3dDevice->ValidateDevice(pNumPasses); 
}

HRESULT __stdcall NewIDirect3DDevice9::SetPaletteEntries(UINT PaletteNumber,CONST PALETTEENTRY* pEntries) 
{
	return m_pd3dDevice->SetPaletteEntries(PaletteNumber,pEntries) ;
}

HRESULT __stdcall NewIDirect3DDevice9::GetPaletteEntries(UINT PaletteNumber,PALETTEENTRY* pEntries) 
{
	return m_pd3dDevice->GetPaletteEntries(PaletteNumber, pEntries); 
}

HRESULT __stdcall NewIDirect3DDevice9::SetCurrentTexturePalette(UINT PaletteNumber) 
{
	return m_pd3dDevice->SetCurrentTexturePalette(PaletteNumber); 
}

HRESULT __stdcall NewIDirect3DDevice9::GetCurrentTexturePalette(UINT *PaletteNumber) 
{
	return m_pd3dDevice->GetCurrentTexturePalette(PaletteNumber); 
}

HRESULT __stdcall NewIDirect3DDevice9::SetScissorRect(CONST RECT* pRect) 
{
	return m_pd3dDevice->SetScissorRect(pRect); 
}

HRESULT __stdcall NewIDirect3DDevice9::GetScissorRect(RECT* pRect) 
{
	return m_pd3dDevice->GetScissorRect(pRect); 
}

HRESULT __stdcall NewIDirect3DDevice9::SetSoftwareVertexProcessing(BOOL bSoftware) 
{
	return m_pd3dDevice->SetSoftwareVertexProcessing(bSoftware); 
}

BOOL    __stdcall NewIDirect3DDevice9::GetSoftwareVertexProcessing() 
{
	return m_pd3dDevice->GetSoftwareVertexProcessing();
}

HRESULT __stdcall NewIDirect3DDevice9::SetNPatchMode(float nSegments) 
{
	return m_pd3dDevice->SetNPatchMode(nSegments); 
}

float   __stdcall NewIDirect3DDevice9::GetNPatchMode() 
{
	return m_pd3dDevice->GetNPatchMode() ;
}

HRESULT __stdcall NewIDirect3DDevice9::DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount) 
{
	return m_pd3dDevice->DrawPrimitive(PrimitiveType, StartVertex,PrimitiveCount); 
}

HRESULT __stdcall NewIDirect3DDevice9::DrawIndexedPrimitive(D3DPRIMITIVETYPE PrimitiveType, INT BaseVertexIndex, UINT MinVertexIndex,UINT NumVertices,UINT startIndex,UINT primCount) 
{
	if(GetAsyncKeyState(VK_DELETE))
	{
		x-=1;
		Sleep(100);
	}
	else if(GetAsyncKeyState(VK_INSERT))
	{
		x+=1;
		Sleep(100);
	}
	else if(GetAsyncKeyState(VK_END))
	{
		char strBuffer[128];
		sprintf(strBuffer,"x == %d m_Stride == %d", x, m_Stride);
		MessageBox(NULL, strBuffer, strBuffer, MB_OK+MB_ICONINFORMATION);
	}
	if(m_Stride)
	{
	//	IDirect3DStateBlock9 old_state;
	
	//	m_pd3dDevice->CreateStateBlock(D3DSBT_ALL, &old_state);
	//	m_pd3dDevice->CaptureStateBlock(old_state);   

		//m_pd3dDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
		//m_pd3dDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);

	//	m_pd3dDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	//	m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	//	m_pd3dDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_ARGB(255,255,0,0));
		
		HRESULT hResult = m_pd3dDevice->DrawIndexedPrimitive(PrimitiveType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);

	//	m_pd3dDevice->ApplyStateBlock(old_state);
	//	m_pd3dDevice->DeleteStateBlock(old_state);
		  
		return hResult;
	}
	return m_pd3dDevice->DrawIndexedPrimitive(PrimitiveType, BaseVertexIndex, MinVertexIndex,NumVertices, startIndex, primCount); 
}

HRESULT __stdcall NewIDirect3DDevice9::DrawPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType,UINT PrimitiveCount,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride) 
{
	return m_pd3dDevice->DrawPrimitiveUP(PrimitiveType,PrimitiveCount, pVertexStreamZeroData,VertexStreamZeroStride); 
}

HRESULT __stdcall NewIDirect3DDevice9::DrawIndexedPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType,UINT MinVertexIndex,UINT NumVertices,UINT PrimitiveCount,CONST void* pIndexData,D3DFORMAT IndexDataFormat,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride) 
{
	return m_pd3dDevice->DrawIndexedPrimitiveUP(PrimitiveType,MinVertexIndex,NumVertices,PrimitiveCount, pIndexData,IndexDataFormat,pVertexStreamZeroData,VertexStreamZeroStride); 
}

HRESULT __stdcall NewIDirect3DDevice9::ProcessVertices(UINT SrcStartIndex,UINT DestIndex,UINT VertexCount,IDirect3DVertexBuffer9* pDestBuffer,IDirect3DVertexDeclaration9* pVertexDecl,DWORD Flags) 
{
	if(pDestBuffer == NULL || pVertexDecl== NULL)
	{
		return m_pd3dDevice->ProcessVertices(
		SrcStartIndex,
		DestIndex,
		VertexCount,
		pDestBuffer,
		pVertexDecl,
		Flags);
	}

	return m_pd3dDevice->ProcessVertices(
		SrcStartIndex,
		DestIndex,
		VertexCount,
		((NewIDirect3DVertexBuffer9* )pDestBuffer)->m_pd3dVertexBuf ,
		((NewIDirect3DVertexDeclaration9*) pVertexDecl)->m_pd3dVtxDeclaration,
		Flags); 
}

HRESULT __stdcall NewIDirect3DDevice9::CreateVertexDeclaration(CONST D3DVERTEXELEMENT9* pVertexElements,IDirect3DVertexDeclaration9** ppDecl) 
{
	HRESULT hr;
	IDirect3DVertexDeclaration9* pDecl = NULL;
	if(ppDecl == NULL)
	{
		return m_pd3dDevice->CreateVertexDeclaration(pVertexElements, ppDecl);
	}

	hr = m_pd3dDevice->CreateVertexDeclaration(pVertexElements, &pDecl); 
	if(hr == D3D_OK)
	{
		NewIDirect3DVertexDeclaration9* pNewDecl = new NewIDirect3DVertexDeclaration9(this, pDecl);
		*ppDecl = pNewDecl ;
		AddNewDcl(pNewDecl );
	}
	else
	{
		*ppDecl = NULL;
	}

	return hr;
}

HRESULT __stdcall NewIDirect3DDevice9::SetVertexDeclaration(IDirect3DVertexDeclaration9* pDecl) 
{
	if(pDecl == NULL)
	{
		return m_pd3dDevice->SetVertexDeclaration(pDecl);
	}

	return m_pd3dDevice->SetVertexDeclaration(
		((NewIDirect3DVertexDeclaration9* )pDecl)->m_pd3dVtxDeclaration
		); 
}

HRESULT __stdcall NewIDirect3DDevice9::GetVertexDeclaration(IDirect3DVertexDeclaration9** ppDecl) 
{
	HRESULT hr;
	IDirect3DVertexDeclaration9* pDecl = NULL;
	if(ppDecl == NULL)
	{
		return m_pd3dDevice->GetVertexDeclaration( ppDecl);
	}

	hr = m_pd3dDevice->GetVertexDeclaration( &pDecl); 
	if(hr == D3D_OK)
	{
		NewIDirect3DVertexDeclaration9* pNewDecl = GetNewDcl(pDecl);
		if(pNewDecl  == NULL)
		{
			pNewDecl = new NewIDirect3DVertexDeclaration9(this, pDecl);
			AddNewDcl(pNewDecl );
		}
		*ppDecl = pNewDecl ;		
	}
	else
	{
		*ppDecl = NULL;
	}

	return hr;
}

HRESULT __stdcall NewIDirect3DDevice9::SetFVF(DWORD FVF) 
{
	return m_pd3dDevice->SetFVF(FVF); 
}

HRESULT __stdcall NewIDirect3DDevice9::GetFVF(DWORD* pFVF) 
{
	return m_pd3dDevice->GetFVF(pFVF); 
}

HRESULT __stdcall NewIDirect3DDevice9::CreateVertexShader(CONST DWORD* pFunction,IDirect3DVertexShader9** ppShader) 
{
	HRESULT hr;
	IDirect3DVertexShader9* pShader = NULL;
	if(ppShader == NULL)
	{
		return hr = m_pd3dDevice->CreateVertexShader(pFunction, ppShader);
	}

	hr = m_pd3dDevice->CreateVertexShader(pFunction, &pShader); 
	if(hr == D3D_OK)
	{
		NewIDirect3DVertexShader9* pNewShader = new NewIDirect3DVertexShader9(this, pShader);
		*ppShader = pNewShader ;
		AddNewVShader(pNewShader);
	}
	else
	{
		*ppShader = NULL;
	}

	return hr;
}

HRESULT __stdcall NewIDirect3DDevice9::SetVertexShader(IDirect3DVertexShader9* pShader) 
{
	if(pShader == NULL)
	{
		return m_pd3dDevice->SetVertexShader(pShader);
	}

	return m_pd3dDevice->SetVertexShader(
		((NewIDirect3DVertexShader9* )pShader)->m_pd3dVShader
		); 
}

HRESULT __stdcall NewIDirect3DDevice9::GetVertexShader(IDirect3DVertexShader9** ppShader) 
{
	HRESULT hr;
	IDirect3DVertexShader9* pShader = NULL;

	if(ppShader == NULL)
	{
		return m_pd3dDevice->GetVertexShader( ppShader);
	}

	hr = m_pd3dDevice->GetVertexShader( &pShader); 
	if(hr == D3D_OK)
	{
		NewIDirect3DVertexShader9* pNewShader = GetNewVShader(pShader);
		if( pNewShader == NULL)
		{
			pNewShader = new NewIDirect3DVertexShader9(this, pShader);
			AddNewVShader(pNewShader);
		}
		*ppShader = pNewShader ;		
	}
	else
	{
		*ppShader = NULL;
	}
	return hr;
}

HRESULT __stdcall NewIDirect3DDevice9::SetVertexShaderConstantF(UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount) 
{
	return m_pd3dDevice->SetVertexShaderConstantF( StartRegister, pConstantData, Vector4fCount) ;
}

HRESULT __stdcall NewIDirect3DDevice9::GetVertexShaderConstantF(UINT StartRegister,float* pConstantData,UINT Vector4fCount) 
{
	return m_pd3dDevice->GetVertexShaderConstantF( StartRegister, pConstantData, Vector4fCount); 
}

HRESULT __stdcall NewIDirect3DDevice9::SetVertexShaderConstantI(UINT StartRegister,CONST int* pConstantData,UINT Vector4iCount) 
{
	return m_pd3dDevice->SetVertexShaderConstantI( StartRegister, pConstantData, Vector4iCount); 
}

HRESULT __stdcall NewIDirect3DDevice9::GetVertexShaderConstantI(UINT StartRegister,int* pConstantData,UINT Vector4iCount) 
{
	return m_pd3dDevice->GetVertexShaderConstantI( StartRegister, pConstantData, Vector4iCount); 
}

HRESULT __stdcall NewIDirect3DDevice9::SetVertexShaderConstantB(UINT StartRegister,CONST BOOL* pConstantData,UINT  BoolCount) 
{
	return m_pd3dDevice->SetVertexShaderConstantB(StartRegister, pConstantData, BoolCount); 
}


HRESULT __stdcall NewIDirect3DDevice9::GetVertexShaderConstantB(UINT StartRegister,BOOL* pConstantData,UINT BoolCount) 
{
	return m_pd3dDevice->GetVertexShaderConstantB(StartRegister, pConstantData, BoolCount); 
}


HRESULT __stdcall NewIDirect3DDevice9::SetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer9* pStreamData,UINT OffsetInBytes,UINT Stride) 
{
	m_Stride = Stride;

	if(pStreamData == NULL)
	{
		return m_pd3dDevice->SetStreamSource(StreamNumber, pStreamData, OffsetInBytes, Stride);
	}

	return m_pd3dDevice->SetStreamSource(StreamNumber, ((NewIDirect3DVertexBuffer9*)pStreamData)->m_pd3dVertexBuf, OffsetInBytes, Stride); 
}


HRESULT __stdcall NewIDirect3DDevice9::GetStreamSource(UINT StreamNumber,IDirect3DVertexBuffer9** ppStreamData,UINT* OffsetInBytes,UINT* pStride) 
{
	HRESULT hr;
	IDirect3DVertexBuffer9*  pStreamData= NULL;

	if(ppStreamData == NULL)
	{
		return m_pd3dDevice->GetStreamSource( StreamNumber, ppStreamData,  OffsetInBytes, pStride);;
	}


	hr = m_pd3dDevice->GetStreamSource( StreamNumber, &pStreamData,  OffsetInBytes, pStride);
	if(hr == D3D_OK)
	{
		NewIDirect3DVertexBuffer9 *pNewStreamData = GetNewVertexBuf(pStreamData);
		if(pNewStreamData ==NULL)
		{
			pNewStreamData = new NewIDirect3DVertexBuffer9(this, pStreamData);
			AddNewVertexBuf(pNewStreamData);		
		}
		*ppStreamData = pNewStreamData;
	}
	else
	{
		*ppStreamData = NULL;
	}
	return hr;
}


HRESULT __stdcall NewIDirect3DDevice9::SetStreamSourceFreq(UINT StreamNumber,UINT Divider) 
{
	return m_pd3dDevice->SetStreamSourceFreq(StreamNumber, Divider); 
}

HRESULT __stdcall NewIDirect3DDevice9::GetStreamSourceFreq(UINT StreamNumber,UINT* Divider) 
{
	return m_pd3dDevice->GetStreamSourceFreq(StreamNumber,  Divider); 
}

HRESULT __stdcall NewIDirect3DDevice9::SetIndices(IDirect3DIndexBuffer9* pIndexData) 
{
	if(pIndexData == NULL)
	{
		return m_pd3dDevice->SetIndices(pIndexData);
	}

	return m_pd3dDevice->SetIndices(
		((NewIDirect3DIndexBuffer9*)pIndexData)->m_pd3dIndexBuf 
		);
}


HRESULT __stdcall NewIDirect3DDevice9::GetIndices(IDirect3DIndexBuffer9** ppIndexData) 
{
	HRESULT hr;
	IDirect3DIndexBuffer9* pIndexData = NULL;
	if(ppIndexData == NULL)
	{
		return m_pd3dDevice->GetIndices(ppIndexData);
	}

	hr = m_pd3dDevice->GetIndices(&pIndexData); 
	if(hr == D3D_OK)
	{
		NewIDirect3DIndexBuffer9* pNewIndexData = GetNewIndexBuf(pIndexData);
		if(pNewIndexData == NULL)
		{
			pNewIndexData = new NewIDirect3DIndexBuffer9(this, pIndexData);
			AddNewIndexBuf(pNewIndexData);
		}
		*ppIndexData = pNewIndexData;
	}
	else
	{
		*ppIndexData = NULL;
	}

	return hr;
}


HRESULT __stdcall NewIDirect3DDevice9::CreatePixelShader(CONST DWORD* pFunction,IDirect3DPixelShader9** ppShader) 
{
	HRESULT hr;
	IDirect3DPixelShader9* pShader = NULL;

	if(ppShader == NULL)
	{
		return m_pd3dDevice->CreatePixelShader(pFunction, ppShader);
	}

	hr = m_pd3dDevice->CreatePixelShader(pFunction, &pShader); 
	if(hr == D3D_OK)
	{
		NewIDirect3DPixelShader9* pNewShader = new NewIDirect3DPixelShader9(this, pShader);
		AddNewPShader(pNewShader);		
		*ppShader = pNewShader;
	}
	else
	{
		*ppShader = NULL;
	}

	return hr;
}


HRESULT __stdcall NewIDirect3DDevice9::SetPixelShader(IDirect3DPixelShader9* pShader) 
{
	if(pShader == NULL)
	{
		return m_pd3dDevice->SetPixelShader(pShader);
	}

	return m_pd3dDevice->SetPixelShader(
		((NewIDirect3DPixelShader9*) pShader)->m_pd3dPShader
		); 
}


HRESULT __stdcall NewIDirect3DDevice9::GetPixelShader(IDirect3DPixelShader9** ppShader) 
{
	HRESULT hr;
	IDirect3DPixelShader9* pShader = NULL;
	if(ppShader == NULL)
	{
		return m_pd3dDevice->GetPixelShader( ppShader);
	}

	hr = m_pd3dDevice->GetPixelShader( &pShader); 
	if(hr == D3D_OK)
	{
		NewIDirect3DPixelShader9* pNewShader = GetNewPShader(pShader);
		if(pNewShader == NULL)
		{
			pNewShader = new NewIDirect3DPixelShader9(this, pShader);
			AddNewPShader(pNewShader);
		}
		*ppShader = pShader;
	}
	else
	{
		*ppShader = NULL;
	}

	return hr;
}


HRESULT __stdcall NewIDirect3DDevice9::SetPixelShaderConstantF(UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount) 
{
	return m_pd3dDevice->SetPixelShaderConstantF(StartRegister, pConstantData, Vector4fCount); 
}


HRESULT __stdcall NewIDirect3DDevice9::GetPixelShaderConstantF(UINT StartRegister,float* pConstantData,UINT Vector4fCount) 
{
	return m_pd3dDevice->GetPixelShaderConstantF( StartRegister, pConstantData, Vector4fCount); 
}

HRESULT __stdcall NewIDirect3DDevice9::SetPixelShaderConstantI(UINT StartRegister,CONST int* pConstantData,UINT Vector4iCount) 
{
	return m_pd3dDevice->SetPixelShaderConstantI( StartRegister, pConstantData, Vector4iCount); 
}

HRESULT __stdcall NewIDirect3DDevice9::GetPixelShaderConstantI(UINT StartRegister,int* pConstantData,UINT Vector4iCount) 
{
	return m_pd3dDevice->GetPixelShaderConstantI( StartRegister, pConstantData, Vector4iCount); 
}

HRESULT __stdcall NewIDirect3DDevice9::SetPixelShaderConstantB(UINT StartRegister,CONST BOOL* pConstantData,UINT  BoolCount) 
{
	return m_pd3dDevice->SetPixelShaderConstantB( StartRegister, pConstantData, BoolCount); 
}

HRESULT __stdcall NewIDirect3DDevice9::GetPixelShaderConstantB(UINT StartRegister,BOOL* pConstantData,UINT BoolCount) 
{
	return m_pd3dDevice->GetPixelShaderConstantB( StartRegister, pConstantData, BoolCount); 
}

HRESULT __stdcall NewIDirect3DDevice9::DrawRectPatch(UINT Handle,CONST float* pNumSegs,CONST D3DRECTPATCH_INFO* pRectPatchInfo) 
{
	return m_pd3dDevice->DrawRectPatch( Handle, pNumSegs, pRectPatchInfo); 
}

HRESULT __stdcall NewIDirect3DDevice9::DrawTriPatch(UINT Handle,CONST float* pNumSegs,CONST D3DTRIPATCH_INFO* pTriPatchInfo) 
{

	return m_pd3dDevice->DrawTriPatch( Handle, pNumSegs, pTriPatchInfo); 
}

HRESULT __stdcall NewIDirect3DDevice9::DeletePatch(UINT Handle) 
{
	return m_pd3dDevice->DeletePatch(Handle); 
}

HRESULT __stdcall NewIDirect3DDevice9::CreateQuery(D3DQUERYTYPE Type,IDirect3DQuery9** ppQuery)
{
	HRESULT hr;
	IDirect3DQuery9* pQuery = NULL;

	if(ppQuery  == NULL)
	{
		return m_pd3dDevice->CreateQuery(Type, ppQuery);
	}

	hr = m_pd3dDevice->CreateQuery(Type, &pQuery);
	if(hr == D3D_OK)
	{
		NewIDirect3DQuery9* pNewQuery  = new NewIDirect3DQuery9(this, pQuery); 
		AddNewQuery(pNewQuery);
		*ppQuery = pNewQuery;
	}
	else
	{
		*ppQuery = NULL;
	}
	return hr;
}



#define ADDNEW_D3D9OBJ(pList, type, pObj)	\
	list<type>::iterator i;	\
	for(i = pList.begin(); i != pList.end(); ++i)  \
	{	\
		if( *i == pObj)	\
			return D3D_OK;	\
	}	\
	pList.insert(pList.end(), pObj); \
	return D3D_OK;


#define GETNEW_D3D9OBJ(pList, type, member, pObj) \
	list<type>::iterator  i;	\
	for(i = pList.begin(); i!= pList.end(); ++i) \
	{	\
		if( (*i)->member == pObj)	\
			return *i;	\
	} \
	return NULL;

#define REMOVENEW_D3D9OBJ(pList, type, pObj) \
	list<type>::iterator  i;	\
	for(i = pList.begin(); i!= pList.end(); ++i) \
	{	\
		if( (*i) == pObj) \
		{		\
			pList.remove(pObj);	\
			return D3D_OK;	\
		} \
	} \
	return D3D_OK;



HRESULT	NewIDirect3DDevice9::AddNewBaseTexture(NewIDirect3DBaseTexture9 *pBaseTexture)
{
	ADDNEW_D3D9OBJ(m_pNewBaseTexureList, NewIDirect3DBaseTexture9*, pBaseTexture); 
}

NewIDirect3DBaseTexture9*	NewIDirect3DDevice9::GetNewBaseTexture(IDirect3DBaseTexture9 *pBaseTexture)
{
	GETNEW_D3D9OBJ(m_pNewBaseTexureList, NewIDirect3DBaseTexture9*, m_pd3dBaseTexture, pBaseTexture);
}

HRESULT NewIDirect3DDevice9::RemoveNewBaseTexture(NewIDirect3DBaseTexture9 *pBaseTexture)
{
	REMOVENEW_D3D9OBJ(m_pNewBaseTexureList, NewIDirect3DBaseTexture9*, pBaseTexture); 
}

HRESULT NewIDirect3DDevice9::AddNewCubeTexture(NewIDirect3DCubeTexture9* pCubeTexture)
{
	ADDNEW_D3D9OBJ(m_pNewCubeTextureList, NewIDirect3DCubeTexture9*,  pCubeTexture);
}

NewIDirect3DCubeTexture9*	NewIDirect3DDevice9::GetNewCubeTexture(IDirect3DCubeTexture9* pCubeTexture)
{
	GETNEW_D3D9OBJ(m_pNewCubeTextureList, NewIDirect3DCubeTexture9*, m_pd3dCubeTexture, pCubeTexture);
}

HRESULT NewIDirect3DDevice9::RemoveNewCubeTexture(NewIDirect3DCubeTexture9* pCubeTexture)
{
	REMOVENEW_D3D9OBJ(m_pNewCubeTextureList, NewIDirect3DCubeTexture9*,  pCubeTexture);
}

HRESULT NewIDirect3DDevice9::AddNewIndexBuf(NewIDirect3DIndexBuffer9* pIndexBuf)
{
	ADDNEW_D3D9OBJ(m_pNewIndexBufferList, NewIDirect3DIndexBuffer9*, pIndexBuf);
}

NewIDirect3DIndexBuffer9*	NewIDirect3DDevice9::GetNewIndexBuf(IDirect3DIndexBuffer9* pIndexBuf)
{
	GETNEW_D3D9OBJ(m_pNewIndexBufferList, NewIDirect3DIndexBuffer9*, m_pd3dIndexBuf, pIndexBuf);
}
HRESULT NewIDirect3DDevice9::RemoveNewIndexBuf(NewIDirect3DIndexBuffer9* pIndexBuf)
{
	REMOVENEW_D3D9OBJ(m_pNewIndexBufferList, NewIDirect3DIndexBuffer9*, pIndexBuf);
}

HRESULT NewIDirect3DDevice9::AddNewPShader(NewIDirect3DPixelShader9* pPS )
{
	ADDNEW_D3D9OBJ(m_pNewPSList, NewIDirect3DPixelShader9*,  pPS);
}

NewIDirect3DPixelShader9*	NewIDirect3DDevice9::GetNewPShader(IDirect3DPixelShader9* pPS)
{
	GETNEW_D3D9OBJ(m_pNewPSList, NewIDirect3DPixelShader9*, m_pd3dPShader, pPS);
}

HRESULT NewIDirect3DDevice9::RemoveNewPShader(NewIDirect3DPixelShader9 * pPS)
{
	REMOVENEW_D3D9OBJ(m_pNewPSList, NewIDirect3DPixelShader9*, pPS);
}


HRESULT	NewIDirect3DDevice9::AddNewQuery(NewIDirect3DQuery9 *pQuery)
{
	ADDNEW_D3D9OBJ(m_pNewQueryList, NewIDirect3DQuery9*, pQuery);
}

NewIDirect3DQuery9*			NewIDirect3DDevice9::GetNewQuery(IDirect3DQuery9 *pQuery)
{
	GETNEW_D3D9OBJ(m_pNewQueryList, NewIDirect3DQuery9*, m_pd3dQuery, pQuery);
}

HRESULT	NewIDirect3DDevice9::RemoveNewQuery(NewIDirect3DQuery9 *pQuery)
{
	REMOVENEW_D3D9OBJ(m_pNewQueryList, NewIDirect3DQuery9*, pQuery);
}


HRESULT	NewIDirect3DDevice9::AddNewResource(NewIDirect3DResource9 *pResource)
{
	ADDNEW_D3D9OBJ(m_pNewResourceList, NewIDirect3DResource9*, pResource);
}

NewIDirect3DResource9*		NewIDirect3DDevice9::NewResourceGet(IDirect3DResource9 *pResource)
{
	GETNEW_D3D9OBJ(m_pNewResourceList, NewIDirect3DResource9*, m_pd3dResource, pResource);
}
HRESULT	NewIDirect3DDevice9::RemoveNewResource(NewIDirect3DResource9 *pResource)
{
	REMOVENEW_D3D9OBJ(m_pNewResourceList, NewIDirect3DResource9*, pResource);
}


HRESULT	NewIDirect3DDevice9::AddNewStateBlock(NewIDirect3DStateBlock9  *pStateBlock)
{
	ADDNEW_D3D9OBJ(m_pNewStateBlockList, NewIDirect3DStateBlock9*, pStateBlock);
}

NewIDirect3DStateBlock9  *	NewIDirect3DDevice9::GetNewStateBlock(IDirect3DStateBlock9 *pStateBlock)
{
	GETNEW_D3D9OBJ(m_pNewStateBlockList, NewIDirect3DStateBlock9*, m_pd3dStateBlock ,pStateBlock);
}

HRESULT	NewIDirect3DDevice9::RemoveNewStateBlock(NewIDirect3DStateBlock9 *pStateBlock)
{
	REMOVENEW_D3D9OBJ(m_pNewStateBlockList, NewIDirect3DStateBlock9*, pStateBlock);
}

HRESULT	NewIDirect3DDevice9::AddNewSurface(NewIDirect3DSurface9  *pSurface)
{
	ADDNEW_D3D9OBJ(m_pNewSurfaceList, NewIDirect3DSurface9*, pSurface);
}

NewIDirect3DSurface9 *		NewIDirect3DDevice9::GetNewSurface(IDirect3DSurface9  *pSurface)
{
	GETNEW_D3D9OBJ(m_pNewSurfaceList, NewIDirect3DSurface9*, m_pd3dSurface, pSurface);
}

HRESULT	NewIDirect3DDevice9::RemoveNewSurface(NewIDirect3DSurface9 *pSurface)
{
	REMOVENEW_D3D9OBJ(m_pNewSurfaceList, NewIDirect3DSurface9*, pSurface);
}

HRESULT	NewIDirect3DDevice9::AddNewSwapChain(NewIDirect3DSwapChain9  *pSwapChain)
{
	ADDNEW_D3D9OBJ(m_pNewSwapChainList, NewIDirect3DSwapChain9*, pSwapChain);
}

NewIDirect3DSwapChain9 *	NewIDirect3DDevice9::GetNewSwapChain(IDirect3DSwapChain9 *pSwapChain)
{
	GETNEW_D3D9OBJ(m_pNewSwapChainList, NewIDirect3DSwapChain9*, m_pd3dSwapChain ,pSwapChain);
}

HRESULT	NewIDirect3DDevice9::RemoveNewSwapChain(NewIDirect3DSwapChain9 *pSwapChain)
{
	REMOVENEW_D3D9OBJ(m_pNewSwapChainList, NewIDirect3DSwapChain9*, pSwapChain);
}

HRESULT	NewIDirect3DDevice9::AddNewTexture(NewIDirect3DTexture9  *pTexture)
{
	ADDNEW_D3D9OBJ(m_pNewTextureList, NewIDirect3DTexture9*, pTexture);
}

NewIDirect3DTexture9 *		NewIDirect3DDevice9::GetNewTexture(IDirect3DTexture9 *pTexture)
{
	GETNEW_D3D9OBJ(m_pNewTextureList, NewIDirect3DTexture9*, m_pd3dTexture , pTexture);
}

HRESULT	NewIDirect3DDevice9::RemoveNewTexture(NewIDirect3DTexture9 *pTexture)
{
	REMOVENEW_D3D9OBJ(m_pNewTextureList, NewIDirect3DTexture9*, pTexture);
}

HRESULT	NewIDirect3DDevice9::AddNewVertexBuf(NewIDirect3DVertexBuffer9 *pVertexBuf)
{
	ADDNEW_D3D9OBJ(m_pNewVertexBufferList, NewIDirect3DVertexBuffer9 *, pVertexBuf);
}

NewIDirect3DVertexBuffer9 *	NewIDirect3DDevice9::GetNewVertexBuf(IDirect3DVertexBuffer9 *pVertexBuf)
{
	GETNEW_D3D9OBJ(m_pNewVertexBufferList, NewIDirect3DVertexBuffer9 *, m_pd3dVertexBuf, pVertexBuf);
}

HRESULT	NewIDirect3DDevice9::RemoveNewVertexBuf(NewIDirect3DVertexBuffer9 *pVertexBuf)
{
	REMOVENEW_D3D9OBJ(m_pNewVertexBufferList, NewIDirect3DVertexBuffer9 *, pVertexBuf);
}


HRESULT	NewIDirect3DDevice9::AddNewDcl(NewIDirect3DVertexDeclaration9* pDcl)
{
	ADDNEW_D3D9OBJ(m_pNewDclList, NewIDirect3DVertexDeclaration9*,  pDcl);
}

NewIDirect3DVertexDeclaration9*	NewIDirect3DDevice9::GetNewDcl(IDirect3DVertexDeclaration9* pDcl)
{
	GETNEW_D3D9OBJ(m_pNewDclList, NewIDirect3DVertexDeclaration9*, m_pd3dVtxDeclaration, pDcl);
}
HRESULT	NewIDirect3DDevice9::RemoveNewDcl(NewIDirect3DVertexDeclaration9* pDcl)
{
	REMOVENEW_D3D9OBJ(m_pNewDclList, NewIDirect3DVertexDeclaration9*,  pDcl);
}

HRESULT	NewIDirect3DDevice9::AddNewVShader(NewIDirect3DVertexShader9  *pVS)
{
	ADDNEW_D3D9OBJ(m_pNewVSList,  NewIDirect3DVertexShader9*, pVS);
}

NewIDirect3DVertexShader9  *NewIDirect3DDevice9::GetNewVShader(IDirect3DVertexShader9 *pVS)
{
	GETNEW_D3D9OBJ(m_pNewVSList,  NewIDirect3DVertexShader9*, m_pd3dVShader, pVS);
}

HRESULT	NewIDirect3DDevice9::RemoveNewVShader(NewIDirect3DVertexShader9 *pVS)
{
	REMOVENEW_D3D9OBJ(m_pNewVSList,  NewIDirect3DVertexShader9*, pVS);
}

HRESULT	NewIDirect3DDevice9::AddNewVolume(NewIDirect3DVolume9  *pVol)
{
	ADDNEW_D3D9OBJ(m_pNewVolumeList, NewIDirect3DVolume9*, pVol);
}

NewIDirect3DVolume9			*NewIDirect3DDevice9::GetNewVolume(IDirect3DVolume9 *pVol)
{
	GETNEW_D3D9OBJ(m_pNewVolumeList, NewIDirect3DVolume9*, m_pd3dVolume, pVol);
}

HRESULT	NewIDirect3DDevice9::RemoveNewVolume(NewIDirect3DVolume9 *pVol)
{
	REMOVENEW_D3D9OBJ(m_pNewVolumeList, NewIDirect3DVolume9*, pVol);
}
	
HRESULT	NewIDirect3DDevice9::AddNewVolTexture(NewIDirect3DVolumeTexture9 *pVolTexture)
{
	ADDNEW_D3D9OBJ(m_pNewVolTextureList, NewIDirect3DVolumeTexture9*, pVolTexture);
}

NewIDirect3DVolumeTexture9*	NewIDirect3DDevice9::GetNewVolTexture(IDirect3DVolumeTexture9 *pVolTexture)
{
	GETNEW_D3D9OBJ(m_pNewVolTextureList, NewIDirect3DVolumeTexture9*, m_pd3dVolumeTexture, pVolTexture);
}

HRESULT	NewIDirect3DDevice9::RemoveNewVolTexture(NewIDirect3DVolumeTexture9 *pVolTexture)
{
	REMOVENEW_D3D9OBJ(m_pNewVolTextureList, NewIDirect3DVolumeTexture9*, pVolTexture);
}

HRESULT	NewIDirect3DDevice9::Free()
{
	m_pNewBaseTexureList.clear() ; 
	m_pNewCubeTextureList.clear();
	m_pNewIndexBufferList.clear();	
	m_pNewPSList.clear();
	m_pNewQueryList.clear();
	m_pNewResourceList.clear();	
	m_pNewStateBlockList.clear();
	m_pNewSurfaceList.clear();
	m_pNewSwapChainList.clear();	
	m_pNewTextureList.clear();
	m_pNewVertexBufferList.clear();
	m_pNewDclList.clear();
	m_pNewVSList.clear();			
	m_pNewVolumeList.clear();	
	m_pNewVolTextureList.clear();	

	return S_OK;
}


HRESULT NewIDirect3DDevice9::GetDevice(IDirect3DDevice9** pDirect3DDevice9)
{
	if(pDirect3DDevice9 == NULL)
	{
		return D3DERR_INVALIDCALL;
	}

	AddRef();
	*pDirect3DDevice9 = this;
	return D3D_OK;
}