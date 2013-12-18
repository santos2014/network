// authored by lizs
#pragma once
#include "code.h"

namespace Santos{

#define ACTOR_NAME_LENGTH 12
#define USER_NAME_LENGTH 32
#define PASSWORD_LENGTH 40
#define IP_LENGTH (16)
#define MAC_LENGTH (20)

#pragma pack(push)
#pragma pack(1)
	struct Packet	{
		short len;

		enum HeaderLen{
			HEADER_LEN = 2
		};
	};

	struct Account{
		Account(){
			memset(this, 0, sizeof(Account));
		}

		short UserName[USER_NAME_LENGTH];
		short Password[PASSWORD_LENGTH];
	};

	struct ResponseBase{
		char code;
		char subCode;

		enum HeaderLen{
			HEADER_LEN = 2
		};
	};

	struct RequestBase : Packet{
		char code;
		char subCode;
	};

	struct ErrorMsg{
		char Len;
#pragma warning(push)
#pragma warning(disable: 4200)
		char Msg[0];
#pragma warning(pop)
	};

	struct ErrorSync : public ResponseBase	{
		byte Type;

		union{
			short MessageID;
			ErrorMsg Msg;
		};

		ErrorSync(){
			memset(this, 0, sizeof(*this));
		}
	};

	struct Register : RequestBase{
		Register(){
			memset(this, 0, sizeof(*this));
			code = eRegister;
			subCode = 0;

			len = sizeof(*this);
		}

		short ip[IP_LENGTH];
		short mac[MAC_LENGTH];
		char QuickRegister;
	};

	struct RegisterResponse : ResponseBase{
		RegisterResponse(){
			memset(this, 0, sizeof(*this));
		}

		int UserID;
	};

	struct CreateRole : public RequestBase{
		CreateRole(){
			memset(this, 0, sizeof(*this));
			code = eLogin;
			subCode = RequireToCreateRole;

			len = sizeof(*this);
		}

		int userId;
		short actorName[ACTOR_NAME_LENGTH];
	};

	struct CreateRoleResponse : public ResponseBase{
		CreateRoleResponse(){
			memset(this, 0, sizeof(*this));

			code = eLogin;
			subCode = RequireToCreateRole;
		}

		int userId;
		short actorName[ACTOR_NAME_LENGTH];
	};

	struct Login : public RequestBase{
		Login(){
			memset(this, 0, sizeof(*this));

			code = eLogin;
			subCode = LogIn;

			len = sizeof(*this);
		}

		int id;
		short userName[USER_NAME_LENGTH];
		short password[PASSWORD_LENGTH];
		short ip[IP_LENGTH];
		short mac[MAC_LENGTH];
		char reconn;
	};

#pragma pack(pop)

}