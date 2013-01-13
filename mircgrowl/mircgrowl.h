#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <winsock2.h>
#include <string>
#include <vector>

#define DEFAULT_BUFLEN 2048
#define DEFAULT_PORT 23053

using namespace std;

#define mircDllFunc(name) int __stdcall name(HWND mWnd, HWND aWnd, char *data, char *parms, BOOL show, BOOL nopause)
#define mircret(ret) { string x = string(ret); strcpy_s(data,(x.length() + 1),x.c_str()); return 3; }

responseStruct registermIRCGrowlNots(char* applicationIcon = "");
responseStruct triggerGeneralNotify(char* notTitle = "", char* notText = "");
responseStruct triggerChatMentionNotify(char* notTitle = "", char* notText = "");
responseStruct triggerPrivMsgNotify(char* notTitle = "", char* notText = "");
responseStruct triggerTransferStatusNotify(char* notTitle = "", char* notText = "");
responseStruct triggerGrowlNotify(int notType, char* notTitle, char* notText);
responseStruct dataSendAndRecieve(char* message, char* server_ip = "127.0.0.1");
char* createGrowlPacket(int packetType, char* appName, vector<notificationProps>notifications, char* appIcon = "");