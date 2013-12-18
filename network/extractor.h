// authored by lizs

#pragma once
#include "allocator\allocator.h"
#include "protocol\packet.h"
#include "circular_buffer.h"
#include "Dispatcher.h"

namespace Santos{

	class Extractor{
	public:
		Extractor(Session * owner) : mAllocator(16, 1024) ,
			mSo(nullptr), mOwner(owner){
		}

		bool extract(CircularBuffer & cb){
			if(!mSo){
				return extract_header(cb);
			}
			else{
				return extract_body(cb);
			}
		}

	private:
		bool extract_header(CircularBuffer & cb){
			if(!cb.read((char*)&mLen, Packet::HEADER_LEN)){
				return false;
			}

			mLen -= Packet::HEADER_LEN;

			mSo = mAllocator.alloc(mLen);
			if(!mSo){
				return false;
			}

			return true;
		}

		bool extract_body(CircularBuffer & cb){
			if (!cb.read(mSo->ptr_data(), mLen)){
				return false;
			}

			NetDelegateContext ctx;
			ctx.ops = NetDelegateContext::eRead;
			ctx.so = mSo;
			Dispatcher::instance()->dispatch(mOwner, ctx);

			mAllocator.free(mSo);

			mSo = nullptr;
			mLen = 0;
			return true;
		}

	private:
		Session * mOwner;
		SmallObject * mSo;
		Allocator mAllocator;
		short mLen;
	};
}