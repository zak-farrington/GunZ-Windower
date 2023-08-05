//** Hook.cpp: 
//**

#include <windows.h>
#include "Hook.h"

//** Hook.cpp: Hook imported function
PVOID HookImportFunc(const char *Dll, const char *FuncName, int Ordinal, void *Function)
{
	DWORD OldProtect;
	void* PrevValue = 0;

	DWORD ImageBase = (DWORD)GetModuleHandle(NULL);
	IMAGE_DOS_HEADER *IDH = (IMAGE_DOS_HEADER *)ImageBase;
	IMAGE_FILE_HEADER *IFH = (IMAGE_FILE_HEADER *)(ImageBase + IDH->e_lfanew + sizeof(DWORD));
	IMAGE_OPTIONAL_HEADER *IOH = (IMAGE_OPTIONAL_HEADER *)((DWORD)(IFH) + sizeof(IMAGE_FILE_HEADER));
	IMAGE_IMPORT_DESCRIPTOR *IID = (IMAGE_IMPORT_DESCRIPTOR *)(ImageBase + IOH->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);

	VirtualProtect((void*)(ImageBase + IOH->DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].VirtualAddress), IOH->DataDirectory[IMAGE_DIRECTORY_ENTRY_IAT].Size, PAGE_READWRITE, &OldProtect);

	while(IID->Name)
	{
		if(stricmp(Dll, (char *)(ImageBase + IID->Name)) == 0)
		{
			IMAGE_THUNK_DATA * pThunk = (IMAGE_THUNK_DATA *)
				((DWORD)IID->OriginalFirstThunk + ImageBase);
			IMAGE_THUNK_DATA * pThunk2 = (IMAGE_THUNK_DATA *)
				((DWORD)IID->FirstThunk + ImageBase);

			while(pThunk->u1.AddressOfData)
			{
				char * Name = 0;
				int ordinal;
				
				if(pThunk->u1.Ordinal & 0x80000000)
				{
					ordinal = pThunk->u1.Ordinal & 0xFFFF;
				}
				else
				{
					IMAGE_IMPORT_BY_NAME *pName = (IMAGE_IMPORT_BY_NAME *)
						((DWORD)pThunk->u1.AddressOfData + ImageBase);

					ordinal = pName->Hint;
					Name = (char *)pName->Name;
				}

				if(Name != 0 && FuncName && strcmp(Name, FuncName) == 0)
				{
					PrevValue = (void*)pThunk2->u1.Function;

#if _MFC_VER == 0x0600
						pThunk2->u1.Function = (DWORD*)Function;
#else
						pThunk2->u1.Function = (DWORD)Function;
#endif

				}
				else if(ordinal == Ordinal)
				{
					PrevValue = (void*)pThunk2->u1.Function;

#if _MFC_VER == 0x0600
					pThunk2->u1.Function = (DWORD*)Function;
#else
					pThunk2->u1.Function = (DWORD)Function;
#endif

				}
				
				pThunk++;
				pThunk2++;
			}
		}
		IID++;
	}
	return PrevValue;
}

DWORD HookGeneralFunc(const char *Dll, const char*FuncName, void *Function, unsigned char *backup)
{
	//** Time to play with some x86 instructions

	DWORD Address = (DWORD)GetProcAddress(GetModuleHandle(Dll), FuncName);
	BYTE jmp[6] = {0xe9, 0x00, 0x00, 0x00, 0x00, 0xc3};

	ReadProcessMemory(GetCurrentProcess(), (void*)Address, backup, 6, 0);
	DWORD Calc = ((DWORD)Function - Address - 5);

	memcpy(&jmp[1], &Calc, 4); //** Build teh JMP

	WriteProcessMemory(GetCurrentProcess(), (void*)Address, jmp, 6, 0); //** Write the jump

	return Address;
}