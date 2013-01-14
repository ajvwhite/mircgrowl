#include "shared.h"
#include "mircgrowl.h"
#include "util_funcs.h"
 
extern "C" {
	void __stdcall LoadDll(void*) {
		// Do anything required on load here
		registermIRCGrowlNots();
	}

	int __stdcall UnloadDll(int timeout) {
		// Do anything required on unload here
		if(!timeout) {
			// Anything to do only when manually unloaded
		}

		return 0;
	}

	mircDllFunc(version) {
		mircret("mIRCgrowl - Growl Notifications for mIRC - v1.0 - Originally written by Alexander White ( https://github.com/ajvwhite/mircgrowl )");
	}

	mircDllFunc(notifyGeneral) {
		responseStruct funcRet;
		programOutput progOut;

		string dataStr = string(data);
		size_t str_found;

		str_found = dataStr.find("\t");
		
		if(str_found != string::npos) {
			char* argparse;
			char* argparse_nxt_tok;

			int argparsec = 1;

			char* title;
			char* mainText;
			string mainTextStr = string("");

			argparse = strtok_s(data, "\t", &argparse_nxt_tok);
			while(argparse != NULL) {
				string token = string(argparse);
				if(argparsec == 1) {
					title = new char[(token.length() + 1)];
					strcpy_s(title, (token.length() + 1), token.c_str());
				} else {
					mainTextStr += token;
				}
				argparse = strtok_s(NULL, "\t", &argparse_nxt_tok);
				argparsec++;
			}
			delete[] argparse, argparse_nxt_tok;

			mainText = new char[(mainTextStr.length() + 1)];
			strcpy_s(mainText, (mainTextStr.length() + 1), mainTextStr.c_str());

			funcRet = triggerGeneralNotify(title, mainText);
			progOut = createProgramOutput(funcRet);
		} else {
			funcRet = triggerGeneralNotify(NULL, data);
			progOut = createProgramOutput(funcRet);
		}

		if(progOut.success == true) {
			mircret("S_OK");
		} else {
			mircret(progOut.stringOut);
		}
	}

	mircDllFunc(notifyChatMention) {
		responseStruct funcRet;
		programOutput progOut;

		funcRet = triggerChatMentionNotify(NULL, data);
		progOut = createProgramOutput(funcRet);

		if(progOut.success == true) {
			mircret("S_OK");
		} else {
			mircret(progOut.stringOut);
		}
	}

	mircDllFunc(notifyPrivateMsg) {
		responseStruct funcRet;
		programOutput progOut;

		funcRet = triggerPrivMsgNotify(NULL, data);
		progOut = createProgramOutput(funcRet);

		if(progOut.success == true) {
			mircret("S_OK");
		} else {
			mircret(progOut.stringOut);
		}
	}

	mircDllFunc(notifyTransferStatus) {
		responseStruct funcRet;
		programOutput progOut;

		string dataStr = string(data);
		size_t str_found;

		str_found = dataStr.find("\t");
		
		if(str_found != string::npos) {
			char* argparse;
			char* argparse_nxt_tok;

			int argparsec = 1;

			char* title;
			char* mainText;
			string mainTextStr = string("");

			argparse = strtok_s(data, "\t", &argparse_nxt_tok);
			while(argparse != NULL) {
				string token = string(argparse);
				if(argparsec == 1) {
					title = new char[(token.length() + 1)];
					strcpy_s(title, (token.length() + 1), token.c_str());
				} else {
					mainTextStr += token;
				}
				argparse = strtok_s(NULL, "\t", &argparse_nxt_tok);
				argparsec++;
			}
			delete[] argparse, argparse_nxt_tok;

			mainText = new char[(mainTextStr.length() + 1)];
			strcpy_s(mainText, (mainTextStr.length() + 1), mainTextStr.c_str());

			funcRet = triggerTransferStatusNotify(title, mainText);
			progOut = createProgramOutput(funcRet);
		} else {
			funcRet = triggerTransferStatusNotify(NULL, data);
			progOut = createProgramOutput(funcRet);
		}

		if(progOut.success == true) {
			mircret("S_OK");
		} else {
			mircret(progOut.stringOut);
		}
	}
}

