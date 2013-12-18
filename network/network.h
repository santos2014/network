//authored by lizs

#pragma once
#include "event2\event.h"

namespace Santos
{
	class Network
	{
	public:
		static Network * instance();

		void startup();
		void shutdown();

		void dispatch();

	private:
		friend class Session;
		Network() : mEB(nullptr){}
		~Network(){}

	private:
		static Network * mInstance;
		event_base * mEB;
	};
}