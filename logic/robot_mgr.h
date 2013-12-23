//authored by lizs

#pragma once
#include <map>
#include "robot_data.h"

namespace Santos
{
	class Session;
	class Robot;
	class RobotMgr
	{
	public:
		static RobotMgr* instance();

		Robot * create();
		void kill(Robot * robot);
		void destroy();

		Robot * get(Session * session);
		void go();
		
	private:
		RobotMgr(){}
		~RobotMgr(){};

		bool load_account_table();
		void save_account_table();
	private:
		static RobotMgr * mInstance;
		std::map<Session*, Robot*> mRobots;
		std::map<int, RobotData *> mAccounts;
	};
}