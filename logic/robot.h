// authored by lizs

#pragma once
#include "delegates\delegate.h"
#include "network\Session.h"
#include "robot_data.h"

namespace Santos
{
	class Robot : public NetDelegate
	{
	public:
		void go();

		void kill();
		void send( const Packet & packet );

		// implement delegate
		virtual void network_callback(const NetDelegateContext & ctx);


	private:
		friend class RobotMgr;
		Robot(Session * session) : mSession(session), mRegistered(false){}
		~Robot(){
			if(mSession){
				delete mSession;
				mSession = nullptr;
			}
		};

		Session * get_session(){
			return mSession;
		}

		void set_data(RobotData * data){
			memcpy((char*)&mData, data, sizeof(RobotData));
		}

		const RobotData & get_data(){
			return mData;
		}

		void handle_msg(SmallObject * so);

		void login();
		void handle_login(ResponseBase * response );

		void reg();
		void handle_register(ResponseBase * response );

		void create_role();
		void handle_create_role();

		void handle_error(ResponseBase * response);

	private:
		Session * mSession;
		bool mRegistered;
		RobotData mData;
	};
}