responseStruct registermIRCGrowlNots(char* applicationIcon) {
	vector<notificationProps>regTypes;
	notificationProps tmp;

	char* packetToSend;
	char* iconLoc;

	iconLoc = getAppIconPath();

	tmp.type = getGrowlTypeText(GR_NOT_GENERAL);
	tmp.enabled = true;
	tmp.icon = iconLoc;

	regTypes.push_back(tmp);

	tmp.type = getGrowlTypeText(GR_NOT_CHATMENT);
	tmp.enabled = true;
	tmp.icon = iconLoc;

	regTypes.push_back(tmp);

	tmp.type = getGrowlTypeText(GR_NOT_PRIVMSG);

	regTypes.push_back(tmp);

	tmp.type = getGrowlTypeText(GR_NOT_TRANSSTAT);

	regTypes.push_back(tmp);

	packetToSend = createGrowlPacket(GR_REGISTER, "mIRC", regTypes, applicationIcon);

	return dataSendAndRecieve(packetToSend);
}

responseStruct triggerGeneralNotify(char* notTitle, char* notText) {
	if(isCharStrEmpty(notText)) {
		notText = "mIRC Has Requested Your Attention";
	}

	return triggerGrowlNotify(GR_NOT_GENERAL, notTitle, notText);
}

responseStruct triggerChatMentionNotify(char* notTitle, char* notText) {
	if(isCharStrEmpty(notText)) {
		notText = "Your screen name was mentioned in a chat room";
	}

	return triggerGrowlNotify(GR_NOT_CHATMENT, notTitle, notText);
}

responseStruct triggerPrivMsgNotify(char* notTitle, char* notText) {
	if(isCharStrEmpty(notText)) {
		notText = "You have recieved a private message";
	}

	return triggerGrowlNotify(GR_NOT_PRIVMSG, notTitle, notText);
}

responseStruct triggerTransferStatusNotify(char* notTitle, char* notText) {
	if(isCharStrEmpty(notText)) {
		notText = "A file transfer's status has changed.";
	}

	return triggerGrowlNotify(GR_NOT_TRANSSTAT, notTitle, notText);
}

responseStruct triggerGrowlNotify(int notType, char* notTitle, char* notText) {
	responseStruct ret;
	vector<notificationProps>notify;
	notificationProps notifyProps;

	char* packetToSend;
	char* notifyTypeText;

	notifyTypeText = getGrowlTypeText(notType);

	if(!isCharStrEmpty(notifyTypeText)) {
		notifyProps.type = notifyTypeText;
		if(isCharStrEmpty(notTitle)) {
			notifyProps.title = notifyProps.type;
		} else {
			notifyProps.title = notTitle;
		}
		if(!isCharStrEmpty(notText)) {
			notifyProps.text = notText;
		} else {
			notifyProps.text = "An event has occured in mIRC.";
		}

		notify.push_back(notifyProps);

		packetToSend = createGrowlPacket(GR_NOTIFY, "mIRC", notify);

		return dataSendAndRecieve(packetToSend);
	} else {
		ret.success = false;
		ret.err_type = GRE_BAD_ARGS;
		ret.critical = true;
		ret.msg = "You have not passed a valid notification type";
		return ret;
	}
}

char* createGrowlPacket(int packetType, char* appName, vector<notificationProps>notifications, char* appIcon) {
	string message;

	switch(packetType) {
		case GR_REGISTER:
			message = string("GNTP/1.0 REGISTER NONE\r\n");
			break;
		case GR_NOTIFY:
			message = string("GNTP/1.0 NOTIFY NONE\r\n");
			break;
		default:
			return "";
			break;
	}

	message += "Application-Name: ";
	message += appName;
	message += "\r\n";

	if(packetType == GR_REGISTER) {
		if(isCharStrEmpty(appIcon)) {
			appIcon = getAppIconPath();
		}

		if(!isCharStrEmpty(appIcon)) {
			message += "Application-Icon: ";
			message += appIcon;
			message += "\r\n";
		}
	}

	int maxNots = 1;
	notificationProps currNot;

	if(packetType == GR_REGISTER) {
		maxNots = notifications.size();
		message += "Notifications-Count: ";
		char numbuf[3];
		_itoa_s(maxNots, numbuf, 10);
		message += numbuf;
		message += "\r\n\r\n";
	}

	int i;
	for(i = 0; i < maxNots; i++) {
		currNot = notifications[i];
		message += "Notification-Name: ";
		message += currNot.type;
		message += "\r\n";

		message += "Notification-Display-Name: ";
		message += currNot.type;
		message += "\r\n";

		if(packetType == GR_REGISTER) {
			message += "Notification-Enabled: ";
			if(currNot.enabled) {
				message += "True\r\n";
			} else {
				message += "False\r\n";
			}
		}

		if(!isCharStrEmpty(currNot.icon)) {
			message += "Notification-Icon: ";
			message += currNot.icon;
			message += "\r\n";
		}

		if(packetType == GR_NOTIFY) {
			message += "Notification-Title: ";
			message += currNot.title;
			message += "\r\n";

			message += "Notification-Text: ";
			message += currNot.text;
			message += "\r\n";
		}

		message += "\r\n";
	}

	char* packet = new char[message.length() + 1];
	strcpy_s(packet, (message.length() + 1), message.c_str());

	return packet;
}

