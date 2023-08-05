#ifndef __DIRECT3D9_H__
#define __DIRECT3D9_H__

#include <d3d9.h>
#include <list>
#include "d3dfont.h"
using namespace std ;

class NewIDirect3D9;
class NewIDirect3DBaseTexture9; 
class NewIDirect3DCubeTexture9; 
class NewIDirect3DDevice9;
class NewIDirect3DIndexBuffer9;
class NewIDirect3DPixelShader9;
class NewIDirect3DQuery9;
class NewIDirect3DResource9;
class NewIDirect3DStateBlock9;
class NewIDirect3DSurface9;
class NewIDirect3DSwapChain9;
class NewIDirect3DTexture9;
class NewIDirect3DVertexBuffer9;
class NewIDirect3DVertexDeclaration9;
class NewIDirect3DVertexShader9;
class NewIDirect3DVolumeTexture9;
class NewIDirect3DVolume9;
 
//IDirect3D9 define
class NewIDirect3D9 : public IDirect3D9
{
	//Constrcut Function 
public:
	NewIDirect3D9(); 

	//IDirect3D9 Interface Methods
public: 
	HRESULT __stdcall QueryInterface(REFIID iid, void ** ppvObject);
	ULONG	__stdcall AddRef(void);
	ULONG	__stdcall Release(void);

	/*** IDirect3D9 methods ***/
	HRESULT __stdcall RegisterSoftwareDevice(void* pInitializeFunction) ;
	UINT    __stdcall GetAdapterCount();
	HRESULT __stdcall GetAdapterIdentifier(UINT Adapter,DWORD Flags,D3DADAPTER_IDENTIFIER9* pIdentifier) ;
	UINT    __stdcall GetAdapterModeCount(UINT Adapter,D3DFORMAT Format) ;
	HRESULT __stdcall EnumAdapterModes(UINT Adapter,D3DFORMAT Format,UINT Mode,D3DDISPLAYMODE* pMode) ;
	HRESULT __stdcall GetAdapterDisplayMode(UINT Adapter,D3DDISPLAYMODE* pMode) ;
	HRESULT __stdcall CheckDeviceType(UINT iAdapter,D3DDEVTYPE DevType,D3DFORMAT DisplayFormat,D3DFORMAT BackBufferFormat,BOOL bWindowed) ;
	HRESULT __stdcall CheckDeviceFormat(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,DWORD Usage,D3DRESOURCETYPE RType,D3DFORMAT CheckFormat) ;
	HRESULT __stdcall CheckDeviceMultiSampleType(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SurfaceFormat,BOOL Windowed,D3DMULTISAMPLE_TYPE MultiSampleType,DWORD* pQualityLevels) ;
	HRESULT __stdcall CheckDepthStencilMatch(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,D3DFORMAT RenderTargetFormat,D3DFORMAT DepthStencilFormat) ;
	HRESULT __stdcall CheckDeviceFormatConversion(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SourceFormat,D3DFORMAT TargetFormat) ;
	HRESULT __stdcall GetDeviceCaps(UINT Adapter,D3DDEVTYPE DeviceType,D3DCAPS9* pCaps) ;
	HMONITOR  __stdcall GetAdapterMonitor(UINT Adapter) ;
	HRESULT __stdcall CreateDevice(UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DDevice9** ppReturnedDeviceInterface) ;

	//Internal Method and member variables
public:
	LONG					m_refCount;
	IDirect3D9*				m_pDirect3D9; 		
};


class NewIDirect3DDevice9: public IDirect3DDevice9
{
public:
	NewIDirect3DDevice9(NewIDirect3D9*  pd3d9, IDirect3DDevice9* pDevice);
	UINT m_Stride;
	UINT x;
public:
    /*** IUnknown methods ***/
	HRESULT __stdcall QueryInterface(REFIID iid, void ** ppvObject);
	ULONG	__stdcall AddRef(void);
	ULONG	__stdcall Release(void);

