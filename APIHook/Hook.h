//** Hook.h: Header file
//**
PVOID HookImportFunc(const char *Dll, const char *FuncName, int Ordinal, void *Function);
DWORD HookGeneralFunc(const char *Dll, const char *FuncName, void *Function, unsigned char *backup);
