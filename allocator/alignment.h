// authored by lizs

#pragma once

#include "allocator_config.h"

namespace Santos{

	// align plus is much too slow than power algorithm
	// , specially when input len is larger than 1024

	template<int base=ALIGNMENT_BASE16>
	class AlignPlus{
	public:
		static short align_low(short len){
			if (len < base){
				return base;
			}

			char cnt = 0;
			while (base * ++cnt <= len)
				;

			return base * --cnt;
		}

		static short align_high(short len){
			if (len < base){
				return base;
			}

			char cnt = 0;
			while (base * ++cnt < len)
				;

			return base * cnt;
		}

		static short step_next(short cur){
			return cur + base;
		}
	};

	class AlignPower2{
	public:
		static short align_low(short len){
			char cnt = 0;
			while (len >> ++cnt)
				;

			return 1 << --cnt;
		}

		static short align_high(short len){
			if(1 == len)
				return 1;

			char non_aligned_cnt = (~len&1) ? 0 : 1;
			char cnt = 1;
			while (len = len >> 1){
				++cnt;
				non_aligned_cnt += (~len&1) ? 0 : 1;
			}

			if(non_aligned_cnt > 1){
				return 1 << cnt;
			}

			return len;
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
	AlignPower2::align_high(input)
#define ALIGN_L(input) \
	AlignPower2::align_low(input)
#define STEP_NEXT(input) \
	AlignPower2::step_next(input)
#endif


}