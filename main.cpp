// Filename: main.cpp
// Copyright 2013 Mark Edward Sinclair

#include <Range.hpp>
#include <XRange.hpp>
#include <Timer.hpp>

#include <QCoreApplication>

#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::ostream& output = std::cout;

void basic_test_range() {
	using namespace std;
	using RG::Range;

	typedef vector<int> vtype;

	Range<1,10> f;
	//	output << Range<1,10>::type;
	vtype v = {1,2,3,4,5,6,7,8,9,10};
	unsigned idx = 0;
	for (auto i : f) {
		//				output << "Testing " << i << " " << *f.end() << endl;
		assert(v[idx++] == i);
	}
	assert(idx == v.size());
	output << "Forward non-stepped test passed" << endl;

	Range<10,1> r;
	idx = 0;
	vtype rv = {10,9,8,7,6,5,4,3,2,1};
	for (auto i : r) {
		//				output << "Testing " << i  << " " << *r.end()<< endl;
		assert(rv[idx++] == i);
	}
	assert(idx == rv.size());
	output << "Reverse non-stepped test passed" << endl;

	Range<0,20,2> fs;
	idx = 0;
	vtype v_s = {0,2,4,6,8,10,12,14,16,18,20};
	for (auto i : fs) {
		//				output << "Testing " << i << " " << *fs.end()<< endl;
		assert(v_s[idx++] == i);
	}
	assert(idx == v_s.size());
	output << "Forward stepped test passed" << endl;

	Range<30,0,3> rs;
	idx = 0;
	vtype rv_s = {30,27,24,21,18,15,12,9,6,3,0};
	for (auto i : rs) {
		//				output << "Testing " << i << " " << *rs.end()<< endl;
		assert(rv_s[idx++] == i);
	}
	assert(idx == rv_s.size());
	output << "Reverse stepped test passed" << endl;

	Range<0,17,2> fso;
	idx = 0;
	vtype v_so = {0,2,4,6,8,10,12,14,16};
	for (auto i : fso) {
		//		output << "Testing " << i << " " << *fso.end()<< endl;
		assert(v_so[idx++] == i);
	}
	assert(idx == v_so.size());
	output << "Forward stepped odd test passed" << endl;

	Range<17,-2,2> rso;
	idx = 0;
	vtype rv_so = {17,15,13,11,9,7,5,3,1,-1};
	for (auto i : rso) {
		//		output << "Testing " << i << " " << *rso.end()<< endl;
		assert(rv_so[idx++] == i);
	}
	assert(idx == rv_so.size());
	output << "Reverse stepped odd test passed" << endl;
}

template<int begin, int end, unsigned step = 1>
void test_range() {
	using std::endl;

	output << "Testing range [" << begin << "," << end << "] by step " << step << endl;

	Timer<> timer;

	long waste = 0;
	timer.start();
	for (int curr = begin; curr <= end; curr+= step) {
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

	RG::Range<begin,end,step> range;
	timer.start();
	for (int curr : range) {
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

void basic_test_xrange()
{
	using namespace std;
	using RG::XRange;

	typedef vector<int> vtype;

	vtype v = {0,1,2,3,4,5,6,7,8,9,10};
	unsigned idx = 0;
	for (int i : XRange(0,10)) {
		assert(v[idx++] == i);
	}
	assert(idx == v.size());
	output << "Forward non-stepped test passed" << endl;

	v = {10,9,8,7,6,5,4,3,2,1,0};
	idx = 0;
	for (int i : XRange(10,0)) {
		assert(v[idx++] == i);
	}
	assert(idx == v.size());
	output << "Reverse non-stepped test passed" << endl;

	v = {0,2,4,6,8,10,12,14,16,18,20};
	idx = 0;
	for (int i : XRange(0,20,2)) {
		assert(v[idx++] == i);
	}
	assert(idx == v.size());
	output << "Forward stepped test passed" << endl;

	v = {30,27,24,21,18,15,12,9,6,3,0};
	idx = 0;
	for (int i : XRange(30,0,3)) {
		assert(v[idx++] == i);
	}
	assert(idx == v.size());
	output << "Reverse stepped test passed" << endl;

	v = {0,2,4,6,8,10,12,14,16};
	idx = 0;
	for (int i : XRange(0,17,2)) {
		assert(v[idx++] == i);
	}
	assert(idx == v.size());
	output << "Forward stepped odd test passed" << endl;

	v = {17,15,13,11,9,7,5,3,1,-1};
	idx = 0;
	for (int i : XRange(17,-2,2)) {
		assert(v[idx++] == i);
	}
	assert(idx == v.size());
	output << "Reverse stepped odd test passed" << endl;
}

void  test_xrange(int begin, int end, unsigned step)
{
	using std::endl;

	output << "Testing range [" << begin << "," << end << "] by step " << step << endl;

	Timer<> timer;

	long waste = 0;
	timer.start();
	for (int curr = begin; curr <= end; curr+= step) {
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

	RG::XRange range(begin,end,step);
	timer.start();
	for (int curr : range) {
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

	basic_test_range();

//	test_range<1,10000000,2>();
//	test_range<1,100000000,2>();
//	test_range<1,1000000000,2>();

	basic_test_xrange();

	test_xrange(1,10000000,2);
	test_xrange(1,100000000,2);
	test_xrange(1,1000000000,2);

	test_xrange(1,10000000,7);
	test_xrange(1,100000000,7);
	test_xrange(1,1000000000,7);

	output.flush();

	return 0;
}
