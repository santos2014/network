//authored by lizs

#include "stdafx.h"
#include "Dispatcher.h"
#include "session.h"
#include "logic\robot.h"
#include "delegates\delegate.h"
#include "logic\robot_mgr.h"
namespace Santos
{
	Dispatcher * Dispatcher::mInstance = nullptr;

	Dispatcher* Dispatcher::instance()	{
		if (!mInstance){
			mInstance = new Dispatcher();
		}
		return mInstance;
	}

	void Dispatcher::dispatch(Session * owner, const NetDelegateContext & ctx) {
		if(!owner){
			return ;
		}

		Robot * robot = RobotMgr::instance()->get(owner);
		if(robot){
			robot->network_callback(ctx);
		}
	}
}