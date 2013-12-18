// authored by lizs

#pragma once
#include "allocator\allocator.h"

namespace Santos{

	struct DelegateContext {
	};

	struct NetDelegateContext : public DelegateContext{
		enum Ops{
			eConn,
			eDisConn,
			eRead,
		};

		Ops ops;
		SmallObject * so;

		NetDelegateContext() : so(nullptr){}
	};

	class Delegate{
	};

	class NetDelegate : public Delegate{
		virtual void network_callback(const NetDelegateContext & ctx) = 0;
	};

}