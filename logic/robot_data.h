#pragma once

#include <string>
#include "network\protocol\packet.h"

namespace Santos{

	struct RobotData{
		RobotData(){
			memset(this, 0, sizeof(RobotData));
		}

		int user_id;
		Account account;
	};

}