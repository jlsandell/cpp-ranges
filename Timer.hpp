// Filename: Timer.hpp
// Copyright 2013 Mark Edward Sinclair

#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>

template <class Unit_t = std::chrono::milliseconds, class Clock_t = std::chrono::system_clock >
class Timer {
public:
	typedef typename std::chrono::time_point<Clock_t> time_type;

	void start() {
		if (_state == State::READY) {
			_start = Clock_t::now();
			_state = State::RUNNING;
		}
	}

	void stop() {
		if (_state == State::RUNNING) {
			_stop = Clock_t::now();
			_state = State::STOPPED;
		}
	}

	int duration() {
		if (_state == State::STOPPED) {
			_state = State::READY;
			int time = std::chrono::duration_cast<Unit_t>(_stop - _start).count();
			return time;
		}
		return -1;
	}

private:

	enum class State { RUNNING, STOPPED, READY};

	time_type _start;
	time_type _stop;
	State _state = State::READY;
};

#endif // TIMER_HPP