    /*** IDirect3DDevice9 methods ***/
    HRESULT __stdcall TestCooperativeLevel() ;
    UINT	__stdcall  GetAvailableTextureMem() ;
    HRESULT __stdcall EvictManagedResources() ;
    HRESULT __stdcall GetDirect3D(IDirect3D9** ppD3D9) ;
    HRESULT __stdcall GetDeviceCaps(D3DCAPS9* pCaps) ;
    HRESULT __stdcall GetDisplayMode(UINT iSwapChain,D3DDISPLAYMODE* pMode) ;
    HRESULT __stdcall GetCreationParameters(D3DDEVICE_CREATION_PARAMETERS *pParameters) ;
    HRESULT __stdcall SetCursorProperties(UINT XHotSpot,UINT YHotSpot,IDirect3DSurface9* pCursorBitmap) ;
    void    __stdcall SetCursorPosition(int X,int Y,DWORD Flags) ;
    BOOL    __stdcall ShowCursor(BOOL bShow) ;
    HRESULT __stdcall CreateAdditionalSwapChain(D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DSwapChain9** ppSwapChain) ;
    HRESULT __stdcall GetSwapChain(UINT iSwapChain,IDirect3DSwapChain9** ppSwapChain) ;
    UINT    __stdcall GetNumberOfSwapChains() ;
    HRESULT __stdcall Reset(D3DPRESENT_PARAMETERS* pPresentationParameters) ;
    HRESULT __stdcall Present(CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion) ;
    HRESULT __stdcall GetBackBuffer(UINT iSwapChain,UINT iBackBuffer,D3DBACKBUFFER_TYPE Type,IDirect3DSurface9** ppBackBuffer) ;
    HRESULT __stdcall GetRasterStatus(UINT iSwapChain,D3DRASTER_STATUS* pRasterStatus) ;
    HRESULT __stdcall SetDialogBoxMode(BOOL bEnableDialogs) ;
    void    __stdcall SetGammaRamp(UINT iSwapChain,DWORD Flags,CONST D3DGAMMARAMP* pRamp) ;
    void    __stdcall GetGammaRamp(UINT iSwapChain,D3DGAMMARAMP* pRamp) ;
    HRESULT __stdcall CreateTexture(UINT Width,UINT Height,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DTexture9** ppTexture,HANDLE* pSharedHandle) ;
    HRESULT __stdcall CreateVolumeTexture(UINT Width,UINT Height,UINT Depth,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DVolumeTexture9** ppVolumeTexture,HANDLE* pSharedHandle) ;
    HRESULT __stdcall CreateCubeTexture(UINT EdgeLength,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DCubeTexture9** ppCubeTexture,HANDLE* pSharedHandle) ;
    HRESULT __stdcall CreateVertexBuffer(UINT Length,DWORD Usage,DWORD FVF,D3DPOOL Pool,IDirect3DVertexBuffer9** ppVertexBuffer,HANDLE* pSharedHandle) ;
    HRESULT __stdcall CreateIndexBuffer(UINT Length,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DIndexBuffer9** ppIndexBuffer,HANDLE* pSharedHandle) ;
    HRESULT __stdcall CreateRenderTarget(UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Lockable,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle) ;
    HRESULT __stdcall CreateDepthStencilSurface(UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Discard,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle) ;
    HRESULT __stdcall UpdateSurface(IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,IDirect3DSurface9* pDestinationSurface,CONST POINT* pDestPoint) ;
    HRESULT __stdcall UpdateTexture(IDirect3DBaseTexture9* pSourceTexture,IDirect3DBaseTexture9* pDestinationTexture) ;
    HRESULT __stdcall GetRenderTargetData(IDirect3DSurface9* pRenderTarget,IDirect3DSurface9* pDestSurface) ;
    HRESULT __stdcall GetFrontBufferData(UINT iSwapChain,IDirect3DSurface9* pDestSurface) ;
    HRESULT __stdcall StretchRect(IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,IDirect3DSurface9* pDestSurface,CONST RECT* pDestRect,D3DTEXTUREFILTERTYPE Filter) ;
    HRESULT __stdcall ColorFill(IDirect3DSurface9* pSurface,CONST RECT* pRect,D3DCOLOR color) ;
    HRESULT __stdcall CreateOffscreenPlainSurface(UINT Width,UINT Height,D3DFORMAT Format,D3DPOOL Pool,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle) ;
    HRESULT __stdcall SetRenderTarget(DWORD RenderTargetIndex,IDirect3DSurface9* pRenderTarget) ;
    HRESULT __stdcall GetRenderTarget(DWORD RenderTargetIndex,IDirect3DSurface9** ppRenderTarget) ;
    HRESULT __stdcall SetDepthStencilSurface(IDirect3DSurface9* pNewZStencil) ;
    HRESULT __stdcall GetDepthStencilSurface(IDirect3DSurface9** ppZStencilSurface) ;
    HRESULT __stdcall BeginScene() ;
    HRESULT __stdcall EndScene() ;
    HRESULT __stdcall Clear(DWORD Count,CONST D3DRECT* pRects,DWORD Flags,D3DCOLOR Color,float Z,DWORD Stencil) ;
    HRESULT __stdcall SetTransform(D3DTRANSFORMSTATETYPE State,CONST D3DMATRIX* pMatrix) ;
    HRESULT __stdcall GetTransform(D3DTRANSFORMSTATETYPE State,D3DMATRIX* pMatrix) ;
    HRESULT __stdcall MultiplyTransform(D3DTRANSFORMSTATETYPE,CONST D3DMATRIX*) ;
    HRESULT __stdcall SetViewport(CONST D3DVIEWPORT9* pViewport) ;
    HRESULT __stdcall GetViewport(D3DVIEWPORT9* pViewport) ;
    HRESULT __stdcall SetMaterial(CONST D3DMATERIAL9* pMaterial) ;
    HRESULT __stdcall GetMaterial(D3DMATERIAL9* pMaterial) ;
    HRESULT __stdcall SetLight(DWORD Index,CONST D3DLIGHT9*) ;
    HRESULT __stdcall GetLight(DWORD Index,D3DLIGHT9*) ;
    HRESULT __stdcall LightEnable(DWORD Index,BOOL Enable) ;
    HRESULT __stdcall GetLightEnable(DWORD Index,BOOL* pEnable) ;
    HRESULT __stdcall SetClipPlane(DWORD Index,CONST float* pPlane) ;
    HRESULT __stdcall GetClipPlane(DWORD Index,float* pPlane) ;
    HRESULT __stdcall SetRenderState(D3DRENDERSTATETYPE State,DWORD Value) ;
    HRESULT __stdcall GetRenderState(D3DRENDERSTATETYPE State,DWORD* pValue) ;
    HRESULT __stdcall CreateStateBlock(D3DSTATEBLOCKTYPE Type,IDirect3DStateBlock9** ppSB) ;
    HRESULT __stdcall BeginStateBlock() ;
    HRESULT __stdcall EndStateBlock(IDirect3DStateBlock9** ppSB) ;
    HRESULT __stdcall SetClipStatus(CONST D3DCLIPSTATUS9* pClipStatus) ;
    HRESULT __stdcall GetClipStatus(D3DCLIPSTATUS9* pClipStatus) ;
    HRESULT __stdcall GetTexture(DWORD Stage,IDirect3DBaseTexture9** ppTexture) ;
    HRESULT __stdcall SetTexture(DWORD Stage,IDirect3DBaseTexture9* pTexture) ;
    HRESULT __stdcall GetTextureStageState(DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD* pValue) ;
    HRESULT __stdcall SetTextureStageState(DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD Value) ;
    HRESULT __stdcall GetSamplerState(DWORD Sampler,D3DSAMPLERSTATETYPE Type,DWORD* pValue) ;
    HRESULT __stdcall SetSamplerState(DWORD Sampler,D3DSAMPLERSTATETYPE Type,DWORD Value) ;
    HRESULT __stdcall ValidateDevice(DWORD* pNumPasses) ;
    HRESULT __stdcall SetPaletteEntries(UINT PaletteNumber,CONST PALETTEENTRY* pEntries) ;
    HRESULT __stdcall GetPaletteEntries(UINT PaletteNumber,PALETTEENTRY* pEntries) ;
    HRESULT __stdcall SetCurrentTexturePalette(UINT PaletteNumber) ;
    HRESULT __stdcall GetCurrentTexturePalette(UINT *PaletteNumber) ;
    HRESULT __stdcall SetScissorRect(CONST RECT* pRect) ;
    HRESULT __stdcall GetScissorRect(RECT* pRect) ;
    HRESULT __stdcall SetSoftwareVertexProcessing(BOOL bSoftware) ;
    BOOL    __stdcall GetSoftwareVertexProcessing() ;
    HRESULT __stdcall SetNPatchMode(float nSegments) ;
    float   __stdcall GetNPatchMode() ;
    HRESULT __stdcall DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType,UINT StartVertex,UINT PrimitiveCount) ;
    HRESULT __stdcall DrawIndexedPrimitive(D3DPRIMITIVETYPE,INT BaseVertexIndex,UINT MinVertexIndex,UINT NumVertices,UINT startIndex,UINT primCount) ;
    HRESULT __stdcall DrawPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType,UINT PrimitiveCount,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride) ;
    HRESULT __stdcall DrawIndexedPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType,UINT MinVertexIndex,UINT NumVertices,UINT PrimitiveCount,CONST void* pIndexData,D3DFORMAT IndexDataFormat,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride) ;
    HRESULT __stdcall ProcessVertices(UINT SrcStartIndex,UINT DestIndex,UINT VertexCount,IDirect3DVertexBuffer9* pDestBuffer,IDirect3DVertexDeclaration9* pVertexDecl,DWORD Flags) ;
    HRESULT __stdcall CreateVertexDeclaration(CONST D3DVERTEXELEMENT9* pVertexElements,IDirect3DVertexDeclaration9** ppDecl) ;
    HRESULT __stdcall SetVertexDeclaration(IDirect3DVertexDeclaration9* pDecl) ;
    HRESULT __stdcall GetVertexDeclaration(IDirect3DVertexDeclaration9** ppDecl) ;
    HRESULT __stdcall SetFVF(DWORD FVF) ;
    HRESULT __stdcall GetFVF(DWORD* pFVF) ;
    HRESULT __stdcall CreateVertexShader(CONST DWORD* pFunction,IDirect3DVertexShader9** ppShader) ;
    HRESULT __stdcall SetVertexShader(IDirect3DVertexShader9* pShader) ;
    HRESULT __stdcall GetVertexShader(IDirect3DVertexShader9** ppShader) ;
    HRESULT __stdcall SetVertexShaderConstantF(UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount) ;
    HRESULT __stdcall GetVertexShaderConstantF(UINT StartRegister,float* pConstantData,UINT Vector4fCount) ;
    HRESULT __stdcall SetVertexShaderConstantI(UINT StartRegister,CONST int* pConstantData,UINT Vector4iCount) ;
    HRESULT __stdcall GetVertexShaderConstantI(UINT StartRegister,int* pConstantData,UINT Vector4iCount) ;
    HRESULT __stdcall SetVertexShaderConstantB(UINT StartRegister,CONST BOOL* pConstantData,UINT  BoolCount) ;
    HRESULT __stdcall GetVertexShaderConstantB(UINT StartRegister,BOOL* pConstantData,UINT BoolCount) ;
    HRESULT __stdcall SetStreamSource(UINT StreamNumber,IDirect3DVertexBuffer9* pStreamData,UINT OffsetInBytes,UINT Stride) ;
    HRESULT __stdcall GetStreamSource(UINT StreamNumber,IDirect3DVertexBuffer9** ppStreamData,UINT* OffsetInBytes,UINT* pStride) ;
    HRESULT __stdcall SetStreamSourceFreq(UINT StreamNumber,UINT Divider) ;
    HRESULT __stdcall GetStreamSourceFreq(UINT StreamNumber,UINT* Divider) ;
    HRESULT __stdcall SetIndices(IDirect3DIndexBuffer9* pIndexData) ;
    HRESULT __stdcall GetIndices(IDirect3DIndexBuffer9** ppIndexData) ;
    HRESULT __stdcall CreatePixelShader(CONST DWORD* pFunction,IDirect3DPixelShader9** ppShader) ;
    HRESULT __stdcall SetPixelShader(IDirect3DPixelShader9* pShader) ;
    HRESULT __stdcall GetPixelShader(IDirect3DPixelShader9** ppShader) ;
    HRESULT __stdcall SetPixelShaderConstantF(UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount) ;
    HRESULT __stdcall GetPixelShaderConstantF(UINT StartRegister,float* pConstantData,UINT Vector4fCount) ;
    HRESULT __stdcall SetPixelShaderConstantI(UINT StartRegister,CONST int* pConstantData,UINT Vector4iCount) ;
    HRESULT __stdcall GetPixelShaderConstantI(UINT StartRegister,int* pConstantData,UINT Vector4iCount) ;
    HRESULT __stdcall SetPixelShaderConstantB(UINT StartRegister,CONST BOOL* pConstantData,UINT  BoolCount) ;
    HRESULT __stdcall GetPixelShaderConstantB(UINT StartRegister,BOOL* pConstantData,UINT BoolCount) ;
    HRESULT __stdcall DrawRectPatch(UINT Handle,CONST float* pNumSegs,CONST D3DRECTPATCH_INFO* pRectPatchInfo) ;
    HRESULT __stdcall DrawTriPatch(UINT Handle,CONST float* pNumSegs,CONST D3DTRIPATCH_INFO* pTriPatchInfo) ;
    HRESULT __stdcall DeletePatch(UINT Handle) ;
    HRESULT __stdcall CreateQuery(D3DQUERYTYPE Type,IDirect3DQuery9** ppQuery) ;
	//Internal Method and member variables
