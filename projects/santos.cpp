// santos.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "logic\robot_mgr.h"
#include "network\network.h"


int main()
{
	Santos::Network::instance()->startup();

	Santos::RobotMgr::instance()->go();
	Santos::Network::instance()->dispatch();

	Santos::RobotMgr::instance()->destroy();
	Santos::Network::instance()->shutdown();

	return 0;
}

