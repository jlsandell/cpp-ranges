// Filename: Range.hpp
// Copyright 2013 Mark Edward Sinclair

#ifndef RANGE_HPP
#define RANGE_HPP

#include <iterator>
#include <iostream>


namespace RG {

enum Type {
	FORWARD = 0, REVERSE = 1, FORWARD_STEP = 2, REVERSE_STEP = 3
};



template<Type t>
class Iterator : public std::iterator<std::forward_iterator_tag,int> {
};

constexpr Type get_type(int begin, int end, unsigned step) {
	return step > 1 ? (begin < end ? Type::FORWARD_STEP : Type::REVERSE_STEP) : (begin < end ? Type::FORWARD : Type::REVERSE );
}

constexpr int get_end_val(int begin, int end, unsigned step, int direction) {
	return (((end - begin)/(int)step) + direction)*(int)step + begin;

}


template<int B, int E, unsigned S = 1>
class Range
{
	static constexpr const int type_vals[] = {1,-1,1,-1};

	static constexpr const Type type = get_type(B,E,S);

	enum {  direction = type_vals[type], end_val = get_end_val(B,E,S,direction)};

public:

	typedef RG::Iterator<type> iterator;
	typedef const RG::Iterator<type> const_iterator;

	iterator begin() { return iterator(B,S);}

	const_iterator begin()  const { return iterator(B,S);}

	iterator end() {return _end;}
	const_iterator end()  const { return _end;}

private:
	static constexpr iterator _end = iterator(end_val,S);
};

template<>
class Iterator<FORWARD> {
public:
	constexpr Iterator()
		: _val(0) {}

	constexpr Iterator(int value, unsigned step)
		: _val(value) {}


	friend bool operator==(const Iterator& lhs, const Iterator& rhs)
	{
		return lhs._val == rhs._val;
	}

	friend bool operator!=(const Iterator& lhs, const Iterator& rhs)
	{
		return !(lhs == rhs);
	}

	Iterator& operator++()
	{
		++_val;
		return *this;
	}

	Iterator operator++(int)
	{
		Iterator copy(*this);
		++(*this);
		return ++copy;
	}

	int operator*() {
		return _val;
	}

private:
	int _val;
};

template<>
class Iterator<REVERSE> {
public:
	constexpr Iterator()
		: _val(0) {}

	constexpr Iterator(int value, unsigned step)
		: _val(value) {}


	friend bool operator==(const Iterator& lhs, const Iterator& rhs)
	{
		return lhs._val == rhs._val;
	}

	friend bool operator!=(const Iterator& lhs, const Iterator& rhs)
	{
		return !(lhs == rhs);
	}

	Iterator& operator++()
	{
		--_val;
		return *this;
	}

	Iterator operator++(int)
	{
		Iterator copy(*this);
		++(*this);
		return ++copy;
	}

	int operator*() {
		return _val;
	}

private:
	int _val;
};

template<>
class Iterator<FORWARD_STEP> {
public:
	constexpr Iterator()
		: _val(0),
		  _step(0)
	{}

	constexpr Iterator(int value, unsigned step)
		: _val(value),
		  _step(step)
	{}


	friend bool operator==(const Iterator& lhs, const Iterator& rhs)
	{
		return lhs._val == rhs._val && lhs._step == rhs._step;
	}

	friend bool operator!=(const Iterator& lhs, const Iterator& rhs)
	{
		return !(lhs == rhs);
	}

	Iterator& operator++()
	{
		_val += _step;
		return *this;
	}

	Iterator operator++(int)
	{
		Iterator copy(*this);
		++(*this);
		return ++copy;
	}

	int operator*() {
		return _val;
	}

private:
	int _val;
	unsigned _step;
};

template<>
class Iterator<REVERSE_STEP> {
public:
	constexpr Iterator()
		: _val(0),
		  _step(0)
	{}

	constexpr Iterator(int value, unsigned step)
		: _val(value),
		  _step(step)
	{}


	friend bool operator==(const Iterator& lhs, const Iterator& rhs)
	{
		return lhs._val == rhs._val && lhs._step == rhs._step;
	}

	friend bool operator!=(const Iterator& lhs, const Iterator& rhs)
	{
		return !(lhs == rhs);
	}

	Iterator& operator++()
	{
		_val -= _step;
		return *this;
	}

	Iterator operator++(int)
	{
		Iterator copy(*this);
		++(*this);
		return ++copy;
	}

	int operator*() {
		return _val;
	}

private:
	int _val;
	unsigned _step;
};

}

#endif // RANGE_HPP