public:
	LONG					m_refCount;
	NewIDirect3D9*			m_pd3d9;
	IDirect3DDevice9*		m_pd3dDevice;


	HRESULT GetDevice(IDirect3DDevice9** ppDevice);

	//all Hooked NewIDirect3DSurface9 Interface
	list<NewIDirect3DBaseTexture9*>			m_pNewBaseTexureList; 
	list<NewIDirect3DCubeTexture9*>			m_pNewCubeTextureList;
	list<NewIDirect3DIndexBuffer9*>			m_pNewIndexBufferList;			
	list<NewIDirect3DPixelShader9*>			m_pNewPSList;
	list<NewIDirect3DQuery9*>				m_pNewQueryList;
	list<NewIDirect3DResource9*>			m_pNewResourceList;	
	list<NewIDirect3DStateBlock9*>			m_pNewStateBlockList;
	list<NewIDirect3DSurface9*>				m_pNewSurfaceList;
	list<NewIDirect3DSwapChain9*>			m_pNewSwapChainList;	
	list<NewIDirect3DTexture9*>				m_pNewTextureList;
	list<NewIDirect3DVertexBuffer9*>		m_pNewVertexBufferList;
	list<NewIDirect3DVertexDeclaration9*>	m_pNewDclList;
	list<NewIDirect3DVertexShader9*>		m_pNewVSList;			
	list<NewIDirect3DVolume9*>				m_pNewVolumeList;	
	list<NewIDirect3DVolumeTexture9*>		m_pNewVolTextureList;	
	
	HRESULT						AddNewBaseTexture(NewIDirect3DBaseTexture9 *pBaseTexture);
	NewIDirect3DBaseTexture9*	GetNewBaseTexture(IDirect3DBaseTexture9 *pBaseTexture);
	HRESULT						RemoveNewBaseTexture(NewIDirect3DBaseTexture9 *pBaseTexture);

	HRESULT						AddNewCubeTexture(NewIDirect3DCubeTexture9* pCubeTexture);
	NewIDirect3DCubeTexture9*	GetNewCubeTexture(IDirect3DCubeTexture9* pCubeTexture);
	HRESULT						RemoveNewCubeTexture(NewIDirect3DCubeTexture9* pCubeTexture);

	HRESULT						AddNewIndexBuf(NewIDirect3DIndexBuffer9* pIndexBuf);
	NewIDirect3DIndexBuffer9*	GetNewIndexBuf(IDirect3DIndexBuffer9* pIndexBuf);
	HRESULT						RemoveNewIndexBuf(NewIDirect3DIndexBuffer9* pIndexBuf);

	HRESULT						AddNewPShader(NewIDirect3DPixelShader9* pPS);
	NewIDirect3DPixelShader9*	GetNewPShader(IDirect3DPixelShader9* pPS);
	HRESULT						RemoveNewPShader(NewIDirect3DPixelShader9 * pPS);

	
	HRESULT						AddNewQuery(NewIDirect3DQuery9 *pQuery);
	NewIDirect3DQuery9*			GetNewQuery(IDirect3DQuery9 *pQuery);
	HRESULT						RemoveNewQuery(NewIDirect3DQuery9 *pQuery);

	
	HRESULT						AddNewResource(NewIDirect3DResource9 *pResource);
	NewIDirect3DResource9*		NewResourceGet(IDirect3DResource9 *pResource);
	HRESULT						RemoveNewResource(NewIDirect3DResource9 *pResource);

	
	HRESULT						AddNewStateBlock(NewIDirect3DStateBlock9  *pStateBlock);
	NewIDirect3DStateBlock9  *	GetNewStateBlock(IDirect3DStateBlock9 *pStateBlock);
	HRESULT						RemoveNewStateBlock(NewIDirect3DStateBlock9 *pStateBlock);

	HRESULT						AddNewSurface(NewIDirect3DSurface9  *pSurface);
	NewIDirect3DSurface9 *		GetNewSurface(IDirect3DSurface9  *pSurface);
	HRESULT						RemoveNewSurface(NewIDirect3DSurface9 *pSurface);
	
	HRESULT						AddNewSwapChain(NewIDirect3DSwapChain9  *pSwapChain);
	NewIDirect3DSwapChain9 *	GetNewSwapChain(IDirect3DSwapChain9 *pSwapChain);
	HRESULT						RemoveNewSwapChain(NewIDirect3DSwapChain9 *pSwapChain);
	
	HRESULT						AddNewTexture(NewIDirect3DTexture9  *pTexture);
	NewIDirect3DTexture9 *		GetNewTexture(IDirect3DTexture9 *pTexture);
	HRESULT						RemoveNewTexture(NewIDirect3DTexture9 *pTexture);

	HRESULT						AddNewVertexBuf(NewIDirect3DVertexBuffer9 *pVertexBuf);
	NewIDirect3DVertexBuffer9 *	GetNewVertexBuf(IDirect3DVertexBuffer9 *pVertexBuf);
	HRESULT						RemoveNewVertexBuf(NewIDirect3DVertexBuffer9 *pVertexBuf);


	HRESULT							AddNewDcl(NewIDirect3DVertexDeclaration9* pDcl);
	NewIDirect3DVertexDeclaration9*	GetNewDcl(IDirect3DVertexDeclaration9* pDcl);
	HRESULT							RemoveNewDcl(NewIDirect3DVertexDeclaration9* pDcl);

	HRESULT						AddNewVShader(NewIDirect3DVertexShader9  *pVS);
	NewIDirect3DVertexShader9  *GetNewVShader(IDirect3DVertexShader9 *pVS);
	HRESULT						RemoveNewVShader(NewIDirect3DVertexShader9 *pVS);

	HRESULT						AddNewVolume(NewIDirect3DVolume9  *pVol);
	NewIDirect3DVolume9			*GetNewVolume(IDirect3DVolume9 *pVol);
	HRESULT						RemoveNewVolume(NewIDirect3DVolume9 *pVol);

	HRESULT						AddNewVolTexture(NewIDirect3DVolumeTexture9 *pVolTexture);
	NewIDirect3DVolumeTexture9*	GetNewVolTexture(IDirect3DVolumeTexture9 *pVolTexture);
	HRESULT						RemoveNewVolTexture(NewIDirect3DVolumeTexture9 *pVolTexture);

	HRESULT		Free();

};

