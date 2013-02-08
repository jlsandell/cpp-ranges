// Filename: main.cpp
// Copyright 2013 Mark Edward Sinclair

#include <Range.hpp>

#include <QCoreApplication>

#include <cassert>
#include <chrono>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

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

void basic_test() {
	using namespace std;
	using RG::Range;

	typedef vector<int> vtype;

	Range<1,10> f;
	//	cout << Range<1,10>::type;
	vtype v = {1,2,3,4,5,6,7,8,9,10};
	int idx = 0;
	for (auto i : f) {
		//				cout << "Testing " << i << " " << *f.end() << endl;
		assert(v[idx++] == i);
	}
	assert(idx == v.size());
	cout << "Forward non-stepped test passed" << endl;

	Range<10,1> r;
	idx = 0;
	vtype rv = {10,9,8,7,6,5,4,3,2,1};
	for (auto i : r) {
		//				cout << "Testing " << i  << " " << *r.end()<< endl;
		assert(rv[idx++] == i);
	}
	assert(idx == rv.size());
	cout << "Reverse non-stepped test passed" << endl;

	Range<0,20,2> fs;
	idx = 0;
	vtype v_s = {0,2,4,6,8,10,12,14,16,18,20};
	for (auto i : fs) {
		//				cout << "Testing " << i << " " << *fs.end()<< endl;
		assert(v_s[idx++] == i);
	}
	assert(idx == v_s.size());
	cout << "Forward stepped test passed" << endl;

	Range<30,0,3> rs;
	idx = 0;
	vtype rv_s = {30,27,24,21,18,15,12,9,6,3,0};
	for (auto i : rs) {
		//				cout << "Testing " << i << " " << *rs.end()<< endl;
		assert(rv_s[idx++] == i);
	}
	assert(idx == rv_s.size());
	cout << "Reverse stepped test passed" << endl;

	Range<0,17,2> fso;
	idx = 0;
	vtype v_so = {0,2,4,6,8,10,12,14,16};
	for (auto i : fso) {
		//		cout << "Testing " << i << " " << *fso.end()<< endl;
		assert(v_so[idx++] == i);
	}
	assert(idx == v_so.size());
	cout << "Forward stepped odd test passed" << endl;

	Range<17,-2,2> rso;
	idx = 0;
	vtype rv_so = {17,15,13,11,9,7,5,3,1,-1};
	for (auto i : rso) {
		//		cout << "Testing " << i << " " << *rso.end()<< endl;
		assert(rv_so[idx++] == i);
	}
	assert(idx == rv_so.size());
	cout << "Reverse stepped odd test passed" << endl;
}

template<int begin, int end, unsigned step = 1>
void test_range() {
	using std::cout;
	using std::endl;

	cout << "Testing range [" << begin << "," << end << "] by step " << step << endl;

	Timer<> timer;

	long waste = 0;
	timer.start();
	for (int curr = begin; curr <= end; curr+= step) {
		waste += curr;
	}
	timer.stop();
	int normal_time = timer.duration();
	cout << "Normal iteration took " << normal_time << " milliseconds.\n";

	std::string s;
	// Just to make sure that the value of waste is needed later on
	// So it can't be ignored by the compiler or something
	if ((waste & 1) != 0) s = ("Waste is odd");
	else s = ("Waste is even");
	cout << s << " " << waste << endl;

	RG::Range<begin,end,step> range;
	timer.start();
	for (int curr : range) {
		waste += curr;
	}
	timer.stop();
	int range_time = timer.duration();
	cout << "Range iteration took " << range_time << " milliseconds.\n";

	// Just to make sure that the value of waste is needed later on
	// So it can't be ignored by the compiler or something
	if ((waste & 1) != 0) s = ("Waste is odd");
	else s = ("Waste is even");
	cout << s << " " << waste << endl;
}

int main(int argc, char *argv[])
{
	using namespace std;

	basic_test();

	cout << "Beginning performance testing." << endl;
	test_range<1,10>();
	test_range<1,100>();
	test_range<1,1000>();

	test_range<1,10000>();
	test_range<1,100000>();
	test_range<1,1000000>();

	test_range<1,10000000>();
	test_range<1,100000000>();
	test_range<1,1000000000>();

	test_range<1,10000000000>();

	test_range<1,10,3>();
	test_range<1,100,2>();
	test_range<1,1000,2>();

	test_range<1,10000,2>();
	test_range<1,100000,2>();
	test_range<1,1000000,2>();

	test_range<1,10000000,2>();
	test_range<1,100000000,2>();
	test_range<1,1000000000,2>();

	test_range<1,10000000000,2>();

	for (auto x : RG::Range<0,1000,2>()) {
		cout << x << "\t";
	}

	return 0;
}
