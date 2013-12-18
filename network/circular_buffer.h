//authored by lizs
#pragma once

namespace Santos
{
#define BUFFER_LEN 1024
	class CircularBuffer
	{
	public:
		CircularBuffer() : mHead(0), mTail(0){
			memset(mBuffer, 0, BUFFER_LEN);
		}

		bool write(const char * buf, int len){
			if (writable_len() < len){
				move();
				if (writable_len() < len)
					return false;
			}

			memmove(tail(), buf, len);
			mTail += len;
			return true;
		}

		// this is oh... shit!!!
		bool move_tail(int offset){
			if(offset > writable_len()){
				return false;
			}

			mTail += offset;
			return true;
		}

		int read(char * const out_buf){
			int len = readable_len();
			if (len <= 0)
				return 0;

			memmove(out_buf, head(), len);
			mHead += len;
			return len;
		}

		bool read(char * const out_but, short len){
			if(readable_len() < len){
				return false;
			}

			memmove(out_but, head(), len);
			mHead += len;
			return true;
		}

		int writable_len(){
			return BUFFER_LEN-mTail;
		}

		int readable_len(){
			return mTail-mHead;
		}

		char * head(){ return mBuffer+mHead; }
		char * tail(){ return mBuffer+mTail; }

	private:
		void move(){
			memmove(mBuffer, head(), readable_len());
			mHead = 0;
			mTail = readable_len();
		}

	private:
		char mBuffer[BUFFER_LEN];
		int mHead;
		int mTail;
	};
}