class NewIDirect3DStateBlock9: public IDirect3DStateBlock9
{
public:
	NewIDirect3DStateBlock9(NewIDirect3DDevice9 * pDevice, IDirect3DStateBlock9 *pStateBlock);
public:
    /*** IUnknown methods ***/
	HRESULT __stdcall QueryInterface(REFIID iid, void ** ppvObject);
	ULONG	__stdcall AddRef(void);
	ULONG	__stdcall Release(void);

    /*** IDirect3DStateBlock9 methods ***/
    HRESULT __stdcall GetDevice(IDirect3DDevice9** ppDevice) ;
    HRESULT __stdcall Capture() ;
    HRESULT __stdcall Apply() ;

public:
	LONG					m_refCount;
	NewIDirect3DDevice9		*m_pd3dDevice;
	IDirect3DStateBlock9	*m_pd3dStateBlock;

};

class NewIDirect3DSwapChain9 :public IDirect3DSwapChain9
{
public:
	NewIDirect3DSwapChain9(NewIDirect3DDevice9 *pDevice, IDirect3DSwapChain9 *pSwapChain);

public:
    /*** IUnknown methods ***/
	HRESULT __stdcall QueryInterface(REFIID iid, void ** ppvObject);
	ULONG	__stdcall AddRef(void);
	ULONG	__stdcall Release(void);

