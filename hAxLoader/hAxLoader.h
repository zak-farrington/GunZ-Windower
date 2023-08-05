//** hAxLoader.h: Header file
//**

//** START: Declerations and Variables

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
BOOL CALLBACK DialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

BOOL ReadConfigFile(HWND hWnd);
BOOL WriteConfigFile(HWND hWnd);

void OnTimer(HWND hWnd, UINT nID);

BOOL EnumerateProcesses(HWND hWnd);

int iProcs = 0;					//** For something ghetto...
int x, y, z;					//** Random int's we can use

char strMessage[512] = "";		//** Used various places when we need to format a message then use it
char strBuffer0[128] = "";		//** Random buffer we can use here and there
char strBuffer1[128] = "";		//** Random buffer we can use here and there
char strBuffer2[128] = "";		//** Random buffer we can use here and there

char strHookDir[128] = "";

char strGunzPath[128] = "";		//** Will hold the path to the previously used hook DLL
char strConfigPath[128] = "";	//** Will hold the path to our configuration file

//** END:	Declerations and Variables


//** START: Timers
/* #define	ENUMERATE_PROC_TIMER	10000 */
#define EDIT_MODIFY_TIMER		10001
//** END:	Timers
