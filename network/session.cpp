//authored by lizs

#include "stdafx.h"
#include "session.h"
#include "libevent_callback.h"
#include "protocol\packet.h"
#include "network.h"

namespace Santos
{
	void Session::open( const char * ip, short port ){
		if(!mClosed){
			throw std::exception("Session already opened!!!");
		}

		mBe = bufferevent_socket_new(Network::instance()->mEB, -1, BEV_OPT_CLOSE_ON_FREE);
		if(!mBe){
			printf("Open socket failed!");
			return;
		}

		bufferevent_setcb(mBe, CBLibevent::cb_read, CBLibevent::cb_write, CBLibevent::cb_events, this);
		bufferevent_enable( mBe, EV_READ | EV_WRITE );

		mClosed = false;
		if (bufferevent_socket_connect_hostname(mBe, NULL, AF_INET, ip, port) < 0){
			close();
		}
	}

	void Session::close()
	{
		if(mClosed){
			return;
		}

		if (mBe)
			bufferevent_free(mBe);

		mBe = nullptr;
		mClosed = true;

		NetDelegateContext ctx;
		ctx.ops = NetDelegateContext::eDisConn;
		Dispatcher::instance()->dispatch(this, ctx);
	}

	void Session::send( const char * buf, int len )	{
		if(mClosed){
			return;
		}

		if (0 != bufferevent_write(mBe, buf, len)){
			printf("bufferevent_write error!!!");
		}
	}

	void Session::send(const Packet & packet){
		send((char*)&packet, packet.len);
	}

	void Session::extract(){
		while (mExtractor.extract(mBuffer))
			;
	}
}