    /*** IDirect3DSwapChain9 methods ***/
    HRESULT __stdcall Present(CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion,DWORD dwFlags) ;
    HRESULT __stdcall GetFrontBufferData(IDirect3DSurface9* pDestSurface) ;
    HRESULT __stdcall GetBackBuffer(UINT iBackBuffer,D3DBACKBUFFER_TYPE Type,IDirect3DSurface9** ppBackBuffer) ;
    HRESULT __stdcall GetRasterStatus(D3DRASTER_STATUS* pRasterStatus) ;
    HRESULT __stdcall GetDisplayMode(D3DDISPLAYMODE* pMode) ;
    HRESULT __stdcall GetDevice(IDirect3DDevice9** ppDevice) ;
    HRESULT __stdcall GetPresentParameters(D3DPRESENT_PARAMETERS* pPresentationParameters) ;

public:
	LONG					m_refCount;
	NewIDirect3DDevice9		*m_pd3dDevice;
	IDirect3DSwapChain9		*m_pd3dSwapChain;
};

class NewIDirect3DResource9:public IDirect3DResource9
{
public:
	NewIDirect3DResource9(NewIDirect3DDevice9 *pDevice, IDirect3DResource9* pResource);
public:
    /*** IUnknown methods ***/
	HRESULT __stdcall QueryInterface(REFIID iid, void ** ppvObject);
	ULONG	__stdcall AddRef(void);
	ULONG	__stdcall Release(void);

    /*** IDirect3DResource9 methods ***/
    HRESULT __stdcall GetDevice(IDirect3DDevice9** ppDevice) ;
    HRESULT __stdcall SetPrivateData(REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) ;
    HRESULT __stdcall GetPrivateData(REFGUID refguid,void* pData,DWORD* pSizeOfData) ;
    HRESULT __stdcall FreePrivateData(REFGUID refguid) ;
    DWORD   __stdcall SetPriority(DWORD PriorityNew) ;
    DWORD   __stdcall GetPriority() ;
    void    __stdcall PreLoad() ;
    D3DRESOURCETYPE __stdcall GetType() ;

public:
	LONG				m_refCount;
	NewIDirect3DDevice9	*m_pd3dDevice;
	IDirect3DResource9	*m_pd3dResource;
};

class NewIDirect3DVertexDeclaration9:public IDirect3DVertexDeclaration9
{
public:
	NewIDirect3DVertexDeclaration9(NewIDirect3DDevice9 *pDevice, IDirect3DVertexDeclaration9* pVertexDcl);
public:
    /*** IUnknown methods ***/
	HRESULT __stdcall QueryInterface(REFIID iid, void ** ppvObject);
	ULONG	__stdcall AddRef(void);
	ULONG	__stdcall Release(void);

    /*** IDirect3DVertexDeclaration9 methods ***/
    HRESULT __stdcall GetDevice(IDirect3DDevice9** ppDevice) ;
    HRESULT __stdcall GetDeclaration(D3DVERTEXELEMENT9*,UINT* pNumElements) ;

public:
	LONG						m_refCount;
	NewIDirect3DDevice9			*m_pd3dDevice;
	IDirect3DVertexDeclaration9	*m_pd3dVtxDeclaration;
};

class NewIDirect3DVertexShader9:public IDirect3DVertexShader9
{
public:
	NewIDirect3DVertexShader9(NewIDirect3DDevice9 *pDevice,IDirect3DVertexShader9 *pVShader);
public:
    /*** IUnknown methods ***/
	HRESULT __stdcall QueryInterface(REFIID iid, void ** ppvObject);
	ULONG	__stdcall AddRef(void);
	ULONG	__stdcall Release(void);

