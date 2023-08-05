#include <cstdio>
#include <ctime>

//** START: Global Functions
char *GetDateTime();
BOOL WriteLog(char* strFileName, char* strLineToWrite);
//** END:	Global Functions


//** START:	Global Variables
char strModuleName[128];		//** Will hold module name
char strLogFile[128];			//** Will hold full path to log file
char strBuffer[512];			//** We can use this in various places
char strDateTime[512];			//** Another fsking buffer... we use this in GetDateTime()
//** END:	Global Variables