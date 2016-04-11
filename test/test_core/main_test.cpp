#include <stdio.h>
#include <assert.h>
#include "../modules.h"
#include "module_inst_caller.h"

int main (){
	NEW_MODULE(__COUNTER__)
#ifdef INST_TIMER
    timer_test_main();
#endif
	
	if (__COUNTER__ != NUM_MODULES * 2)
		assert(0 == "Not all modules are in work in main_test || module_inst_caller");
    return 0;
}
