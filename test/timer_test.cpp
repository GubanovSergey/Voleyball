#include <stdio.h>
#include <assert.h>
#include "timer_test.h"

using tests::test_var;

MK_TEST(timer, 0) {
	int pass_cnt = 0;
    Timer t(0.05);
    pass_cnt += test_var (t.get_time(), Timer::timer_t(0.0), NULL);

    ++t;
    auto time = t.get_time();
    pass_cnt += test_var (time, Timer::timer_t(0.0 + 0.05), NULL);
    return test_var (pass_cnt, 2, "Test1: ");
}

MK_TEST(timer, 1) {
    int pass_cnt = 0;
    Timer t(0.01, 1);
    pass_cnt += test_var(t.get_time(), Timer::timer_t(1.0), NULL);

    ++t;
    auto time = t.get_time();
    pass_cnt += test_var (time, Timer::timer_t(1.0 + 0.01), NULL);

    Timer t2 = t;
    pass_cnt += test_var (t2.time_cmp(t) == 0, true, NULL);
    ++t2;
    time = t2.get_time();
    pass_cnt += test_var (time, Timer::timer_t(1.0 + 0.01 + 0.01), NULL);
    pass_cnt += test_var (t.time_cmp(t2) < 0 && t2.time_cmp(t) > 0, true, NULL);
    return test_var(pass_cnt, 5, "Test2: ");
}

MK_TEST(timer, 2) {
	int pass_cnt = 0;
	try {
		Timer t_glob (1E-7, 0);
	}
	catch (std::invalid_argument) {
		pass_cnt += 1;
	}
	return test_var(pass_cnt, 1, "Test3: ");
}
