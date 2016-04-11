#ifndef TIMER_H

#define TIMER_H
#include <cstdio>
#include <stdexcept>
#include <algorithm>
#include <functional>

class Timer {
public:
	typedef double timer_t;
	int time_cmp (const Timer & rhs);

private:
    static constexpr timer_t PREC_MIN = 1E-6;
	static constexpr timer_t DEF_NUM = 1;

    const timer_t prec_;
    timer_t time_;
    timer_t handle_prec (timer_t prec) {
        if (prec < PREC_MIN) {
			throw std::invalid_argument("Wrong precision got in Timer");
		}
		else
			return prec;
    }

public:
    explicit Timer (timer_t prec = DEF_NUM, timer_t init_val = 0):
		prec_ (handle_prec(prec)),
        time_ (init_val) {}

    void operator ++ () {
        time_ += prec_;
    }

    timer_t get_time () const {
        return time_;
    }
};

#endif //TIMER_H
