#include <sys/types.h>
#include <sys/stat.h>
#include <tchar.h>

enum growl_packet_types {
	GR_REGISTER = 1,
	GR_NOTIFY = 2
};

enum growl_notification_types {
	GR_NOT_GENERAL = 1,
	GR_NOT_CHATMENT = 2,
	GR_NOT_PRIVMSG = 3,
	GR_NOT_TRANSSTAT = 4
};

enum cust_err_types {
	GRE_NO_ERROR = 0,
	GRE_SOCKET_ERR = 1,
	GRE_SERVER_RESP_ERR = 2,
	GRE_GROWL_ERR = 3,
	GRE_BAD_ARGS = 4,
	GRE_GENERAL_ERR = 5
};

typedef struct ProgramOutput {
	bool success;
	char* stringOut;

	ProgramOutput()
		: success(true), stringOut("")
	{}
} programOutput;

typedef struct ResponseStruct {
	bool success;
	char* msg;
	int err_code;
	int err_type;
	bool critical;

	ResponseStruct()   // Example of a constructor used in a structure.
		: success(true), msg(""), err_code(0), err_type(GRE_SOCKET_ERR), critical(false)
	{}
} responseStruct;

typedef struct NotificationProps {
	char *type;
	char *title;
	bool enabled;
	char *icon;
	char *text;

	NotificationProps()
		: type(""), title(""), enabled(true), icon(""), text("")
	{}
} notificationProps;