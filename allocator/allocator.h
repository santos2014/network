// authored by lizs
#pragma once

#include <map>
#include <vector>
#include "alignment.h"

namespace Santos{

	class SmallObject{
	public:
		static SmallObject* create(short alignedLen){			
			return new SmallObject(alignedLen, new char[alignedLen]);
		}

		bool write(const char * data, short len){
			if(len > mAlignedLen){
				return false;
			}

			memcpy(mData, data, len);
			mLen = len;
			return true;
		}

		char * ptr_data(){
			return mData;
		}

	private:
		friend class Allocator;

		SmallObject(short alignedLen, char * data) :
			mAlignedLen(alignedLen),
			mData(data),
			mLen(0){
		}

		~SmallObject(){
			delete [] mData;
			mData = nullptr;
			mLen = 0;
			mAlignedLen = 0;
		}

		short get_aligned_len(){
			return mAlignedLen;
		}

	private:
		short mAlignedLen;
		short mLen;
		char * mData;
	};
	
	class Allocator{
	public:
		Allocator(short l = 1, short h = 1024){
			mL = ALIGN_L(l);
			mH = ALIGN_H(h);

			short _ = mL;
			while (_ <= mH){
				mCache.insert(std::make_pair(_, new std::vector<SmallObject*>()));
				_ = STEP_NEXT(_);
			}
		}

		~Allocator(){}

		SmallObject * alloc(const char * data, short len){
			short alignedLen = ALIGN_H(len);
			SmallObject * so = _alloc(alignedLen);
			if(so){
				so->write(data, len);
			}

			return so;
		}

		SmallObject * alloc(short len){
			return _alloc(ALIGN_H(len));
		}

		void free(SmallObject * so){
			if(!so){
				return;
			}

			auto ite = mCache.find(so->get_aligned_len());
			if(mCache.end() == ite){
				// invalid so
				throw std::exception("Invalid so!");
			}

			auto group = ite->second;
			group->push_back(so);
		}

	private:
		SmallObject * _alloc(short alignedLen){
			auto ite = mCache.find(alignedLen);
			if(mCache.end() == ite){
				return nullptr;
			}

			auto group = ite->second;
			if(group->size()){
				SmallObject * so = group->back();
				group->pop_back();
				return so;
			}
			else{
				return SmallObject::create(alignedLen);
			}
		}
		
	private:
		short mH, mL;
		std::map<short, std::vector<SmallObject*>*> mCache;
	};
}