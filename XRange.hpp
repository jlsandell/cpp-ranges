// Filename: XRange.hpp
// Copyright 2013 Mark Edward Sinclair

#ifndef XRANGE_HPP
#define XRANGE_HPP

#include <iterator>

namespace RG {

class XRange
{
public:
	XRange(int begin, int end, unsigned step = 1);

	class iterator : public std::iterator<std::forward_iterator_tag,int> {
	public:
		iterator(int value, int step);

		friend bool operator==(const iterator& lhs, const iterator& rhs);
		friend bool operator!=(const iterator& lhs, const iterator& rhs);

		iterator& operator++();
		iterator operator++(int);

		iterator& operator+=(unsigned);

		int operator*() const;

	private:
		int _value;
		int _step;
	};
	typedef const iterator const_iterator;

	iterator begin();
	const_iterator begin() const;

	iterator end();
	const_iterator end() const;

	int get_begin() const;
	int get_end() const;
	int get_step() const;

private:
	int _begin;
	int _end;
	int _step;
};

}
#endif // XRANGE_HPP
