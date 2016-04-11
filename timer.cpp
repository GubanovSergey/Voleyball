#include "timer.h"

int Timer::time_cmp (const Timer & rhs) {
    using std::min;
	int k = (time_ >= rhs.time_) ? 1 : -1;
	
    if ((time_ >= rhs.time_ && (time_ - rhs.time_) < min(prec_, rhs.prec_) / 2) ||
        (time_ < rhs.time_ && (rhs.time_ - time_) < min(prec_, rhs.prec_) / 2))
        return 0;
    else
        return k;
}
