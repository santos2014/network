// authored by lizs

#pragma once

#include "allocator_config.h"

namespace Santos{
	
	template<int base=ALIGNMENT_BASE16>
	class AlignPlus{
	public:
		static short align_low(short len){
			if (len < base){
				return base;
			}

			if(0 == len%base){ // already aligned
				return len;
			}

			return (len-len%base);
		}

		static short align_high(short len){
			if (len < base){
				return base;
			}

			if(0 == len%base){ // already aligned
				return len;
			}

			return (len-len%base + base);
		}

		static short step_next(short cur){
			return cur + base;
		}
	};

	template<int base=ALIGNMENT_BASE16>
	class AlignPower2{
	public:
		static short align_low(short len){
			if(len < base)
				return base;
			
			int previous = len;
			while (len = len & (len-1)){
				if(len){
					previous = len;
				}
			}

			return previous;
		}

		static short align_high(short len){
			if(len < base)
				return base;

			if(len & (len-1) == 0){
				return len;
			}
			else{
				return align_low(len) << 1;
			}
		}

		static short step_next(short cur){
			return cur << 1;
		}
	};

#ifdef ALIGNMENT_USE_BASE16
#define ALIGN_H(input) \
	AlignPlus<ALIGNMENT_BASE16>::align_high(input)
#define ALIGN_L(input) \
	AlignPlus<ALIGNMENT_BASE16>::align_low(input)
#define STEP_NEXT(input) \
	AlignPlus<ALIGNMENT_BASE16>::step_next(input)
#endif

#ifdef ALIGNMENT_USE_BASE32
#define ALIGN_H(input) \
	AlignPlus<ALIGNMENT_BASE32>::align_high(input)
#define ALIGN_L(input) \
	AlignPlus<ALIGNMENT_BASE32>::align_low(input)
#define STEP_NEXT(input) \
	AlignPlus<ALIGNMENT_BASE32>::step_next(input)
#endif

#ifdef ALIGNMENT_USE_POWER
#define ALIGN_H(input) \
	AlignPower2<ALIGNMENT_BASE16>::align_high(input)
#define ALIGN_L(input) \
	AlignPower2<ALIGNMENT_BASE16>::align_low(input)
#define STEP_NEXT(input) \
	AlignPower2<ALIGNMENT_BASE16>::step_next(input)
#endif


}