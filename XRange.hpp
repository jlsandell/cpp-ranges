// Filename: XRange.hpp
// Copyright 2013 Mark Edward Sinclair

#ifndef XRANGE_HPP
#define XRANGE_HPP

#include <iterator>
#include <stdexcept>

namespace RG {

template<class T = int>
class XRange
{
public:
	XRange(T begin, T end, T step = 1)
		: _begin(begin)
	{
		if (step <= 0) throw(std::invalid_argument("Error, the step must be "
												   "greater than or equal to zero"));

		char direction = begin < end ? 1 : -1;
		_end = (((end - begin)/step) + direction)*step + begin;
		_step = direction * step;
	}

	class iterator : public std::iterator<std::forward_iterator_tag,int> {
	public:
		iterator(T value, T step)
			: _value(value),
			  _step(step) {}

		friend bool operator==(const iterator& lhs, const iterator& rhs)
		{
			return lhs._step == rhs._step && lhs._value == rhs._value;
		}

		friend bool operator!=(const iterator& lhs, const iterator& rhs)
		{
			return !(lhs == rhs);
		}

		iterator& operator++()
		{
			_value += _step;
			return *this;
		}

		iterator operator++(int)
		{
			iterator copy(*this);
			++(*this);
			return copy;
		}

		iterator& operator+=(unsigned n)
		{
			_value += n * _step;
			return (*this);
		}

		T operator*() const
		{
			return _value;
		}

	private:
		T _value;
		T _step;
	};
	typedef const iterator const_iterator;

	iterator begin()
	{
		return iterator(_begin,_step);
	}

	const_iterator begin() const
	{
		return iterator(_begin,_step);
	}

	iterator end()
	{
		return iterator(_end,_step);
	}

	const_iterator end() const
	{
		return iterator(_end,_step);
	}

	T get_begin() const { return _begin;}
	T get_end() const {return _end;}
	T get_step() const {return _step;}

private:
	T _begin;
	T _end;
	T _step;
};

}
#endif // XRANGE_HPP