    /*** IDirect3DVertexShader9 methods ***/
    HRESULT __stdcall GetDevice(IDirect3DDevice9** ppDevice) ;
    HRESULT __stdcall GetFunction(void*,UINT* pSizeOfData) ;
public:
	LONG						m_refCount;
	NewIDirect3DDevice9			*m_pd3dDevice;
	IDirect3DVertexShader9		*m_pd3dVShader;
};

class NewIDirect3DPixelShader9:public IDirect3DPixelShader9
{
public:
	NewIDirect3DPixelShader9(NewIDirect3DDevice9	*pDevice, IDirect3DPixelShader9 *pPShader);
public:
    /*** IUnknown methods ***/
	HRESULT __stdcall QueryInterface(REFIID iid, void ** ppvObject);
	ULONG	__stdcall AddRef(void);
	ULONG	__stdcall Release(void);

    /*** IDirect3DPixelShader9 methods ***/
    HRESULT __stdcall GetDevice(IDirect3DDevice9** ppDevice) ;
    HRESULT __stdcall GetFunction(void*,UINT* pSizeOfData) ;

public:
	LONG					m_refCount;
	NewIDirect3DDevice9		*m_pd3dDevice;
	IDirect3DPixelShader9	*m_pd3dPShader;
};

class NewIDirect3DBaseTexture9 : public IDirect3DBaseTexture9
{
public:
	NewIDirect3DBaseTexture9 (NewIDirect3DDevice9 *pDevice, IDirect3DBaseTexture9* pBaseTexture);
public:
    /*** IUnknown methods ***/
	HRESULT __stdcall QueryInterface(REFIID iid, void ** ppvObject);
	ULONG	__stdcall AddRef(void);
	ULONG	__stdcall Release(void);

    /*** IDirect3DResource9 methods ***/
    HRESULT __stdcall GetDevice(IDirect3DDevice9** ppDevice) ;
    HRESULT __stdcall SetPrivateData(REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) ;
    HRESULT __stdcall GetPrivateData(REFGUID refguid,void* pData,DWORD* pSizeOfData) ;
    HRESULT __stdcall FreePrivateData(REFGUID refguid) ;
    DWORD   __stdcall SetPriority(DWORD PriorityNew) ;
    DWORD   __stdcall GetPriority() ;
    void    __stdcall PreLoad() ;
    D3DRESOURCETYPE __stdcall  GetType() ;
    DWORD   __stdcall SetLOD(DWORD LODNew) ;
    DWORD   __stdcall GetLOD() ;
    DWORD   __stdcall GetLevelCount() ;
    HRESULT __stdcall SetAutoGenFilterType(D3DTEXTUREFILTERTYPE FilterType) ;
    D3DTEXTUREFILTERTYPE __stdcall  GetAutoGenFilterType() ;
    void __stdcall  GenerateMipSubLevels() ;

public:
	LONG					m_refCount;
	NewIDirect3DDevice9		*m_pd3dDevice;
	IDirect3DBaseTexture9	*m_pd3dBaseTexture;
};


class NewIDirect3DTexture9: public IDirect3DTexture9
{
public:
	NewIDirect3DTexture9(NewIDirect3DDevice9* pDevice, IDirect3DTexture9 *pTexture);
public:
    /*** IUnknown methods ***/
	HRESULT __stdcall QueryInterface(REFIID iid, void ** ppvObject);
	ULONG	__stdcall AddRef(void);
	ULONG	__stdcall Release(void);

    /*** IDirect3DBaseTexture9 methods ***/
    HRESULT __stdcall GetDevice(IDirect3DDevice9** ppDevice) ;
    HRESULT __stdcall SetPrivateData(REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) ;
    HRESULT __stdcall GetPrivateData(REFGUID refguid,void* pData,DWORD* pSizeOfData) ;
    HRESULT __stdcall FreePrivateData(REFGUID refguid) ;
    DWORD   __stdcall SetPriority(DWORD PriorityNew) ;
    DWORD   __stdcall GetPriority() ;
    void    __stdcall PreLoad() ;
    D3DRESOURCETYPE __stdcall  GetType() ;
    DWORD   __stdcall SetLOD(DWORD LODNew) ;
    DWORD   __stdcall GetLOD() ;
    DWORD   __stdcall GetLevelCount() ;
    HRESULT __stdcall SetAutoGenFilterType(D3DTEXTUREFILTERTYPE FilterType) ;
    D3DTEXTUREFILTERTYPE __stdcall  GetAutoGenFilterType() ;
    void __stdcall    GenerateMipSubLevels() ;
	
    HRESULT __stdcall GetLevelDesc(UINT Level,D3DSURFACE_DESC *pDesc);
    HRESULT __stdcall GetSurfaceLevel(UINT Level,IDirect3DSurface9** ppSurfaceLevel);
    HRESULT __stdcall LockRect(UINT Level,D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags);
    HRESULT __stdcall UnlockRect(UINT Level);
    HRESULT __stdcall AddDirtyRect(CONST RECT* pDirtyRect);
public:
	LONG					m_refCount;
	NewIDirect3DDevice9		*m_pd3dDevice;
	IDirect3DTexture9		*m_pd3dTexture;
};

class NewIDirect3DVolumeTexture9: public IDirect3DVolumeTexture9
{
public:
	NewIDirect3DVolumeTexture9(NewIDirect3DDevice9 *pDevice, IDirect3DVolumeTexture9 *pVolumeTexture);
public:
    /*** IUnknown methods ***/
	HRESULT __stdcall QueryInterface(REFIID iid, void ** ppvObject);
	ULONG	__stdcall AddRef(void);
	ULONG	__stdcall Release(void);

