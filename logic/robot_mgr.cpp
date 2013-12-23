//authored by lizs

#include "stdafx.h"
#include "robot_mgr.h"
#include "robot.h"
#include "network\session.h"
#include <fstream>
#include "robot_data.h"

namespace Santos
{
	RobotMgr * RobotMgr::mInstance = nullptr;

	RobotMgr* RobotMgr::instance(){
		if (!mInstance)
			mInstance = new RobotMgr();
		return mInstance;
	}

	void RobotMgr::destroy(){
		save_account_table();

		for(auto ite = mRobots.begin(); ite != mRobots.end(); ++ite)
			delete ite->second;
		mRobots.clear();
	}
	
	void RobotMgr::go(){
		if(!load_account_table()){			
		}

		for (int i = 0; i < 100; ++i){
			Robot * santos = create();
			santos->go();
		}
	}

	void RobotMgr::kill( Robot * robot ){
		if(!robot)
			return;

		auto ite = mRobots.find(robot->get_session());
		if (ite != mRobots.end()){
			delete ite->second;
			mRobots.erase(ite);
		}
	}
	
	Robot * RobotMgr::create(){
		Robot * robot = new Robot(Session::create());

		if (mAccounts.size() > 0)
		{
			auto ite = mAccounts.begin();
			robot->set_data(ite->second);
			mAccounts.erase(ite);
		}

		mRobots.insert(std::make_pair(robot->get_session(), robot));
		return robot;
	}

	Robot * RobotMgr::get( Session * session ){
		auto ite = mRobots.find(session);
		if(ite != mRobots.end()){
			return ite->second;
		}

		return nullptr;
	}

	bool RobotMgr::load_account_table()	{
		std::ifstream reader;
		reader.open("account_table.txt", std::ios_base::in | std::ios_base::binary);
		if (!reader.is_open()){
			reader.close();
			return false;
		}
		else{
			RobotData * _data = new RobotData();

			while (reader){
				reader.read((char*)_data, sizeof(RobotData));
				mAccounts.insert(std::make_pair(_data->user_id, _data));
				_data = new RobotData();
			}

			reader.close();
			return true;
		}
	}

	void RobotMgr::save_account_table()	{
		std::ofstream writer;
		writer.open("account_table.txt", std::ios_base::out | std::ios_base::binary);
		if(!writer.is_open()){
			throw std::exception("account table can't be opened!");
		}

		for(auto ite = mRobots.begin(); ite != mRobots.end(); ++ite){
			const RobotData & data = ite->second->get_data();
			writer.write((const char*)&data, sizeof(RobotData));
		}

		writer.close();
	}

}