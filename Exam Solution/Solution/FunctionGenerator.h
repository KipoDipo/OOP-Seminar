#pragma once
#include "Generator.h"

template <typename T, typename Func>
class FunctionGenerator : public Generator<T>
{
private:
	Func function;

public:
	FunctionGenerator(const Func& function) : function(function) {}

	T operator()() override { return function(); }

	bool reset() override { return false; }
	bool hasNext() override { return true; }
	bool hasNext(size_t count) override { return true; };
};