    /*** IDirect3DBaseTexture9 methods ***/
    HRESULT __stdcall GetDevice(IDirect3DDevice9** ppDevice) ;
    HRESULT __stdcall SetPrivateData(REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) ;
    HRESULT __stdcall GetPrivateData(REFGUID refguid,void* pData,DWORD* pSizeOfData) ;
    HRESULT __stdcall FreePrivateData(REFGUID refguid) ;
    DWORD   __stdcall SetPriority(DWORD PriorityNew) ;
    DWORD   __stdcall GetPriority() ;
    void    __stdcall PreLoad() ;
    D3DRESOURCETYPE __stdcall  GetType() ;
    DWORD  __stdcall SetLOD(DWORD LODNew) ;
    DWORD  __stdcall GetLOD() ;
    DWORD  __stdcall GetLevelCount() ;
    HRESULT __stdcall SetAutoGenFilterType(D3DTEXTUREFILTERTYPE FilterType) ;
    D3DTEXTUREFILTERTYPE __stdcall  GetAutoGenFilterType() ;
    void    __stdcall GenerateMipSubLevels() ;
    HRESULT __stdcall GetLevelDesc(UINT Level,D3DVOLUME_DESC *pDesc) ;
    HRESULT __stdcall GetVolumeLevel(UINT Level,IDirect3DVolume9** ppVolumeLevel) ;
    HRESULT __stdcall LockBox(UINT Level,D3DLOCKED_BOX* pLockedVolume,CONST D3DBOX* pBox,DWORD Flags) ;
    HRESULT __stdcall UnlockBox(UINT Level) ;
    HRESULT __stdcall AddDirtyBox(CONST D3DBOX* pDirtyBox) ;

public:
	LONG					m_refCount;
	NewIDirect3DDevice9		*m_pd3dDevice;
	IDirect3DVolumeTexture9	*m_pd3dVolumeTexture;

};

class NewIDirect3DCubeTexture9 :public IDirect3DCubeTexture9
{
public:
	NewIDirect3DCubeTexture9 (NewIDirect3DDevice9 *pDevice, IDirect3DCubeTexture9 *pCubeTexture);

public:
    /*** IUnknown methods ***/
	HRESULT __stdcall QueryInterface(REFIID iid, void ** ppvObject);
	ULONG	__stdcall AddRef(void);
	ULONG	__stdcall Release(void);

    /*** IDirect3DBaseTexture9 methods ***/
    HRESULT __stdcall GetDevice(IDirect3DDevice9** ppDevice) ;
    HRESULT __stdcall SetPrivateData(REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) ;
    HRESULT __stdcall GetPrivateData(REFGUID refguid,void* pData,DWORD* pSizeOfData) ;
    HRESULT __stdcall FreePrivateData(REFGUID refguid) ;
    DWORD   __stdcall SetPriority(DWORD PriorityNew) ;
    DWORD   __stdcall GetPriority() ;
    void    __stdcall PreLoad() ;
    D3DRESOURCETYPE __stdcall  GetType() ;
    DWORD   __stdcall SetLOD(DWORD LODNew) ;
    DWORD   __stdcall GetLOD() ;
    DWORD   __stdcall GetLevelCount() ;
    HRESULT __stdcall SetAutoGenFilterType(D3DTEXTUREFILTERTYPE FilterType) ;
    D3DTEXTUREFILTERTYPE __stdcall  GetAutoGenFilterType() ;
    void    __stdcall  GenerateMipSubLevels() ;
    HRESULT __stdcall GetLevelDesc(UINT Level,D3DSURFACE_DESC *pDesc) ;
    HRESULT __stdcall GetCubeMapSurface(D3DCUBEMAP_FACES FaceType,UINT Level,IDirect3DSurface9** ppCubeMapSurface) ;
    HRESULT __stdcall LockRect(D3DCUBEMAP_FACES FaceType,UINT Level,D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags) ;
    HRESULT __stdcall UnlockRect(D3DCUBEMAP_FACES FaceType,UINT Level) ;
    HRESULT __stdcall AddDirtyRect(D3DCUBEMAP_FACES FaceType,CONST RECT* pDirtyRect) ;

public:
	LONG					m_refCount;
	NewIDirect3DDevice9		*m_pd3dDevice;
	IDirect3DCubeTexture9	*m_pd3dCubeTexture;

};


class NewIDirect3DVertexBuffer9: public IDirect3DVertexBuffer9
{
public:
	NewIDirect3DVertexBuffer9(NewIDirect3DDevice9 *pDevice, IDirect3DVertexBuffer9 *pVertexBuf);
public:
    /*** IUnknown methods ***/
	HRESULT __stdcall QueryInterface(REFIID iid, void ** ppvObject);
	ULONG	__stdcall AddRef(void);
	ULONG	__stdcall Release(void);

    /*** IDirect3DResource9 methods ***/
    HRESULT __stdcall GetDevice(IDirect3DDevice9** ppDevice) ;
    HRESULT __stdcall SetPrivateData(REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) ;
    HRESULT __stdcall GetPrivateData(REFGUID refguid,void* pData,DWORD* pSizeOfData) ;
    HRESULT __stdcall FreePrivateData(REFGUID refguid) ;
    DWORD   __stdcall SetPriority(DWORD PriorityNew) ;
    DWORD   __stdcall GetPriority() ;
    void    __stdcall PreLoad() ;
    D3DRESOURCETYPE __stdcall GetType() ;
    HRESULT __stdcall Lock(UINT OffsetToLock,UINT SizeToLock,void** ppbData,DWORD Flags) ;
    HRESULT __stdcall Unlock() ;
    HRESULT __stdcall GetDesc(D3DVERTEXBUFFER_DESC *pDesc) ;
public:
	LONG					m_refCount;
	NewIDirect3DDevice9		*m_pd3dDevice;
	IDirect3DVertexBuffer9	*m_pd3dVertexBuf;
};

