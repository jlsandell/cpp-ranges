// Filename: main.cpp
// Copyright 2013 Mark Edward Sinclair

//#include "Range.hpp"
#include "XRange.hpp"
#include "Timer.hpp"

#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::ostream& output = std::cout;

template<class T = int>
void basic_test_xrange()
{
	using namespace std;
	using RG::XRange;

	typedef vector<int> vtype;

	vtype v = {0,1,2,3,4,5,6,7,8,9,10};
	unsigned idx = 0;
	for (int i : XRange<T>(0,10)) {
		assert(v[idx++] == i);
	}
	assert(idx == v.size());
	output << "Forward non-stepped test passed" << endl;

	v = {10,9,8,7,6,5,4,3,2,1,0};
	idx = 0;
	for (int i : XRange<T>(10,0)) {
		assert(v[idx++] == i);
	}
	assert(idx == v.size());
	output << "Reverse non-stepped test passed" << endl;

	v = {0,2,4,6,8,10,12,14,16,18,20};
	idx = 0;
	for (int i : XRange<T>(0,20,2)) {
		assert(v[idx++] == i);
	}
	assert(idx == v.size());
	output << "Forward stepped test passed" << endl;

	v = {30,27,24,21,18,15,12,9,6,3,0};
	idx = 0;
	for (int i : XRange<T>(30,0,3)) {
		assert(v[idx++] == i);
	}
	assert(idx == v.size());
	output << "Reverse stepped test passed" << endl;

	v = {0,2,4,6,8,10,12,14,16};
	idx = 0;
	for (int i : XRange<T>(0,17,2)) {
		assert(v[idx++] == i);
	}
	assert(idx == v.size());
	output << "Forward stepped odd test passed" << endl;

	v = {17,15,13,11,9,7,5,3,1,-1};
	idx = 0;
	for (int i : XRange<T>(17,-2,2)) {
		assert(v[idx++] == i);
	}
	assert(idx == v.size());
	output << "Reverse stepped odd test passed" << endl;
}

template<class T>
void  test_xrange(T begin, T end, T step)
{
	using std::endl;

	output << "Testing range [" << begin << "," << end << "] by step " << step << endl;

	Timer<> timer;

	long waste = 0;
	timer.start();
	for (auto curr = begin; curr <= end; curr+= step) {
		waste += curr;
	}
	timer.stop();
	int normal_time = timer.duration();
	output << "Normal iteration took " << normal_time << " milliseconds.\n";

	std::string s;
	// Just to make sure that the value of waste is needed later on
	// So it can't be ignored by the compiler or something
	if ((waste & 1) != 0) s = ("Waste is odd");
	else s = ("Waste is even");
	output << s << " " << waste << endl;

	RG::XRange<T> range(begin,end,step);
	timer.start();
	for (auto curr : range) {
		waste += curr;
	}
	timer.stop();
	int range_time = timer.duration();
	output << "Range iteration took " << range_time << " milliseconds.\n";

	// Just to make sure that the value of waste is needed later on
	// So it can't be ignored by the compiler or something
	if ((waste & 1) != 0) s = ("Waste is odd");
	else s = ("Waste is even");
	output << s << " " << waste << endl;
}



int main(int argc, char *argv[])
{
	using namespace std;


	basic_test_xrange();

	test_xrange(1,10000000,2);
	test_xrange(1,100000000,2);
	test_xrange(1,1000000000,2);

	test_xrange(1,10000000,7);
	test_xrange(1,100000000,7);
	test_xrange(1,1000000000,7);

	test_xrange<float>(1,1020034.33,2.5);

	output.flush();

	return 0;
}
