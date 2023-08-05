#ifndef ___HOOKSYS_H__
#define ___HOOKSYS_H__

//HMODULE of Microsoft D3D9.dll
extern HMODULE  g_hd3d9;

//Function Direct3DCraete9 of Microsoft D3D9.dll
typedef DWORD (WINAPI *Proto_Direct3DCreate9)(UINT SDKVersion);
extern  Proto_Direct3DCreate9 pDirect3DCreate9;


BOOL OpenMSD3D9();
BOOL CloseMSD3D9(); 

#endif  //___HOOK_H__

