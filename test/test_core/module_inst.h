#ifndef MODULE_INST_H
#define MODULE_INST_H

#ifndef MODULE	//TODO make_log
#warning module_inst.h was included while MODULE is not instansiated
#else

#include "../../macro.h"
#include <array>

namespace tests {
	// Structure containing array with funcs
	// Cnt - number of funcs
	// N, S... - for generating number sequences
	template<int Cnt, int N=Cnt,int...S>
	struct MK_CAT_(MODULE, MakeTests, ):MK_CAT_(MODULE, MakeTests, )<Cnt,N-1,N-1,S...>{};

	// When sequence is generated
	// make array with func pointers
	template<int Cnt, int...S>
	struct MK_CAT_(MODULE, MakeTests, )<Cnt,0,S...> {
		static constexpr std::array<TestPtr,Cnt> funcs {
			MK_TEST_NAME(MODULE)<S>...
		};
	};
}

MK_MODULE_TEST(MODULE) {
		int pass_cnt = 0;
		auto funcs = tests::MK_CAT_(MODULE, MakeTests, )<test_num>::funcs;
		for (int i = 0; i < test_num; ++i)
			pass_cnt += funcs[i]();
		return tests::test_var(pass_cnt, std::move(test_num), MK_STRING(MK_CAT_(MODULE, ,tests:)));
}

#undef MODULE
#endif	//MODULE
#endif	//MODULE_INST_H