responseStruct dataSendAndRecieve(char* message, char* server_ip) {
	// Initialise the variables required for this function

	// winsock2 variable declarations
	WSADATA wsaData;
	struct sockaddr_in server;
	SOCKET sock;

	// General winsock2 response
	int ret;

	// Create packetdata vars
	char packetdata[DEFAULT_BUFLEN];
	int packetdatalen = DEFAULT_BUFLEN;

	// Integer to hold packet size
	int packetsize;
	
	// header line
	char* headerlines = NULL;
	char* headerlines_nxt_tok = NULL;
	
	// Current header pos
	int headerlinec = 1;

	string str, head_part1, head_part2;
	size_t str_found;
	size_t str_found2;

	// Reported error status
	bool reported_error = false;
	
	// Return struct
	responseStruct funcRet;

	// To begin with we have no errors.
	//funcRet.err_code = 0;
	//funcRet.err_type = GRE_NO_ERROR;

	// Initialise the winsock2 socket
	ret = WSAStartup(MAKEWORD(2,0), &wsaData);
    if (ret != NO_ERROR) {
		funcRet.success = false;
		funcRet.err_code = ret;
		funcRet.err_type = GRE_SOCKET_ERR;
		funcRet.msg = "Socket startup failed";
		funcRet.critical = true;
		WSACleanup();
		delete[] headerlines, headerlines_nxt_tok, str_found, str_found2;
		return funcRet;
    }
 
	// Create winsock2 socket
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
		funcRet.success = false;
		funcRet.err_code = WSAGetLastError();
		funcRet.err_type = GRE_SOCKET_ERR;
		funcRet.msg = "Socket creation failed";
		funcRet.critical = true;
		closesocket(sock);
		WSACleanup();
		delete[] headerlines, headerlines_nxt_tok, str_found, str_found2;
		return funcRet;
    }
 
	// Configure the winsock2 socket
	server.sin_family = AF_INET;
	server.sin_port = htons(DEFAULT_PORT); // Port 23053
	server.sin_addr.S_un.S_addr = inet_addr(server_ip); // Localhost
 
	// Connect to server
	ret = connect(sock, (SOCKADDR*)&server, sizeof(server));
	if(ret == SOCKET_ERROR) {
		funcRet.success = false;
		funcRet.err_code = WSAGetLastError();
		funcRet.err_type = GRE_SOCKET_ERR;
		funcRet.msg = "Connection to the server failed";
		funcRet.critical = true;
		closesocket(sock);
		WSACleanup();
		delete[] headerlines, headerlines_nxt_tok, str_found, str_found2;
		return funcRet;
	}
 
	// Send required data to the server.
	memset(packetdata, 0, sizeof(packetdata));
	_snprintf_s(packetdata, sizeof(packetdata), message);
	ret = send(sock, packetdata, sizeof(packetdata), 0);
	if(ret == SOCKET_ERROR) {
		funcRet.success = false;
		funcRet.err_code = WSAGetLastError();
		funcRet.err_type = GRE_SOCKET_ERR;
		funcRet.msg = "The socket transmission failed";
		funcRet.critical = false;
		closesocket(sock);
		WSACleanup();
		delete[] headerlines, headerlines_nxt_tok, str_found, str_found2;
		return funcRet;
	}

    // Shutdown the send part of the connection since no more data will be sent
    ret = shutdown(sock, SD_SEND);
    if (ret == SOCKET_ERROR) {
		funcRet.success = false;
		funcRet.err_code = WSAGetLastError();
		funcRet.err_type = GRE_SOCKET_ERR;
		funcRet.msg = "Send socket shutdown failed";
		funcRet.critical = false;
		closesocket(sock);
		WSACleanup();
		delete[] headerlines, headerlines_nxt_tok, str_found, str_found2;
		return funcRet;
    }
 
	// Recieve response from server.
	memset(packetdata, 0, packetdatalen);
	packetsize = recv(sock, packetdata, packetdatalen, 0);
	if(packetsize == SOCKET_ERROR) {
		funcRet.success = false;
		funcRet.err_code = WSAGetLastError();
		funcRet.err_type = GRE_SOCKET_ERR;
		funcRet.msg = "Recieve failed";
		funcRet.critical = false;
		closesocket(sock);
		WSACleanup();
		delete[] headerlines, headerlines_nxt_tok, str_found, str_found2;
		return funcRet;
	}

	// Did we recieve any data back?
	if(packetsize > 0) {
		// OK we did, we know the Growl Header recieved is parsed
		// line by line by the \r\n terminators, so lets create
		// a token parser, based on that fact
		headerlines = strtok_s(packetdata, "\r\n", &headerlines_nxt_tok);
		while(headerlines != NULL) {
			// Ok lets create a string object from the data
			str = string(headerlines);

			// The first line should be the standard growl
			// Identifier so handle it.
			if(headerlinec == 1) {
				// OK this should be the response overview header
				// see if it holds the expected header line

				// Fine the GNTP string should be at the start
				str_found = str.find("GNTP");
				if(str_found != string::npos && str_found == 0) {
					// Ok the GNTP string was found, need to now
					// find either -OK or -ERROR
					str_found = str.find("-OK");
					str_found2 = str.find("-ERROR");
					if(str_found != string::npos || str_found2 != string::npos) {
						if(str_found != string::npos) {
							reported_error = false;
						} else {
							reported_error = true;
						}
					} else {
						funcRet.success = false;
						funcRet.err_type = GRE_SERVER_RESP_ERR;
						funcRet.msg = "Unexpected status response recieved from the server.";
						funcRet.critical = false;
						closesocket(sock);
						WSACleanup();
						delete[] headerlines, headerlines_nxt_tok, str_found, str_found2;
						return funcRet;
					}
				} else {
					funcRet.success = false;
					funcRet.err_type = GRE_SERVER_RESP_ERR;
					funcRet.msg = "Response recieved from the server was not a Growl Server Response.";
					funcRet.critical = false;
					closesocket(sock);
					WSACleanup();
					delete[] headerlines, headerlines_nxt_tok, str_found, str_found2;
					return funcRet;
				}
			} else {
				// OK past the first line so deal with the rest of
				// the data... currently we are only looking
				// for error information! So only do it on
				// reported error!
				if(reported_error) {
					// The lines are in format:
					//		Error-Description: Some error
					//
					// We use this format to extract information.
					str_found = str.find(":");
					if(str_found != string::npos) {
						head_part1 = str.substr(0, str_found);
						head_part2 = str.substr((str_found + 2));
						if(head_part1.compare("Error-Description") == 0) {
							char* msgStr = new char[(head_part2.length() + 1)];
							strcpy_s(msgStr, (head_part2.length() + 1), head_part2.c_str());
							funcRet.msg = msgStr;
							funcRet.err_type = GRE_GROWL_ERR;
							//delete[] writable;
						} else if(head_part1.compare("Error-Code") == 0) {
							funcRet.err_code = atoi(head_part2.c_str());
						}
					}
				}
			}
			headerlines = strtok_s(NULL, "\r\n", &headerlines_nxt_tok);
			headerlinec++;
		}
        delete[] headerlines, headerlines_nxt_tok, str_found, str_found2;
	} else {
		if(packetsize == 0) {
			funcRet.success = false;
			funcRet.err_type = GRE_SERVER_RESP_ERR;
			funcRet.msg = "Empty response recieved from the server.";
			funcRet.critical = false;
			closesocket(sock);
			WSACleanup();
			delete[] headerlines, headerlines_nxt_tok, str_found, str_found2;
			return funcRet;
		} else {
			funcRet.success = false;
			funcRet.err_type = GRE_SERVER_RESP_ERR;
			funcRet.msg = "No response from the Growl server, maybe it's not running?";
			funcRet.critical = true;
			closesocket(sock);
			WSACleanup();
			delete[] headerlines, headerlines_nxt_tok, str_found, str_found2;
			return funcRet;
		}
	}
	
	// Clean up the socket, all finished
	closesocket(sock);
	WSACleanup();

	if(reported_error) {
		funcRet.success = false;
		if(funcRet.msg == NULL) {
			funcRet.msg = "General Error : There was a reported error with your request.";
		}
		funcRet.critical = false;
	} else {
		funcRet.success = true;
		funcRet.msg = "Packet sent successfully.";
		funcRet.critical = false;
	}

	delete[] headerlines, headerlines_nxt_tok, str_found, str_found2;
	return funcRet;
}