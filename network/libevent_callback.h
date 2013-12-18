// authored by lizs

#pragma once

#include "Session.h"
#include "delegates\delegate.h"
#include "dispatcher.h"

namespace Santos
{
	class CBLibevent
	{
	public:
		static void cb_events(bufferevent * be, short events, void * ctx){
			if(!be){
				return;
			}

			Session * session = (Session*)ctx;
			session->attach_buffer_event(be);

			if (events & BEV_EVENT_ERROR){
				printf("BEV_EVENT_ERROR for : %d \n", session->get_fd());
				session->close();
				return;
			}

			if (events & (BEV_EVENT_EOF)) {
				printf("BEV_EVENT_EOF for : %d \n", session->get_fd());
				session->close();
				return;
			}

			if (events & (BEV_EVENT_TIMEOUT)) {
				printf("BEV_EVENT_TIMEOUT for : %d \n", session->get_fd());
				session->close();
				return;
			}

			if (events & (BEV_EVENT_CONNECTED)) {
				printf("BEV_EVENT_CONNECTED for : %d \n", session->get_fd());

				NetDelegateContext ctx;
				ctx.ops = NetDelegateContext::eConn;
				Dispatcher::instance()->dispatch(session, ctx);
			}
		}

		static void cb_read(bufferevent * be, void * ctx){
			Session * session = (Session*)ctx;

			CircularBuffer & cb = session->get_buf();

			int readed = bufferevent_read(be, cb.tail(), cb.writable_len());
			if (readed && cb.move_tail(readed)){				
				session->extract();
			}
		}

		static void cb_write(bufferevent * be, void * ctx){
			// do nothing
		}
	};
}