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

NewIDirect3DVolumeTexture9::NewIDirect3DVolumeTexture9(NewIDirect3DDevice9 *pDevice, IDirect3DVolumeTexture9 *pVolumeTexture)
{
	m_refCount = 0;
	m_pd3dDevice		= pDevice;
	m_pd3dVolumeTexture = pVolumeTexture;
}

HRESULT __stdcall NewIDirect3DVolumeTexture9::QueryInterface(REFIID iid, void ** ppvObject)
{
	return m_pd3dVolumeTexture->QueryInterface(iid, ppvObject);
}

ULONG	__stdcall NewIDirect3DVolumeTexture9::AddRef(void)
{
	m_refCount++;
	m_refCount = m_pd3dVolumeTexture->AddRef();
	return m_refCount;
}

ULONG	__stdcall NewIDirect3DVolumeTexture9::Release(void)
{
	m_refCount--;
	m_refCount = m_pd3dVolumeTexture->Release();
	if(m_refCount <=0)
	{
		m_pd3dDevice->RemoveNewVolTexture(this); 
		delete this;
		return 0;
	}

	return m_refCount;

}


HRESULT __stdcall NewIDirect3DVolumeTexture9::GetDevice(IDirect3DDevice9** ppDevice)
{
	return m_pd3dDevice->GetDevice(ppDevice);
}

HRESULT __stdcall NewIDirect3DVolumeTexture9::SetPrivateData(REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) 
{
	return m_pd3dVolumeTexture->SetPrivateData( refguid, pData, SizeOfData, Flags) ;
}

HRESULT __stdcall NewIDirect3DVolumeTexture9::GetPrivateData(REFGUID refguid,void* pData,DWORD* pSizeOfData)
{
	return m_pd3dVolumeTexture->GetPrivateData( refguid, pData, pSizeOfData) ;
}

HRESULT __stdcall NewIDirect3DVolumeTexture9::FreePrivateData(REFGUID refguid)
{
	return m_pd3dVolumeTexture->FreePrivateData( refguid) ;
}

DWORD   __stdcall NewIDirect3DVolumeTexture9::SetPriority(DWORD PriorityNew)
{
	return m_pd3dVolumeTexture->SetPriority(PriorityNew);
}

DWORD   __stdcall NewIDirect3DVolumeTexture9::GetPriority()
{
	return m_pd3dVolumeTexture->GetPriority() ;
}

void    __stdcall NewIDirect3DVolumeTexture9::PreLoad()
{
	m_pd3dVolumeTexture->PreLoad() ;
}

D3DRESOURCETYPE __stdcall NewIDirect3DVolumeTexture9:: GetType()
{
	return m_pd3dVolumeTexture->GetType() ;
}

DWORD  __stdcall NewIDirect3DVolumeTexture9::SetLOD(DWORD LODNew)
{
	return m_pd3dVolumeTexture->SetLOD(LODNew);
}

DWORD  __stdcall NewIDirect3DVolumeTexture9::GetLOD()
{
	return m_pd3dVolumeTexture->GetLOD();
}

DWORD  __stdcall NewIDirect3DVolumeTexture9::GetLevelCount()
{
	return m_pd3dVolumeTexture->GetLevelCount();
}

HRESULT __stdcall NewIDirect3DVolumeTexture9::SetAutoGenFilterType(D3DTEXTUREFILTERTYPE FilterType)
{
	return m_pd3dVolumeTexture->SetAutoGenFilterType(FilterType) ;
}

D3DTEXTUREFILTERTYPE __stdcall NewIDirect3DVolumeTexture9::GetAutoGenFilterType()
{
	return m_pd3dVolumeTexture->GetAutoGenFilterType() ;
}

void    __stdcall NewIDirect3DVolumeTexture9::GenerateMipSubLevels()
{
	m_pd3dVolumeTexture->GenerateMipSubLevels() ;
}

HRESULT __stdcall NewIDirect3DVolumeTexture9::GetLevelDesc(UINT Level,D3DVOLUME_DESC *pDesc)
{
	return m_pd3dVolumeTexture->GetLevelDesc(Level, pDesc) ;
}

HRESULT __stdcall NewIDirect3DVolumeTexture9::GetVolumeLevel(UINT Level,IDirect3DVolume9** ppVolumeLevel)
{
	HRESULT hr;
	ULONG   refCount;

	IDirect3DVolume9* pVolumeLevel = NULL;
	if(ppVolumeLevel == NULL)
	{
		return m_pd3dVolumeTexture->GetVolumeLevel(Level, ppVolumeLevel) ;;	
	}
	
	hr =m_pd3dVolumeTexture->GetVolumeLevel(Level, &pVolumeLevel) ;

	if(hr == D3D_OK)
	{
		NewIDirect3DVolume9* pNewVol = m_pd3dDevice->GetNewVolume(pVolumeLevel); 
		if(pNewVol == NULL)
		{
			pNewVol = new NewIDirect3DVolume9(m_pd3dDevice, pVolumeLevel);
			m_pd3dDevice->AddNewVolume(pNewVol);
		}
		*ppVolumeLevel = pNewVol;
	}
	else
	{
		*ppVolumeLevel = NULL;		
	}

	return hr;
}

HRESULT __stdcall NewIDirect3DVolumeTexture9::LockBox(UINT Level,D3DLOCKED_BOX* pLockedVolume,CONST D3DBOX* pBox,DWORD Flags)
{
	return m_pd3dVolumeTexture->LockBox(Level, pLockedVolume, pBox, Flags) ;
}

HRESULT __stdcall NewIDirect3DVolumeTexture9::UnlockBox(UINT Level)
{
	return m_pd3dVolumeTexture->UnlockBox(Level) ;
}

HRESULT __stdcall NewIDirect3DVolumeTexture9::AddDirtyBox(CONST D3DBOX* pDirtyBox)
{
	return m_pd3dVolumeTexture->AddDirtyBox(pDirtyBox) ;
}
