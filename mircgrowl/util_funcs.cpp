#include "shared.h"
#include "util_funcs.h"

char* getAppIconPath(TCHAR* iconPath) {
	char* iconLoc;

	// Find the mIRC profile path, where the logo is intended to be
	TCHAR szPath[MAX_PATH];

	// Fetch the OS Roaming %APPDATA% path
	if ( SUCCEEDED( SHGetFolderPath( NULL, CSIDL_APPDATA, NULL, 0, szPath ) ) ) {
		// To this path append the expected location of the logo
		PathAppend(szPath, iconPath);

		// Does the file exist?
		if(FileExists(szPath)) {
			// Path could be UTF8, convert
			iconLoc = unicodetoansi(szPath);
		} else {
			iconLoc = "";
		}
	} else {
		iconLoc = "";
	}

	return iconLoc;
}

programOutput createProgramOutput(responseStruct funcRet) {
	programOutput ret;

	string outMsg = string("");

	if(funcRet.success == true) {
		ret.success = true;
		
		outMsg += "SUCCESS: ";
		outMsg += funcRet.msg;
	} else {
		ret.success = false;
		if(funcRet.err_code >= 0) {
			outMsg = getCustomErrorTypeText(funcRet.err_type);
			outMsg += " (";
			char numbuf[6];
			_itoa_s(funcRet.err_code, numbuf, 10);
			outMsg += numbuf;
			outMsg += "): ";
			outMsg += funcRet.msg;
			if(funcRet.err_type == GRE_SOCKET_ERR) {
				outMsg += " : ";
				outMsg += getSocketErrorDesc(funcRet.err_code);
			}
		} else {
			outMsg = getCustomErrorTypeText(funcRet.err_type);
			outMsg += ": ";
			outMsg += funcRet.msg;
		}
	}

	char* msgStr = new char[(outMsg.length() + 1)];
	strcpy_s(msgStr, (outMsg.length() + 1), outMsg.c_str());
	ret.stringOut = msgStr;

	return ret;
}

bool isCharStrEmpty(char* stringToTest) {
	if(stringToTest == NULL || stringToTest[0] == '\0') {
		return true;
	} else {
		return false;
	}
}

char* getGrowlTypeText(int notifyType) {
	switch(notifyType) {
		case GR_NOT_GENERAL: return "General Notification"; break;
		case GR_NOT_CHATMENT: return "Chatroom Mention"; break;
		case GR_NOT_PRIVMSG: return "Private Message"; break;
		case GR_NOT_TRANSSTAT: return "File Transfer Status Change"; break;
		default: return ""; break;
	}
}

char* getCustomErrorTypeText(int errorType) {
	switch(errorType) {
		case GRE_NO_ERROR: return "No Error"; break;
		case GRE_SOCKET_ERR: return "Socket Error"; break;
		case GRE_SERVER_RESP_ERR: return "Server Response Error"; break;
		case GRE_GROWL_ERR: return "Growl Error"; break;
		case GRE_BAD_ARGS: return "Invalid Function Argument(s)"; break;
		case GRE_GENERAL_ERR: return "General Error"; break;
		default: return "Unknown Error"; break;
	}
}

