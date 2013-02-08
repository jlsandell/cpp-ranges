// Filename: XRange.cpp
// Copyright 2013 Mark Edward Sinclair

#include "XRange.hpp"

namespace RG {

XRange::XRange(int begin, int end, unsigned step)
	: _begin(begin)
{
	char direction = begin < end ? 1 : -1;
	_end = (((end - begin)/(int)step) + direction)*(int)step + begin;
	_step = begin < end ? step : -step;
}

bool operator ==(const XRange::iterator& lhs, const XRange::iterator&rhs)
{
	return lhs._step == rhs._step && lhs._value == rhs._value;
}

bool operator!=(const XRange::iterator& lhs, const XRange::iterator& rhs)
{
	return !(lhs == rhs);
}

XRange::iterator::iterator(int value, int step)
	: _value(value),
	  _step(step) {}

XRange::iterator& XRange::iterator::operator ++()
{
	_value += _step;
	return *this;
}

XRange::iterator XRange::iterator::operator ++(int)
{
	iterator copy(*this);
	++(*this);
	return ++copy;
}

XRange::iterator& XRange::iterator::operator +=(unsigned n)
{
	_value += n * _step;
	return (*this);
}

int XRange::iterator::operator *() const
{
	return _value;
}

XRange::iterator XRange::begin() {
	return iterator(_begin,_step);
}

XRange::const_iterator XRange::begin() const {
	return iterator(_begin,_step);
}

XRange::iterator XRange::end()
{
	return iterator(_end,_step);
}

XRange::const_iterator XRange::end() const
{
	return iterator(_end,_step);
}

int XRange::get_begin() const
{
	return _begin;
}

int XRange::get_end() const
{
	return _end;
}

int XRange::get_step() const
{
	return _step;
}

}
