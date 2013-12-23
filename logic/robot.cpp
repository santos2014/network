#include "stdafx.h"
#include "robot.h"
#include "robot_mgr.h"
#include "network\protocol\packet.h"
#include <fstream>
#include "stringops.h"

namespace Santos
{
	void Robot::kill(){
		RobotMgr::instance()->kill(this);
	}

	void Robot::send( const Packet & packet ) {
		mSession->send(packet);
	}

	void Robot::network_callback(const NetDelegateContext & ctx ){
		switch (ctx.ops)
		{
		case NetDelegateContext::eConn:
			{
				if(mData.user_id == 0){
					// require registration
					reg();
				}
				else{
					// create role
					login();
				}
			}
			break;

		case NetDelegateContext::eDisConn:
			{
				//RobotMgr::instance()->kill(this);
			}
			break;

		case NetDelegateContext::eRead:
			{
				handle_msg(ctx.so);
			}
			break;

		default:
			break;
		}
	}

	void Robot::handle_msg( SmallObject * so ){
		//printf("Robot, recieve a msg :) \n");
		ResponseBase * response = (ResponseBase *)(so->ptr_data());
		switch (response->code)
		{
		case eRegister:
			handle_register(response);
			break;
		case eLogin:
			handle_login(response);
			break;
		case ErrorReport:

			handle_error(response);
			break;
		default:
			break;
		}
	}

	void Robot::go(){
		if (mData.user_id != 0){
			mSession->open("127.0.0.1", 9527);
		}
		else{
			mSession->open("127.0.0.1", 5401);
		}
	}

	void Robot::handle_register( ResponseBase * response ){
		RegisterResponse * full = (RegisterResponse*)response;
		mData.user_id = full->UserID;
		
		char * raw = (char *)full;
		raw += ResponseBase::HEADER_LEN;
		raw += sizeof(mData.user_id);
		char len = *raw;
		raw += sizeof(len);
		memcpy(mData.account.UserName, raw, len);
		raw += len;
		len = *raw;
		raw += sizeof(len);
		memcpy(mData.account.Password, raw, len);

		mRegistered = true;
		
		// switch to scene server
		mSession->close();
		mSession->open("127.0.0.1", 9527);
	}

	void Robot::login()	{
		Login rq;
		memcpy(rq.userName, mData.account.UserName, USER_NAME_LENGTH*2);
		memcpy(rq.password, mData.account.Password, PASSWORD_LENGTH*2);

		send(rq);
	}

	void Robot::reg(){
		Register data;
		send(data);
	}

	void Robot::handle_login( ResponseBase * response ){
		switch (response->subCode)
		{
		case SyncCreateRole:
			handle_create_role();
			break;
		case RequireToCreateRole:
			create_role();
			break;
		case LogIn:
			// fuck
			break;
		default:
			break;
		}
	}

	void Robot::create_role(){
		CreateRole rq;
		rq.userId = mData.user_id;		
		wsprintf((wchar_t*)rq.actorName, L"%x", rq.userId);

		send(rq);
	}

	void Robot::handle_create_role(){
		login();
	}

	void Robot::handle_error( ResponseBase * response )	{
		ErrorSync * error = (ErrorSync*)response;

		switch (error->Type)
		{
		case 0:
		case 1:
			printf("Error received, code : {%d}", error->MessageID);
			break;
		case 2:
			{
				//std::wstring msg = StringOps::_Utf8String2WString(error->Msg.Msg, error->Msg.Len);
				//wprintf(L"Error received, utf-8 format msg : {%s} \n", msg.c_str());
			}
			break;
		default:
			break;
		}
	}
}