char* getSocketErrorDesc(int errorCode) {
	switch(errorCode) {
		case WSAEACCES: return "An attempt was made to access a socket in a way forbidden by its access permissions."; break;
		case WSAEADDRINUSE: return "Address already in use."; break;
		case WSAEADDRNOTAVAIL: return "Cannot assign requested address."; break;
		case WSAEAFNOSUPPORT: return "Address family not supported by protocol family."; break;
		case WSAEALREADY: return "Operation already in progress."; break;
		case WSAECONNABORTED: return "Software caused connection abort."; break;
		case WSAECONNREFUSED: return "Connection was actively refused."; break;
		case WSAECONNRESET: return "Connection reset by peer."; break;
		case WSAEDESTADDRREQ: return "Destination address required."; break;
		case WSAEFAULT: return "Bad address."; break;
		case WSAEHOSTDOWN: return "Host is down."; break;
		case WSAEHOSTUNREACH: return "No route to host."; break;
		case WSAEINPROGRESS: return "Operation now in progress."; break;
		case WSAEINTR: return "Interrupted function call."; break;
		case WSAEINVAL: return "Invalid argument."; break;
		case WSAEISCONN: return "Socket is already connected."; break;
		case WSAEMFILE: return "Too many open files."; break;
		case WSAEMSGSIZE: return "Message too long."; break;
		case WSAENETDOWN: return "Network is down."; break;
		case WSAENETRESET: return "Network dropped connection on reset."; break;
		case WSAENETUNREACH: return "Network is unreachable."; break;
		case WSAENOBUFS: return "No buffer space available."; break;
		case WSAENOPROTOOPT: return "Bad protocol option."; break;
		case WSAENOTCONN: return "Socket is not connected."; break;
		case WSAENOTSOCK: return "Socket operation on nonsocket."; break;
		case WSAEOPNOTSUPP: return "Operation not supported."; break;
		case WSAEPFNOSUPPORT: return "Protocol family not supported."; break;
		case WSAEPROCLIM: return "Too many processes."; break;
		case WSAEPROTONOSUPPORT: return "Protocol not supported."; break;
		case WSAEPROTOTYPE: return "Protocol wrong type for socket."; break;
		case WSAESHUTDOWN: return "Cannot send after socket shutdown."; break;
		case WSAESOCKTNOSUPPORT: return "Socket type not supported."; break;
		case WSAETIMEDOUT: return "Connection timed out."; break;
		case WSATYPE_NOT_FOUND: return "Class type not found."; break;
		case WSAEWOULDBLOCK: return "Resource temporarily unavailable."; break;
		case WSAHOST_NOT_FOUND: return "Host not found."; break;
		case WSA_INVALID_HANDLE: return "Specified event object handle is invalid."; break;
		case WSA_INVALID_PARAMETER: return "One or more parameters are invalid."; break;
		case WSA_IO_INCOMPLETE: return "Overlapped I/O event object not in signaled state."; break;
		case WSA_IO_PENDING: return "Overlapped operations will complete later."; break;
		case WSA_NOT_ENOUGH_MEMORY: return "Insufficient memory available."; break;
		case WSANOTINITIALISED: return "Successful WSAStartup not yet performed."; break;
		case WSANO_DATA: return "Valid name, no data record of requested type."; break;
		case WSANO_RECOVERY: return "This is a nonrecoverable error."; break;
		case WSASYSCALLFAILURE: return "System call failure."; break;
		case WSASYSNOTREADY: return "Network subsystem is unavailable."; break;
		case WSATRY_AGAIN: return "Nonauthoritative host not found."; break;
		case WSAVERNOTSUPPORTED: return "Winsock.dll version out of range."; break;
		case WSAEDISCON: return "Graceful shutdown in progress."; break;
		case WSA_OPERATION_ABORTED: return "Overlapped operation aborted."; break;
		default: return "Undefined WinSock Error"; break;
	}
}

std::string strtoupper(std::string str) {
	int leng=str.length();
	for(int i=0; i<leng; i++)
		if (97<=str[i]&&str[i]<=122)//a-z
			str[i]-=32;
	return str;
}
std::string strtolower(std::string str) {
	int leng=str.length();
	for(int i=0; i<leng; i++)
		if (65<=str[i]&&str[i]<=90)//A-Z
			str[i]+=32;
    return str;
}

/**
 * Returns true if the file or directory exists and false if neither exists.
 *
 * @param filepath file path, can be relative or absolute
 * @return true if the file or directory exists
 */
bool FileExists(const TCHAR* filepath) {
    struct _stat buf;
	int res;

	res = _tstat(filepath, &buf);
    return (res == 0);
}

char* unicodetoansi(TCHAR* unicodestr) {
	char* ansistr;
	size_t lenW = 0;
	size_t count;
	if( SUCCEEDED( StringCchLength(unicodestr, STRSAFE_MAX_CCH, &count) ) ) {
		lenW = count;
	}
	int lenA = WideCharToMultiByte(CP_ACP, 0, unicodestr, lenW, 0, 0, NULL, NULL);
	if (lenA > 0) {
		ansistr = new char[lenA + 1]; // allocate a final null terminator as well
		WideCharToMultiByte(CP_ACP, 0, unicodestr, lenW, ansistr, lenA, NULL, NULL);
		ansistr[lenA] = 0; // Set the null terminator yourself
	} else {
		// handle the error
		return "";
	}

	return ansistr;
}

TCHAR* ansitounicode(char* ansistr) {
    int lenA = lstrlenA(ansistr);
	int lenW;
	TCHAR* unicodestr;

	lenW = MultiByteToWideChar(CP_ACP, 0, ansistr, lenA, 0, 0);
	if (lenW > 0) {
		// Check whether conversion was successful
		MultiByteToWideChar(CP_ACP, 0, ansistr, lenA, unicodestr, lenW);
	} else {
		// handle the error
		return _T("");
	}

	return unicodestr;
}