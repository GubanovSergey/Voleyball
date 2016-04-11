#ifndef TIMER_TEST_H
#define TIMER_TEST_H

#include "test_core/basics.hpp"
#include "../macro.h"
#include "modules.h"

#ifdef INST_TIMER
#include "../timer.h"
template <int N> tests::Test MK_TEST_NAME(timer) ;
#endif //INST_TIMER

#endif //TIMER_TEST_H
