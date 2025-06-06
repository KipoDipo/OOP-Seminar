#pragma once

#include <stdexcept>

class EmptyGeneratorException : std::exception
{
public:
	EmptyGeneratorException() 
		: std::exception("This generator is exhausted")
	{}
};

template <typename T>
class Generator
{
public:
	virtual ~Generator() = default;

	virtual T operator()() = 0;

	virtual bool reset() = 0;
	virtual bool hasNext() = 0;
	virtual bool hasNext(size_t count) = 0;
};