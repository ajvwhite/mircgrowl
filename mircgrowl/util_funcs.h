#include <stdio.h>
#include <winsock2.h>
#include <string>
#include <strsafe.h>
#include <commdlg.h>
#include <shlobj.h>
#include <shlwapi.h>

using namespace std;

char* getAppIconPath(TCHAR* iconPath = _T("\\mIRC\\mirc-logo.png"));
programOutput createProgramOutput(responseStruct funcRet);
bool isCharStrEmpty(char* stringToTest);
char* getGrowlTypeText(int notifyType);
char* getCustomErrorTypeText(int errorType);
char* getSocketErrorDesc(int errorCode);
std::string strtolower(std::string str);
std::string strtoupper(std::string str);
bool FileExists(const TCHAR* filepath);
char* unicodetoansi(TCHAR* unicodestr);
TCHAR* ansitounicode(char* cansistr);