//authored by lizs

#include "stdafx.h"
#include "network.h"
namespace Santos{
	Network * Network::mInstance = nullptr;

	Network * Network::instance(){
		if(!mInstance){
			mInstance = new Network();
		}
		return mInstance;
	}

	void Network::startup(){
#ifdef WIN32
			WSADATA wsaData;
			DWORD Ret;
			if ((Ret = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0) {
				printf("WSAStartup failed with error %d\n", Ret);
				
				throw std::exception("WSAStartup failed!!!");
			}
#endif

			mEB = event_base_new();
			if(!mEB){
				throw std::exception("event_base_new failed!!!");
			}
		}

	void Network::dispatch(){
		if(!mEB){
			throw std::exception("Network isn't ready!!!");
		}

		event_base_dispatch(mEB);
	}

	void Network::shutdown(){
		WSACleanup();
		delete this;
	}
}