#pragma once

#include <cstdint>
#include "GeneratorDataSource.h"
#include "DataSourceExcpetions.h"

class FibonacciGenerator : public Generator<uint64_t>
{
public:
	FibonacciGenerator(size_t maxTerms);

	uint64_t operator()() override;

	bool reset() override;
	bool hasNext() override;
	bool hasNext(size_t count) override;

private:
	size_t maxTerms;
	size_t currentIndex;

	uint64_t first;
	uint64_t second;
};
