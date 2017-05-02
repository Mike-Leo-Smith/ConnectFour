//
// Created by Mike Smith on 2017/4/27.
//

#ifndef CONNECT_CLOCK_H
#define CONNECT_CLOCK_H

#include <chrono>

class Clock
{
private:
	std::chrono::high_resolution_clock _clock;
	time_t _start;
	
public:
	Clock(void) { reset(); }
	void reset(void) { _start = std::chrono::duration_cast<std::chrono::milliseconds>(_clock.now().time_since_epoch()).count(); }
	time_t tick(void) const { return std::chrono::duration_cast<std::chrono::milliseconds>(_clock.now().time_since_epoch()).count() - _start; }
};

#endif  // CONNECT_CLOCK_H
