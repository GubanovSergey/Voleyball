#ifndef MODULE_INST_CALLER
#define MODULE_INST_CALLER

#include "basics.hpp"

#define NEW_MODULE1(x)
#define NEW_MODULE(x) NEW_MODULE1(x) 

#define NUM_MODULES 1
NEW_MODULE(__COUNTER__)
#ifdef INST_TIMER
	#undef MODULE_INST_H
	#define test_num 3
	#include "../timer_test.h"
	#define MODULE timer
	#include "module_inst.h"
#endif

#endif	//MODULE_INST_CALLER