class NewIDirect3DIndexBuffer9: public IDirect3DIndexBuffer9
{
public :
	NewIDirect3DIndexBuffer9(NewIDirect3DDevice9 *pDevice, IDirect3DIndexBuffer9 *pIndexBuf);
public:
    /*** IUnknown methods ***/
	HRESULT __stdcall QueryInterface(REFIID iid, void ** ppvObject);
	ULONG	__stdcall AddRef(void);
	ULONG	__stdcall Release(void);

    /*** IDirect3DResource9 methods ***/
    HRESULT __stdcall GetDevice(IDirect3DDevice9** ppDevice) ;
    HRESULT __stdcall SetPrivateData(REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) ;
    HRESULT __stdcall GetPrivateData(REFGUID refguid,void* pData,DWORD* pSizeOfData) ;
    HRESULT __stdcall FreePrivateData(REFGUID refguid) ;
    DWORD   __stdcall SetPriority(DWORD PriorityNew) ;
    DWORD   __stdcall GetPriority() ;
    void    __stdcall PreLoad() ;
    D3DRESOURCETYPE __stdcall  GetType() ;
    HRESULT __stdcall Lock(UINT OffsetToLock,UINT SizeToLock,void** ppbData,DWORD Flags) ;
    HRESULT __stdcall Unlock() ;
    HRESULT __stdcall GetDesc(D3DINDEXBUFFER_DESC *pDesc) ;
public:
	LONG					m_refCount;
	NewIDirect3DDevice9		*m_pd3dDevice;
	IDirect3DIndexBuffer9	*m_pd3dIndexBuf;

};

class NewIDirect3DSurface9:public IDirect3DSurface9
{
public:
	NewIDirect3DSurface9(NewIDirect3DDevice9 *pDevice, IDirect3DSurface9 *pSurface);
public:
    /*** IUnknown methods ***/
	HRESULT __stdcall QueryInterface(REFIID iid, void ** ppvObject);
	ULONG	__stdcall AddRef(void);
	ULONG	__stdcall Release(void);

    /*** IDirect3DResource9 methods ***/
    HRESULT __stdcall GetDevice(IDirect3DDevice9** ppDevice) ;
    HRESULT __stdcall SetPrivateData(REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) ;
    HRESULT __stdcall GetPrivateData(REFGUID refguid,void* pData,DWORD* pSizeOfData) ;
    HRESULT __stdcall FreePrivateData(REFGUID refguid) ;
    DWORD   __stdcall SetPriority(DWORD PriorityNew) ;
    DWORD   __stdcall GetPriority() ;
    void    __stdcall PreLoad() ;
    D3DRESOURCETYPE __stdcall GetType() ;
    HRESULT __stdcall GetContainer(REFIID riid,void** ppContainer) ;
    HRESULT __stdcall GetDesc(D3DSURFACE_DESC *pDesc) ;
    HRESULT __stdcall LockRect(D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags) ;
    HRESULT __stdcall UnlockRect() ;
    HRESULT __stdcall GetDC(HDC *phdc) ;
    HRESULT __stdcall ReleaseDC(HDC hdc) ;

public:
	LONG					m_refCount;
	NewIDirect3DDevice9*	m_pd3dDevice;
	IDirect3DSurface9*		m_pd3dSurface;
};

class NewIDirect3DVolume9: public IDirect3DVolume9
{
public :
	NewIDirect3DVolume9(NewIDirect3DDevice9 *pDevice, IDirect3DVolume9* pVolume);
public:
    /*** IUnknown methods ***/
	HRESULT __stdcall QueryInterface(REFIID iid, void ** ppvObject);
	ULONG	__stdcall AddRef(void);
	ULONG	__stdcall Release(void);

    /*** IDirect3DVolume9 methods ***/
    HRESULT __stdcall GetDevice(IDirect3DDevice9** ppDevice) ;
    HRESULT __stdcall SetPrivateData(REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) ;
    HRESULT __stdcall GetPrivateData(REFGUID refguid,void* pData,DWORD* pSizeOfData) ;
    HRESULT __stdcall FreePrivateData(REFGUID refguid) ;
    HRESULT __stdcall GetContainer(REFIID riid,void** ppContainer) ;
    HRESULT __stdcall GetDesc(D3DVOLUME_DESC *pDesc) ;
    HRESULT __stdcall LockBox(D3DLOCKED_BOX * pLockedVolume,CONST D3DBOX* pBox,DWORD Flags) ;
    HRESULT __stdcall UnlockBox() ;
public:
	LONG				m_refCount;
	NewIDirect3DDevice9 *m_pd3dDevice;
	IDirect3DVolume9	*m_pd3dVolume;
};

class NewIDirect3DQuery9: public IDirect3DQuery9
{
public:
	NewIDirect3DQuery9(NewIDirect3DDevice9 *pDevice, IDirect3DQuery9 *pQuery);
public:
    /*** IUnknown methods ***/
	HRESULT __stdcall QueryInterface(REFIID iid, void ** ppvObject);
	ULONG	__stdcall AddRef(void);
	ULONG	__stdcall Release(void);

    /*** IDirect3DQuery9 methods ***/
    HRESULT __stdcall GetDevice(IDirect3DDevice9** ppDevice) ;
    D3DQUERYTYPE __stdcall GetType() ;
    DWORD   __stdcall GetDataSize() ;
    HRESULT __stdcall Issue(DWORD dwIssueFlags) ;
    HRESULT __stdcall GetData(void* pData,DWORD dwSize,DWORD dwGetDataFlags) ;
public:
	LONG				m_refCount;
	NewIDirect3DDevice9	*m_pd3dDevice;
	IDirect3DQuery9		*m_pd3dQuery;
};


#endif  //__DIRECT3D9_H__