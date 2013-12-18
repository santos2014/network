//authored by lizs

#pragma once
#include "circular_buffer.h"
#include "event2\bufferevent.h"
#include "extractor.h"

namespace Santos
{
	class Session
	{
	public:
		static Session * create(){
			return new Session();
		}

		void open(const char * ip, short port);
		void close();
		void send(const Packet & packet);


		~Session(){
			if(!mClosed){
				close();
			}
		}

	private:
		friend class CBLibevent;
		Session() : mBe(nullptr), mExtractor(this), mClosed(true){}

		evutil_socket_t get_fd(){
			return bufferevent_getfd(mBe);
		}

		void attach_buffer_event(bufferevent * be){
			mBe = be;
		}

		CircularBuffer & get_buf(){
			return mBuffer;
		}

		void extract();
		void send(const char * buf, int len);

	private:
		bool mClosed;
		bufferevent * mBe;
		CircularBuffer mBuffer;
		Extractor mExtractor;
	};
}