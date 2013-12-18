// authored by lizs

#pragma once
#include <list>
#include <map>
#include "allocator/allocator.h"
#include "delegates/delegate.h"

namespace Santos{

	class Session;
	class Dispatcher{
	public:
		static Dispatcher* instance();

		void dispatch(Session * owner, const NetDelegateContext & ctx);

	private:
		Dispatcher(){}
		~Dispatcher(){};

	private:
		static Dispatcher * mInstance;
		std::map<Session *, std::list<SmallObject*>> mItems;
	};
}